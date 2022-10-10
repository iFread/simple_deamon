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
{ private:
 int hour;
 int min;
 int sec;

public:
 m_clock(); // устанавливает объект m_clock = 00:00:00
 m_clock(const char*s); // принимает строку формата hh:mm:ss
 explicit m_clock(int hh,int mm=0,int ss=0); // принимает дату в виде целых чисел
  //
// сравнение даты
  bool compare(time_t t);
 // bool compare(const struct tm& t); // нужна ли работа с tm,
                            // или скрыть ее в time_t

 //


 // запись и чтение даты
 friend std::ostream& operator<<(std::ostream &os, const m_clock& cl);
 friend std::istream& operator>>(std::istream &is, m_clock &cl);


};


};








#endif // CORED_H
