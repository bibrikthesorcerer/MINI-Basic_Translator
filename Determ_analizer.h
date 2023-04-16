#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "State.h"


// Абстрактный класс "конечный лексический анализатор"
class Determ_analizer
{
public:

   /*
   * @brief Виртуальная функция парсинга - совершает переходы по таблице переходов в зависимости от входного символа
   */
   virtual void parse() = 0;

   //Классы "символьная лексема" и "лексема"
   class Symbol_lexem 
   {
   public:
      std::string m_name;
      size_t m_id;

      Symbol_lexem(const char* str = "", size_t id = -1);

      Symbol_lexem(const Symbol_lexem& obj);

      Symbol_lexem& operator=(const Symbol_lexem& obj);

      friend bool operator<(const Symbol_lexem& obj1, const Symbol_lexem& obj2);
   };

   class Lexem
   {
   public:
      std::string m_name;
      size_t m_id;

      Lexem(std::string str = "", size_t id = -1);

      Lexem& operator=(const char* str);

      friend bool operator<(const Lexem& obj1, const Lexem& obj2);

   };

   //Структура Input_symbol - представляет символ и его принадлежность к алфавиту конечного автомата
   struct Input_symbol
   {
      int s_value; //ASCII - код символа
      Symbol_lexem s_class; //Принадлежность к алфавиту

      Input_symbol() { s_value = -1; s_class = ""; }
   };

   struct variable
   {
      std::string var_name;
      double var_value = 0;
   };

protected:
   std::list<std::tuple<Lexem, long long int, size_t>> m_lexem_list;    //Список лексем анализатора

   State m_curr_state;                                                  //Текущее состояние анализатора

   Input_symbol m_curr_sym;                                             //Текущий входной символ

   std::fstream m_file;                                                 //Рабочий файловый поток

   std::map<std::string, variable> m_name_table;                        //Таблица имён
   std::map<std::string, Symbol_lexem> m_collection_of_Symlex;          //Коллекция возможных символьных лексем анализатора
   std::map<std::string, Lexem> m_collection_of_Lex;                    //Коллекция возможных лексем анализатора
   std::map<std::string, State>  m_collection_of_States;                //Коллекция состояний анализатора

   /*
   * @brief Виртуальная функция транслитерации. Удалена по умолчанию, определяется в производном классе непосредственно.
   * @param int sym
   * @returns объект структуры Input_symbol
   */
   virtual Input_symbol transliterator(int sym) = 0;
 
};

