#include <iostream>
#include <vector>
using namespace std;

template<typename V>
class Dictionary{
private:
    vector<pair<int,V>> table;
    int size = 0;
public:
    Dictionary(int s);
    int HashFunction(int k, int i);
    
    typename vector<pair<int,V>>::iterator search(int key) const; 
    bool insert(int key, V value);
    bool remove(int key);

    void print() const;
};

template<typename V>
Dictionary<V>::Dictionary(int s){
    for(int i=0;i<s;i++){
        pair<int,V> temp = {-1, V()};
        table.push_back(temp);
    }
}

template<typename V>
int Dictionary<V>::HashFunction(int k, int i){
    int m =  table.size();
    int h1 = k % m;
    int h2 = i * (1 + (k % (m-1)));
    int h = (h1 + h2) % m;
    return h;
}


template<typename V>
typename vector<pair<int,V>>::iterator Dictionary<V>::search(int key) const{
    int i = 0;
    while(true){
        int hash = HashFunction(key, i);
        if(table[hash].first == -1){
            return table.end();
        }else if(table[hash].first == key){
            return table.begin() + hash;
        }
        i++;
    }
}

template<typename V>
bool Dictionary<V>::insert(int key, V value){
    int i = 0;
    while(true){
        int hash = HashFunction(key, i);
        if(table[hash].first == -1){
            table[hash].first = key;
            table[hash].second = value;
            size++;
            return true;
        }else if(table[hash].first == key){
            table[hash].second = value;
            return true;
        }
        i++;
    }

    return false;
}

template<typename V>
bool Dictionary<V>::remove(int key){
    int i = 0;
    while(true){
        int hash = HashFunction(key, i);
        if(table[hash].first == key){
            table[hash].first = -1;
            table[hash].second = V();
            size--;
            return true;
        }
        i++;
    }
    return false;
}

template<typename V>
void Dictionary<V>::print() const{
    for(auto i : table){
        if(i.first == -1){
            cout << "nill ";
        }else{
            cout << "K:" << i.first << " " << "V:" << i.second << " ";
        }
    }
    cout << endl;
}

int main(){
    vector<int> keys(10);
    vector<float> values {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};

    Dictionary<float> dict(19);

    for(int i = 0; i < 10; i++){
        cin >> keys[i];
    }
    for(int i = 0; i < 10; i++){
        dict.insert(keys[i], values[i]);
    }
    dict.print();

    dict.remove(keys[6]);
    dict.insert(keys[2], 1.1);
    dict.print();
    return 0;
}