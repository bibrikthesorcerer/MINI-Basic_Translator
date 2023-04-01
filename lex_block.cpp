// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <tuple>
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
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('c', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('n', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('d', 0, &Lex_block_mb::A2q));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('o', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('r', 0, &Lex_block_mb::F1b));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('o', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('t', 7, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('o', 0, &Lex_block_mb::E1a));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('s', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('u', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('b', 0, &Lex_block_mb::E1b));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('f', 0, &Lex_block_mb::A2r));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('e', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('t', 0, &Lex_block_mb::F1a));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('e', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('x', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('t', 0, &Lex_block_mb::C1a));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('e', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('t', 21,&Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('u', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('r', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('n', 0, &Lex_block_mb::A2s));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('m', 0, &Lex_block_mb::G1a));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('t', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('e', 0, &Lex_block_mb::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('p', 0, &Lex_block_mb::A2t));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('o', 0, &Lex_block_mb::A2u));
}

void Lex_block_mb::init_states()
{
   m_collect_of_states[  "A1"] = State("A1", 0);
   m_collect_of_states[  "A2"] = State("A2", 1);
   m_collect_of_states[  "A3"] = State("A3", 2);
   m_collect_of_states[  "B1"] = State("B1", 3);
   m_collect_of_states[  "C1"] = State("C1", 4);
   m_collect_of_states[  "C2"] = State("C2", 5);
   m_collect_of_states[  "D1"] = State("D1", 6);
   m_collect_of_states[  "D2"] = State("D2", 7);
   m_collect_of_states[  "D3"] = State("D3", 8);
   m_collect_of_states[  "D4"] = State("D4", 9);
   m_collect_of_states[  "D5"] = State("D5", 10);
   m_collect_of_states[  "D6"] = State("D6", 11);
   m_collect_of_states[  "E1"] = State("E1", 12);
   m_collect_of_states[  "E2"] = State("E2", 13);
   m_collect_of_states[  "F1"] = State("F1", 14);
   m_collect_of_states[  "F2"] = State("F2", 15);
   m_collect_of_states[  "F3"] = State("F3", 16);
   m_collect_of_states[  "G1"] = State("G1", 17);
   m_collect_of_states[  "H1"] = State("H1", 18);
   m_collect_of_states["STOP"] = State("STOP", 19);
}

void Lex_block_mb::init_func_table()
{
}

State Lex_block::F1a()
{
    m_reg_class = m_collection_of_Lex["lex_let"];
    return e_F1();
}
State Lex_block::F1b()
{
    m_reg_class = m_collection_of_Lex["lex_for"];
    return e_F1();
}

State Lex_block::F2a()
{
    m_reg_var_name = static_cast<char>(m_curr_sym.s_value);
    return e_F2();
}
State Lex_block::F3a()
{
    m_reg_var_name += m_curr_sym.s_value + '0';
    return e_F3();
}

State Lex_block::M1()
{
    if (m_reg_detection == 0)
        return Error1();
    if (m_curr_sym.s_value == std::get<0>(m_detect_table[m_reg_detection]))
    {
        return (this->*std::get<2>(m_detect_table[m_reg_detection]))();
    }
    else
    {
        m_reg_detection = std::get<1>(m_detect_table[m_reg_detection]);
        if (m_reg_detection == 0)
            return Error1();
        return M1();
    }

}

State Lex_block::M2()
{
    if (m_curr_sym.s_value != 'e')
    {
        DA1D();
        return B1b();
    }
    else
    {
        return D3a();
    }
}

State Lex_block::M3()
{
    if (m_curr_sym.s_value != 'e')
    {
        DA1D();
        return B1b();
    }
    else
    {
        return e_D3();
    }

}

State Lex_block::EXIT3()
{
    DA1D();
    return EXIT2();
}
State Lex_block::EXIT4()
{
    DA2D();
    return EXIT2();
}
State Lex_block::EXIT5()
{
    DA3D();
    return EXIT2();
}
State Lex_block::EXIT6()
{
    DA1E();
    return EXIT2();
}

State Lex_block_mb::E2a()
{
   m_reg_class = "lex_line";
   return m_collect_of_states["E2"];
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
   m_name_table.emplace(std::pair<std::string, double>(const_id, m_reg_number));
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
   while (m_curr_state.m_id != 19)
   {
      m_curr_sym = transliterator(m_file.get());

      m_curr_state = (this->*m_func_table[m_curr_state][m_curr_sym.s_class])();
   }

}

void Lex_block_mb::add_variable()
{
   m_name_table.emplace(std::pair<std::string, double>(m_reg_var_name, m_reg_number));
   m_reg_nt_pointer = reinterpret_cast<long long int>(&m_name_table[m_reg_var_name]);

}

void Lex_block_mb::create_lexem()
{
   if(m_reg_class.m_id == 0 /*line*/ || m_reg_class.m_id == 2 /*aur oper*/)
   {
      std::tuple<Lexem, long long int, int> tup(m_reg_class, m_reg_value, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }
   else if (m_reg_class.m_id == 1 /*operand*/ ||m_reg_class.m_id == 4 /*next*/ || m_reg_class.m_id == 5 /*let*/ || \
         m_reg_class.m_id == 6 /*let*/ || m_reg_class.m_id == 7 /*for*/ || m_reg_class.m_id == 8 /*goto*/ || \
         m_reg_class.m_id == 9 /*gosub*/)
   {
      std::tuple<Lexem, long long int, int> tup(m_reg_class, m_reg_nt_pointer, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }
   else if (m_reg_class.m_id == 3 /*relation*/)
   {
      std::tuple<Lexem, long long int, int> tup(m_reg_class, m_reg_relation, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }
   else if (m_reg_class.m_id == 10 /*open_br*/ || m_reg_class.m_id == 11 /*close_br*/ || \
      m_reg_class.m_id == 12 /*if*/ || m_reg_class.m_id == 13 /*return*/ || m_reg_class.m_id == 14 /*end*/ || \
      m_reg_class.m_id == 15 /*to*/ || m_reg_class.m_id == 16 /*step*/ || m_reg_class.m_id == 17 /*rem*/ || \
      m_reg_class.m_id == 18 /*error*/ || m_reg_class.m_id == 19 /*eof*/)
   {
      std::tuple<Lexem, long long int, int> tup(m_reg_class, -1, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }

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

