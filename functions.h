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
/// config variables
string Nickname {"Player1"};
bool UseBoold =1;  //config bool to use Bolded letters in terminal
bool DebugMode =1;  //config bool to set debug mode
/// ordinary variables
int c, ex;
int escape, GraSkonczona = 0;
int NrLiterki =0;
int IsCorrect =0;
char CharNeeded {};
DWORD TimeStart = GetTickCount();    
DWORD old = GetTickCount();
DWORD Runtime{};

void SortFileTopScore();
void PlayGame();
void ShowMainMenu();
void ShowTopScore();
void LoadTopScore();
std::ostream& bold_on(std::ostream& os)  // bolding terminal characters
{
return os << "\e[1m";
}
std::ostream& Redbold_on(std::ostream& os)  // bolding terminal characters
{
return os << "\e[1;31m";
}
std::ostream& bold_off(std::ostream& os)  // unbolding terminal characters
{
return os << "\e[0m";
}
class Wynik;

string writeword_lev1 {"Krotki tekst na poczatek"};  //Main text to write to check speed
string writeword_lev2 {"Wyindywidualizowalismy sie z rozentuzjazmowanego tlumu"};
string writeword_lev3 {"Wyindywidualizowalismy sie z rozentuzjazmowanego tlumu, ktory entuzjastycznie oklaskiwal przeliteraturalizowana i przekarykaturyzowana sztuke"};

//Classes

class Wynik {
private:
    static vector<Wynik> objList;
public:
    string Name;
    long int Score;
    int Level;

    static vector<Wynik> getAllObjects(){
        if(DebugMode) {
            cout << "DEBUG: Sorting all objects in Wynik list  --------" << endl;
            cout << "Object are in ObjList at adress: " << &objList << endl;
        }
        std::sort(objList.begin(), objList.end(), [](Wynik & one, Wynik & two){  //sorting bigger Level first, then Less Score = better
            return (two.Level < one.Level) || 
            ((one.Level == two.Level) && (one.Score < two.Score));
            });
        return objList;
    }
    Wynik();
    Wynik(long int Score_param);
    Wynik(long int Score_param, string Name_param);
    Wynik(long int Score_param, string Name_param, int Level_param);
    ~Wynik();
    void Print();
    void Save();
};

//declaring class functions

Wynik::Wynik(){
    Name = "Default";
    Score = 0;
    Level = 1;
    objList.push_back(*this);
    if(DebugMode) {
        cout << "DEBUG: Constructing() Class Wynik object: " << this << " with Name: " << this->Name << " and Score: " << this->Score << endl;
        cout << "Object push to list adress: " << &objList << endl;
    }
}

Wynik::Wynik(long int Score_param) : Score(Score_param) {
    Name = "Default";
    Level = 1;
    objList.push_back(*this);
    if(DebugMode) {
    cout << "DEBUG: Constructing(param) Class Wynik object: " << this << " with Name: " << this->Name << " and Score: " << this->Score << endl;
    cout << "Object push to list adress: " << &objList << endl;
    }
}
Wynik::Wynik(long int Score_param, string Name_param) : Name (Name_param) , Score(Score_param){
    objList.push_back(*this);
    if(DebugMode) {
        cout << "DEBUG: Constructing(param,param) Class Wynik object: " << this << " with Name: " << this->Name << " and Score: " << this->Score << endl;
        cout << "Object push to list adress: " << &objList << endl;
    }
}


Wynik::Wynik(long int Score_param, string Name_param, int Level_param) : Name (Name_param) , Score(Score_param) , Level(Level_param) {
    objList.push_back(*this);
    if(DebugMode) {
        cout << "DEBUG: Constructing(param,param) Class Wynik object: " << this << " with Name: " << this->Name << " and Score: " << this->Score << endl;
        cout << "Object push to list adress: " << &objList << endl;
    }
}

