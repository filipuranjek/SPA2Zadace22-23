#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class DSU
{
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n);
        for(int i=0; i<n; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }
    
    int find(int x)
    {
        if(parent[x] == x){
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if(x == y){
            return;
        }
        if(rank[x] < rank[y]){
            parent[x] = y;
        }
        else{
            parent[y] = x;
            if(rank[x] == rank[y]){
                rank[x]++;
            }
        }
    }
};

class Graph
{
private:
    vector<vector<int>> AMatrix;

    int totalWeightOfGraph(vector<vector<int>> adjMatrix)
    {
        int sum = 0;
        for(int i=0; i<adjMatrix.size(); i++){
            for(int j=0; j<adjMatrix[i].size(); j++){
                if(i <= j){
                    sum += adjMatrix[i][j];
                }
            }
        }
        return sum;
    }   

    void printGraph(vector<vector<int>> adjMatrix)
    {
        for(int i=0; i<adjMatrix.size(); i++){
            for(int j=0; j<adjMatrix[i].size(); j++){
                if(i <= j){
                    if(adjMatrix[i][j] != 0){
                        cout << i << "-->" << j << " w: " << adjMatrix[i][j] << endl;
                    }
                }
            }
        }
    }
    
    /* mjesto za pomoćne funkcije za algoritme
    
    
    
    
    
    */

public:

    //konstruktor, paziti na kopiranje
    Graph(vector<vector<int>> adjMatrix)
    {
        AMatrix.resize(adjMatrix.size());
        for(int i=0; i < adjMatrix.size(); i++){
            AMatrix[i].resize(adjMatrix[i].size());
            for(int j=0; j < adjMatrix[i].size(); j++){
                AMatrix[i][j] = adjMatrix[i][j];
            }
        }
    }

    int GraphWeight()
    {
        return(totalWeightOfGraph(AMatrix));
    }

    void print()
    {
        printGraph(AMatrix);
    }

    void primMST(Graph G)
    {

    }

    void kruskalMST(Graph G)
    {
        int n = AMatrix.size();
        vector<pair<int, pair<int, int>>> edges;
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                if(AMatrix[i][j] != 0){
                    edges.push_back({AMatrix[i][j], {i, j}});
                }
            }
        }
        
        // sort edges by weight
        sort(edges.begin(), edges.end());

        DSU dsu(n);
        vector<pair<int, int>> mst;
        
        for(auto edge: edges){
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            if(dsu.find(u) != dsu.find(v)){
                dsu.merge(u, v);
                mst.push_back({u, v});
            }
        }

        for(auto edge : mst){
            cout << edge.first << " " << edge.second << " ";
            cout << endl;
        }
    }

};

int main()
{
    //ovdje pretvoriti input u dvodimenzionalnu matricu i proslijediti konstruktoru
    //paziti na izgled matrice

    string filename = "inputgraph.txt";
    ifstream input;

    input.open(filename);
    
    if(!input.is_open()){
        return(1);
    }

    string line;
    getline(input, line);

    int vectorSize = line[0] - 48;
    int brojBridova = line[2] - 48;

    vector<vector<int>> Matrix(vectorSize, vector<int>(vectorSize, 0));

    while(input){
        string line;
        getline(input, line);

        if(line[4] != ' ' && brojBridova != 0){
            int n = line[0] - 48;
            int m = line[2] - 48;
            int w = line[4] - 48;
            
            brojBridova--;

            //cout << n  << " " << m << " " << w << endl;

            Matrix[n][m] = w;
            Matrix[m][n] = w;
        }
    }

    input.close();

    Graph g(Matrix);

    g.print();
    cout << endl;
    cout << g.GraphWeight() << endl;

    g.kruskalMST(g);

    return 0;
}