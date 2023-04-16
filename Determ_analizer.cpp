#include "Determ_analizer.h"
#include <iostream>

bool operator<(const Determ_analizer::Symbol_lexem& obj1, const Determ_analizer::Symbol_lexem& obj2)
{
   return obj1.m_id < obj2.m_id;
}

bool operator<(const Determ_analizer::Lexem& obj1, const Determ_analizer::Lexem& obj2)
{
   return obj1.m_id < obj2.m_id;
}

Determ_analizer::Symbol_lexem::Symbol_lexem(const char* str, size_t id)
{
   m_name = str;
   m_id = id;
}

Determ_analizer::Symbol_lexem::Symbol_lexem(const Symbol_lexem& obj)
{
   *this = obj;
}

Determ_analizer::Symbol_lexem& Determ_analizer::Symbol_lexem::operator=(const Symbol_lexem& obj)
{
   m_name = obj.m_name;
   m_id = obj.m_id;
   return *this;
}

Determ_analizer::Lexem::Lexem(std::string str, size_t id)
{
   m_name = str;
   m_id = id;
}

Determ_analizer::Lexem& Determ_analizer::Lexem::operator=(const char* str)
{
   m_name = str; 
   return *this;
}