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


// NonTerminal class
NonTerminal::NonTerminal()
{
    m_name = "";
    m_id = -1;
}
NonTerminal::NonTerminal(const NonTerminal& nonTerminal)
{
    m_id = obj.m_id;
    m_name = obj.m_name;
}
NonTerminal::NonTerminal(std::string name, size_t id);
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

friend bool Terminal::operator==(const Terminal& obj1, const Terminal& obj2)
{
    return obj1.m_id == obj2.m_id;
}
friend bool Terminal::operator<(const Terminal& obj1, const Terminal& obj2)
{
    return obj1.m_id < obj2.m_id;
}
