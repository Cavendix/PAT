#include <iostream>
#include <vector>
#include <climits>
#include <stdio.h>

using namespace std;

const int INF = INT_MAX;

// Floyd-Warshall 算法
void floydWarshall(vector<vector<int>>& graph,int n) {

    // 初始化距离矩阵和路径计数矩阵
    vector<vector<int>>dist = graph;
    vector<vector<long long>>count(n, vector<long long>(n, 0));
    vector<vector<vector<long long>>> through_k(n, vector<vector<long long>>(n, vector<long long>(n, 0)));

    // 初始化最短路径数目和经过某点的最短路径数目
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] != INF && i != j) {
                count[i][j] = 1;
            }
        }
    }

    // Floyd算法
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i!=j&&j!=k&&k!=i&& dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    count[i][j] = count[i][k] * count[k][j];
                }
                else if (i!=j&&j!=k&&k!=i&& dist[i][k] != INF && dist[k][j] != INF && dist[i][j] == dist[i][k] + dist[k][j]) {
                    count[i][j] += count[i][k] * count[k][j];
                }
            }
        }
    }

    // Floyd算法
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i!=j&&j!=k&&k!=i && dist[i][j] == dist[i][k] + dist[k][j]) {
                    through_k[i][j][k] = count[i][k] * count[k][j];
                }
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        double Influence=0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if(i!=j&&j!=k&&k!=i){
                    Influence += dist[i][j] * (static_cast<double>(through_k[i][j][k]) / count[i][j]);
                }  
            }
        }
        printf("%.3lf\n",Influence);
    }
}

int main() {
    int n, e;
    cin >> n >> e;
    
    vector<vector<int>> graph(n,vector<int>(n,INF));

    for(int i=0;i<n;i++){
        graph[i][i]=0;
    }
    
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u-1][v-1]=w;
        graph[v-1][u-1]=w;
    }

    floydWarshall(graph,n);
    return 0;
}
