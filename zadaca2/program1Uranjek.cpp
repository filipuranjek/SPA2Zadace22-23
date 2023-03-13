#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <math.h>
using namespace std;

class universalHash{
private:
    vector<list<pair<int,float>>> table {7};
    //default_random_engine generator; 
    //uniform_int_distribution<int> distribution;
    vector<int> probCoef;
public:
    universalHash();
    int hashFunction(int key);

    void insert(int key, float value);
    float search(int key);

    void printCoef() const;
    void printTable() const;
};

universalHash::universalHash(){
    default_random_engine generator; 
    uniform_int_distribution<int> distribution(0,6);
    generator = default_random_engine(time(0));

    for(int i=0;i<7;i++){
        probCoef.push_back(distribution(generator)); // generator ce generirat random broj uzeci u obzir unfiormnu distribuciju izmedju 0 i 6  
    }

}

void universalHash::printCoef() const{
    for(auto i : probCoef){
        cout << i << " ";
    }

    cout << endl;
}

int universalHash::hashFunction(int key){
    int sum = 0;
    int n = floor(log10(key));
    for(int i=0; i<=n;i++){
        int digit = key%10;
        sum += digit * probCoef[i];
        key /= 10;
    }

    return sum % 7;
}

void universalHash::insert(int key, float value){
    int index = hashFunction(key);
    pair<int,float> insert = {key, value};

    for(auto &i : table[index]){
        if(i.first == key){
            i.second = value;
            return;
        }
    }

    table[index].push_back(insert);
    return;
}

void universalHash::printTable() const{
    for(int i=0; i<7;i++){
        cout << "List" << endl;
        for(auto &j : table[i]){
            cout << "Key:" << j.first << " Value:" << j.second << " ";
        }
        cout << endl;
    }
}

float universalHash::search(int key){
    int index = hashFunction(key);
    for(auto &i : table[index]){
        if(i.first == key){
            return i.second;
        }
    }

    return -1e9;
}

int main(){

    universalHash H;
    //H.printCoef();

    auto generator = default_random_engine(time(0));
    auto distribute = uniform_real_distribution<float>(-1, 1);

    vector<int> keys = {
        127, 99, 331, 381, 35, 434, 372,
        72, 383, 12, 309, 500, 146, 81,
        132, 316, 222, 329, 15, 377, 92,
    };

    for(const auto& i : keys) {
        H.insert(i, distribute(generator)); 
    }

    H.printTable();
    cout << endl;
    cout << H.search(127) << endl;
    return 0;
}