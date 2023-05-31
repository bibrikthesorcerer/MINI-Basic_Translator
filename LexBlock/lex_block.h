#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "Determ_analizer.h"



class Lex_block : public Determ_analizer
{
public:

   /*
   Символьные лексемы:
      sl_letter, 
      sl_digit, 
      sl_aur_op, 
      sl_relat,
      sl_op_brace,
      sl_cls_brace,
      sl_dot,
      sl_space,
      sl_lf,
      sl_eof,
      sl_error
   
   Лексемы:
      lex_line, 
      lex_operand, 
      lex_aur_oper,
      lex_relation, 
      lex_next, 
      lex_let,
      lex_for, 
      lex_goto, 
      lex_gosub,
      lex_op_brace, 
      lex_cls_brace, 
      lex_if, 
      lex_return, 
      lex_end, 
      lex_to,
      lex_step, 
      lex_rem, 
      lex_error,
      lex_eof
   */

   /*Определим fucnt_ptr - указатель на метод класса.
   funct_ptr может принимать указатели на методы класса, соответствующие следующему прототипу:
   State Lex_block::ИМЯ_МЕТОДА ()
   */
   typedef State (Lex_block::*funct_ptr)();


   /*@brief Удалим конструктор по умолчанию и оставим лишь конструктор с параметрами, 
   дабы объект класса при создании сразу связывал себя с рабочим файлом.
   */
   Lex_block() = delete;

   /*@brief Конструктор с параметрами
   * @param Переменная std::string filename, хранящая имя рабочего файла
   */
   Lex_block(std::string filename);

   std::list<std::tuple<Lexem, long long int, size_t>> get_lexem_list()
   {
      return m_lexem_list;
   }

   virtual void parse() override;

   void print_lexem_list();

   /*@brief Деструктор, закрывающий файловый поток после удаления объекта класса
   */
   ~Lex_block();


protected:
   //следующие поля наследуются от класса Determ_analizer:
   //std::list<std::tuple<Lexem, long long int, size_t>> m_lexem_list;  //список лексем анализатора
   //std::map<std::string, double> m_name_table;                        //таблица имён
   //State m_curr_state;                                                //текущее состояние анализатора
   //Input_symbol m_curr_sym;                                           //текущий входной символ
   //std::fstream m_file;                                               //рабочий файловый поток
   //std::map<std::string, Symbol_lexem> m_collection_of_Symlex;        //коллекция существующих символьных лексем
   //std::map<std::string, Lexem> m_collection_of_Lex;                  //коллекция существующих лексем
   //std::map<std::string, State>  m_collection_of_States;              //коллекция существующих состояний



   const size_t m_state_number = 19;
   const size_t m_class_number = 10;

   int m_reg_order;                                                        // Регистр порядка
   int m_reg_counter;                                                      // Регистр счётчика
   int m_reg_sign;                                                         // Регистр знака числа
   bool m_error_flag;

   Lexem m_reg_class;                                                      // Регистр класса. служит для хранения класса лексемы

   size_t m_reg_detection  = 0;                                            // Регистр обнаружения. хранит номер позиции в таблице обнаружения для поиска ключевых слов.
   size_t m_reg_value;                                                     // Регистр значения. хранит значения лексем
   size_t m_reg_relation;                                                  // Регистр отношения. хранит информацию о первом символе отношения
   int m_reg_line_num   = 1;                                            // Номер строки. хранит номер текущей строки в программе.

   double m_reg_number;                                                    // Регистр числа. используется для вычисления констант

   long long int m_reg_nt_pointer;                                         // Регистр указателя. содержит указатель для лексем PUSH и POP

   std::string m_reg_var_name;                                             // Регистр переменной. накапливает имя переменной

   std::map<int, long long int> m_collection_of_lines;                  // Коллекция указателей на лексемы "номер строки"
   std::map<int, long long int> m_collection_of_gotos;
   std::map<char, size_t> m_beg_vector;                                    // Начальный вектор
   std::map<State, std::map<Symbol_lexem, funct_ptr>> m_func_table;        // Таблица переходов анализатора

   std::vector<std::tuple<char, size_t, funct_ptr>> m_detect_table;        // Таблица обнаружения


