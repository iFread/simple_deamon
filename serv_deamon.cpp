#include "cored.h"
#include <iostream>
#include <string>

int main(int argc,char*argv[])
{

core::m_clock random(12,23,15);
core::m_clock cur(time(0));
core ::m_clock ziro;

//std::cout<<random<<"\n";
//std::cout<<cur<<"\n";
//std::cout<<ziro<<"\n";

std::string s;
int n=0;
while (n<3) {


std::cin>>s>>ziro;

std::cout<<ziro<<" "<<s<<"\n";
s.clear();
++n;}
return 0;
}
