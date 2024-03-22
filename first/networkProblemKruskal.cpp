#include <vector>
#include<iostream>
#include <algorithm>
#include<stdio.h>
using namespace std;

bool compare(vector<int> a, vector<int> b) {
    return a[2] < b[2];
}

// 并查集的查找函数
int findParent(int v, vector<int>& parent) {
    if (parent[v] == -1)
        return v;
    return findParent(parent[v], parent);
}

// 并查集的合并函数
void unionVertices(int x, int y, vector<int>& parent) {
    int x_set = findParent(x, parent);
    int y_set = findParent(y, parent);
    parent[x_set] = y_set;
}

// Kruskal算法寻找最小生成树
void kruskalMST(vector<vector<int>>& edges, int V) {

    vector<int> parent(V, -1); // 记录每个顶点的父节点
    vector<vector<int>> result; // 存储最小生成树的边
    int court=0;

    int edgeCount = 0; // 已选择的边数
    for (const vector<int>& edge : edges) {
        if (edgeCount == V - 1)
            break;

        int x = findParent(edge[0], parent);
        int y = findParent(edge[1], parent);

        if (x != y) {
            result.push_back(edge);
            unionVertices(x, y, parent);
            edgeCount++;
            court+=edge[2];
        }
    }
    printf("%d",court);
}


int main(){
    int m,n;
    scanf("%d%d",&m,&n);
    vector<vector<int>>edges;
    for(int i=0;i<m;i++){
        int a;
        scanf("%d",&a);
        vector<int>edge;
        edge.push_back(m);
        edge.push_back(i);
        edge.push_back(a);
        edges.push_back(edge);
    }
    for(int i=0;i<n;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        vector<int>edge;
        edge.push_back(a);
        edge.push_back(b);
        edge.push_back(c);
        edges.push_back(edge);
    }


    sort(edges.begin(),edges.end(),compare);

    kruskalMST(edges, m+1);
}
