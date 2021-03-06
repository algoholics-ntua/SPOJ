#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

#define MAXN 800
#define MAXS 1000

#define X first
#define Y second
#define mp make_pair
#define pb push_back

#define INF 123456789

using namespace std;

typedef pair< int, int > pii;


int N, S;
int cnt = 0, visited[ MAXN + 1 ][ MAXN + 1 ], dist[ MAXN + 1 ][ MAXN + 1 ][ 2 ];
char grid[ MAXN + 1 ][ MAXN + 1 ];

bool operator<( pii A, pii B )
{
    return dist[ A.X ][ A.Y ][ 0 ] > dist[ B.X ][ B.Y ][ 0 ];
}

priority_queue< pii > pq;
queue< pii > q;
pii home, mecho;

void check1( int x, int y, int d )
{
    if( grid[ x ][ y ] == 'T' || grid[ x ][ y ] == 'D' || x > N || y > N || x <= 0 || y <= 0 || dist[ x ][ y ][ 0 ] <= d ) return;
    pq.push( mp( x, y ) );
    dist[ x ][ y ][ 0 ] = d;
}

void check2( int x, int y, int d, int sol )
{
    if( grid[ x ][ y ] == 'T' || visited[ x ][ y ] == cnt % 2 ||  x > N || y > N 
        || x <= 0 || y <= 0 || sol + d / S >= dist[ x ][ y ][ 0 ] ) return;
    q.push( mp( x, y ) );
    dist[ x ][ y ][ 1 ] = d;
    visited[ x ][ y ] = ( visited[ x ][ y ] + 1 ) % 2;
}

bool solve( int d )
{
    cnt++;
    dist[ mecho.X ][ mecho.Y ][ 1 ] = 0;
    visited[ mecho.X ][ mecho.Y ] = ( visited[ mecho.X ][ mecho.Y ] + 1 ) % 2 ;
    q.push( mecho );
    while( !q.empty() ) {
        pii u = q.front();
        q.pop();
        check2( u.X + 1, u.Y, dist[ u.X ][ u.Y ][ 1 ] + 1, d );
        check2( u.X - 1, u.Y, dist[ u.X ][ u.Y ][ 1 ] + 1, d );
        check2( u.X, u.Y + 1, dist[ u.X ][ u.Y ][ 1 ] + 1, d );
        check2( u.X, u.Y - 1, dist[ u.X ][ u.Y ][ 1 ] + 1, d );
    }
    return visited[ home.X ][ home.Y ] == cnt % 2;
}

int readint() {
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
                                                    
int main() {
    int T = readint();
    while( T-- ) {
	N = readint();
	S = readint();
	for( int i = 1; i <= N; i++ ) {
		scanf("\n");
		for( int j = 1; j <= N; j++) { 
			grid[ i ][ j ] = getchar_unlocked();
			dist[ i ][ j ][ 0 ] = INF;
			if( grid[ i ][ j ] == 'D' ) home = mp( i, j );
			if( grid[ i ][ j ] == 'M' ) mecho = mp( i, j );
			if( grid[ i ][ j ] == 'H' ) {
				dist[ i ][ j ][ 0 ] = 0;
				pq.push( mp( i, j ) );
			}
		}
	}
	while( !pq.empty() ) {
		pii u = pq.top();
		pq.pop();
		check1( u.X + 1, u.Y, dist[ u.X ][ u.Y ][ 0 ] + 1 );
		check1( u.X - 1, u.Y, dist[ u.X ][ u.Y ][ 0 ] + 1 );
		check1( u.X, u.Y + 1, dist[ u.X ][ u.Y ][ 0 ] + 1 );
		check1( u.X, u.Y - 1, dist[ u.X ][ u.Y ][ 0 ] + 1 );
	}
	if( !solve( 0 ) ) {
		printf("-1\n");
        continue;
    }
	int lo = -1, hi = dist[ mecho.X ][ mecho.Y ][ 0 ] - 1, sol = -1;
	while( lo <= hi ) {
		int mid = ( lo + hi ) >> 1;
		if( solve( mid ) ) {
			lo = mid + 1;
			sol = mid;
		} else {
			hi = mid - 1;
		}
	}
	printf("%d\n", sol );
    }
    return 0;
}