   virtual Determ_analizer::Input_symbol transliterator(int sym);


private:

   /*
   * @brief Вычисление константы с помощью соответствующих регистров
   */
   void calc_constant();

   /*
   * @brief Заполнение коллекции возможных лексем
   */
   void fill_lexems();

   /*
   * @brief Заполнение коллекции возможных символьных лексем
   */
   void fill_symbol_lexems();

   /*
   * @brief Добавление константы в коллекцию m_name_table
   */
   void add_constant();

   /*
   * @brief Добавление переменной в коллекцию m_name_table
   */
   void add_variable();

   /*
   * @brief Создание лексемы и добавление её в список лексем
   */
   void create_lexem();

   /*
   * @brief Метод, заполняющий начальный вектор парами буква-индекс
   */
   void init_beg_vect();

   /*
   * @bried Метод, заполняющий таблицу обнаружения тройками буква-переход-альтернатива
   */
   void init_detect_table();

   /*
   * @brief Заполнение коллекции возможных состояний
   */
   void init_states();

   /*
   * @brief Заполнение таблицы переходов соответствующими указателями на методы
   */
   void init_func_table();

   /*
   * @brief Таблица отношений
   * @param Принимает long long int ch - код отношения (цифра от 1 до 6)
   * @returns Возвращает строку типа const char*, представляющую соотв. отношение
   */
   const char* relation_table(long long int ch);

   void DA1D();
   void DA2D();
   void DA3D();
   void DA1E();

   //методы, которыми заполнится таблица

   State Error1();

   State e_A1() { return m_collection_of_States["A1"]; }
   State e_A2() { return m_collection_of_States["A2"]; }
   State e_A3() { return m_collection_of_States["A3"]; }
   State e_B1() { return m_collection_of_States["B1"]; }
   State e_C1() { return m_collection_of_States["C1"]; }
   State e_C2() { return m_collection_of_States["C2"]; }
   State e_D1() { return m_collection_of_States["D1"]; }
   State e_D2() { return m_collection_of_States["D2"]; }
   State e_D3() { return m_collection_of_States["D3"]; }
   State e_D4() { return m_collection_of_States["D4"]; }
   State e_D5() { return m_collection_of_States["D5"]; }
   State e_D6() { return m_collection_of_States["D6"]; }
   State e_E1() { return m_collection_of_States["E1"]; }
   State e_E2() { return m_collection_of_States["E2"]; }
   State e_F1() { return m_collection_of_States["F1"]; }
   State e_F2() { return m_collection_of_States["F2"]; }
   State e_F3() { return m_collection_of_States["F3"]; }
   State e_G1() { return m_collection_of_States["G1"]; }
   State e_H1() { return m_collection_of_States["H1"]; }

   State A1a();
   State A1b();
   State A1c();
   State A1d();
   State A1e();

   State A2a();
   State A2b();
   State A2c();
   State A2d();
   State A2e();
   State A2f();
   State A2g();
   State A2h();
   State A2i();
   State A2j();
   State A2k();
   State A2m();
   State A2n();
   State A2o();
   State A2p();
   State A2q();
   State A2r();
   State A2s();
   State A2t();
   State A2u();

   State A3a();
   State A3b();
   State A3c();
   State A3d();
   State A3e();
   State A3f();
   State A3g();


   State B1a();
   State B1b();
   State B1c();
   State B1d();
   State B1e();

   State C1a();

   State C2a();
   State C2b();
   State C2c();
   State C2d();

   State D1a();
   State D1b();
   State D1c();

   State D2a();
   State D2b();
   State D2c();

   State D3a();

   State D4a();

   State D5a();
   State D5b();
   State D5c();

   State D6a();

   State E1a();
   State E1b();

   State E2a();
   State E2b();
   State E2c();

   State F1a();
   State F1b();

   State F2a();

   State F3a();

   State G1a();

   State H1a();
   State H1b();
   State H1c();
   State H1d();
   State H1e();
   State H1f();

   State M1();
   State M2();
   State M3();

   State EXIT1();
   State EXIT2();
   State EXIT3();
   State EXIT4();
   State EXIT5();
   State EXIT6();


};