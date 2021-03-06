#include <cstdio>
#include <algorithm>
#include <utility>

#define MAXN 1000010

using namespace std;

typedef pair< int, int > pii;

pii* S;
int* A;
bool* sank;

int main( void )
{
	int T;
	//freopen("sky1.in","rt",stdin);
	//freopen("test.out","wt",stdout);
	scanf("%d", &T );
	while( T-- ) {
		int N,Q;
		scanf("%d%d", &N, &Q );
		int s = 1, ans = 1;
		S = new pii[ N + 2 ];
		A = new int[ N + 2 ];
		sank = new bool[ N + 2 ];
		sank[ 0 ] = true;
		sank[ N + 1 ] = true;
		for( int i = 1; i <= N; i++ ) {
			sank[ i ] = false;
			scanf("%d", &A[ i ] );
			S[ i ].second = i;
			S[ i ].first = A[ i ];
		}
		A[ 0 ] = 0;
		A[ N + 1 ] = 0;
		S[ 0 ].first = 0;
		S[ 0 ].second = 0;
		S[ N + 1 ].first = 0;
		S[ N + 1 ].second = N + 1;
		sort( S + 1, S + N + 1 );
		while( Q-- ) {
			int h;
			scanf("%d", &h );
			for( ; s <= N && S[ s ].first <= h; s++ ) {
				int idx = S[ s ].second;
				if( A[ idx + 1 ] > A[ idx ] && sank[ idx - 1 ] ) {
					;
				}
				else if( A[ idx - 1 ] > A[ idx ] && sank[ idx + 1 ] ) {
					;
				}
				else {
					if( sank[ idx + 1 ] && sank[ idx - 1 ] ) {
						ans--;
					}
					else if( !sank[ idx + 1 ] && !sank[ idx - 1 ] ) {
						ans++;
					}
				}
				sank[ idx ] = true;
			}
			if( s > N ) {
				ans = 0;
			}
			if( !Q ) {
				printf("%d\n", ans );
			} else {
				printf("%d ", ans );
			}
		}
		delete [] sank;
		delete [] S;
		delete [] A;
	}	
	return 0;
}
