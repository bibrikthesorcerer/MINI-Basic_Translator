#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "lex_block.h"


void Lex_block_mb::init_beg_vect()
{
   m_beg_vector['e'] = 1;
   m_beg_vector['f'] = 3;
   m_beg_vector['g'] = 5;
   m_beg_vector['i'] = 11;
   m_beg_vector['l'] = 12;
   m_beg_vector['n'] = 14;
   m_beg_vector['r'] = 17;
   m_beg_vector['s'] = 23;
   m_beg_vector['t'] = 26;
}                  

void Lex_block_mb::init_detect_table()
{
   m_detect_table = std::vector<std::tuple<char, int, funct_ptr>>(26);
   m_detect_table[ 0] = std::tuple<char, int, funct_ptr>('n', 0, B1d);
   m_detect_table[ 1] = std::tuple<char, int, funct_ptr>('d', 0, A2q);
   m_detect_table[ 2] = std::tuple<char, int, funct_ptr>('o', 0, B1d);
   m_detect_table[ 3] = std::tuple<char, int, funct_ptr>('r', 0, F1b);
   m_detect_table[ 4] = std::tuple<char, int, funct_ptr>('o', 0, B1d);
   m_detect_table[ 5] = std::tuple<char, int, funct_ptr>('t', 7, B1d);
   m_detect_table[ 6] = std::tuple<char, int, funct_ptr>('o', 0, E1a);
   m_detect_table[ 7] = std::tuple<char, int, funct_ptr>('s', 0, B1d);
   m_detect_table[ 8] = std::tuple<char, int, funct_ptr>('u', 0, B1d);
   m_detect_table[ 9] = std::tuple<char, int, funct_ptr>('b', 0, E1b);
   m_detect_table[10] = std::tuple<char, int, funct_ptr>('f', 0, A2r);
   m_detect_table[11] = std::tuple<char, int, funct_ptr>('e', 0, B1d);
   m_detect_table[12] = std::tuple<char, int, funct_ptr>('t', 0, F1a);
   m_detect_table[13] = std::tuple<char, int, funct_ptr>('e', 0, B1d);
   m_detect_table[14] = std::tuple<char, int, funct_ptr>('x', 0, B1d);
   m_detect_table[15] = std::tuple<char, int, funct_ptr>('t', 0, C1a);
   m_detect_table[16] = std::tuple<char, int, funct_ptr>('e', 0, B1d);
   m_detect_table[17] = std::tuple<char, int, funct_ptr>('t', 21,B1d);
   m_detect_table[18] = std::tuple<char, int, funct_ptr>('u', 0, B1d);
   m_detect_table[19] = std::tuple<char, int, funct_ptr>('r', 0, B1d);
   m_detect_table[20] = std::tuple<char, int, funct_ptr>('n', 0, A2s);
   m_detect_table[21] = std::tuple<char, int, funct_ptr>('m', 0, G1a);
   m_detect_table[22] = std::tuple<char, int, funct_ptr>('t', 0, B1d);
   m_detect_table[23] = std::tuple<char, int, funct_ptr>('e', 0, B1d);
   m_detect_table[24] = std::tuple<char, int, funct_ptr>('p', 0, A2t);
   m_detect_table[25] = std::tuple<char, int, funct_ptr>('o', 0, A2u);
}

void Lex_block_mb::fill_lexems()
{
   m_collect_of_lex["lex_line"]        = 0;
   m_collect_of_lex["lex_operand"]     = 1;
   m_collect_of_lex["lex_aur_oper"]    = 2;
   m_collect_of_lex["lex_relation"]    = 3;
   m_collect_of_lex["lex_next"]        = 4;
   m_collect_of_lex["lex_let"]         = 5;
   m_collect_of_lex["lex_for"]         = 6;
   m_collect_of_lex["lex_goto"]        = 7;
   m_collect_of_lex["lex_gosub"]       = 8;
   m_collect_of_lex["lex_op_brace"]    = 9;
   m_collect_of_lex["lex_cls_brace"]   = 10;
   m_collect_of_lex["lex_if"]          = 11;
   m_collect_of_lex["lex_return"]      = 12;
   m_collect_of_lex["lex_end"]         = 13;
   m_collect_of_lex["lex_to"]          = 14;
   m_collect_of_lex["lex_step"]        = 15;
   m_collect_of_lex["lex_rem"]         = 16;
   m_collect_of_lex["lex_error"]       = 17;
   m_collect_of_lex["lex_eof"]         = 18;

}