Wynik::~Wynik(){
    if(DebugMode) {
        cout << "DEBUG: Descruting Class Wynik object: " << this << " Name: " << this->Name << " Score: " << this->Score <<endl;
    }
}
void Wynik::Print(){
        if(UseBoold){
            if (this->Name==Nickname) {
            cout << "Player: " << Redbold_on << this->Name << bold_off;
            for(int i=0; i<(12 - this->Name.size()); i++){ //Lined to 12 char Name
                cout << " ";
            } 
            }else {
            cout << "Player: " << bold_on << this->Name << bold_off;
            for(int i=0; i<(12 - this->Name.size()); i++){ //Lined to 12 char Name
                cout << " ";
            }
            }
        } else {
            cout << "Player: " << this->Name;
            for(int i=0; i<(12 - this->Name.size()); i++){ //Lined to 12 char Name
                cout << " ";
            }
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
        if(UseBoold){
            cout << "\e[1m" << this->Score << "\e[0m";
        } else {
            cout << this->Score;
        }

        if(UseBoold){
            cout << "        Level: " << "\e[1m" << this->Level << "\e[0m" << endl;
        } else {
            cout << "        Level: " << this->Level << endl;
        }
}
void Wynik::Save(){
        fstream file ("top.txt", std::ofstream::out | std::ofstream::app);
        if (file.is_open()){
        file << this->Name << " " << this->Score << " " << this->Level << endl;
        file.close();
        } else {
            cout << "Cannot open Top Scores file to save.\n";
        }
}
// rest of non class functions
void LoadTopScore(){   //Loading top score from file top.txt
    string Name;
    long int Score;
    int Level;
    fstream file ("top.txt", std::ofstream::in);
    if (file.is_open()){
        auto Wersy = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
        file.seekg(0);
        for (int i=0; i < Wersy; i++){
            file >> Name >> Score >> Level;
            Wynik* set1 = new Wynik (Score, Name, Level);   
        }
    } else {
        cout << "Cannot open Top Scores file to load.\n";
    }
    file.seekg(ios_base::end);
    file.close();
}
void LoadCfgFile(){  //Loading configuration file
    string Name1, Name2, Name3;
    string enter1, enter2, enter3;
    bool val1, val2;
    string val3;
    fstream file ("configuration.cfg", std::ofstream::in);
    if (file.is_open()){
        file.seekg(0);
        file >> Name1 >> enter1 >> val1;
        file >> Name2 >> enter2 >> val2;
        file >> Name3 >> enter3 >> val3;
        if (Name1 == "UseBoold"){
            UseBoold = val1;
        } else {
            cout << "Cannot find UseBoold value in config file." << endl;
        }
            if (Name2 == "DebugMode"){
                DebugMode = val2;
            } else {
                cout << "Cannot find DebugMode value in config file." << endl;
            }
                if (Name3 == "Nickname"){
                    Nickname = val3;
                } else {
                    cout << "Cannot find Nickname value in config file." << endl;
                }
                    if(DebugMode) {
                        cout << "DEBUG: Loading configuration.cfg." << endl;
                    }  
    } else {
        cout << "Cannot open configuration.cfg file to load.\n";
    }
    file.seekg(ios_base::end);
    file.close();  
}
void SaveCfgFile(){  //Saving configuration file
        fstream file ("configuration.cfg", std::ofstream::out);
        if (file.is_open()){
        file << "UseBoold = " << UseBoold << endl;
        file << "DebugMode = " << DebugMode << endl;
        file << "Nickname = " << Nickname << endl;
            if(DebugMode) {
                cout << "DEBUG: Saving configuration.cfg." << endl;
            }
        file.close();
        } else {
            cout << "Cannot open Top Scores file to save.\n";
        }
    }

vector<Wynik> Wynik::objList; // for Wynik class declaration

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
                cout << Redbold_on << writeword[x] << bold_off;
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
            cout << Redbold_on << writeword[NrLiterki] << bold_off;
        }
        else {
            cout << writeword[NrLiterki];
        }
    }
}

void clear() { //Clear screen and go to 0,0 on windows
    if(DebugMode) {
            cout << "DEBUG: Disabled Clear()" << endl;
        }
    else {
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
}

void PlayGame(string writeword, int Lev){
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
                cout << "Pharse written in: " << Redbold_on << Runtime << bold_off << " ms.\n";
            }
            else {
                cout << "Pharse written in: " << Runtime << " ms.\n";
            }
            cout << "Average: " << (Runtime/size(writeword)) << " ms per char" << endl;
            Wynik *new1 = new Wynik ((Runtime), Nickname, Lev);
            new1->Save();
            Sleep(1000);
        } else {
            cout << "Game was interrupted." << endl;
        }
    }

void ShowTopScore(){    //Show top score for all levels at once
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

void ShowTopScore(int Lev){    // Shows Top Score for single level
    vector<Wynik>::iterator it;
    int pager = 0;
    auto list = Wynik::getAllObjects();
    clear();
    cout << "--------       TOP SCORE      ----------" << endl;
    for (it = list.begin(); it!=list.end(); ++it ){
        if(it->Level == Lev){
            pager++;
            it->Print();
            if(pager==20){
                pager=0;
                cout << "Press any key to show more." << endl;
                getch();
            }
        }
    }
    cout << "Press any key to continue." << endl;
    getch();
} 
/*
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
*/
#endif 