#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <tuple>
#include <sstream>
#include "Lex_block.h"



void Lex_block::init_beg_vect()
{
   m_beg_vector['E'] = 1;
   m_beg_vector['F'] = 3;
   m_beg_vector['G'] = 5;
   m_beg_vector['I'] = 11;
   m_beg_vector['L'] = 12;
   m_beg_vector['N'] = 14;
   m_beg_vector['R'] = 17;
   m_beg_vector['S'] = 23;
   m_beg_vector['T'] = 26;
}                  

void Lex_block::init_detect_table()
{
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('-', 0, &Lex_block::B1d));// костыль
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('N', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('D', 0, &Lex_block::A2q));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('O', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('R', 0, &Lex_block::F1b));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('O', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('T', 8, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('O', 0, &Lex_block::E1a));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('S', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('U', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('B', 0, &Lex_block::E1b));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('F', 0, &Lex_block::A2r));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('E', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('T', 0, &Lex_block::F1a));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('E', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('X', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('T', 0, &Lex_block::C1a));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('E', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('T', 22,&Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('U', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('R', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('N', 0, &Lex_block::A2s));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('M', 0, &Lex_block::G1a));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('T', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('E', 0, &Lex_block::B1d));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('P', 0, &Lex_block::A2t));
   m_detect_table.push_back(std::make_tuple<char, int, funct_ptr>('O', 0, &Lex_block::A2u));
}

void Lex_block::init_states()
{
   m_collection_of_States[  "A1"] = State(  "A1", 0);
   m_collection_of_States[  "A2"] = State(  "A2", 1);
   m_collection_of_States[  "A3"] = State(  "A3", 2);
   m_collection_of_States[  "B1"] = State(  "B1", 3);
   m_collection_of_States[  "C1"] = State(  "C1", 4);
   m_collection_of_States[  "C2"] = State(  "C2", 5);
   m_collection_of_States[  "D1"] = State(  "D1", 6);
   m_collection_of_States[  "D2"] = State(  "D2", 7);
   m_collection_of_States[  "D3"] = State(  "D3", 8);
   m_collection_of_States[  "D4"] = State(  "D4", 9);
   m_collection_of_States[  "D5"] = State(  "D5", 10);
   m_collection_of_States[  "D6"] = State(  "D6", 11);
   m_collection_of_States[  "E1"] = State(  "E1", 12);
   m_collection_of_States[  "E2"] = State(  "E2", 13);
   m_collection_of_States[  "F1"] = State(  "F1", 14);
   m_collection_of_States[  "F2"] = State(  "F2", 15);
   m_collection_of_States[  "F3"] = State(  "F3", 16);
   m_collection_of_States[  "G1"] = State(  "G1", 17);
   m_collection_of_States[  "H1"] = State(  "H1", 18);
   m_collection_of_States["STOP"] = State("STOP", 19);
}

void Lex_block::init_func_table()
{
   for (auto it = m_collection_of_States.begin(); it != m_collection_of_States.end(); it++)
   {
      for (auto it_sym = m_collection_of_Symlex.begin(); it_sym != m_collection_of_Symlex.end(); it_sym++)
      { 
         
         (m_func_table[it->second])[it_sym->second] = &Lex_block::Error1;

      }
   }

   (m_func_table[m_collection_of_States["A1"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::E2a;
   (m_func_table[m_collection_of_States["A1"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_A1;
   (m_func_table[m_collection_of_States["A1"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::e_A1;
   (m_func_table[m_collection_of_States["A1"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT1;
   
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::C2a;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D1a;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::A2a;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::H1a;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::A2h;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::A3b;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_dot"       ]] = &Lex_block::e_D6;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_A2;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::e_A1;
   (m_func_table[m_collection_of_States["A2"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT1;

   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::B1a;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D1a;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::A2a;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::H1a;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::A2h;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::A3b;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_dot"       ]] = &Lex_block::e_D6;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_A3;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::e_A1;
   (m_func_table[m_collection_of_States["A3"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT1;

   (m_func_table[m_collection_of_States["B1"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::M1;
   (m_func_table[m_collection_of_States["B1"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_B1;

   (m_func_table[m_collection_of_States["C1"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::C2d;
   (m_func_table[m_collection_of_States["C1"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_C1;

   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::B1b;
   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::A3a;
   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::A2g;
   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::H1b;
   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::A2k;
   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::A3c;
   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_C2;
   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::A1a;
   (m_func_table[m_collection_of_States["C2"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT2;

   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::M2;
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D1b;
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::A2c;
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::H1c;
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::A2i; 
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::A3d;
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_dot"       ]] = &Lex_block::D2c;
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_D1;
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::A1b;
   (m_func_table[m_collection_of_States["D1"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT3;

   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::M3;
   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D2a;
   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::A2d;
   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::H1d;
   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::A2m; 
   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::A3e;
   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_D2;
   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::A1c;
   (m_func_table[m_collection_of_States["D2"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT4;

   (m_func_table[m_collection_of_States["D3"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D5a;
   (m_func_table[m_collection_of_States["D3"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::D4a;
   (m_func_table[m_collection_of_States["D3"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_D3;

   (m_func_table[m_collection_of_States["D4"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D5b;
   (m_func_table[m_collection_of_States["D4"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_D4;

   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::B1c;
   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D5c;
   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::A2e;
   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::H1e;
   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::A2n;
   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::A3f;
   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_D5;
   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::A1d;
   (m_func_table[m_collection_of_States["D5"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT5;

   (m_func_table[m_collection_of_States["D6"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D2b;
   (m_func_table[m_collection_of_States["D6"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_D6;

   (m_func_table[m_collection_of_States["E1"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::E2b;
   (m_func_table[m_collection_of_States["E1"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_E1;

   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::B1e;
   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::E2c;
   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::A2f;
   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::H1f;
   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::A2j;
   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::A3g;
   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_E2;
   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::A1e;
   (m_func_table[m_collection_of_States["E2"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT6;

   (m_func_table[m_collection_of_States["F1"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::F2a;
   (m_func_table[m_collection_of_States["F1"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_F1;

   (m_func_table[m_collection_of_States["F2"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::F3a;
   (m_func_table[m_collection_of_States["F2"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::A2o;
   (m_func_table[m_collection_of_States["F2"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_F2;

   (m_func_table[m_collection_of_States["F3"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::A2o;
   (m_func_table[m_collection_of_States["F3"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_F3;

   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::e_G1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::e_G1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::e_G1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::e_G1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::e_G1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::e_G1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_G1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_dot"       ]] = &Lex_block::e_G1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::e_A1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT1;
   (m_func_table[m_collection_of_States["G1"]])[m_collection_of_Symlex["sl_error"     ]] = &Lex_block::e_G1;

   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_letter"    ]] = &Lex_block::C2b;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_digit"     ]] = &Lex_block::D1c;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_aur_op"    ]] = &Lex_block::A2g;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_relat"     ]] = &Lex_block::A2p;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_op_brace"  ]] = &Lex_block::A2k;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_cls_brace" ]] = &Lex_block::A3c;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_dot"       ]] = &Lex_block::D6a;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_space"     ]] = &Lex_block::e_H1;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_lf"        ]] = &Lex_block::A1a;
   (m_func_table[m_collection_of_States["H1"]])[m_collection_of_Symlex["sl_eof"       ]] = &Lex_block::EXIT2;


}


State Lex_block::A1b()
{
   DA1D();
   return A1a();
}

State Lex_block::A1c()
{
   DA2D();
   return A1a();
}

State Lex_block::A1d()
{
   DA3D();
   return A1a();
}

State Lex_block::A1e()
{
   DA1E();
   return A1a();
}

State Lex_block::A2a()
{
   m_reg_class = m_collection_of_Lex["lex_aur_oper"];
   m_reg_value = m_curr_sym.s_value;
   return A2b();
}

State Lex_block::A2b()
{
   create_lexem();
   return e_A2();
}

State Lex_block::A2c()
{
   DA1D();
   return A2g();
}

State Lex_block::A2d()
{
   DA2D();
   return A2g();
}

State Lex_block::A2e()
{
   DA3D();
   return A2g();
}

State Lex_block::A2f()
{
   DA1E();
   return A2g();
}

State Lex_block::A2j()
{
   DA1E();
   return A2k();
}

State Lex_block::A2h()
{
   m_reg_class = m_collection_of_Lex["lex_op_brace"];
   create_lexem();
   return e_A2();
}

State Lex_block::A2i()
{
   DA1D();
   return A2k();
}

State Lex_block::A2m()
{
   DA2D();
   return A2k();
}

State Lex_block::A2n() 
{
   DA3D();
   return A2k();
}

State Lex_block::A2o()
{
   if (m_curr_sym.s_value != '=')
   {
      return Error1();
   }
   else
   {
      add_variable();
      return A2b();
   }

}

State Lex_block::A2q()
{
   m_reg_class = m_collection_of_Lex["lex_end"];
   return A2b();
}

State Lex_block::A2r()
{
   m_reg_class = m_collection_of_Lex["lex_if"];
   return A2b();
}

State Lex_block::A2s()
{
   m_reg_class = m_collection_of_Lex["lex_return"];
   return A2b();
}

State Lex_block::A2t()
{
   m_reg_class = m_collection_of_Lex["lex_step"];
   return A2b();
}

State Lex_block::A2u()
{
   m_reg_class = m_collection_of_Lex["lex_to"];
   return A2b();
}

State Lex_block::A3a()
{
   m_reg_var_name += m_curr_sym.s_value +'0';
   add_variable();
   create_lexem();
   return e_A3();
}

State Lex_block::A3d()
{
   DA1D();
   return A3c();
}

State Lex_block::A3b()
{
   m_reg_class = m_collection_of_Lex["lex_cls_brace"];
   create_lexem();
   return e_A3();
}

State Lex_block::A3e()
{
   DA2D();
   return A3c();
}

State Lex_block::A3f()
{
   DA3D();
   return A3c();
}

State Lex_block::A3g()
{
   DA1E(); 
   return A3c();
}

State Lex_block::B1c()
{
   DA3D();
   return B1b();
}

State Lex_block::B1b()
{
   if (m_reg_var_name != "")
      add_variable();
   create_lexem();
   return B1a();
}

State Lex_block::B1a()
{
   m_reg_detection = m_beg_vector[m_curr_sym.s_value];
   if (m_reg_detection == 0)
   {
      return Error1();
   }
   return e_B1();
}

State Lex_block::C1a()
{
   m_reg_class = m_collection_of_Lex["lex_next"];
   return e_C1();
}

State Lex_block::C2a()
{
   m_reg_class = m_collection_of_Lex["lex_operand"];
   return C2d();
}

State Lex_block::C2d()
{
   m_reg_var_name = static_cast<char>(m_curr_sym.s_value);
   return e_C2();
}

State Lex_block::B1d()
{
   m_reg_detection++;
   return e_B1();
}


//alexey

State Lex_block::C2b()
{
   create_lexem();
   return C2a();
}

State Lex_block::A2g()
{
   if (m_reg_var_name != "")
      add_variable();
   create_lexem();
   if (m_curr_sym.s_value == '=')
      m_reg_relation = 1;
   else if (m_curr_sym.s_value == '!')
      m_reg_relation = 2;
   else if (m_curr_sym.s_value == '<')
      m_reg_relation = 3;
   else if (m_curr_sym.s_value == '>')
      m_reg_relation = 4;
   return A2a();
}

State Lex_block::A2p()
{

   if (m_curr_sym.s_value == '=')
   {
      if (m_reg_relation == 2)
      {
         //ничего делать не надо, присвоен уже корректный код
      }
      else if (m_reg_relation == 3)
      {
         m_reg_relation = 5;
      }
      else if (m_reg_relation == 4)
      {
         m_reg_relation = 6;
      }
      else
      {   
         return Error1();
      }
   }
   else// здесь после одного знака встретили не = а что угодно - это ошибка
   {
      return Error1();
   }
      return A2b();
}

State Lex_block::A2k()
{
   if(m_reg_var_name != "")
      add_variable();
   create_lexem();
   if (m_curr_sym.s_value == '=')
      m_reg_relation = 1;
   else if (m_curr_sym.s_value == '!')
      m_reg_relation = 2;
   else if (m_curr_sym.s_value == '<')
      m_reg_relation = 3;
   else if (m_curr_sym.s_value == '>')
      m_reg_relation = 4;
   return A2h();
}

State Lex_block::A3c()
{

   if (m_reg_var_name != "")
      add_variable();
   create_lexem();
   if (m_curr_sym.s_value == '=')
      m_reg_relation = 1;
   else if (m_curr_sym.s_value == '!')
      m_reg_relation = 2;
   else if (m_curr_sym.s_value == '<')
      m_reg_relation = 3;
   else if (m_curr_sym.s_value == '>')
      m_reg_relation = 4;
   return A3b();
}

State Lex_block::A1a()
{
   if (m_reg_var_name != "")
      add_variable();
   create_lexem();
   if (m_curr_sym.s_class.m_id == 3 && m_curr_sym.s_value == '=')
      m_reg_relation = 1;
   else if (m_curr_sym.s_value == '<')
      m_reg_relation = 3;
   else if (m_curr_sym.s_value == '>')
      m_reg_relation = 4;
   return e_A1();
}

State Lex_block::EXIT2()
{
   if (m_reg_var_name != "")
      add_variable();
   create_lexem();
   return EXIT1();
}

State Lex_block::EXIT1()
{
   m_reg_class = m_collection_of_Lex["lex_eof"];
   create_lexem();
   return m_collection_of_States["STOP"];
}

State Lex_block::H1c()
{
   DA1D();
   return H1b();
}

State Lex_block::H1b()
{
   if (m_reg_var_name != "")
      add_variable();
   create_lexem();
   return H1a();
}

State Lex_block::H1a()
{
   m_reg_class = m_collection_of_Lex["lex_relation"];
   if (m_curr_sym.s_value == '=')
      m_reg_relation = 1;
   else if (m_curr_sym.s_value == '!')
      m_reg_relation = 2;
   else if (m_curr_sym.s_value == '<')
      m_reg_relation = 3;
   else if (m_curr_sym.s_value == '>')
      m_reg_relation = 4;
   return e_H1();
}

State Lex_block::H1d()
{
   DA2D();
   if (m_curr_sym.s_value == '=')
      m_reg_relation = 1;
   else if (m_curr_sym.s_value == '!')
      m_reg_relation = 2;
   else if (m_curr_sym.s_value == '<')
      m_reg_relation = 3;
   else if (m_curr_sym.s_value == '>')
      m_reg_relation = 4;
   return H1b();
}

State Lex_block::H1e()
{
   DA3D();
   if (m_curr_sym.s_value == '=')
      m_reg_relation = 1;
   else if (m_curr_sym.s_value == '!')
      m_reg_relation = 2;
   else if (m_curr_sym.s_value == '<')
      m_reg_relation = 3;
   else if (m_curr_sym.s_value == '>')
      m_reg_relation = 4;
   return H1b();
}

State Lex_block::H1f()
{
   DA1E();
   return H1b();
}

State Lex_block::G1a()
{
   m_reg_class = m_collection_of_Lex["lex_rem"];
   create_lexem();
   return e_G1();
}

State Lex_block::E1a()
{
   m_reg_class = m_collection_of_Lex["lex_goto"];
   return e_E1();
}

State Lex_block::E1b()
{
   m_reg_class = m_collection_of_Lex["lex_gosub"];
   return e_E1();
}

State Lex_block::E2a()
{
   m_reg_class = m_collection_of_Lex["lex_line"];
   m_reg_line_num = m_curr_sym.s_value;
   return E2b();
}

State Lex_block::E2b()
{
   m_reg_line_num = m_curr_sym.s_value;
   return e_E2();
}

State Lex_block::E2c()
{
   m_reg_line_num = m_reg_line_num * 10 + m_curr_sym.s_value;
   return e_E2();
}

State Lex_block::D1c()
{
   if (m_reg_class.m_id != 17)
      create_lexem();
   return D1a();
}

State Lex_block::D1a()
{
   m_reg_class = m_collection_of_Lex["lex_operand"];
   m_reg_number = m_curr_sym.s_value;
   return e_D1();
}

State Lex_block::D1b()
{
   m_reg_number = m_reg_number * 10 + m_curr_sym.s_value;
   return e_D1();
}

State Lex_block::D2a()
{
   m_reg_counter++;
   m_reg_number = m_reg_number * 10 + m_curr_sym.s_value;
   return e_D2();
}

State Lex_block::D2b()
{
   m_reg_class = m_collection_of_Lex["lex_operand"];
   m_reg_counter = 1;
   m_reg_number = m_curr_sym.s_value;
   return e_D2();
}

State Lex_block::D2c()
{
   m_reg_counter = 0;
   return e_D2();
}

State Lex_block::D3a()
{
   m_reg_counter = 0;
   return e_D3();
}

State Lex_block::D4a()
{
   if (m_curr_sym.s_value == '-')
   {
      m_reg_sign = -1;
   }
   else if (m_curr_sym.s_value == '+')
   {
      m_reg_sign = +1;
   }
   else
   {
      return Error1();
   }
   return e_D4();
}

State Lex_block::D5a()
{
   m_reg_sign = +1;
   return D5b();
}

State Lex_block::D5b()
{
   m_reg_order = m_curr_sym.s_value;
   return e_D5();
}

State Lex_block::D5c()
{
   m_reg_order = m_reg_order * 10 + m_curr_sym.s_value;
   return e_D5();
}

State Lex_block::D6a()
{
   if (m_curr_sym.s_value == '=')
      m_reg_relation = 1;
   else if (m_curr_sym.s_value == '!')
      m_reg_relation = 2;
   else if (m_curr_sym.s_value == '<')
      m_reg_relation = 3;
   else if (m_curr_sym.s_value == '>')
      m_reg_relation = 4;
   create_lexem();
   return e_D6();
}

State Lex_block::B1e()
{
   DA1E();
   return B1b();
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
    if (m_curr_sym.s_value != 'E')
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
    if (m_curr_sym.s_value != 'E')
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

void Lex_block::DA1E()
{ 
   m_reg_value = m_reg_line_num;

}

void Lex_block::print_lexem_list()
{
   for (auto it = m_lexem_list.begin(); it != m_lexem_list.end(); ++it)
   {
      switch (std::get<0>(*it).m_id)
      { 
      case 0: //line
      {
         std::cout << std::endl << std::get<2>(*it) << " ";
         break;
      }
      case 1: //operand
      {
         std::cout << (reinterpret_cast<variable*>(std::get<1>(*it))->var_name) << " ";
         break;
      }
      case 2: // ar op
      {
         std::cout << ((char)std::get<1>(*it)) << " ";
         break;
      }
      case 3: // relation
      {
         std::cout << (relation_table(std::get<1>(*it))) << " ";
         break;
      }
      case 4: //next
      {
         std::cout << "NEXT " << (reinterpret_cast<variable*>(std::get<1>(*it))->var_name) << " ";
         break;
      }
      case 5: //let
      {
         std::cout << "LET " << (reinterpret_cast<variable*>(std::get<1>(*it))->var_name) << " =" << " ";
         break;
      }
      case 6: //for
      {
         std::cout << "FOR " << (reinterpret_cast<variable*>(std::get<1>(*it))->var_name) << " =" << " ";
         break;
      }
      case 7: //goto
      {
          if(std::get<1>(*it) != 0)
          {
              std::cout << "GOTO " << std::get<2>(*(reinterpret_cast<std::tuple<Lexem, long long int, size_t>*>(*reinterpret_cast<long long int*>(std::get<1>(*it))))) << " ";
          }
          else
          {
              std::cout << "GOTO ERROR" << " ";
          }
         break;
      }
      case 8: //gosub
      {
          if (std::get<1>(*it) != 0)
          {
              std::cout << "GOSUB " << std::get<2>(*(reinterpret_cast<std::tuple<Lexem, long long int, size_t>*>(*reinterpret_cast<long long int*>(std::get<1>(*it))))) << " ";
          }
          else
          {
              std::cout << "GOSUB ERROR" << " ";
          }
         break;
      }
      case 9:// (
      {
         std::cout << "(" << " ";
         break;
      }
      case 10:// )
      {
         std::cout << ")" << " ";
         break;
      }
      case 11:// if
      {
         std::cout << "IF" << " ";
         break;
      }
      case 12:// return
      {
         std::cout << "RETURN" << " ";
         break;
      }
      case 13:// end
      {
         std::cout << "END" << " ";
         break;
      }
      case 14:// to
      {
         std::cout << "TO" << " ";
         break;
      }
      case 15:// step
      {
         std::cout << "STEP" << " ";
         break;
      }
      case 16:// rem
      {
         std::cout << "REM" << " ";
         break;
      }
      case 17:// err
      {
         std::cout << "!ERROR!" << " ";
         break;
      }
      case 18:// return
      {
         std::cout << std::endl << "EOF" << " ";
         break;
      }


      };
   }
   std::cout << std::endl;

}

Lex_block::~Lex_block()
{
   m_file.close();
}


const char* Lex_block::relation_table(long long int ch)
{
   switch (ch)
   {
   case(1): {return "="; }
   case(2): {return "!="; }
   case(3): {return "<"; }
   case(4): {return ">"; }
   case(5): {return "<="; }
   case(6): {return ">="; }
   default:
      break;
   }
   return 0;
}


//void Lex_block::DA1ECYCLE() {}


void Lex_block::DA1D()
{
   m_reg_order -= m_reg_counter;
   calc_constant();
   return;
}

void Lex_block::DA2D()
{
   m_reg_order -= m_reg_counter;
   m_reg_class = m_collection_of_Lex["lex_operand"];
   calc_constant();
   return;
}

void Lex_block::DA3D()
{
   if (m_reg_sign == -1)
   {
      m_reg_order *= -1;
   }
      m_reg_order -= m_reg_counter;
      calc_constant();
      return;
}

State Lex_block::Error1()
{
    m_error_flag = true;
   if(m_reg_class.m_id != 17 )//error
   {
      m_reg_class = m_collection_of_Lex["lex_error"];
      create_lexem();
   }

   // если ошибка произошла на цифре или букве, то пропустим последующие цифры и\или буквы
   if (m_curr_sym.s_class.m_id == 0 || m_curr_sym.s_class.m_id == 1)
   {
      while (m_curr_sym.s_class.m_id == 0 || m_curr_sym.s_class.m_id == 1)
      {
         m_curr_sym = transliterator(m_file.get());
      }
   }

   if (m_curr_sym.s_class.m_id == 10)//error
   {
      while (m_curr_sym.s_class.m_id == 10)
      {
         m_curr_sym = transliterator(m_file.get());
      }
   }
   if (m_curr_sym.s_class.m_id == 9) // eof
   {
      return EXIT1();
   }
   else if (m_curr_sym.s_class.m_id == 8) // lf
   {
      return m_collection_of_States["A1"];
   }
   return m_curr_state;
}

void Lex_block::fill_lexems()
{
   m_collection_of_Lex["lex_line"]        = Lexem("lex_line",  0);
   m_collection_of_Lex["lex_operand"]     = Lexem("lex_operand",  1);
   m_collection_of_Lex["lex_aur_oper"]    = Lexem("lex_aur_oper",  2);
   m_collection_of_Lex["lex_relation"]    = Lexem("lex_relation",  3);
   m_collection_of_Lex["lex_next"]        = Lexem("lex_next",  4);
   m_collection_of_Lex["lex_let"]         = Lexem("lex_let",  5);
   m_collection_of_Lex["lex_for"]         = Lexem("lex_for",  6);
   m_collection_of_Lex["lex_goto"]        = Lexem("lex_goto",  7);
   m_collection_of_Lex["lex_gosub"]       = Lexem("lex_gosub",  8);
   m_collection_of_Lex["lex_op_brace"]    = Lexem("lex_op_brace",  9);
   m_collection_of_Lex["lex_cls_brace"]   = Lexem("lex_cls_brace", 10);
   m_collection_of_Lex["lex_if"]          = Lexem("lex_if", 11);
   m_collection_of_Lex["lex_return"]      = Lexem("lex_return", 12);
   m_collection_of_Lex["lex_end"]         = Lexem("lex_end", 13);
   m_collection_of_Lex["lex_to"]          = Lexem("lex_to", 14);
   m_collection_of_Lex["lex_step"]        = Lexem("lex_step", 15);
   m_collection_of_Lex["lex_rem"]         = Lexem("lex_rem", 16);
   m_collection_of_Lex["lex_error"]       = Lexem("lex_error", 17);
   m_collection_of_Lex["lex_eof"]         = Lexem("lex_eof", 18);

}

void Lex_block::fill_symbol_lexems()
{
   m_collection_of_Symlex["sl_letter"]      = Symbol_lexem("sl_letter",    0);
   m_collection_of_Symlex["sl_digit"]       = Symbol_lexem("sl_digit",     1);
   m_collection_of_Symlex["sl_aur_op"]      = Symbol_lexem("sl_aur_op",    2);
   m_collection_of_Symlex["sl_relat"]       = Symbol_lexem("sl_relat",     3);
   m_collection_of_Symlex["sl_op_brace"]    = Symbol_lexem("sl_op_brace",  4);
   m_collection_of_Symlex["sl_cls_brace"]   = Symbol_lexem("sl_cls_brace", 5);
   m_collection_of_Symlex["sl_dot"]         = Symbol_lexem("sl_dot",       6);
   m_collection_of_Symlex["sl_space"]       = Symbol_lexem("sl_space",     7);
   m_collection_of_Symlex["sl_lf"]          = Symbol_lexem("sl_lf",        8);
   m_collection_of_Symlex["sl_eof"]         = Symbol_lexem("sl_eof",       9);
   m_collection_of_Symlex["sl_error"]       = Symbol_lexem("sl_error",     10);
}

void Lex_block::calc_constant()
{
   m_reg_number = m_reg_number * std::powl(10.0, m_reg_order);
   add_constant();
   m_reg_number = 0;
   m_reg_counter = 0;
   m_reg_order = 0;
}

void Lex_block::add_constant()
{
   std::ostringstream str_stream;
   str_stream << m_reg_number;
   std::string const_id = str_stream.str();
   variable var;
   var.var_name = const_id;
   var.var_value = m_reg_number;
   m_name_table.emplace(std::pair<std::string, variable>(const_id, var));
   m_reg_nt_pointer = reinterpret_cast<long long int>(&m_name_table[const_id]);

}

Lex_block::Lex_block(std::string filename)
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
   init_states();
   init_func_table();
   m_curr_state = m_collection_of_States["A1"];
}

void Lex_block::parse()
{
   while (m_curr_state.m_id != 19)
   {
      m_curr_sym = transliterator(m_file.get());

      m_curr_state = (this->*m_func_table[m_curr_state][m_curr_sym.s_class])();
   }

   //проверим, есть ли строки для всех goto
   for (auto& itGoto : m_collection_of_gotos)
   {
       auto findIt = m_collection_of_lines.find(itGoto.first);
       if (findIt == m_collection_of_lines.end())
       {
           m_error_flag = true;
           return;
       }
       else
       {
           itGoto.second = findIt->second;
       }
   }
}

void Lex_block::add_variable()
{
   variable var;
   var.var_name = m_reg_var_name;
   var.var_value = 0;
   m_name_table.emplace(std::pair<std::string, variable>(m_reg_var_name, var));
   m_reg_nt_pointer = reinterpret_cast<long long int>(&m_name_table[m_reg_var_name]);
   m_reg_var_name = "";

}

void Lex_block::create_lexem()
{
   if (m_reg_class.m_id == 0 /*line*/)
   {
      //если мы добавляем строку в код, но она уже содержится, то....
      if (m_collection_of_lines.contains(m_reg_line_num))
      {
         Error1();
         return;
         //m_reg_class = m_collection_of_Lex["lex_error"];
         //create_lexem();
      }
      else
      {
         m_reg_nt_pointer = reinterpret_cast<long long int>(&m_collection_of_lines[m_reg_line_num]);
      }
      std::tuple<Lexem, long long int, int> tup(m_reg_class, m_reg_nt_pointer, m_reg_line_num);
      m_lexem_list.push_back(tup);

      //в коллекции запись с номером строки теперь указывает на свою же лексему в списке лексем
      auto it = &(*(--m_lexem_list.end()));
      m_collection_of_lines[m_reg_line_num] = reinterpret_cast<long long int>(it);
   }
   if (m_reg_class.m_id == 7 /*goto*/ || m_reg_class.m_id == 8 /*gosub*/)
   {
      m_collection_of_gotos[m_reg_line_num] = 0;
      m_reg_nt_pointer = reinterpret_cast<long long int>(&m_collection_of_gotos[m_reg_line_num]);
      std::tuple<Lexem, long long int, int> tup(m_reg_class, m_reg_nt_pointer, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }

   if(m_reg_class.m_id == 2 /*aur oper*/)
   {
      std::tuple<Lexem, long long int, int> tup(m_reg_class, m_reg_value, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }
   else if (m_reg_class.m_id == 1 /*operand*/ ||m_reg_class.m_id == 4 /*next*/ || m_reg_class.m_id == 5 /*let*/ || \
         m_reg_class.m_id == 6 /*for*/)
   {
      std::tuple<Lexem, long long int, int> tup(m_reg_class, m_reg_nt_pointer, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }
   else if (m_reg_class.m_id == 3 /*relation*/)
   {
      std::tuple<Lexem, long long int, int> tup(m_reg_class, m_reg_relation, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }
   else if (m_reg_class.m_id == 9 /*open_br*/ || m_reg_class.m_id == 10 /*close_br*/ || \
      m_reg_class.m_id == 11 /*if*/ || m_reg_class.m_id == 12 /*return*/ || m_reg_class.m_id == 13 /*end*/ || \
      m_reg_class.m_id == 14 /*to*/ || m_reg_class.m_id == 15 /*step*/ || m_reg_class.m_id == 16 /*rem*/ || \
      m_reg_class.m_id == 17 /*error*/ || m_reg_class.m_id == 18 /*eof*/)
   {
      std::tuple<Lexem, long long int, int> tup(m_reg_class, -1, m_reg_line_num);
      m_lexem_list.push_back(tup);
   }

}

Determ_analizer::Input_symbol Lex_block::transliterator(int sym)
{
   Determ_analizer::Input_symbol symbol;
   symbol.s_value = 0;
   if (isdigit(sym))
   {
      symbol.s_class = m_collection_of_Symlex["sl_digit"];
      symbol.s_value = sym - '0';
   }
   else if ((sym > 64 && sym < 91))
   {
      symbol.s_class = m_collection_of_Symlex["sl_letter"];
      symbol.s_value = sym;
   }
   else if (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^')
   {
      symbol.s_class = m_collection_of_Symlex["sl_aur_op"];
      symbol.s_value = sym;
   }
   else if (sym == '=' || sym == '!' || sym == '<' || sym == '>')
   {
      symbol.s_class = m_collection_of_Symlex["sl_relat"];
      symbol.s_value = sym;

   }
   else if (sym == ' ' || sym == '\t')
   {
      symbol.s_class = m_collection_of_Symlex["sl_space"];
   }
   else if (sym == '\n' || sym == '\r\n')
   {
      symbol.s_class = m_collection_of_Symlex["sl_lf"];
   }
   else if (sym == EOF)
   {
      symbol.s_class = m_collection_of_Symlex["sl_eof"];
   }
   else if (sym == '(')
   {
      symbol.s_class = m_collection_of_Symlex["sl_op_brace"];
      symbol.s_value = sym;
   }
   else if (sym == ')')
   {
      symbol.s_class = m_collection_of_Symlex["sl_cls_brace"];
      symbol.s_value = sym;
   }
   else if (sym == '.')
   {
      symbol.s_class = m_collection_of_Symlex["sl_dot"];
      symbol.s_value = sym;
   }
   else
   {
      symbol.s_class = m_collection_of_Symlex["sl_error"];
   }
   return symbol;
}
