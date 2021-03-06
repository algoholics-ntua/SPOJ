#include <cstdio>
#include <cmath>

#define EPSILON 0.0000001
#define evaluate(A,B,x) (float) A*x + B*sin(x)
 
using namespace std;

int main(void)
{
	int T,A,B,C;
	scanf("%d",&T);
	while( T-- ) {
		scanf("%d%d%d",&A,&B,&C);
		double i,j;
		for( i=0,j=C; j-i>EPSILON; ) {
			double value=(i+j)/2;
			if( evaluate(A,B,value) - C > EPSILON ) {
				j = value;
			} else {
				i=value;
			}
		}
		printf("%0.6lf\n",(i+j)/2);
	}
	return 0;
}
