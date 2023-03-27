#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "det_analizer.h"

class Lex_block_mb : public det_analizer
{
public:
   //enum class symbol_lexem
   //{
   //   sl_letter, 
   //   sl_digit, 
   //   sl_aur_op, 
   //   sl_relat,
   //   sl_op_brace,
   //   sl_cls_brace,
   //   sl_dot,
   //   sl_space,
   //   sl_lf,
   //   sl_eof,
   //   sl_error
   //};
   //enum class Lexem {
   //   lex_line, lex_operand, lex_aur_oper,
   //   lex_relation, lex_next, lex_let,
   //   lex_for, lex_goto, lex_gosub,
   //   lex_op_brace, lex_cls_brace, lex_if, 
   //   lex_return, lex_end, lex_to,
   //   lex_step, lex_rem, lex_error,
   //   lex_eof
   //};

   Lex_block_mb(std::string filename);


   virtual void parse();

   ~Lex_block_mb()
   {
      m_file.close();
   }

protected:
   //следующие поля наследуются от класса det_analizer:
   //std::map<State, std::map<symbol_lexem, funct_ptr>> m_func_table;    //таблица переходов анализатора
   //std::list<std::tuple<Lexem, long long int, size_t>> m_lexem_list; //список лексем анализатора
   //std::map<std::string, double> m_name_table;                       //таблица имён
   //State m_curr_state;                                               //текущее состояние анализатора
   //inp_symbol m_curr_sym;                                            //текущий входной символ
   //std::fstream m_file;                                              //рабочий файловый поток

   const size_t m_state_number = 23;
   const size_t m_class_number = 10;

   Lexem m_reg_class;               //Регистр класса. служит для хранения класса лексемы
   long long int m_reg_nt_pointer;  //Регистр указателя. содержит указатель для лексем PUSH и POP
   size_t m_reg_relation;           //Регистр отношения. хранит информацию о первом символе отношения
   double m_reg_number;             // Регистр числа. используется для вычисления констант
   size_t m_reg_order;              // Регистр порядка
   size_t m_reg_counter;            // Регистр счётчика
   size_t m_reg_is_negative;        // Регистр знака числа
   size_t m_reg_line_num = 1;       // Номер строки. хранит номер текущей строки в программе.
   std::string m_reg_var_name;      // Регистр переменной. накапливает имя переменной
   size_t m_reg_detection = 0;      //Регистр обнаружения. хранит номер позиции в таблице обнаружения для поиска ключевых слов.
   size_t m_reg_value;              // Регистр значения. хранит значения лексем

   std::map<char, int> m_beg_vector;   // начальный вектор

   std::vector<std::tuple<char, int, funct_ptr>> m_detect_table; // таблица обнаружения

   virtual det_analizer::inp_symbol transliterator(int sym);


private:

   void fill_lexems();

   void fill_symbol_lexems();
   /*
   * @brief добавление константы в коллекцию m_name_table
   */
   void add_constant();
   /*
   * @brief добавление переменной в коллекцию m_name_table
   */
   void add_variable();

   void create_lexem();

   /*
   * @brief метод, заполняющий начальный вектор парами буква-индекс
   */
   void init_beg_vect();

   /*
   * @bried метод, заполняющий таблицу обнаружения тройками буква-переход-альтернатива
   */
   void init_detect_table();

   void init_func_table();

};