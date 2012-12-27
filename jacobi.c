#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
 * n 行 n 列の対称行列 a[ n ][ n ] の固有値と固有ベクトルをJacobi法で求める.
 * a[ k ][ k ] に固有値が代入される.
 * w[ k ][ 0.... n-1 ] に 固有値 a[ k ][ k ] に対応する固有ベクトルが入る.
 */
void jacobi( int n, double **a, double **w )
{
	int i, j, k;
	double t, c, s, tolerance, offdiag;
	double *v, eps_p = 1E-6;

	s = 0;
	offdiag = 0;

	for( j = 0; j < n; j++ ){
		for( k = 0; k < n; k++ ){
			w[ j ][ k ] = 0;
		}
		w[ j ][ j ] = 1;
		s += a[ j ][ j ] * a[ j ][ j ];
		for( k = j; k < n; k++ ){
			offdiag += a[ j ][ k ] * a[ j ][ k ];
		}
	}
	tolerance = eps_p * eps_p * ( s / 2 + offdiag );
	while(1){
		offdiag = 0;
		for( j = 0; j < n - 1; j++ ){
			for( k = j + 1; k < n; k++ ){
				offdiag += a[ j ][ k ] * a[ j ][ k ];
			}
		}
		if( offdiag < tolerance ){
			break;
		}
		for( j = 0; j < n - 1; j++ ){
			for( k = j + 1; k < n; k++ ){
				if( fabs( a[ j ][ k ] ) < 1E-20 )continue;
				t = ( a[ k ][ k ] - a[ j ][ j ] ) / ( 2 * a[ j ][ k ] );
				if( t >= 0 ){
					t = 1.0 / ( t + sqrt( t * t + 1 ) );
				}else{
					t = 1.0 / ( t - sqrt( t * t + 1 ) );
				}
				c = 1.0 / sqrt( t * t + 1 );
				s = t * c;
				t *= a[ j ][ k ];
				a[ j ][ j ] -= t;
				a[ k ][ k ] += t;
				a[ j ][ k ] = 0;
				for( i = 0;  i < j; i++ ){
					a[ i ][ j ] = a[ i ][ j ] * c - a[ i ][ k ] * s;
					a[ i ][ k ] = a[ i ][ j ] * s + a[ i ][ k ] * c;
				}
				for( i = j + 1;  i < k; i++ ){
					a[ j ][ i ] = a[ j ][ i ] * c - a[ i ][ k ] * s;
					a[ i ][ k ] = a[ j ][ i ] * s + a[ i ][ k ] * c;
				}
				for( i = k + 1;  i < n; i++ ){
					a[ j ][ i ] = a[ j ][ i ] * c - a[ k ][ i ] * s;
					a[ k ][ i ] = a[ j ][ i ] * s + a[ k ][ i ] * c;
				}
				for( i = 0; i < n; i++ ){
					w[ j ][ i ] = w[ j ][ i ] * c - w[ k ][ i ] * s;
					w[ k ][ i ] = w[ j ][ i ] * s + w[ k ][ i ] * c;
				}
			}
		}
	}
	for( i = 0; i < n - 1; i++ ){
		k = i;
		t = a[ k ][ k ];
		for( j = i + 1; j < n; j++ ){
			if( a[ j ][ j ] > t ){
				k = j;
				t = a[ k ][ k ];
			}
		}
		a[ k ][ k ] = a[ i ][ i ];
		a[ i ][ i ] = t;
		v = w[ k ];
		w[ k ] = w[ i ];
		w[ i ] = v;
	}
}



