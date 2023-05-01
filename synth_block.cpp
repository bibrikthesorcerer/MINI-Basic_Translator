#include "synth_block.h"

bool operator<(const SynthSymbol& obj, const SynthSymbol& obj1)
{
    return obj.m_id < obj1.m_id;
}

bool operator==(const SynthSymbol& obj, const SynthSymbol& obj1)
{
    return obj.m_id == obj1.m_id;
}

SynthSymbol::SynthSymbol()
{
    m_name = "";
    m_id = -1;
}

SynthSymbol::SynthSymbol(const SynthSymbol& obj)
{
    m_id = obj.m_id;
    m_name = obj.m_name;
}

SynthSymbol::SynthSymbol(size_t id, std::string name)
{
    m_id = id;
    m_name = name;
}

SynthSymbol& SynthSymbol::operator=(const SynthSymbol& obj)
{
    m_id = obj.m_id;
    m_name = obj.m_name;
    return *this;
}

bool operator<(const Terminal& obj, const Terminal& obj1)
{
    return obj.m_id < obj1.m_id;
}

bool operator==(const Terminal& obj, const Terminal& obj1)
{
    return obj.m_id == obj1.m_id;
}

Terminal::Terminal()
{
    m_name = "";
    m_id = -1;
}

Terminal::Terminal(const Terminal& obj)
{
    m_id = obj.m_id;
    m_name = obj.m_name;
}

Terminal::Terminal(size_t id, std::string name)
{
    m_id = id;
    m_name = name;
}

Terminal& Terminal::operator=(const Terminal& obj)
{
    m_id = obj.m_id;
    m_name = obj.m_name;
    return *this;
}

// NonTerminal class
NonTerminal::NonTerminal()
{
    m_name = "";
    m_id = -1;
}
NonTerminal::NonTerminal(const NonTerminal& nonTerminal)
{
    m_id = nonTerminal.m_id;
    m_name = nonTerminal.m_name;
}
NonTerminal::NonTerminal(std::string name, size_t id)
{
    m_name = name;
    m_id = id;
}
NonTerminal& NonTerminal::operator=(const NonTerminal& obj)
{
    m_name = obj.m_name;
    m_id = obj.m_id;
    return *this;
}

bool operator==(const NonTerminal& obj1, const NonTerminal& obj2)
{
    return obj1.m_id == obj2.m_id;
}
bool operator<(const NonTerminal& obj1, const NonTerminal& obj2)
{
    return obj1.m_id < obj2.m_id;
}

Grammar::Grammar(const std::string filename)
{
    std::ifstream in(filename);
    if (!in)
    {
        std::cout << "Error. Failed to open file." << std::endl;
        return;
    }
    std::string partOfFile;                 // Прочитанная часть файла
    size_t key = 0;     // Неправильно задается ключ
    size_t flagFirstNonTerminal = 0;        // Флаг, указывающий на то, что был прочитан первый нетерминал в строке
    std::vector<SynthSymbol*> rightPartRule;// Вектор, который содержит указатели на симловы (терминалы или нетерминалы) из файла
    NonTerminal firstNonTerminal;           // Первый нетерминал в строке

    while (!in.eof())
    {
        in >> partOfFile;
        if (partOfFile.front() == '{' && partOfFile.back() == '}')
        {
            std::pair<std::string, size_t> field(partOfFile, key);
            m_collectOfNonTerm.insert(field);
            if (flagFirstNonTerminal == 0)
            {
                NonTerminal forCopy(partOfFile, key); // Переменная, созданная ради копирования в firstNonTerminal
                firstNonTerminal = forCopy;
                flagFirstNonTerminal = 1;
                continue;
            }
        }
        else
        {
            if (partOfFile == "~")
                continue;

            std::pair<std::string, size_t> field(partOfFile, key);
            m_collectOfTerm.insert(field);
        }
        if (flagFirstNonTerminal == 1)
        {
            SynthSymbol* rightSymRule; // Ссылка на символ (терминал или нетерминал) в правой части правила
            rightSymRule = new SynthSymbol(key, partOfFile);
            rightPartRule.push_back(rightSymRule);
        }
        if (in.peek() == '\n' || in.peek() == EOF)
        {
            Rule theRules_(firstNonTerminal, rightPartRule); // Правило, для списка правил (т.е для m_setOfRules)
            std::pair<NonTerminal, Rule> field(firstNonTerminal, theRules_);
            m_setOfRules.insert(field);
            rightPartRule.clear();
            flagFirstNonTerminal = 0;
        }
        key++; // Неправильно задается ключ
    }

    in.close();
}

std::ostream& operator <<(std::ostream& out, const Grammar& obj)
{
    for (auto i : obj.m_collectOfNonTerm)
        out << "NonTerm - " << i.first << std::endl;
    for (auto i : obj.m_collectOfTerm)
        out << "Term - " << i.first << std::endl;
    for (auto i : obj.m_setOfRules)
    {
        out << i.first.m_name << " ~ ";
        for (auto j : i.second.m_rightPart)
            out << j->m_name << " "; 
        out << std::endl;
    }

    return out;
}

Grammar::Rule::Rule()
{
    m_leftPart = NonTerminal();
    m_rightPart = std::vector<SynthSymbol*>();
}

Grammar::Rule::Rule(const Rule& obj)
{
    m_leftPart = obj.m_leftPart;
    m_rightPart = obj.m_rightPart;
}

Grammar::Rule::Rule(NonTerminal leftPart_, std::vector<SynthSymbol*> rightPart_)
{
    m_leftPart = leftPart_;
    for (auto i : rightPart_)
        m_rightPart.push_back(i);
}

/*
Grammar::Rule::~Rule()
{
    delete &m_leftPart;
    for (auto i : m_rightPart)
        delete i;
}
*/

void Grammar::Rule::push_back(SynthSymbol* newSynthSymbol)
{
    m_rightPart.push_back(newSynthSymbol);
}

Grammar::Rule& Grammar::Rule::operator=(const Rule& obj)
{
    if (*this == obj)
        return *this;

    m_leftPart = obj.m_leftPart;
    m_rightPart.clear();

    for (auto i : obj.m_rightPart)
        m_rightPart.push_back(i);

    return *this;
}

bool operator ==(const Grammar::Rule& obj_1, const Grammar::Rule& obj_2)
{
    if (!(obj_1.m_leftPart == obj_2.m_leftPart))
        return 0;
    else if (obj_1.m_rightPart != obj_2.m_rightPart)
        return 0;
    else
        return 1;
}