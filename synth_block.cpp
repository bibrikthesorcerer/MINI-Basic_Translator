#include "synth_block.h"
friend bool SynthSymbol::operator<(const SynthSymbol& obj, const SynthSymbol& obj1)
{
    return obj.m_id < obj1.m_id;
}
friend bool SynthSymbol::operator==(const SynthSymbol& obj, const SynthSymbol& obj1)
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

friend bool Terminal::operator<(const Terminal& obj, const Terminal& obj1)
{
    return obj.m_id < obj1.m_id;
}

friend bool Terminal::operator==(const Terminal& obj, const Terminal& obj1)
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

Grammar::Grammar(const std::string filename)
{
    std::ifstream in(filename);
    if (!in)
    {
        std::cout << "Error. Failed to open file." << std::endl;
        return;
    }
    std::string partOfFile; //Прочитанная часть файла
    size_t key = 0; // Неправильно задается ключ

    while (!in.eof())
    {
        std::getline(in, partOfFile, ' ');
        if (partOfFile.front() == '{' && partOfFile.back() == '}')
        {
            std::pair<std::string, size_t> field = make_pair(partOfFile, key);
            m_collectOfNonTerm.insert(field);
            key++; // Неправильно задается ключ
        }
        else // Некоторые нетерминалы все же проходят
        {
            if (partOfFile == "~")
                continue;

            std::pair<std::string, size_t> field = make_pair(partOfFile, key);
            m_collectOfTerm.insert(field);
            key++;
        }
    }

    in.close();
}

std::ostream& operator <<(std::ostream& out, const Grammar& obj)
{
    for (auto i : obj.m_collectOfNonTerm)
        out << "NonTerm -" << i.first << std::endl;
    for (auto i : obj.m_collectOfTerm)
        out << "Term -" << i.first << std::endl;

    return out;
}