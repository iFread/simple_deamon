#include "cored.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <wait.h>
#include <vector>

/*
serv_deamon или service
  основная утилита по управлению демоном, парсит входную строку,и запускает

 -c/--cmd comand hh/mm/ss
 -e/--exe [-s/--su]  path, или имя приложения,  hh/mm/ss
          запуск от root
*/

//const char* read_token(char* const t);
int main(int argc,char*argv[])
{
    if(argc<2)
    {
       std::cerr<<"Do not key\nEnter "<<argv[0]<<" -h or --help for more information\n";
   exit(EXIT_FAILURE);
   }

  /*
  for(int i=1;;)
{

}  //прием списка команд

*/
core::command_list com(argc-1,argv+1);

//   core::m_clock mm("23/24/15");
//   core::m_clock nn(time(0));
//    std::cout<<(nn==time(0))<<"\n";
//    std::cout<<(mm<time(0))<<"\n";
//core::m_clock n2(time(0));
//std::cout<<(nn>n2)<<"\n";

    int i=1;
    char* ch=argv[i];
    std::string key;
    std::string comand;
    std::string option;
    while (*ch!='\0')
      {
        if(isalpha(*ch))
            key.push_back(*ch);
        ch++;
    // считываем ключ
    //std::cin>>key;

     }
    i++;
    ch=argv[i];
    if(*ch=='-'){
        while ((*ch)!='\0')
        {
           if(isalpha(*ch))
               option.push_back(*ch);
         ch++;
        }
   // std::cin>>option;
 ++i;
    }
 // std::cin>>comand;
comand=std::string(argv[i]);
i++;
core::m_clock tm(argv[i]);
//std::cin>>tm;


if(key=="s"||key=="start")
{
   pid_t pid;

   pid=fork();
    if(pid==0)
    {// формируем вектор для отправки

      std::vector<const char*> vec;

    vec.push_back("sudo");
    vec.push_back("-k");
    vec.push_back("../bin/./d_start");
    vec.push_back("start");
    vec.push_back(NULL);
       // const char* sudo="/usr/bin/sudo";
       // const char*bash="usr/bin/bash";
      //execl(sudo,"sudo","-k","../bin/./d_start",NULL);
//


 //  char* p[]={"sudo","-k","../bin/./d_start","start",NULL};//new char*[vec.size()+1];
//   for(int i{0};i<vec.size();++i)
//   {
//     p[i]=vec[i];
//   }

 //   execvp(vec[0],const_cast<char* const*>(vec.data()));
  //    exit(1);
  }


      if(pid<0)
       { std::cerr<<"Ошибка вызова fork\n";
     exit(EXIT_FAILURE);
      }
    std::cout<<" current pid = "<<pid<<"\n";

    waitpid(pid,NULL,0);
}



std::cout<<argv[0]<<": "<<"-"<<key<<" ";
if(!option.empty())
     std::cout<<"-"<<option<<" ";
std::cout<<comand<<" "<<tm<<"\n";

return 0;
}

//const char* read_token(char* const t)
//{


//}
