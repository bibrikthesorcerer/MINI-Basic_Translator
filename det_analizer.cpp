#include "det_analizer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

//void det_analizer::parse()
//{
//
//    while (!m_file.eof())
//    {
//       m_curr_sym = transliterator(m_file.get());
//       m_curr_state = (*m_func_table[m_curr_state][m_curr_sym.s_class])();
//    }
//
//   m_file.close();
//
//}

bool operator<(const State& obj1, const State& obj2)
{
   return obj1.m_name == obj2.m_name && obj1.m_id < obj2.m_id;
}

bool operator<(const symbol_lexem& obj1, const symbol_lexem& obj2)
{
   return obj1.m_name == obj2.m_name && obj1.m_id < obj2.m_id;
}

bool operator<(const Lexem& obj1, const Lexem& obj2)
{
   return obj1.m_name == obj2.m_name && obj1.m_id < obj2.m_id;
}
