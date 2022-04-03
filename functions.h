#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "constants.h"
#include <conio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sysinfoapi.h>
#include <windows.h>

using namespace std;

std::ostream& bold_on(std::ostream& os)
{
return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
return os << "\e[0m";
}

void timecheck(DWORD &old){
    DWORD NewTime = GetTickCount();
    DWORD DiffTime = NewTime - old;
    cout << "Passed ms: " << DiffTime << endl;
}

void ShowBolded(int NrLiterki, string writeword){
    for(int x =0; x < size(writeword); x++) {
        if(writeword[x]==32){
            if(x==NrLiterki){
                cout << (char)falseSpace;
            }
            else {
                cout << " " ;
            }
        }
        else{
        if(x==NrLiterki){
                cout << bold_on << writeword[x] << bold_off;
            }
            else {
                cout << writeword[x];
            }    
        }
    }
}

void PrintSpace(int NrLiterki, string writeword){
    if(writeword[NrLiterki]==32){
        cout << (char)falseSpace;
    }
    else {
        cout << bold_on << writeword[NrLiterki] << bold_off;
    }
}

void clear() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

#endif