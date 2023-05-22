#include <iostream>
#include <vector>

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
            for (int j = 0; j < n; ++j)
                if(j + i < n)
                    totalweight += adjMatrix[i][j + i];

        return totalweight;   
    }

    void printGraph(vector<vector<int>> adjMatrix)
    {
        int n = adjMatrix.size();
        
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                if(adjMatrix[i][j + i] != 0  && j + i < n)
                    cout << i << " - " << j + i << " (" << adjMatrix[i][j + i] << ")" << endl;
        } 
    }
    
    pair<int, int> findMinWeightIndex(vector<int> visited)
    {
        //index i minvalue
        int index = 1e9;
        int minValue = 1e9;
        int start = 1e9;

        for (int i = 0; i < visited.size(); ++i)
        {
            if(visited[i] == 1)
            {
                for (int j = 0; j < visited.size(); ++j)
                {
                    if(AMatrix[i][j] != 0 && AMatrix[i][j] < minValue && visited[j] == 0)
                    {
                        minValue = AMatrix[i][j];
                        index = j;
                        start = i;
                    }
                }
            }
        }
        
        return make_pair(start, index);
    }

    int find(int i, vector<int> &parent)
    {
        while(parent[i] != i)
            i = parent[i];

        return i;
    }

    void union_new(int i, int j, vector<int> &parent)
    {
        int a = find(i, parent);
        int b = find(j, parent);

        parent[a] = b;
    }

public:

    //konstruktor, paziti na kopiranje
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

    Graph primMST()
    {
        //pokupi dimenziju grafa nad kojim radimo mst
        int n = AMatrix.size();

        //napravi praznu matricu susjedstava
        vector<vector<int>> matrix(n, vector<int>(n, 0));

        //indikatori posjecenosti
        vector<int> visited(n, 0);

        //proizvoljno posjecen vrh, nije bitno ali krecemo od 0
        visited[0] = 1;

        //ponavljaj n - 1 puta jer imamo jednog dodanog vec
        for(int i = 0; i < n - 1; ++i)
        {
            //spremi dobivene vrijednosti
            pair<int, int> start_minIndex = findMinWeightIndex(visited);
            int start = start_minIndex.first, minIndex = start_minIndex.second;

            //spremi second kao novi visited, lijevi je uvijek visited
            visited[minIndex] = 1;

            //ispuni novu matricu 
            matrix[start][minIndex] = AMatrix[start][minIndex];
            matrix[minIndex][start] = AMatrix[minIndex][start];

        }

        //napravi novi graf
        Graph MSTG(matrix);

        //vrati graf
        return MSTG;        
    }

    Graph kruskalMST()
    {
        int n = AMatrix.size();
        //random counter samo
        int k = 0;

        //prazna matrica susjedstava i parent array za cuvanje informacije
        //koji su elementi u kojem skupu
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        vector<int> parent(n);

        //napravi parent array tako da je svako svoj predstavnik
        for(int i = 0; i < n; ++i)
            parent[i] = i;

        //ponavljaj petlju n - 1 puta
        while(k < n - 1)
        {
            int a = -1;
            int b = -1;
            int minValue = 1e9;
            //iteriraj po grafu i to po gornjoj dijagonali
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    //postoji brid izmedju i-j, nisu spojeni, brid ima manji value nego minimum trenutni
                    if(AMatrix[i][j + i] != 0 && (j + i < n) && (find(i, parent) != find(j + i, parent)) && AMatrix[i][j + i] < minValue)
                    {
                        //setaj minvalue, pokupi i,j u a i b varijable
                        minValue = AMatrix[i][j + i];
                        a = i;
                        b = j + i;
                    }
                }
            }

            //unija dva koja nisu u istom setu
            union_new(a, b, parent);

            //ispunjavanje nove matrice
            matrix[a][b] = AMatrix[a][b];
            matrix[b][a] = AMatrix[b][a];

            k++;
        }

        //napravi novi graf
        Graph MSTG(matrix);

        //vrati graf
        return MSTG;
    }
};

int main()
{

    vector<vector<int>> matrix(7, vector<int>(7, 0));
    
    matrix = {
        {0, 50, 60, 0, 0, 0, 0},
        {50, 0, 0, 120, 90, 0, 0},
        {60, 0, 0, 0, 0, 50, 0},
        {0, 120, 0, 0, 0, 80, 70},
        {0, 90, 0, 0, 0, 0, 40},
        {0, 0, 50, 80, 0, 0, 140},
        {0, 0, 0, 70, 40, 140, 0}
    };


    Graph g1(matrix);
    Graph g2(matrix); 

    Graph Prim_alg = g1.primMST(); 
    Graph Kruskal_alg = g2.kruskalMST();

    Prim_alg.print();

    cout << endl;
    
    Kruskal_alg.print();
    
}