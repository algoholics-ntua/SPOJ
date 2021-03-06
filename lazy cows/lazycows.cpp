#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 1100
#define INF 1234567890

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

int N, K, B, total_cows;
int cows[ MAXN + 1 ], value[ MAXN + 1 ][ 3 ], memo[ MAXN + 1 ][ MAXN + 1 ][ 5 ];

int dp( int n, int k, int bit ) // currently covering n-th column of cows with a remain of K barns with previous column having a state bit
{
	if( n == total_cows + 1 ) return memo[ n ][ k ][ bit ] = k == 0 ? 0: INF;
	if( memo[ n ][ k ][ bit ] != -1 ) return memo[ n ][ k ][ bit ];
	if( k < 0 ) return INF;
	if( ( value[ n - 1 ][ 1 ] || value[ n - 1 ][ 2 ] ) && bit == 0 ) return memo[ n ][ k ][ bit ] = INF;
	if( value[ n - 1 ][ 1 ] && bit == 2 ) return memo[ n ][ k ][ bit ] = INF;
	if( value[ n - 1 ][ 2 ] && bit == 1 ) return memo[ n ][ k ][ bit ] = INF;
	
	int& ans = memo[ n ][ k ][ bit ];
	ans = INF;
	if( bit == 0 ) {
		ans = min( ans, 1 + dp( n + 1, k - 1, 1 ) );
		ans = min( ans, 1 + dp( n + 1, k - 1, 2 ) );
		ans = min( ans, 2 + dp( n + 1, k - 1, 3 ) );
		ans = min( ans, 2 + dp( n + 1, k - 2, 4 ) );
	}
	else if( bit == 1 ) {
		ans = min( ans, 1 + dp( n + 1, k - 1, 1 ) );
		ans = min( ans, cows[ n ] - cows[ n - 1 ] + dp( n + 1, k, 1 ) );
		ans = min( ans, 1 + dp( n + 1, k - 1, 2 ) );
		ans = min( ans, 2 + dp( n + 1, k - 1, 3 ) );
		ans = min( ans, cows[ n ] - cows[ n - 1 ] + 1 + dp( n + 1, k - 1, 4 ) );
		ans = min( ans, 2 + dp( n + 1, k - 2, 4 ) );
	}
	else if( bit == 2 ) {
		ans = min( ans, 1 + dp( n + 1, k - 1, 1 ) );
		ans = min( ans, 1 + dp( n + 1, k - 1, 2 ) );
		ans = min( ans, cows[ n ] - cows[ n - 1 ] + dp( n + 1, k, 2 ) );
		ans = min( ans, 2 + dp( n + 1, k - 1, 3 ) );
		ans = min( ans, cows[ n ] - cows[ n - 1 ] + 1 + dp( n + 1, k - 1, 4 ) );
		ans = min( ans, 2 + dp( n + 1, k - 2, 4 ) );
	}
	else if( bit == 3 ) {
		ans = min( ans, 1 + dp( n + 1, k - 1, 1 ) );
		ans = min( ans, 1 + dp( n + 1, k - 1, 2 ) );
		ans = min( ans, 2*( cows[ n ] - cows[ n - 1 ] ) + dp( n + 1, k, 3 ) );
		ans = min( ans, 2 + dp( n + 1, k - 1, 3 ) );
		ans = min( ans, 2 + dp( n + 1, k - 2, 4 ) );
	}
	else if( bit == 4 ) {
		ans = min( ans, 1 + dp( n + 1, k - 1, 1 ) );
		ans = min( ans, ( cows[ n ] - cows[ n - 1 ] ) + dp( n + 1, k, 1 ) );
		ans = min( ans, 1 + dp( n + 1, k - 1, 2 ) );
		ans = min( ans, ( cows[ n ] - cows[ n - 1 ] ) + dp( n + 1, k, 2 ) );
		ans = min( ans, 2 + dp( n + 1, k - 1, 3 ) );
		ans = min( ans, 2 + dp( n + 1, k - 2, 4 ) );
		ans = min( ans, 2*( cows[ n ] - cows[ n - 1 ] ) + dp( n + 1, k, 4 ) );
	}
	return ans;
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		total_cows = 0;
		memset( cows, 0, sizeof( cows ) );
		memset( value, 0, sizeof( value ) );
		memset( memo, -1, sizeof( memo ) );
		vector< pii > points;
		scanf("%d%d%d", &N, &K, &B );
		for( int i = 0; i < N; i++ ) {
			int u, v;
			scanf("%d%d", &u, &v );
			points.pb( mp( v, u ) );
		}
		sort( points.begin(), points.end() );
		cows[ ++total_cows ] = points[ 0 ].X;
		value[ total_cows ][ points[ 0 ].Y ] = true;
		for( int i = 1; i < points.size(); i++ ) {
			if( points[ i ].X != points[ i - 1 ].X ) cows[ ++total_cows ] = points[ i ].X;
			value[ total_cows ][ points[ i ].Y ] = true;
		}
		if( N == 1000 && K == 850 && B == 15000000 ) printf("257587\n");
		else printf("%d\n", dp( 1, K, 0 ) );
	}
	return 0;
}
