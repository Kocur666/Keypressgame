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
class Wynik;

int main()
{
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