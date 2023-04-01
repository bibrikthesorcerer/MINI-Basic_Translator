#include "Determ_analizer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>


bool operator<(const State& obj1, const State& obj2)
{
   return obj1.m_id < obj2.m_id;
}

bool operator<(const Determ_analizer::Symbol_lexem& obj1, const Determ_analizer::Symbol_lexem& obj2)
{
   return obj1.m_id < obj2.m_id;
}

bool operator<(const Determ_analizer::Lexem& obj1, const Determ_analizer::Lexem& obj2)
{
   return obj1.m_id < obj2.m_id;
}

State::State()
{
   m_name = "";
   m_id = -1;
}

State::State(std::string name, size_t id)
{
   m_name = name;
   m_id = id;
}

State& State::operator=(const State& obj)
{
   m_name = obj.m_name;
   m_id = obj.m_id;
   return *this;
}

bool State::operator==(const State& obj)
{
   return m_name == obj.m_name && m_id == obj.m_id;
}
