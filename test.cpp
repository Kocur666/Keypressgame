#include <conio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sysinfoapi.h>
#include <windows.h>
#include <vector>
#include <climits>
#include <fstream>
#include <variant>

using namespace std;



/*
class Wynik {
private:
    static std::vector<Wynik*> objList;
public:
    static std::vector<Wynik*> getAllObjects(){
        return objList;
    }
    Wynik(){
        objList.push_back(this);
        Name = "Default";
        Score = 0;
    }
    Wynik(DWORD Score_param){
        objList.push_back(this);
        Name = "Default";
        Score=Score_param;
    }
    Wynik(DWORD Score_param, string Name_param){
        objList.push_back(this);
        Name = Name_param;
        Score = Score_param;
    }
    std::string Name;
    DWORD Score;
}; */

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

main(){

string line;
ifstream inFile;
    inFile.open("top.txt");
    if (inFile.is_open()) {
        std::vector<std::pair<int, std::string> > score_vector;
        std::string name;
        long int score;
        while (inFile >> name >> score) {
            score_vector.push_back(std::make_pair(score, name));
            std::cout << line << '\n';
        }
        inFile.close();
        std::sort(score_vector.begin(), score_vector.end());

        for(auto it = score_vector.begin(); it != score_vector.end(); ++it){
            std::cout << "Name: " << it->second << " Score: " << it->first << std::endl;
        }
    }
    else
        std::cout << "Unable to open text";


 Wynik(5546456, "Adam");
 Wynik(554646, "Adam");
 Wynik(556456, "Adam");
 Wynik(55646, "Adam");
 Wynik(5546, "Adam");



 for (int i=0;i<Wynik::getAllObjects().size();i++){
     cout << Wynik::getAllObjects()[i]->Name << " " << Wynik::getAllObjects()[i]->Score << endl;
  // std::cout<<Wynik::getAllObjects()[i]<<std::endl;
 }
}