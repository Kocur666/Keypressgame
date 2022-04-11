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

void SortFileTopScore();
void PlayGame();
void ShowMainMenu();
void ShowTopScore();
void InitiateTest();
void SaveTopScoreToFile();
void ShowMainMenu(){

clear();
printf("--------------------------------------\n");
printf("1.  Play New game                     \n");
printf("2.  Show Top scores                   \n");
printf("3.  Change config files               \n");
printf("4.  Change Name                       \n");
printf("ESC EXIT GAME                         \n");
printf("                                      \n");
printf("Yourname: %s        \n", Nickname.c_str());
printf("--------------------------------------\n");

switch(int ex = getch())
    {
        case 49:
            clear();
            printf("--------------------------------------\n");
            printf("1.  Play Level 1 Easy                 \n");
            printf("2.  Play Level 2 Medium               \n");
            printf("3.  Play Level 3 Hard                 \n");
            printf("                                      \n");
            printf("ESC EXIT                              \n");
            printf("                                      \n");
            printf("Yourname: %s        \n", Nickname.c_str());
            printf("--------------------------------------\n");
            switch(int ex2 = getch())
                {
                case 49:
                    PlayGame(writeword_lev1, 1);
                    break;
                case 50:
                    PlayGame(writeword_lev2, 2);
                    break;
                case 51:
                    PlayGame(writeword_lev3, 3);
                    break;
                case 27:
                    clear();
                    cout << endl << "Pressed ESC" << endl;  // key esc
                    break;
                default:
                    clear();
                    cout << endl << "Wrong key pressed - Aborting" << endl;  // not those keys
                    break;
                }
            break;
        case 50:
clear();
            printf("--------------------------------------\n");
            printf("1.  Show Easy Top Score               \n");
            printf("2.  Show Medium Top Score             \n");
            printf("3.  Show Hard Top Score               \n");
            printf("4.  Show All in One Top Score         \n");
            printf("ESC EXIT                              \n");
            printf("                                      \n");
            printf("Yourname: %s        \n", Nickname.c_str());
            printf("--------------------------------------\n");
            switch(int ex2 = getch())
                {
                case 49:
                    clear();
                    ShowTopScore(1);
                    break;
                case 50:
                    clear();
                    ShowTopScore(2);
                    break;
                case 51:
                    clear();
                    ShowTopScore(3);
                    break;
                case 52:
                    clear();
                    ShowTopScore();
                    break;
                case 27:
                    clear();
                    cout << endl << "Pressed ESC" << endl;  // key esc
                    break;
                default:
                    clear();
                    cout << endl << "Wrong key pressed - Aborting" << endl;  // not those keys
                    break;
                }
            break;
        case 51:
            clear();
            printf("USE  BOOLD in Terminal is set to: %s \n", UseBoold ? "true" : "false");
            printf("DEBUG MODE is set to: %s \n", DebugMode ? "true" : "false");
            cout << "----------------------------------" <<endl;
            cout << "Set UseBoold to false    press 0" <<endl;
            cout << "Set UseBoold to true     press 1" <<endl;
            cout << "Set DebugMode to false   press 2" <<endl;
            cout << "Set DebugMode to true    press 3" <<endl;
            cout << "Save configuration file  press 4" <<endl;
            cout << "Exit menu              press ESC" <<endl;
            switch(int ex2 = getch())
                {
                case 48:
                    UseBoold = 0;
                    cout << "Use Boold set to False" << endl;
                    break;
                case 49:
                    UseBoold = 1;
                    cout << "Use Boold set to True" << endl;
                    break;
                case 50:
                    DebugMode = 0;
                    cout << "Debug Mode set to False" << endl;
                    break;
                case 51:
                    UseBoold = 1;
                    cout << "Debug Mode set to true" << endl;
                    break;
                case 52:
                    cout << "Saving Config file" << endl;                
                    SaveCfgFile();
                    break;
                default:
                    clear();
                    cout << endl << "Wrong key pressed - Aborting" << endl;  // not those keys
                    break;
                }
            break;
        case 52:
            clear();
            cout << endl << "Write Your Name:" << endl;  // key 3
            cin >> Nickname ;
            break;
        case 57:    //Hidden menu 9 - test functions
            clear();
            cout << endl << "Test submenu" << endl;  // key 9
            InitiateTest();
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
    } else {
       // SortFileTopScore();
    }
}



#endif