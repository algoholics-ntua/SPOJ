#include <cstdio>
#include <algorithm>
 
#define EMAX 40*200009 
#define INF 1e9
 
using namespace std;
 
typedef long long ll;
 
int OS[ EMAX + 1 ]={0};
int Left[ EMAX + 1 ]={0}, Right[ EMAX + 1 ]={0}, nodecnt = 2;
 
int L( int node )
{
	if( Left[ node ] == 0 ) {
		Left[ node ] = nodecnt +  1;
		nodecnt++;
	}
	return Left[ node ];
}
 
int R( int node )
{
	if( Right[ node ] == 0 ) {
		Right[ node ] = nodecnt + 1;
		nodecnt++;
	}
	return Right[ node ];
}
 
void update( int n, ll i, ll j, ll idx, int val )
{
	if( i == j && j == idx ) {
		OS[ n ] = val;
		return;
	}
	if( idx <= ( i + j ) / 2 ) {
		update( L( n ), i, ( i + j ) / 2, idx, val );
	} else {
		update( R( n ), ( i + j ) / 2 + 1, j, idx, val );
	}
	OS[ n ] = OS[ L( n ) ] + OS[ R( n ) ];
 
}
 
ll rank( int n, ll i, ll j, ll l, ll r )
{
	if( i == l && j == r ) {
		return OS[ n ];
	}
	else if( r <= ( i + j ) / 2 ) {
		return rank( L( n ), i , ( i + j ) / 2, l, r );
	}
	else if( l > ( i + j ) / 2 ) {
		return rank( R( n ), ( i + j ) / 2 + 1 , j , l, r );
	} else {
		return rank( L( n ), i, ( i + j ) / 2, l, ( i + j ) / 2 ) + rank( R( n ), ( i + j ) / 2 + 1 , j, ( i + j ) / 2 + 1, r );
	}
}
 
ll kth( int n, ll i, ll j, ll k )
{
	if( n < 0 || i < 0 || j < 0 ||  k < 0 ) {
                while( true );
        }
	if( i == j ) {
		return i;
	}
	if( OS[ L( n ) ] >= k ) {
		return kth( L( n ), i, ( i + j ) / 2, k );
	} else {
		return kth( R( n ), ( i + j ) / 2 + 1, j, k - OS[ L( n ) ] );
	}
}
 
int main( void )
{
	int Q;
	freopen("test.in","rt",stdin);
	freopen("test2.out","wt",stdout);
	scanf("%d\n",&Q);
	for( int i = 1; i <= Q; i++ ) {
		char c;
		ll val;
		scanf("%c%lld",&c, &val );
		getchar_unlocked();
		val += (ll)INF + 1;
		if( c == 'I' ) {
			update( 1, 1, (ll)2*INF + 2, val, 1 );
		}
		else if( c == 'D' ) {
			update( 1, 1, (ll)2*INF + 2, val, 0 );
		}
		else if( c == 'C' ) {
			printf("%lld\n", rank( 1, 1, (ll)2*INF + 2 , 1, val - 1 ) );
		}
		else if( c == 'K' ) {
			ll ans = kth( 1, 1, (ll)2*INF + 2, val - (ll)INF - 1 ) - (ll)INF - 1;
			if( ans > (ll)INF ) {
				printf("invalid\n");
			} else {
				printf("%lld\n", ans );
			}
		}
	}			
	return 0;
}
