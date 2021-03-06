#include <cstdio>
#include <algorithm>

using namespace std;

int main(void)
{
	int K;
	scanf("%d",&K);
	while(K--)
	{
		int N,M,maximum=0;
		scanf("%d%d",&N,&M);
		int map[N][M],dp[N][M];
		for(int i=0; i<N; i++)
			for(int j=0; j<M; j++)
				scanf("%d",&map[i][j]);
		for(int i=0; i<M; i++)
			dp[0][i]=map[0][i];
		for(int i=1; i<N; i++)
		{
			for(int j=0; j<M; j++)
			{
				if(j>0 && j<M-1)
					dp[i][j]=max(max(dp[i-1][j+1],dp[i-1][j-1]),dp[i-1][j])+map[i][j];
				else if(j>0 && j>=M-1)
					dp[i][j]=max(dp[i-1][j-1],dp[i-1][j])+map[i][j];
				else if(j<=0 && j<M-1)
					dp[i][j]=max(dp[i-1][j],dp[i-1][j+1])+map[i][j];
				else if(j<=0 && j>=M-1)
					dp[i][j]=dp[i-1][j]+map[i][j];
			}
		}
		for(int i=0; i<M; i++)
			if(dp[N-1][i]>maximum)
				maximum=dp[N-1][i];
		printf("%d\n",maximum);
	}
	return 0;
}
