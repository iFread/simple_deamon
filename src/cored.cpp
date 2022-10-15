#include "cored.h"
#include <chrono>
#include <ctime>
#include <string>



namespace  core
{

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
int m_clock::read_value(char *s)
{
 char*ch=s;
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
  }
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
    while(cur_r!=_sec)
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


}
