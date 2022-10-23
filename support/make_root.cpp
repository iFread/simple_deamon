#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "cored.h"
#include <exception>
#include <fstream>
//вспомогательная программа, запускается с правами root
// осуществляет все действия с демоном:
/*
запуск, остановку, установку задачи, коректировку списка задач,
как удалять задание из списка


*/

int get_uid(const char* path);
int start_deamon(const char* name); // запуск демона
bool parent_correct(pid_t ppid);  //проверить корректность родителя
bool exe_correct();// проверка что процесс запущен корректно

const char*_PATH="sim_deamon";

/*
config(path);
если нужно
      start(path);
 else
*/

int main(int argc,char* argv[])
{

 // 1. проверка родителя :
     //  - получить ppid
    // получить путь ./proc/ppid/exe
    // сравнить с константой parrent_path
char cwd[256];

getcwd(cwd,256);
std::cout<<"current path :"<<cwd<<"\n";
 std::string s;
    try{s =(argv[1]);
  // std::cout<<s<<"\n";}
}
    catch(const char* s)
    {
      std::cout<< s<<"\n";
    }
  if(s=="s"||s=="start")
    {std::string path=cwd;
      path+="/../bin/";
      path+=_PATH;
      std::cout<<path<<"\n";
       start_deamon(path.c_str());
    }

    return 0;

 }

// установить взаимодействие с родителем
//  получить нужную информацию,
// если все хорошо,
bool exe_correct()
{
  bool fl_exe=false;


  return fl_exe;
}
//проверяет запущен ли демон, если нет запускает
int start_deamon(const char* name)
{ pid_t pid;
    uid_t uid;
  try
    {//std::cout<<"open .pid file\n";
  if((uid=get_uid(name))!=0)
  {
 // при запуске без sudo нет прав для того чтобы сделать владельцем root
     if(chown(name,0,0)<0)
         throw "ошибка функции chown";
     if(chmod(name,S_IRWXU|S_IRGRP|S_IROTH)<0)
         throw  "ошибка функции chmod";
  pid=fork();
  if(pid==0)
  {
    execl(name,NULL);
   exit(EXIT_FAILURE);  //запуск демона
   } // в родителе, создать файл с pid демона
  //int fd;

  std::fstream out;
  out.open("/var/run/sim_deamon.pid",std::ios_base::out);
  out<<pid;
  out.close();

  }
    else {
      throw "демон уже запущен";
}
     }
     catch(const char* s)//std::exception& ex)//std::exception &ex)
    {
      std::cout<<"Exception: "<<s<<"\n";
    }
    return  pid;
   }  // pid

int get_uid(const char*path)
{

   struct stat st;
    if((stat(path,&st))<0){ // это надо писать в лог
      std::cerr<<"Ошибка вызова stat, программа остановлена\n";
exit(EXIT_FAILURE);
    }
  //  std::cout<<"uid "<<path<<" "<<st.st_uid<<"\n";
    return st.st_uid;
    }


