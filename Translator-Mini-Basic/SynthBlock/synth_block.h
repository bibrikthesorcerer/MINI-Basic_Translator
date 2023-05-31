#pragma once
#include"../SynthBlock/CF_grammar.h"
#include "../LexBlock/lex_block.h"
#include <stack>
#include <QTextStream>
#include <QString>

struct ATOM_BASIC {
	enum ATOM_TYPE { LET, IF_GOTO, FOR_STEP, FOR, LINE, GOTO, GOSUB, RETURN, END, REM, NEXT } type;
	std::list<long long int> atributs;

	ATOM_BASIC& operator=(const ATOM_BASIC& obj)
	{
		type = obj.type;
		atributs = obj.atributs;
		return *this;
	}
	ATOM_BASIC(){}
	ATOM_BASIC(const ATOM_BASIC& obj)
	{
		*this = obj;
	}
};

class BF_grammar : public CF_grammar
{
	std::shared_ptr<Symbol> Dollar;
	enum BF_RELATION { More, Less, Equal, None, MORE_LESS, MORE_EQ, LESS_EQ };
	std::map<Symbol, std::map<Symbol, BF_RELATION>> m_BF_table;
	std::set<Grammar_rule> m_sorted_by_right_part;
	std::list<std::shared_ptr<Symbol>> m_in_word;
	std::map<std::string, Determ_analizer::Lexem> m_lexems;
	std::map<size_t, ATOM_BASIC> m_atom_output;
    bool m_errorFlag = false;
    QTextStream* m_output;
public:
    QString m_outputStr;

public:
	BF_grammar(const std::string filename, std::list<std::tuple<Determ_analizer::Lexem, long long int, size_t>> lexem_list = std::list<std::tuple<Determ_analizer::Lexem, long long int, size_t>>()) : CF_grammar(filename)
	{
        m_output = new QTextStream(&m_outputStr);
		sort_by_right_part();
		Dollar = std::make_shared<Symbol>();
		Dollar->m_id = -1;
		Dollar->m_name = "$";
		create_BF_table();
		fill_symbol_list(lexem_list);
	}
	void synth_analize();
	void print_BF_table();
	void print_sorted_rules();
	void fill_symbol_list(std::list<std::tuple<Determ_analizer::Lexem, long long int, size_t>>);
	std::map<size_t, ATOM_BASIC> get_atoms()
	{
		return m_atom_output;
	}
	bool get_errorFlag()
	{
		return m_errorFlag;
	}
private:
	bool EQUAL(std::shared_ptr<Symbol> A, std::shared_ptr<Symbol> B);
	bool MORE(std::shared_ptr<Symbol> A, std::shared_ptr<Symbol> B);
	bool LESS(std::shared_ptr<Symbol> A, std::shared_ptr<Symbol> B);

	BF_RELATION check_relation(std::shared_ptr<Symbol> A, std::shared_ptr<Symbol> B);
	void create_BF_table();
	std::shared_ptr<Symbol> process_wrap(Grammar_rule&);
	void sort_by_right_part();

};
