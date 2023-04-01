#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>

//класс "состояние конечного анализатора"
class State
{
public:
   std::string m_name;  //имя состояния
   size_t m_id;         //уникальный идентификатор состояния

   //конструктор по умолчанию присваивает состоянию пустой id
   State();
      
   //коструктор с параметрами присваивает состоянию id из входной строки
   State(std::string name, size_t id);

   //оператор присваивания, копирующий id объекта obj в объект this
   State& operator=(const State& obj);

   //оператор сравнения, сравнивающий id двух состояний
   bool operator==(const State& obj);

   //оператор сравнения "меньше", сравнивающий id двух объектов с пом. отношения <
   friend bool operator<(const State& obj1, const State& obj2);    

   ~State() {}
};


// абстрактный класс "конечный лексический анализатор"
class Determ_analizer
{
public:
   /*
   * @brief виртуальная функция парсинга - совершает переходы по таблице переходов в зависимости от входного символа
   */
   virtual void parse() = 0;

   //перечисления "символьная лексема" и "лексема"
   class Symbol_lexem 
   {
   public:
      std::string m_name;
      size_t m_id;
      Symbol_lexem(const char* str = "", size_t id = -1) 
      { 
         m_name = str; 
         m_id = id;
      }
      Symbol_lexem& operator=(const Symbol_lexem& obj) 
      {
         m_name = obj.m_name;
         m_id = obj.m_id;
         return *this;
      }
      friend bool operator<(const Symbol_lexem& obj1, const Symbol_lexem& obj2);
   };
   class Lexem
   {
   public:
      std::string m_name;
      size_t m_id;
      Lexem(std::string str = "", size_t id = -1) { m_name = str; m_id = id; }
      Lexem& operator=(const char* str) { m_name = str; return *this; }
      friend bool operator<(const Lexem& obj1, const Lexem& obj2);

   };

   //структура Input_symbol - представляет символ и его принадлежность к алфавиту конечного автомата
   struct Input_symbol
   {
      int s_value; //ASCII - код символа
      Symbol_lexem s_class; //принадлежность к алфавиту
      Input_symbol() { s_value = -1; s_class = ""; }
      //friend bool operator<(Input_symbol& sym1, Input_symbol& sym2);
   };

   struct variable
   {
      std::string var_name;
      double var_value = 0;
   };

protected:
   std::list<std::tuple<Lexem, long long int, size_t>> m_lexem_list; //список лексем анализатора
   std::map<std::string, variable> m_name_table;                       //таблица имён
   State m_curr_state;                                               //текущее состояние анализатора
   Input_symbol m_curr_sym;                                            //текущий входной символ
   std::fstream m_file;                                              //рабочий файловый поток

   std::map<std::string, Symbol_lexem> m_collection_of_Symlex;
   std::map<std::string, Lexem> m_collection_of_Lex;
   std::map<std::string, State>  m_collection_of_States;

   /*
   * @brief Виртуальная функция транслитерации. Удалена по умолчанию, определяется в производном классе непосредственно.
   * @param int sym
   * @returns объект структуры Input_symbol
   */
   virtual Input_symbol transliterator(int sym) = 0;
 
};

