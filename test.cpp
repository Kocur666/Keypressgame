#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <conio.h>
#include <sysinfoapi.h>

using namespace std;

class MyClass{
private:
 static std::vector<MyClass*> objList2;
public:
 MyClass() {
  objList2.push_back(this);
 }
 static std::vector<MyClass*> getAllObjects(){
  return objList2;
 }
};


class Wynik {
private:
    static std::vector<Wynik*> objList;
public:
    static std::vector<Wynik*> getAllObjects(){
        return objList;
    }
    Wynik(){
        objList.push_back(this);
        Name = "Default";
        Score = 0;
    }
    Wynik(DWORD Score_param){
        objList.push_back(this);
        Name = "Default";
        Score=Score_param;
    }
    Wynik(DWORD Score_param, string Name_param){
        objList.push_back(this);
        Name = Name_param;
        Score = Score_param;
    }
    std::string Name;
    DWORD Score;
};
std::vector<Wynik*> Wynik::objList;

std::vector<MyClass*> MyClass::objList2;


main(){
 MyClass m,a,g,h,t,s;
 Wynik aa, bb, cc, dd, ee;
 Wynik(5546456, "Adam");

 for (int i=0;i<Wynik::getAllObjects().size();i++){
     cout << Wynik::getAllObjects()[i]->Name << " " << Wynik::getAllObjects()[i]->Score << endl;
  // std::cout<<Wynik::getAllObjects()[i]<<std::endl;
 }
}