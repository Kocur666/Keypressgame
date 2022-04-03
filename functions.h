#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "constants.h"
#include "menus.h"
#include <conio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sysinfoapi.h>
#include <windows.h>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

int c, ex;
int escape, GraSkonczona = 0;
int NrLiterki =0;
int IsCorrect =0;
char CharNeeded {};
DWORD TimeStart = GetTickCount();    
DWORD old = GetTickCount();
DWORD Runtime{};

void PlayGame();
void ShowMainMenu();
void ShowTopScore();
class Wynik;

string writeword {"A jakby tak podejsc"};

class Wynik {
private:
    static vector<Wynik*> objList;
public:
    static vector<Wynik*> getAllObjects(){
        return objList;
    }
    Wynik(){
        objList.push_back(this);
        Name = "Default";
        Score = 0;
    }
    Wynik(long int Score_param){
        objList.push_back(this);
        Name = "Default";
        Score=Score_param;
    }
    Wynik(long int Score_param, string Name_param){
        objList.push_back(this);
        Name = Name_param;
        Score = Score_param;
    }
    void Print(){
        cout << "Gracz: " << this->Name;
        for(int i=0; i<(15 - this->Name.size()); i++){ //Lined to 15 char Name
            cout << " ";
        }
        cout << " Wynik: "; //Lined to 10 chars Score
        int digits = 0;
        int check = this->Score;
        if (check == 0) digits = 1;
        while (check) {
            check /= 10;
            digits++;
        }
        for (int i=0; i<(10-digits); i++){
            cout << " ";
        }  
        cout << this->Score << endl;
    }
    void Save(){
        fstream file ("top.txt", std::ofstream::out | std::ofstream::app);
        if (file.is_open()){
        file << this->Name << " " << this->Score << endl;
        file.close();
        } else {
            cout << "Cannot open Top Scores file to save.\n";
        }
    }
    string Name;
    long int Score;
};

vector<Wynik*> Wynik::objList; // for Wynik class declaration

std::ostream& bold_on(std::ostream& os)  // bolding terminal characters
{
return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)  // unbolding terminal characters
{
return os << "\e[0m";
}

void timecheck(DWORD &old){  // checking time passed in ms using windows.h ticker
    DWORD NewTime = GetTickCount();
    DWORD DiffTime = NewTime - old;
    cout << "Passed ms: " << DiffTime << endl;
}

void ShowBolded(int NrLiterki, string writeword){ //Show bolded type to text with bolded char to paste
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

void PrintSpace(int NrLiterki, string writeword){ //Shows space as falseSpace character and bolds other chars for single char show
    if(writeword[NrLiterki]==32){
        cout << (char)falseSpace;
    }
    else {
        cout << bold_on << writeword[NrLiterki] << bold_off;
    }
}

void clear() { //Clear screen and go to 0,0 on windows
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

void PlayGame(){
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
                GraSkonczona=0;
                cout << "Exiting..." << endl;
                break;
            }
            else if (c!=writeword[NrLiterki]){
                NrLiterki-- ;
            }
            else {
                GraSkonczona = 1;
            }
        }
        clear();
        Runtime = (GetTickCount()- old);
        if (GraSkonczona == 1){
            cout << "Haslo wpisane w czasie: " << bold_on << Runtime << bold_off << " ms.\n";
            cout << "Srednia: " << (Runtime/size(writeword)) << " ms na znak" << endl;
            //Wynik(500,"Gracz1"); //why crashing system ???
            Wynik* new1 = new Wynik ((Runtime),"Gracz1");
            Sleep(1000);
        } else {
            cout << "Przerwana gra." << endl;
        }
    }

void ShowTopScore(){
    Wynik *Wynik_pointer;
    cout << "------------Top Scores---------------" <<endl;
    for (int i=0;i<Wynik::getAllObjects().size();i++){
        //cout << Wynik::getAllObjects()[i]->Name << " " << Wynik::getAllObjects()[i]->Score << endl;
        //cout << "ilosc objektow: " <<Wynik::getAllObjects().size() << endl;
        Wynik_pointer = Wynik::getAllObjects()[i];
        Wynik_pointer->Print();
        Wynik_pointer->Save();
        //cout << Wynik_pointer->Print() << " " << Wynik_pointer->Name << " " << Wynik_pointer->Score <<endl;
    }
    cout << "Aby wyjsc nacisnij dowolny klawisz." << endl;
    getch();
} 
#endif 