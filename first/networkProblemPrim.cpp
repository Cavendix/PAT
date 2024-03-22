#include <vector>
#include<iostream>
#include <algorithm>
#include<stdio.h>
#include <climits>
using namespace std;

// 定义无限大的值，用于初始化距离数组
#define INF INT_MAX
int OverallWeight=0;

// 获取未包含在最小生成树中的顶点中距离树最近的顶点的索引
int minKey(vector<int>& key, vector<bool>& mstSet, int V) {
    int min = INF;
    int min_index;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    OverallWeight+=min;
    return min_index;
}

void primMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V);  // 存储最小生成树的边
    vector<int> key(V, INF);  // 存储顶点到最小生成树的最小距离
    vector<bool> mstSet(V, false);  // 用于标记顶点是否已包含在最小生成树中

    key = graph[0];  // 从第一个顶点开始构建最小生成树
    parent[0] = 0;  // 第一个顶点没有父节点
    mstSet[0]=true;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);  // 获取未包含在最小生成树中的顶点中距离树最近的顶点的索引
        mstSet[u] = true;  // 将该顶点标记为已包含在最小生成树中

        // 更新与顶点 u 相邻的顶点的距离
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("%d",OverallWeight);
}



int main(){
    int m,n;
    scanf("%d%d",&m,&n);
    vector<vector<int>>graph(m+1,vector<int>(m+1,INF));
    for(int i=0;i<m;i++){
        int a;
        scanf("%d",&a);
        graph[i][m]=a;
        graph[m][i]=a;

    }
    for(int i=0;i<n;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        graph[a][b]=c;
        graph[b][a]=c;

    }

    primMST(graph, m+1);
}
