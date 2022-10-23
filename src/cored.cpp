#include "cored.h"
#include <chrono>
#include <ctime>
#include <string>



namespace  core
{

 const char* command[]={"start","stop","add","remove","help"};
//  список команд доступных для управления демоном
 const char ch_key[]="rsadh";// символьные ключи



 command_list::command_list(int c,char*s[])
 {
     int i=0;
     while (i<c)
     {
       int cnt=0;
while(*(s[i]+cnt)!='\0'){
   Token t= read_token(s[i],cnt);
   if(t.isCorrect())
    std::cout<<t.data()<<"\n";
         }
 i++;
     }
 }
 bool Token::isCorrect() const
 {
   if(tp==Token::type::none)
       return false;
   if(!key&&value.empty())
       return false;
   return true;
 }
Token read_token(const char*s,int &pos)
{


const char*ch=s+pos;
/*
Если первый символ '-'
   проверить следуюший символ
     Если следующий символ '-' поиск ключа в строке
     Иначе поиск в массиве символов
Иначе считать аргумент или опцию


при получении команды pos не равен нулю, никогда

*/

std::string str;
while (*ch!='\0') {

  //  std::cout<<*ch;
//-k,--key

if(std::isalpha(*ch))
{
   if(((ch-s) == 2&&pos==0) && (ch-s)<strlen(s)-1) // поиск строковой команды
   {
     str=(ch);
     pos+=(ch-s)+str.size();
 //  std::cout<<"string key "<<str;
     //break;
     return {Token::type::_cmd,str.c_str()};
   }
     if((ch-s)==1)
   {
     pos+=2;
         return {Token::type::_cmd,*ch};

     }
     if(pos>0)
    {   pos++;
         return {Token::type::_cmd,*ch};


     }
  if(pos==0)
  {
  str=(ch);
  pos+=str.size();
      return {Token::type::_value,ch};

  }


}
//if(std::isdigit(*ch)||*ch=='/')
if((std::isdigit(*ch)||*ch=='+'||*ch=='/'||*ch==':')&&pos==0)
{ // если ввод начинался с - и встретили цифру,
    // смотрим на корректность ввода m_clock
   if(*s=='-')
        { ch--;
   m_clock clck(ch);
   std::cout<<clck<<"\n";
   }
          str=(ch);
    pos+=str.size();
    return Token(Token::type::_time,ch);
}
ch++;
}
return Token(Token::type::none,"");
}




m_clock::m_clock():hour(0),min(0),sec(0)
{}

//m_clock::m_clock(struct tm* _tm)
//{

//}

m_clock::m_clock(const time_t &t)
{
    struct tm *u;
    u=localtime(&t);
hour=u->tm_hour;
min=u->tm_min;
sec=u->tm_sec;
}

m_clock::m_clock(int hh,int mm,int ss)
{
    if(hh<0||hh>23)
        hour=0;
    else hour=hh;

   if(mm<0||mm>59)
       min=0;
   else min=mm;
   if(ss<0||ss>59)
       sec=0;
    else sec=ss;
}
//предполагаем что строка всегда имеет
//m_clock::m_clock(const char*s)   //строка может быть форматов hh:mm:ss, hh:mm, или hh/mm/ss, hh/mm
//{  //т.е. считывая строку проверяем разделитель,
//    char ch;
//   int cnt=0;
//    while(s[cnt])

//}
m_clock::m_clock(const char* s)
{
    std::string str(s);
    read_value(str.c_str());
}


std::ostream & operator<<(std::ostream& os,const m_clock& tm)
{
   if(tm.hour<10)
      os<<'0';
  os<<tm.hour<<':';
  if(tm.min<10)
      os<<'0';
 os <<tm.min<<':';
 if(tm.sec<10)
     os<<'0';
   os<<tm.sec;
   return os;
}

// если возвращать количество прочитанных символов, строки
//
int m_clock::read_value(const char *s)
{
 //char*ch=s;
 int cnt=0;
 /*
первый символ может быть либо цифрой, тогда читать значение
либо '/',':' тогда устанавливается текущее значение
или некорректное значение,

для этого нужен указатель на переменную, в которую будет производиться чтение
если   \0

*/
 //if((*s)==' ')
  //  s++;

 time_t now=time(0);
 tm* ltm=localtime(&now);
 int val=-999;
 while(((*(s+cnt))!='\0')){


//    if(std::isdigit(*ch))
//    {
//       val=val+((*ch)-0x30);
//    }

    switch(*(s+cnt))
 {
    case '/':
    case ':':
//std::cout<<"case terminator:\n";
        //установить нужное значение
     if(val<0)
         val=get_value(ltm);
        set_value(val);
       val=-999;
        break;
   case '+':
   case '-': // считать следующее за знаком значение и прибавить к текущему
//std::cout<<"case operand\n";
    { char op=*(s+cnt);  //сохранить знак операции
           cnt++;
        int diff=0;
        while (((*(s+cnt))!=':')&&((*(s+cnt))!='/')&&((*(s+cnt))!='\0'))
    {
            if(std::isdigit(*(s+cnt)))
            {
               diff=diff*10+((*(s+cnt))-0x30);
            } else
             {
             std::cerr<<"unknown value\n";
             exit(-1);
            }
         cnt++;
        }
        // cnt--;
         val=get_value(ltm); // получаем соответствующее значение
        if(op=='+')
        {
          val+=diff;
          if(cur_r==_hour)
           {      if(val>23)
                  val=val%24;
              } else
                if(val>59)
                    val=val%60;
        }
         if(op=='-'){
             val-=diff;
         if(val<0)
        val=(cur_r==_hour)?24-val:60-val;
         }
    }
cnt--;
        break;
       case '0': case '1': case '2':case '3': case '4': case '5': case '6': case '7': case '8':
       case '9':
  //      std::cout<<"case digit\n";
      if(val<0)
          val=0;
        val=val*10+((*(s+cnt))-0x30);
        break;
    default:
        std::cerr<<"unknoun value\n";
        return -1;
        break;
    }


//if(*ch=='\0')
  //  end_read();  // выставляет все оставшиеся значения в 0

    cnt++;

 }
// if(*(s+cnt)=='\0')
 //{
// val=get_value(ltm);
 if(val<0){
   val=get_value(ltm);
// std::cout<<"cur value "<<val<<"\n";
 }
 // std::cout<<"cur value "<<val<<"\n";
 set_value(val)  ;


 //}
end_read();

 return 0;
}


int m_clock::get_value(struct tm*ltm)
{


if(cur_r==_hour)
    return ltm->tm_hour;
if(cur_r==_min)
    return ltm->tm_min;
if(cur_r==_sec)
    return ltm->tm_sec;
return 0;
}

void m_clock::set_value(int val)
{if(cur_r==_sec)
    {
      sec=val;
    cur_r=_none;

    }
    if(cur_r==_min)
    {
      min=val;
    cur_r=_sec;
    }
  if(cur_r==_hour)
  {
    hour=val;
    cur_r=_min;
      }


}

void m_clock::end_read()
{
    while(cur_r!=_none)
    {
      set_value(0);
    }
    cur_r=_hour;
}
std::istream& operator>>(std::istream &is, m_clock& tm)
{

 char buf[16]={0};
// is.get(buf,10,'\n'); //читает, строку из 10 символов или до первого '\n'
 char ch=0;
 int i=0;
//is.get(); //
while ((ch=is.get())&&(ch!='\n'))//!(std::isspace(ch=is.get()))&&ch!='\n'&&ch!=EOF)   &&(ch!=' ')
{
 if(ch==' ')
     continue;
 buf[i]=ch;
i++;

};
buf[++i]='\0';

//i=0;
//i=tm.read_value(buf);
//i+=tm.read_value(buf+i);
tm.read_value(buf);




// is>>hh>>ch1>>mm>>ch2>>ss;
// if(!is) //
// {
//     return is;
// }
//std::cout<<"ch2= "<<ch2<<"\n";
// tm=m_clock(hh,mm,ss);
 return is;
}
// сравнение времени

bool m_clock::operator<(const time_t &t) const
{ long cur=hour*60*60+min*60+sec;
 // получаем значение секунд текущего времени
    tm *ltm=localtime(&t);
 long _t=ltm->tm_hour*60*60+ltm->tm_min*60+ltm->tm_sec;

 return cur<_t ;
  }

bool m_clock::operator>(const time_t &t) const
{ long cur=hour*60*60+min*60+sec;
   tm*ltm=localtime(&t);
   long _t=ltm->tm_hour*60*60+ltm->tm_min*60+ltm->tm_sec;
    return (cur>_t);
 }

bool m_clock::operator==(const time_t &t) const
{
 long cur=hour*60*60+min*60+sec;
tm*ltm=localtime(&t);
 long _t=ltm->tm_hour*60*60+ltm->tm_min*60+ltm->tm_sec;

 return cur==_t;
}


bool m_clock:: operator<(const m_clock &m)const
{
  long sec_cur=hour*60*60+min*60+sec;
long sec_m=m.hour*60*60+m.min*60+m.sec;
return sec_cur<sec_m;
}
bool m_clock::operator>(const m_clock &m) const
{
    long sec_cur=hour*60*60+min*60+sec;
  long sec_m=m.hour*60*60+m.min*60+m.sec;
  return sec_cur>sec_m;

}

bool m_clock::operator==(const m_clock &m) const
{
    long sec_cur=hour*60*60+min*60+sec;
  long sec_m=m.hour*60*60+m.min*60+m.sec;
  return sec_cur==sec_m;
}

}
