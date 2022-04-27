#include <limits.h>
#include <string.h>

#include <iostream>
#include <queue>
#include <ctime>
using namespace std;

#define V 7

// BFS(너비우선탐색) 알고리즘
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
  bool visited[V];
  memset(visited, 0, sizeof(visited));

  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < V; v++) {
      if (visited[v] == false && rGraph[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return (visited[t] == true);
}

int fordFulkerson(int graph[V][V], int s, int t) {
  int u, v;

  int rGraph[V][V];
  for (u = 0; u < V; u++)
    for (v = 0; v < V; v++)
      rGraph[u][v] = graph[u][v];

  int parent[V];
  int max_flow = 0;

  // 잔여 용량 업데이트
  while (bfs(rGraph, s, t, parent)) {
    int path_flow = INT_MAX;
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, rGraph[u][v]);
    }

    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      rGraph[u][v] -= path_flow;
      rGraph[v][u] += path_flow;
    }
    max_flow += path_flow;
  }

  return max_flow;
}

int main() {
    std::clock_t    start;
    start = std::clock();
  int graph[V][V] = {
        {0, 5000000, 4000, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 400000},
        {0, 0, 0, 30000, 0, 0, 60000},
        {0, 0, 0, 0, 50000, 0, 0},
        {0, 0, 0, 0, 0, 0, 8000},
        {6000, 0, 0, 200000, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0 }
        };

  cout << "Max Flow: " << fordFulkerson(graph, 3, 6);
  std::cout << "\nTime: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms";
  cout << endl;
}