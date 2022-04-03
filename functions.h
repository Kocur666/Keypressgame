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
#include <algorithm>

using namespace std;

string Nickname {"Player1"};
int c, ex;
int escape, GraSkonczona = 0;
int NrLiterki =0;
int IsCorrect =0;
char CharNeeded {};
bool UseBoold =1;
DWORD TimeStart = GetTickCount();    
DWORD old = GetTickCount();
DWORD Runtime{};

void SortFileTopScore();
void PlayGame();
void ShowMainMenu();
void ShowTopScore();
void LoadTopScore();
class Wynik;

string writeword {"A jakby tak podejsc"};  //Main text to write to check speed

class Wynik {
private:
    static vector<Wynik> objList;
public:
    static vector<Wynik> getAllObjects(){
        std::sort(objList.begin(), objList.end(), [](Wynik & one, Wynik & two){return one.Score < two.Score;}); 
        return objList;
    }
    Wynik(){
        Name = "Default";
        Score = 0;
        objList.push_back(*this);
    }
    Wynik(long int Score_param){
        Name = "Default";
        Score=Score_param;
        objList.push_back(*this);
    }
    Wynik(long int Score_param, string Name_param){
        Name = Name_param;
        Score = Score_param;
        objList.push_back(*this);
    }
    void Print(){
        cout << "Player: " << this->Name;
        for(int i=0; i<(15 - this->Name.size()); i++){ //Lined to 15 char Name
            cout << " ";
        }
        cout << " Score: "; //Lined to 10 chars Score
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

void LoadTopScore(){
    string Name;
    long int Score;
    fstream file ("top.txt", std::ofstream::in);
    if (file.is_open()){
    auto Wersy = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
    file.seekg(0);
    for (int i=0; i < (Wersy +1); i++){
        file >> Name >> Score;
        Wynik* set1 = new Wynik (Score, Name);   
    }
    } else {
        cout << "Cannot open Top Scores file to load.\n";
    }
    file.close();
}

vector<Wynik> Wynik::objList; // for Wynik class declaration

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

void ShowBolded(int NrLiterki, string writeword, bool UseBoold){ //Show bolded type to text with bolded char to paste
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
                if(UseBoold){
                cout << bold_on << writeword[x] << bold_off;
                }
                else {
                cout << writeword[x];   
                }
            }
            else {
                cout << writeword[x];
            }    
        }
    }
}

void PrintSpace(int NrLiterki, string writeword, bool UseBoold){ //Shows space as falseSpace character and bolds other chars for single char show
    if(writeword[NrLiterki]==32){
        cout << (char)falseSpace;
    }
    else {
        if (UseBoold) {
            cout << bold_on << writeword[NrLiterki] << bold_off;
        }
        else {
            cout << writeword[NrLiterki];
        }
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
            cout << "Now press: ";
            PrintSpace (NrLiterki, writeword, UseBoold);
            cout << endl << "Paste as fast as You can: " << endl;
            ShowBolded(NrLiterki, writeword, UseBoold);       
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
            if (UseBoold){
                cout << "Pharse written in: " << bold_on << Runtime << bold_off << " ms.\n";
            }
            else {
                cout << "Pharse written in: " << Runtime << " ms.\n";
            }
            cout << "Average: " << (Runtime/size(writeword)) << " ms per char" << endl;
            Wynik *new1 = new Wynik ((Runtime), Nickname);
            new1->Save();
            Sleep(1000);
        } else {
            cout << "Game was interrupted." << endl;
        }
    }

void ShowTopScore(){
    vector<Wynik>::iterator it;
    int pager = 0;
    auto list = Wynik::getAllObjects();
    clear();
    cout << "--------       TOP SCORE      ----------" << endl;
    for (it = list.begin(); it!=list.end(); ++it ){
        pager++;
        it->Print();
        if(pager==20){
            pager=0;
            cout << "Press any key to show more." << endl;
            getch();
        }
    }
    cout << "Press any key to continue." << endl;
    getch();
} 

void SortFileTopScore(){
    string line;
    fstream inFile;
    inFile.open("top.txt");
    if (inFile.is_open()) {
        std::vector<std::pair<int, std::string> > score_vector;
        std::string name;
        long int score;
        while (inFile >> name >> score) {
            score_vector.push_back(std::make_pair(score, name));
            std::cout << line << '\n';
        }
        std::sort(score_vector.begin(), score_vector.end());
            inFile.clear();
            inFile.seekg(0);
        for(auto it = score_vector.begin(); it != score_vector.end(); ++it){
            inFile << it->second << " " << it->first << endl;
        }
    }
    else
        std::cout << "Unable to open top.txt";
    inFile.close();
}

#endif 