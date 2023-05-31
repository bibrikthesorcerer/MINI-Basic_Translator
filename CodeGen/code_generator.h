#pragma once
#include "../SynthBlock/synth_block.h"
#include "../LexBlock/lex_block.h"

class Code_generator
{
	std::map<size_t, ATOM_BASIC> m_atom_sequence;
	std::map<std::string, Determ_analizer::variable> m_operands;
public:
	Code_generator(std::map<std::string, Determ_analizer::variable> name_table, std::map<size_t, ATOM_BASIC> atoms) : m_atom_sequence(atoms), m_operands(name_table) {	}
	~Code_generator(){	}
	void Generate(std::string filename = "output.txt");
private:
	void translate_expression(std::ofstream& out_file, std::list<long long int> atributes);
};
