#pragma once
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <stack>
#include <iostream>
#include <fstream>
#include <set>
#include <string>

class SynthSymbol
{
public:
    std::string m_name;
    size_t      m_id;

    SynthSymbol();

    SynthSymbol(const SynthSymbol& obj);

    SynthSymbol(size_t id, std::string name);

    SynthSymbol& operator=(const SynthSymbol& obj);

    friend bool operator<(const SynthSymbol& obj, const SynthSymbol& obj1);

    friend bool operator==(const SynthSymbol& obj, const SynthSymbol& obj1);


};

class Terminal : public SynthSymbol
{
public:
    Terminal();

    Terminal(const Terminal& obj);

    Terminal(size_t id, std::string name);

    Terminal& operator=(const Terminal& obj);

    friend bool operator<(const Terminal& obj, const Terminal& obj1);

    friend bool operator==(const Terminal& obj, const Terminal& obj1);
};

class NonTerminal : public SynthSymbol
{
public:
    NonTerminal();
    NonTerminal(const NonTerminal& nonTerminal);
    NonTerminal(std::string name, size_t id);

    NonTerminal& operator=(const NonTerm& obj); // Разве здесь не NonTerminal нужен?

    friend bool operator==(const NonTerminal& obj1, const NonTerminal& obj2);
    friend bool operator<(const NonTerminal& obj1, const NonTerminal& obj2);
};

//Класс, отвечающий за грамматику для синтаксического блока
class Grammar
{
	std::map<std::string, int> m_setOfRules; // Изменить пару на другие типы
	std::map<std::string, size_t> m_collectOfNonTerm;
	std::map<std::string, size_t> m_collectOfTerm;

public:

	//Класс, отвечающий за правила в грамматике
	class Rule
	{
        SynthSymbol m_leftPart; // Возможно изменить на NonTerminal
		std::vector<SynthSymbol*> m_rightPart;

	public:
        //Конструктор класс Rule без пераметров
        Rule();

        /*
        *@brief Конструктор копирования класс Rule
        *@param Объект класса Rule
        */
        Rule(const Rule& obj);
	};

    /*
    *@brief Конструктор класс Grammar с пераметрами
    *@param Имя файла
    */
    Grammar(const std::string filename);

    friend std::ostream& operator <<(std::ostream& out, const Grammar& obj);
};