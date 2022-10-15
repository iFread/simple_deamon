#ifndef CORED_H
#define CORED_H

#include <iostream>
//#include <ctime>

// определить классы и структуры данных для демона и программ работы с демоном:

namespace core
{
//struct Date
//{
//  int year;
//  int month;
//  int day;

//};

struct m_clock
{
public:
    enum current_read{_hour,_min,_sec};
private:
 int hour;
 int min;
 int sec;
 current_read cur_r{_hour}; // указатель на читаемое значение устанавливается на _hour
                            //т.е. если cur_r не равна _hour идет считывание переменной

 int*cur_val {&hour};
public:
 m_clock(); // устанавливает объект m_clock = 00:00:00
 m_clock(const char*s); // принимает строку формата hh:mm:ss
 explicit m_clock(int hh,int mm=0,int ss=0); // принимает дату в виде целых чисел
 explicit m_clock(const time_t &t);
 //
// сравнение даты
  bool compare(const time_t &t);
 // bool compare(const struct tm& t); // нужна ли работа с tm,
                            // или скрыть ее в time_t

 //

private:
//чтение переменной как понять какой
  int read_value(char*s);

  void set_value(int val);  // записывает переданное значение , и изменяет флаг cur_r
  int get_value(struct tm*t); // возвращает нужное значение в зависимости от указателя cur_r  т.е. может вернуть значение часов,минут, или секунд
                           //для переданного time_t , не изменяет положение указателя

  void end_read();              //
  // запись и чтение даты

public:

 friend std::ostream& operator<<(std::ostream &os, const m_clock& cl);
 friend std::istream& operator>>(std::istream &is, m_clock &cl);

};


};








#endif // CORED_H
