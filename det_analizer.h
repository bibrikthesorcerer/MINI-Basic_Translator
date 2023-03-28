#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>

//состояния конечного автомата
class State
{
public:
   std::string m_name; //уникальный идентификатор состояния
   size_t m_id;

   State() { m_name = ""; m_id = -1; }                                                          //конструктор по умолчанию присваивает состоянию пустой id
   State(std::string name, size_t id) { m_name = name; m_id = id; }                             //коструктор с параметрами присваивает состоянию id из входной строки
   State& operator=(const State& obj) { m_name = obj.m_name; m_id = obj.m_id; return *this; }   //оператор присваивания, копирующий id объекта obj в объект this
   bool operator==(const State& obj) { return m_name == obj.m_name && m_id == obj.m_id; }       //оператор сравнения, сравнивающий id двух состояний
   friend bool operator<(const State& obj1, const State& obj2);                                    //оператор сравнения "меньше", сравнивающий id двух объектов с пом. отношения <
   ~State() {}
};

//перечисления "символьная лексема" и "лексема"
class symbol_lexem 
{
public:
   std::string m_name;
   size_t m_id;
   symbol_lexem& operator=(const char* str) { m_name = str; return *this; }
   friend bool operator<(const symbol_lexem& obj1, const symbol_lexem& obj2);        

};
class Lexem
{
public:
   std::string m_name;
   size_t m_id;
   Lexem& operator=(const char* str) { m_name = str; return *this; }
   friend bool operator<(const Lexem& obj1, const Lexem& obj2);

};

//определим указатель на функции
//typedef State(det_analizer::*funct_ptr)();

// абстрактный класс "конечный лексический анализатор"
class det_analizer
{
public:
   /*
   * @brief виртуальная функция парсинга - совершает переходы по таблице переходов в зависимости от входного символа
   */
   virtual void parse() = 0;


   //структура inp_symbol - представляет символ и его принадлежность к алфавиту конечного автомата
   struct inp_symbol
   {

      int s_value; //ASCII - код символа
      symbol_lexem s_class; //принадлежность к алфавиту
      //inp_symbol() { s_value = -1; s_class = ""; }
      //friend bool operator<(inp_symbol& sym1, inp_symbol& sym2);
   };


protected:
   //std::map<State, std::map<symbol_lexem,funct_ptr>> m_func_table;    //таблица переходов анализатора
   std::list<std::tuple<Lexem, long long int, size_t>> m_lexem_list; //список лексем анализатора
   std::map<std::string, double> m_name_table;                       //таблица имён
   State m_curr_state;                                               //текущее состояние анализатора
   inp_symbol m_curr_sym;                                            //текущий входной символ
   std::fstream m_file;                                              //рабочий файловый поток
   std::map<std::string, size_t> m_sym_lex_collection;
   std::map<std::string, size_t> m_collect_of_lex;
   std::map<std::string, State>  m_collect_of_states;


   /*
   * @brief Виртуальная функция транслитерации. Удалена по умолчанию, определяется в производном классе непосредственно.
   * @param int sym
   * @returns объект структуры inp_symbol
   */
   virtual inp_symbol transliterator(int sym) = 0;
 
};

