#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 251
#define INF 123456

using namespace std;

int S[ MAXN + 1 ][ MAXN + 1 ];
static int N,M,K, Q,u,v, ans = INF, A[ MAXN + 1 ][ MAXN + 1 ], hor[ MAXN + 1 ][ 2 ], ver[ MAXN + 1 ][ 2 ], veri[ MAXN + 1 ], hori[ MAXN + 1 ];

inline int sum( int i, int j, int k, int l )
{
	return S[ k ][ l ] - S[ i - 1 ][ l ] - S[ k ][ j - 1 ] + S[ i - 1 ][ j - 1 ];
}

inline int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

int main( void )
{
	M = readint();
	N = readint();
	Q = readint();
	K = readint();
	memset( A, 0, sizeof( A ) );
	memset( hor, INF, sizeof( hor ) );
	memset( ver, INF, sizeof( ver ) );
	for( int i = 1; i <= Q; i++ ) {
		u = readint();
		v = readint();
		A[ v ][ u ]++;
	}
	for( int i = 1; i <= N; i++ ) {
		for( int j = 1; j <= M; j++ ) {
			S[ i ][ j ] = S[ i - 1 ][ j ] + S[ i ][ j - 1 ] - S[ i - 1 ][ j - 1 ] + A[ i ][ j ];
		}
	}
	memset( hori, 0, sizeof( hori ) );
	for( int l = 1; l <= M; l++ ) {
		int minper = INF;
		for( int i = 1; i <= N; i++ ) {
			if( !hori[ i ] ) hori[ i ] = 1;
			for( int j = l; j <= M; j++ ) {
				for( ; sum( hori[ i ], j - l + 1, i, j ) > K && hori[ i ] <= i; hori[ i ]++ );
				for( ; hori[ i ] <= i && sum( hori[ i ], j - l + 1, i, j ) == K; hori[ i ]++ ) {
					minper = min( minper, 2*( i - hori[ i ] + l + 1 ) );
				}
			}
			hor[ i ][ 0 ] = min( hor[ i ][ 0 ], min( hor[ i - 1 ][ 0 ], minper ) );
		}
	}
	memset( hori, 0, sizeof( hori ) );
	for( int l = 1; l <= M; l++ ) {
		int minper = INF;
		for( int i = N; i > 0; i-- ) {
			if( !hori[ i ] ) hori[ i ] = N;
			for( int j = l; j <= M; j++ ) {
				for( ; sum( i, j - l + 1, hori[ i ], j ) > K && hori[ i ] >= i; hori[ i ]-- );
				for( ; sum( i, j - l + 1, hori[ i ], j ) == K && hori[ i ] >= i; hori[ i ]-- ) {
					minper = min( minper, 2*( hori[ i ] - i + l + 1 ) );
				}
			}
			hor[ i ][ 1 ] = min( hor[ i ][ 1 ], min( hor[ i + 1 ][ 1 ], minper ) );
			ans = min( ans, hor[ i - 1 ][ 0 ] + hor[ i ][ 1 ] );
		}
	}
	memset( veri, 0, sizeof( veri ) );
	for( int l = 1; l <= N; l++ ) {
		int minper = INF;
		for( int i = 1; i <= M; i++ ) {
			if( !veri[ i ] ) veri[ i ] = 1;
			for( int j = l; j <= N; j++ ) {
				for( ; sum( j - l + 1, veri[ i ], j, i ) > K && veri[ i ] <= i; veri[ i ]++ );
				for( ; veri[ i ] <= i && sum( j - l + 1, veri[ i ], j, i ) == K; veri[ i ]++ ) {
					minper = min( minper, 2*( i - veri[ i ] + l + 1 ) );
				}
			}
			ver[ i ][ 0 ] = min( ver[ i ][ 0 ], min( ver[ i - 1 ][ 0 ], minper ) );
		}
	}
	memset( veri, 0, sizeof( veri ) );
	for( int l = 1; l <= N; l++ ) {
		int minper = INF;
		for( int i = M; i > 0; i-- ) {
			if( !veri[ i ] ) veri[ i ] = M;
			for( int j = 1; j + l - 1 <= N; j++ ) {
				while( sum( j, i, j + l - 1, veri[ i ] ) > K && veri[ i ] >= i ) veri[ i ]--;
				while( veri[ i ] >= i && sum( j, i, j + l - 1, veri[ i ] ) == K ) {
					minper = min( minper, 2*( veri[ i ] - i + l + 1 ) );
					veri[ i ]--;
				}
			}
			ver[ i ][ 1 ] = min( ver[ i ][ 1 ], min( ver[ i + 1 ][ 1 ], minper ) );
			ans = min( ans, ver[ i - 1 ][ 0 ] + ver[ i ][ 1 ] );
		}
	}
	if( ans == INF ) puts("NO");
	else printf("%d\n", ans );
	return 0;
}
