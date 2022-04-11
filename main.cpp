#include <conio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sysinfoapi.h>
#include <windows.h>
#include "constants.h"
#include "menus.h"
#include "functions.h"

using namespace std;

void SortFileTopScore();
void PlayGame();
void ShowMainMenu();
void ShowTopScore();
void SaveTopScoreToFile();
class Wynik;


int main()
{
    LoadCfgFile();
    clear();
    LoadTopScore();  // Load Top score from file top.txt
    ShowMainMenu();  // Shows Main menu

    // Showing runtime
    Runtime = (GetTickCount()- TimeStart);
    if (UseBoold){
        cout << "Program was running:" << Runtime << " miliseconds or less precise: " << bold_on << (Runtime/1000) << " full seconds" << bold_off << endl;
    }
    else {
        cout << "Program was running:" << Runtime << " miliseconds or less precise: " <<  (Runtime/1000) << " full seconds" << endl;
    }
    return 0;
}
void InitiateTest(){
   vector<Wynik>::iterator it;
    size_t pager = 0;
    //objList
    auto objList = Wynik::getAllObjects();
    cout << "--------       TEST SCORE      ----------" << endl;
    size_t i = 0;
    objList.push_back(Wynik(99999, "Name", 4, 90, 80, "Abrakadabra farba i babra Abrakadabra farba i babra Abrakadabra farba i babra Abrakadabra farba i babra "));
    for (it = objList.begin(); it!=objList.end(); ++it ){       
            cout << "Item nr: " << " Name: " << objList[i].Name << "Score: " << objList[i].Score << " " << endl;
            i++;
            }
    
    cout << "Press any key to continue." << endl;
    getch();

}