void Lex_block_mb::fill_symbol_lexems()
{
   m_sym_lex_collection["sl_digit"]       = 0;
   m_sym_lex_collection["sl_letter"]      = 1;
   m_sym_lex_collection["sl_aur_op"]      = 2;
   m_sym_lex_collection["sl_relat"]       = 3;
   m_sym_lex_collection["sl_space"]       = 4;
   m_sym_lex_collection["sl_lf"]          = 5;
   m_sym_lex_collection["sl_eof"]         = 6;
   m_sym_lex_collection["sl_op_brace"]    = 7;
   m_sym_lex_collection["sl_cls_brace"]   = 8;
   m_sym_lex_collection["sl_dot"]         = 9;
   m_sym_lex_collection["sl_error"]       = 10;
}

void Lex_block_mb::add_constant()
{
   std::string const_id = std::to_string(m_reg_number);
   try
   {
      m_name_table.at(const_id);
   }
   catch (std::out_of_range err)
   {
      m_name_table.insert(std::pair<std::string, double>(const_id, m_reg_number));
   }
   m_reg_nt_pointer = reinterpret_cast<long long int>(&m_name_table[const_id]);

}

Lex_block_mb::Lex_block_mb(std::string filename)
{
   m_file = std::fstream(filename);
   if (!m_file)
   {
      std::cout << "Couldn't open file " << filename << std::endl;
   }
   init_beg_vect();
   init_detect_table();
   fill_lexems();
   fill_symbol_lexems();
   init_func_table();
}

void Lex_block_mb::parse()
{
   while (m_curr_state.m_id != "s_STOP")
   {
      m_curr_sym = transliterator(m_file.get());

      m_curr_state = (*m_func_table[m_curr_state][m_curr_sym.s_class])();
   }

}

void Lex_block_mb::add_variable()
{
   try
   {
      m_name_table.at(m_reg_var_name);
   }
   catch (std::out_of_range err)
   {
      m_name_table.insert(std::pair<std::string, double>(m_reg_var_name, m_reg_number));
   }
   m_reg_nt_pointer = reinterpret_cast<long long int>(&m_name_table[m_reg_var_name]);

}

det_analizer::inp_symbol Lex_block_mb::transliterator(int sym)
{
   det_analizer::inp_symbol symbol;
   symbol.s_value = 0;
   if (isdigit(sym))
   {
      symbol.s_class = "sl_digit";
      symbol.s_value = sym - '0';
   }
   else if ((sym > 64 && sym < 91) || (sym > 96 && sym < 123))
   {
      symbol.s_class = "sl_letter";
      symbol.s_value = sym;
   }
   else if (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '%')
   {
      symbol.s_class = "sl_aur_op";
      symbol.s_value = sym;
   }
   else if (sym == '=' || sym == '!' || sym == '<' || sym == '>')
   {
      symbol.s_class = "sl_relat";
      symbol.s_value = sym;

   }
   else if (sym == ' ' || sym == '\t')
   {
      symbol.s_class = "sl_space";
   }
   else if (sym == '\n' || sym == '\r\n')
   {
      symbol.s_class = "sl_lf";
   }
   else if (sym == EOF)
   {
      symbol.s_class = "sl_eof";
   }
   else if (sym == '(')
   {
      symbol.s_class = "sl_op_brace";
      symbol.s_value = sym;
   }
   else if (sym == ')')
   {
      symbol.s_class = "sl_cls_brace";
      symbol.s_value = sym;
   }
   else if (sym == '.')
   {
      symbol.s_class = "sl_dot";
      symbol.s_value = sym;
   }
   else
   {
      symbol.s_class = "sl_error";
   }
   return symbol;
}

