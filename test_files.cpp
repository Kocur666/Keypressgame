
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


void LoadTopScore(){   //Loading top score from file top.txt
    string Name;
    long int Score;
    int Level;
    int Rps;
    size_t Word_length{};
    string Word_played_param{};
    fstream file ("top.txt", std::ofstream::in);
    if (file.is_open()){
        auto Wersy = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
        file.seekg(0);
        for (int i=0; i < Wersy/2; i++){
            file >> Name >> Score >> Level >> Rps >>Word_length;
            file.ignore();
            getline(file, Word_played_param);  //still now working
            cout << "Name: " << Name << " Score: " << Score << " Level: " << Level <<" RPS: " << Rps << " World_Length: " << Word_length;
            cout << "Loaded Word: " << Word_played_param << endl <<endl;
        }
    } else {
        cout << "Cannot open Top Scores file to load.\n";
    }
    file.seekg(ios_base::end);
    file.close();
}

int main(){
LoadTopScore();
    return 0;
}