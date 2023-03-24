#include "det_automa.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>

inp_symbol det_automa::transliterator(int sym)
{
   return inp_symbol();
}

void det_automa::copy_det_automa(const det_automa& obj)
{
   m_state_num = obj.m_trans_table.capacity();
   m_sym_num = obj.m_trans_table[0].capacity();
   m_curr_state = obj.m_curr_state;
   m_filename = obj.m_filename;
   m_file = std::fstream(obj.m_filename);
   if (!m_file)
   {
      std::cout << "couldn't open file " << m_filename << std::endl;
      return;
   }

   m_curr_sym = transliterator(m_file.get());
   m_trans_table = obj.m_trans_table;
   m_finite_states= obj.m_finite_states;
}

det_automa::det_automa(const state start_state, const std::vector<std::vector<state>> trans_table, const std::vector<state> finite_states, const std::string filename)
{
   m_state_num  = trans_table.capacity();
   m_sym_num    = trans_table[0].capacity();
   m_curr_state = start_state;
   m_filename = filename;
   m_file = std::fstream(m_filename);
   if (!m_file)
   {
      std::cout << "couldn't open file " << filename << std::endl;
      return;
   }

   m_curr_sym = transliterator(m_file.get());
   m_trans_table = trans_table;
   m_finite_states = finite_states;
}

det_automa::det_automa()
{
   m_state_num = 0;
   m_sym_num = 0;
   m_curr_state;
   m_curr_sym;
   m_trans_table;
   m_finite_states;              
   m_file;                             
   m_filename;
}

det_automa::det_automa(const det_automa& obj)
{
   copy_det_automa(obj);
}

det_automa& det_automa::operator=(const det_automa& obj)
{
   copy_det_automa(obj);
   return *this;
}

void det_automa::parse()
{
   bool flag = 1;
   while (flag)
   {
      m_curr_state = m_trans_table[(int)m_curr_state][(int)m_curr_sym.s_class];
      if (m_file.peek() == EOF)
         flag = 0;
      else
         m_curr_sym = transliterator(m_file.get()); //взяли новый символ
   }

   if (m_file.eof())
   {
      m_file.clear();
   }

   std::vector<state>::iterator iter = find(m_finite_states.begin(), m_finite_states.end(), m_curr_state);
   if (iter != m_finite_states.end())
      m_file << "\ncorrect word";
   else
      m_file << "\nincorrect word";
}
