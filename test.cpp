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

vector<Wynik> Wynik::objList; // for Wynik class declaration

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

vector<Wynik> listofWynik;

 Wynik *w1 = new Wynik(5546456, "Adam");
 listofWynik.push_back(*w1);
 Wynik *w2 = new Wynik(554645, "Adam1");
 listofWynik.push_back(*w2);
 Wynik *w3 = new Wynik(55464, "Adam2");
 listofWynik.push_back(*w3);
 Wynik *w4 = new Wynik(5546, "Adam3");
 listofWynik.push_back(*w4);
 Wynik *w5 = new Wynik(554, "Adam4");
 listofWynik.push_back(*w5);
 Wynik *w6 = new Wynik(55, "Adam5");
 listofWynik.push_back(*w6);
 std::sort(listofWynik.begin(), listofWynik.end(), [](Wynik & one, Wynik & two){return one.Score < two.Score;});
 vector<Wynik>::iterator it;

for (it = listofWynik.begin(); it!=listofWynik.end(); ++it){
    cout << it->Name <<" "<< it->Score << endl;
}
auto list = Wynik::getAllObjects();
for (it = list.begin(); it!=list.end(); ++it ){
    cout << it->Name <<" "<< it->Score << endl;
}
 //for (int i=0;i<Wynik::getAllObjects().size();i++){
 //    cout << *Wynik::getAllObjects()[i]->Name << " " << *Wynik::getAllObjects()[i]->Score << endl;
 //  std::cout<<Wynik::getAllObjects()[i]<<std::endl;
 //}
}