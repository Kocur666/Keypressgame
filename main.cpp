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

void PlayGame();
void ShowMainMenu();
void ShowTopScore();
class Wynik;

int main()
{
    //Wynik aa, bb, cc, dd, ee; //populating Top Scores
    Wynik(63345266);
    Wynik(6345356);
    Wynik(5546456, "Adam");  //populating Top Scores
    clear();
    ShowMainMenu(); 

    // Showing runtime
    Runtime = (GetTickCount()- TimeStart);
    cout << "Program pracowal:" << Runtime << " milisekund lub inaczej: " << bold_on << (Runtime/1000) << " pelnych sekund" << bold_off << endl;
    return 0;
}