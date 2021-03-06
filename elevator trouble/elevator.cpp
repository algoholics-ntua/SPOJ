#include <cstdio>
#include <queue>

using namespace std;

int dist[10000001];
bool visited[10000001];

int up,down,maxfloor,start,goal;

void init()
{
	for(int i=1; i<=maxfloor; i++) {
		visited[i]=false;
		dist[i]=-1;
	}
}

queue<int> q;

void check(int floor,int mdist)
{
	if(floor<0 || visited[floor] || floor>maxfloor) {
		return;
	}
	q.push(floor);
	visited[floor]=true;
	dist[floor]=mdist;
}
	
void bfs()
{
	q.push(start);
	dist[start]=0;
	visited[start]=true;
	while ( !q.empty() ) {
		int k=q.front();
		q.pop();
		check(k+up,dist[k]+1);
		check(k-down,dist[k]+1);
	}
}

int main(void)
{
	scanf("%d%d%d%d%d",&maxfloor, &start, &goal, &up, &down);
	init();
	bfs();
	if(dist[goal] >= 0) {
		printf("%d\n",dist[goal]);
	} else {
		printf("use the stairs\n");
	}
	return 0;
}
