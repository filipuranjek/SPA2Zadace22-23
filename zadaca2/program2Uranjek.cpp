#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class usernameHash{
private:
    vector<bool> table;
public:
    usernameHash(int m){
        table.resize(m,0);
    }

    int h1(const string& s);
    int h2(const string& s);
    int h3(const string& s);
    int h4(const string& s);

    void insert(const string& s);
    void search(const string& s);

};

int usernameHash::h1(const string& s){
    unsigned long long int ret = 0;
    int m = table.size();
    for(int i=0; i<s.length(); i++){
        ret += (s[i] % m); 
    }

    return ret % m;
}

int usernameHash::h2(const string& s){
    unsigned long long int ret = 1;
    int m = table.size();
    for(int i=0;i<s.length();i++){
        ret += s[i] * pow(19,i);
        ret %= m;
    }

    return ret % m;
}

int usernameHash::h3(const string& s){
    unsigned long long int ret = 7;
    int m = table.size();
    for(int i=0;i<s.length();i++){
        ret += s[i] * pow(30,i);
        ret %= m;
    }

    return ret % m;
}

int usernameHash::h4(const string& s){
    unsigned long long int ret = 3;
    int p = 7;
    int m = table.size();
    for(int i=0;i<s.length();i++){
        ret += s[i] * pow(3,i) * pow(p,i);
        ret %= m;
    }

    return ret % m;
}

void usernameHash::search(const string& s){
    int index1 = h1(s);
    if(table[h1(s)] == true && table[h2(s)] == true && table[h3(s)] == true && table[h4(s)] == true){
        cout << "Element je vjerojatno u tablici" << endl;
    }else{
        cout << "Element nije u tablici" << endl;
    }
}

void usernameHash::insert(const string& s){
    int index1 = h1(s);
    int index2 = h2(s);
    int index3 = h3(s);
    int index4 = h4(s);

    table[index1] = 1;
    table[index2] = 1;
    table[index3] = 1;
    table[index4] = 1;
}


int main(){
    usernameHash db(100);

    vector<string> names = {
        "jopis107", "hstranput", "Matej293", "MateaCucman", "JosipCestar", 
        "lanamak", "DanijelaValjak", "filipuranjek", "domagojziros", "lsanic",
        "TomislavVinkovic", "IvoSusac", "matej2810", "KresimirSecan", 
        "inespejic", "InesSimunovic", "IvanFrantal", "Frle001", "inesstrapac", 
        "mkolak", "Dpritisa", "istvavk", "mtoldi", "lbrodar5", "mkristic", 
        "andreamatasovic", "balentovicanja", "IvanaVinkovic", "prakidzija", 
        "DMV1204", "JMesaric", "KarloKampic", "jurick1910", "LarisaDarojkovic"
    };

    for(auto& name : names) {
        db.insert(name);
    }

    db.search("jopis107");
    db.search("ivosulinjo");
    db.search("braneBB");
    db.search("ludiIstva23");
    db.search("akiKawasaki");
    
    return 0;
}