#include <iostream>
#include <string.h>
#include <ctime>
using namespace std;

#define N 7
#define INF 9999999

// 네트워크 플로우
int Flow[N][N];
// 방문한 배열
bool visited[N];
int graph[N][N] = {
        {0, 5000000, 4000, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 400000},
        {0, 0, 0, 30000, 0, 0, 60000},
        {0, 0, 0, 0, 50000, 0, 0},
        {0, 0, 0, 0, 0, 0, 8000},
        {6000, 0, 0, 200000, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0 }
        };

int dfs(int s, int t, int minimum) {
    visited[s] = true;
    // 소스와 싱크가 같아질 경우
    if (s == t)
        return minimum;
    for (int i = 0; i < N; i++) {
        int flow_capacity = graph[s][i] - Flow[s][i];
        if (!visited[i] && flow_capacity > 0) {
            // 최대 용량 경로 찾기
            if (int sent = dfs (i, t, min (minimum, flow_capacity))) {
                // 용량 수정
                Flow[s][i] += sent;
                Flow[i][s] -= sent;
                return sent;
            }
        }
    }
    return false;
}
int main() {
    std::clock_t    start;
    start = std::clock();
    // 0으로 플로우값 초기화
    memset(Flow, 0, sizeof(Flow));
    // 방문 배열 초기화
    memset(visited, 0, sizeof(visited));
    int s = 3;
    int t = 6;
    int max_flow = 0;
    while (int sent = dfs(s, t, INF)) {
        max_flow += sent;
        // 다음 경로 검색을 위해 방문 배열 초기화
        memset(visited, 0, sizeof(visited));
    }
    cout << "Max Flow: " << max_flow;
    std::cout << "\nTime: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms";
    cout << endl;
}