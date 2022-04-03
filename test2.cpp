#include <iostream>
#include <vector>
using namespace std;

class Site {
public:
    int i;
};

int main() {
    vector<Site> listofsites;
    Site *s1 = new Site;
    s1->i = 7;
    Site *s2 = new Site;
    s2->i = 9;
    listofsites.push_back(*s1);
    listofsites.push_back(*s2);
    vector<Site>::iterator it;
    for (it = listofsites.begin(); it != listofsites.end(); ++it) {
        cout << it->i;
    }
    return 0;
}