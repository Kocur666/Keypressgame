#ifndef MENUS_H
#define MENUS_H

#include "constants.h"
#include "functions.h"
#include <conio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sysinfoapi.h>
#include <windows.h>

void ShowMainMenu(){

clear();
printf("--------------------------------------\n");
printf("1.  Play New game                     \n");
printf("2.  Show Top scores                   \n");
printf("3.  Change config files               \n");
printf("ESC EXIT GAME                         \n");
printf("--------------------------------------\n");

switch(int ex = getch())
    {
        case 49:
            clear();
            cout << endl << "Pressed 1" << endl;//key 1
            PlayGame();
            break;
        case 50:
            clear();        
            ShowTopScore();
            break;
        case 51:
            clear();
            cout << endl << "Pressed 3" << endl;  // key 3
            cout << "Not implemented yet" <<endl;
            Wynik();
            break;
        case 27:
            clear();
            escape = 1;
            cout << endl << "Pressed ESC" << endl;  // key esc
            break;
        default:
            clear();
            cout << endl << "Wrong key pressed" << endl;  // not those keys
            ShowMainMenu();
            break;
    }
    if (escape!=1){
        ShowMainMenu();
    }
}



#endif