#include <conio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sysinfoapi.h>
#include <windows.h>
using namespace std;

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ESC 27

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
    int character=0xB0;
    for(int x =0; x < size(writeword); x++) {
        if(writeword[x]==32){
            if(x==NrLiterki){
                cout << (char)character;
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
int character=0xB0;
    if(writeword[NrLiterki]==32){
        cout << (char)character;
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

int main()
{
    int c, ex;
    int escape = 0;
    int NrLiterki =0;
    int IsCorrect =0;
    char CharNeeded {};
    DWORD TimeStart = GetTickCount();    
    DWORD old = GetTickCount();
    DWORD Runtime{};
    string writeword {"A jakby tak podejsc z dupy strony ktora i tak nie jest zbyt dobra strona patrzac obiektywnie"};
    clear();
    while(1)
    {
     //   cout << "Wpisz jak najszybciej haslo: " << endl << bold_on << writeword << bold_off << endl;
        for(NrLiterki =0; NrLiterki < size(writeword); NrLiterki++) {
            clear();
            cout << "Nacisnij teraz: ";
            PrintSpace (NrLiterki, writeword);
            cout << endl << "Wpisz jak najszybciej haslo: " << endl;
            ShowBolded(NrLiterki, writeword);       
            c = getch();
            if(NrLiterki==0){
                old = GetTickCount();
            }
            if (c==27){
                escape =1;
                cout << "Exiting..." << endl;
                break;
            }
            else if (c==writeword[NrLiterki]){
                //clear();
                // cout << "Nacisnij teraz: ";
                //PrintSpace (NrLiterki+1, writeword); 
                //cout << endl;
                //timecheck(old);
            }
            else {
                //clear();
                //cout << "Nacisnij teraz: ";
                //PrintSpace(NrLiterki, writeword);
                //cout << endl;
                NrLiterki-- ;
            }
        }
        clear();
        Runtime = (GetTickCount()- old);
        cout << "Haslo wpisane w czasie: " << bold_on << Runtime << bold_off << " ms.\n";
        cout << "Srednia: " << (Runtime/size(writeword)) << " ms na znak" << endl;
        if(escape==1) break;  // If escape was pressed - we will leave loop
        Sleep(7000);
    }
    // Showing runtime
    Runtime = (GetTickCount()- TimeStart);
    cout << "Program pracowal:" << Runtime << " milisekund lub inaczej: " << bold_on << (Runtime/1000) << " pelnych sekund" << bold_off << endl;
    return 0;
}