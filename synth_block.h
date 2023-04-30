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

    NonTerminal& operator=(const NonTerminal& obj);

    friend bool operator==(const NonTerminal& obj1, const NonTerminal& obj2);
    friend bool operator<(const NonTerminal& obj1, const NonTerminal& obj2);
};

//Класс, отвечающий за грамматику для синтаксического блока
class Grammar
{
public:

    //Класс, отвечающий за правила в грамматике
    class Rule
    {
    public:
        NonTerminal m_leftPart;
        std::vector<SynthSymbol*> m_rightPart;

        //Конструктор по умолчанию класса Rule
        Rule();

        /*
        *@brief Конструктор копирования класса Rule
        *@param Объект класса Rule
        */
        Rule(const Rule& obj);

        /*
        *@brief Конструктор с параметрами класса Rule
        *@param Нетерминал, отвечающий за левую часть правила
        *@param Вектор указателей на SynthSymbol, отвечающий за правую часть правила
        */
        Rule(NonTerminal leftPart_, std::vector<SynthSymbol*> rightPart_);

        //Деструктор класса Rule
//        ~Rule(); - неправильная реализация

        /*
        *@brief Функция, которая добавляет в конец правой части новый синтаксический символ
        *@param Указатель на элемент типа SynthSymbol
        */
        void push_back(SynthSymbol* newSynthSymbol);
    };

    std::multimap<NonTerminal, Rule> m_setOfRules; // Здесь нужен NonTerminal или все же SyntSymbol
    std::map<std::string, size_t> m_collectOfNonTerm;
    std::map<std::string, size_t> m_collectOfTerm;

    /*
    *@brief Конструктор класс Grammar с пераметрами
    *@param Имя файла
    */
    Grammar(const std::string filename);

    friend std::ostream& operator <<(std::ostream& out, const Grammar& obj);
};