#ifndef CORED_H
#define CORED_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
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

//std::vector<std::string> comand;
//extern const char* command[];//={"start","stop","add","remove","help"};
//  список команд доступных для управления демоном
extern const char ch_key[];//="rsadh";// символьные ключи




struct m_clock
{
public:
    enum current_read{_hour,_min,_sec,_none};
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
  bool operator<(const time_t &t)const;
 bool operator>(const time_t&t)const;
 bool operator==(const time_t&t)const;
  // bool compare(const struct tm& t); // нужна ли работа с tm,
                            // или скрыть ее в time_t
bool operator<(const m_clock& m)const;
bool operator>(const m_clock& m)const;
bool operator==(const m_clock &m)const;
 //

private:
//чтение переменной как понять какой
  int read_value(const char*s);
  void set_value(int val);  // записывает переданное значение , и изменяет флаг cur_r
  int get_value(struct tm*t); // возвращает нужное значение в зависимости от указателя cur_r  т.е. может вернуть значение часов,минут, или секунд
                           //для переданного time_t , не изменяет положение указателя

  void end_read();              //
  // запись и чтение даты

public:

 friend std::ostream& operator<<(std::ostream &os, const m_clock& cl);
 friend std::istream& operator>>(std::istream &is, m_clock &cl);

};

//нужен список команд, список доступных опций,для определенной команды

class Token
{
  // виды токенов, которые будут считываться
public:
    enum class type{none,_cmd,_option,_value,_time};
    Token(type t,  char s):key{s},value{s},tp{t}{}
 Token(type t,const char* s):value{s},tp{t}{}
  const char* data() const{ return value.c_str();}
  bool isCorrect()const;
private:
  char key{0};
  std::string value;
  type tp{Token::type::none};

};
// читает входную строку в буфер

    Token read_token(const char*s,int& pos); //читает поток и возвращает полученный token



class Command
{
char key;
std::string option;
const char*path;
m_clock tim;
public:
Command():key(0),path{nullptr},tim{-1,-1,-1}{}
 bool isCorrect()const; // проверка на корректность значений
 void set(char k);//,const char* path=nullptr,const char* op=nullptr);
 void set(char k,const char* path);
 void set_option(const char* op);
};

class command_list
{
    //char _cmd;  //если больше одной команды???
    std::map<char  ,std::string> _cmd;
    std::vector<const char*> path; // для аргументов команды
    m_clock tm;
public:
    command_list(int c,char* s[]);
  bool isCorrect()const;
  std::vector<const char*> get_cmd();
};







}







#endif // CORED_H
