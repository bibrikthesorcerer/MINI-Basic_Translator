#include <iostream>

//класс "состояние конечного анализатора"
class State
{
public:
   std::string m_name;  //имя состояния
   size_t m_id;         //уникальный идентификатор состояния

   //конструктор по умолчанию присваивает состоянию пустой id
   State();

   //конструктор с параметрами присваивает состоянию id из входной строки
   State(std::string name, size_t id);

   //конструктор копирования
   State(const State& obj);

   //оператор присваивания, копирующий id объекта obj в объект this
   State& operator=(const State& obj);

   //оператор сравнения, сравнивающий id двух состояний
   bool operator==(const State& obj);

   //оператор сравнения "меньше", сравнивающий id двух объектов с пом. отношения <
   friend bool operator<(const State& obj1, const State& obj2);

   ~State() {}
};
