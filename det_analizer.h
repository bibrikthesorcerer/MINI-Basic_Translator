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
   std::string m_id; //уникальный идентификатор состояния

   State() { m_id = ""; }                                                  //конструктор по умолчанию присваивает состоянию пустой id
   State(std::string id) { m_id = id; }                                    //коструктор с параметрами присваивает состоянию id из входной строки
   State& operator=(const State& obj) { m_id = obj.m_id; return *this; }   //оператор присваивания, копирующий id объекта obj в объект this
   bool operator==(const State& obj) { return m_id == obj.m_id; }          //оператор сравнения, сравнивающий id двух состояний
   friend bool operator<(const State& obj1, const State& obj2);            //оператор сравнения "меньше", сравнивающий id двух объектов с пом. отношения <
   ~State() {}
};

//определим указатель на функции
typedef State(*funct_ptr)();

// абстрактный класс "конечный лексический анализатор"
class det_analizer
{
public:
   /*
   * @brief виртуальная функция парсинга - совершает переходы по таблице переходов в зависимости от входного символа
   */
   virtual void parse();

   //перечисления "символьная лексема" и "лексема"
   enum class symbolLexem;
   enum class Lexem;

   //структура inp_symbol - представляет символ и его принадлежность к алфавиту конечного автомата
   struct inp_symbol
   {
      int s_value; //ASCII - код символа
      symbolLexem s_class; //принадлежность к алфавиту
   };


protected:
   std::map<State, std::map<symbolLexem,funct_ptr>> m_func_table;    //таблица переходов анализатора
   std::list<std::tuple<Lexem, long long int, size_t>> m_lexem_list; //список лексем анализатора
   std::map<std::string, double> m_name_table;                       //таблица имён
   State m_curr_state;                                               //текущее состояние анализатора
   inp_symbol m_curr_sym;                                            //текущий входной символ
   std::fstream m_file;                                              //рабочий файловый поток


   /*
   * @brief Виртуальная функция транслитерации. Удалена по умолчанию, определяется в производном классе непосредственно.
   * @param int sym
   * @returns объект структуры inp_symbol
   */
   virtual inp_symbol transliterator(int sym) = 0;
 
};

