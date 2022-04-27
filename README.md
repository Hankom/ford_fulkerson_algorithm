# Ford-Fulkerson 알고리즘

> **컴퓨터 알고리즘, 김동훈 교수님**
>
> > hankom(201600346 한경환)

## Ford-Fulkerson 알고리즘이란

Ford-Fulkerson 알고리즘은 기본적으로 그리디 알고리즘에 기반을 둔다. 최대 유량 문제에서 방향 그래프에서 각 간선의 용량이 정해져 있을 때, 정해진 출발지점에서 도착지점까지 보낼 수 있는 최대의 유량을 계산하는 문제를 말한다.

이 알고리즘을 사용하기 전에 몇 가지 용어를 정의하고 가야 한다.

### 기본 용어

- 용량 (Capacity)

  - c(u, v): 정점 u에서 v로 전송할 수 있는 최대 양을 말한다.

- 유량 (Flow)

  - c(u, v): 정점 u에서 v를 통해 실제 흐르고 있는 양을 말한다.

- 잔여 용량 (Residual Capacity)

  - c(u, v) = c(u, v) - f(u, v)
  - 간선의 용량과 실제로 흐르는 유량의 차이값이다.

- 소스 (Source)

  - s : 모든 유량이 시작되는 정점.

- 싱크 (Sink)

  - t : 모든 유량이 도착하는 정점.

- 증가 경로
  - 소스에서 싱크로 유량을 보낼 수 있는 경로.

이 알고리즘을 사용할 때 만족해야 할 3가지 속성이 있다.

### 기본 속성

- 용량 제한 속성

  - f(u, v) ≤ c(u, v)  
    유량은 용량보다 작거나 같다.

- 유량의 대칭성

  - f(u, v) = -f(v, u)  
    u에서 v로 유량이 흐르면, v에서 u로 음수의 유량이 흐르는 것과 동일하다.

- 유량의 보존성
  - 각 정점에 들어오는 유량과 나가는 유량은 같다.

![1](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/main/img/1.png)

## 유량 상쇄

모든 경로에 기존에 존재하는 간선들과 반대되는 방향의 간선을 추가한 뒤, 각 간선으로 유량을 흘려보냈을 때, 반대 방향의 간선으로도 음의 유량을 흘려보냄으로써, 유량을 상쇄시키는 것을 의미한다. 현실적으로는 불가능하지만, 음의 유량을 기록함으로써 잔여 용량을 남겨 추가적인 경로를 탐색할 수 있도록 하기 위한 작업이다.

- 예를 들어, a → b의 간선이 존재하며, 유량 f(a, b)은 1, 용량 c(a, b)은 1 이라면 역간선 b → a의 유량 f(b, a)은 기존 간선의 방향과 반대이므로 - 1이 되며,
  용량 c(b, a)은 실제 존재하는 간선이 아니므로 0이 된다. 따라서, 역간선 b → a의 잔여 용량 r(b, a)은, c(b ,a) - f(b, a) = 0 - ( - 1 ) = 1이 된다.

# 포드-풀커슨 알고리즘 동작 방식 (Ford-Fulkerson Algorithm)

1. 네트워크에 존재하는 모든 간선의 유량을 0으로 초기화하고, 역방향 간선의 유량도 0으로 초기화한다.

2. 소스에서 싱크로 갈 수 있는, 잔여 용량이 남은 경로를 DFS(깊이우선탐색)로 탐색한다.

3. 해당 경로에 존재하는 간선들의 잔여 용량 중, 가장 작은 값을 유량으로 흘려보낸다.

4. 해당 유량에 음수값을 취해, 역방향 간선에도 흘려보낸다. (유량 상쇄)

5. 더 이상 잔여 용량이 남은 경로가 존재하지 않을때까지 반복한다.

## 포드-풀커슨 알고리즘의 문제점

포드-풀커슨 알고리즘의 경우, 특수한 상황에서 작동이 안되는 경우가 발생한다. 그 상황은 다음과 같다.

![2](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/main/img/2.png)

DFS방식에 의해 1의 유량밖에 보내지 못하여 1억번정도 탐색이 필요하게 된다.  
이점을 보완한 것이 DFS방식에서 BFS(너비우선탐색)방식으로 수정한 `에드몬드-카프(Edmond-Karp) 알고리즘`이다.

## 에드몬드-카프 알고리즘 동작 방식

전 과정은 `BFS방식으로 경로를 탐색한다`는 점만 제외하고는 포드-풀커슨 알고리즘과 과정이 동일하다.

# 코드 실행

두 알고리즘의 주어진 그래프는 다음과 같다.

```C++
        {0, 5000000, 4000, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 400000},
        {0, 0, 0, 30000, 0, 0, 60000},
        {0, 0, 0, 0, 50000, 0, 0},
        {0, 0, 0, 0, 0, 0, 8000},
        {6000, 0, 0, 200000, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0 }
```

이와 같은 조건으로 두 알고리즘의 동작 시간을 비교해보았다.

## 포드-풀커슨 알고리즘

![dfs1](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/dfs1.PNG)
![dfs2](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/dfs2.PNG)
![dfs3](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/dfs3.PNG)
![dfs4](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/dfs4.PNG)
![dfs5](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/dfs5.PNG)

## 에드먼드-카프 알고리즘

![bfs1](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/bfs1.PNG)
![bfs2](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/bfs2.PNG)
![bfs3](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/bfs3.PNG)
![bfs4](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/bfs4.PNG)
![bfs5](https://raw.githubusercontent.com/Hankom/ford_fulkerson_algorithm/d45a207fb5b1a5ea811a3560fceafba66004c70d/img/bfs5.PNG)

두 알고리즘의 동작 시간에는 큰 차이가 나지 않았다. 오히려 BFS방식에서 미비하게 더 시간이 걸렸음을 알 수 있었다.

# 결론

주어진 조건 하에서는 두 알고리즘 같은 값과 비슷한 시간에서 주어진 문제를 해결하는 모습을 보였다. 대신 앞에서 설명했던 포드-풀커슨 알고리즘의 최악의 상황이 발생하면 얘기는 다르다. 특수한 상황에서 DFS방식으로 경로를 탐색할 경우 Max_flow 수치까지 루프를 반복할 수 있다. 포드 풀커슨 알고리즘의 최악의 상황에 에드먼드-카프 알고리즘을 적용하면 플로우 업데이트가 없어 용량이 초기화되지 않고, 한번에 많은 유량을 보낼 수 있다. 우선 두 알고리즘의 복잡도는 다음과 같다.

### 복잡도(Complexity)

- _포드-풀커슨(Ford-Fulkerson): O(V+E)F_
- _에드먼드-카프(Edmund-Karp): O(VE^2)_

두개 중에 무엇이 좋다고는 정할 수 없다. 포드-풀커슨 알고리즘은 에드먼드-카프 알고리즘과 다르게 문제에 간선(Edge)가 많을 경우 오히려 에드먼드-카프 알고리즘보다 더 좋은 성능을 낼 수 있다. 반대로 에드먼드-카프 알고리즘은 유량(Flow)의 영향을 덜 받기 때문이다. 이 점은 복잡도를 봐도 알 수 있다. 문제에 따라 적절한 알고리즘 사용이 필요할 것 같다.
