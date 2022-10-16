#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "cored.h"

#include <fstream>
//вспомогательная программа, запускается с правами root
// осуществляет все действия с демоном:
/*
запуск, остановку, установку задачи, коректировку списка задач,
как удалять задание из списка


*/

int get_uid(const char* path);
int start_deamon(const char* name); // запуск демона

#define _PATH "../bin/sim_deamon"

/*
config(path);
если нужно
      start(path);
 else
*/

int main(int argc,char* argv[])
{
   //смена владельца и прав доступа
//    uid_t uid;
//if((uid=get_uid(_PATH))!=0)
//{ // можно сменить каталог, тогда chown,chmod, должны получать имя бинарного файла
//   // либо брать имена из CMakeLists.txt
//    //
//if(chown(_PATH,0,0)<0) {
//    std::cerr<<"Ошибка смены владельца, нет прав\n";
// exit(EXIT_FAILURE);}
// if(chmod(_PATH,S_IRWXU|S_IRGRP|S_IROTH)<0)
// {
//      std::cerr<<"Ошибка chmod.\n";
//   exit(EXIT_FAILURE);
// }

////}

//}
//  else
//    std::cout<<"program allready started with "<<uid<<" owner\n";
//  std::cout<<"ppid = "<<getppid()<<"\n";
//for(int i=1;i<argc;++i){
    std::string s(argv[1]);
  // std::cout<<s<<"\n";}

  if(s=="s"||s=="start")
    {
       start_deamon(_PATH);
    }

    return 0;

 }

//проверяет запущен ли демон, если нет запускает
int start_deamon(const char* name)
{ pid_t pid;
    uid_t uid;
  try
    {
  if((uid=get_uid(name))!=0)
  {
     if(chown(name,0,0)<0)
         throw "ошибка функции chown";
     if(chmod(name,S_IRWXU|S_IRGRP|S_IROTH)<0)
         throw  "ошибка функции chmod";

  pid=fork();
  if(pid==0)
  {
    execl(name,NULL);
    return 0;  //запуск демона
   } // в родителе, создать файл с pid демона
  //int fd;

  std::fstream out;
  out.open("/var/run/sim_deamon.pid",std::ios_base::out);
  out<<pid;
   }
    else throw "демон уже запущен";

     }
     catch(std::exception &ex)
    {
      std::cout<<ex.what()<<"\n";
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
    std::cout<<"uid "<<path<<" "<<st.st_uid<<"\n";
    return st.st_uid;
    }


