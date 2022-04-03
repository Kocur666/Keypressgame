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
            else if (c!=writeword[NrLiterki]){
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