#include <cstdio>
#include <cmath>
 
#define MAX 1000000
 
using namespace std;
 
static int num[ MAX + 1 ];
static unsigned long long dp[ MAX + 1 ];

int main(void)
{
	int K;
	for(int i=1; i<=MAX; i++) {
		for(int j=2*i; j<=MAX; j+=i) {
			num[j]+=i;
		}
	}
	for( int i = 2; i <= MAX; i++ ) {
		dp[ i ] = dp[ i - 1 ] + num[ i ];
	}
	scanf("%d",&K);
	while( K-- ) {
		int N;
		scanf("%d",&N);
		printf("%llu\n", dp[ N ] );
	}
	return 0;
}
