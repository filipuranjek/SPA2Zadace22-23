#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
class Graph
{
private:
    vector<vector<int>> AMatrix;

    int totalWeightOfGraph(vector<vector<int>> adjMatrix)
    {
        int totalweight = 0;
        int n = adjMatrix.size();

        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                    totalweight += adjMatrix[i][j];

        return totalweight;   
    }

    void printGraph(vector<vector<int>> adjMatrix)
    {
        int n = adjMatrix.size();
        
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if(adjMatrix[i][j] != 0)
                    cout << i << " - " << j << " (" << adjMatrix[i][j] << ")" << endl; 
    }
    
public:

    Graph(vector<vector<int>> &adjMatrix)
    {
		AMatrix = adjMatrix;
    }

    int GraphWeight()
    {
        return totalWeightOfGraph(AMatrix);
    }

    void print()
    {
        printGraph(AMatrix);
    }

    int minDist(vector<int> dist, vector<bool> visited){
        int min = 1e9;
        int min_index;

        for(int i=0; i<AMatrix.size();i++){
            if(visited[i] == false && dist[i] <= min){  // ako vrh nije posjecen i ako je manji od trenutnog min
                min = dist[i];
                min_index = i;
            }
        }

        return min_index;
    }

    void dijkstra(int start, int end){
        int n = AMatrix.size();

        vector<int> dist(n, 1e9);
        vector<bool> visited(n, false);

        dist[start] = 0;

        for(int i=0; i<n-1; i++){
            int u = minDist(dist, visited);

            visited[u] = true;

            for(int j=0; j<n; j++){
                if(!visited[j] && AMatrix[u][j] && dist[u] != 1e9 && dist[u] + AMatrix[u][j] < dist[j]){
                    dist[j] = dist[u] + AMatrix[u][j];
                }
            }

        }
        cout << dist[end] << endl;
    }
};

int main()
{
    int n, k, l, r, w, s, f;
    cin >> n >> k >> s >> f;

    vector<vector<int>> Matrix(n, vector<int>(n, 0));

    for (int i = 0; i < k; ++i) {
        cin >> l >> r >> w;
        Matrix[l - 1][r - 1] = w + 12;
        Matrix[r - 1][l - 1] = w + 12;
    }
    
    Graph g(Matrix);

    g.dijkstra(s-1,f-1);
    

    return 0;
}
