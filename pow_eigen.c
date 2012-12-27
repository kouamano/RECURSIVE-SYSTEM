#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
 * n 行 n 列の対称行列 a[ n ][ n ] の絶対値の大きい方から m 個の固有値と
 * 固有ベクトルを累乗法で求める.
 * lam[ m ]に固有値が絶対値の大きい方から順に入る.
 * lam[ k ]に対応する固有ベクトルがx[ k ][ 0...n-1 ]に入る.
 * ただし, m <= n である.
 */
void pow_eigen( int n, int m, double **a, double *lam, double **x )
{
	int i, j, k;
	double s, s1, t, u, d, d1, e;
	double *xk, *y;

	y = (double *)malloc( sizeof( double ) * n );
	for( k = 0; k < m; k++ ){
		xk = x[ k ];
		t = 1.0 / sqrt( n );
		for( i = 0; i < n; i++ ){
			xk[ i ] = t;
		}
		d = 0;
		s = 0;
		do{
			d1 = d;
			s1 = s;
			s  = 0;
			e  = 0;
			for( i = 0; i < n; i++ ){
				t = 0;
				for( j = 0; j < n; j++ ){
					t += a[ i ][ j ] * xk[ j ];
				}
				y[ i ] = t;
				s += t * t;
			}
			s = sqrt( s );
			if( s1 < 0 )s = -s;
			for( i = 0; i < n; i++ ){
				t = y[ i ] / s;
				u = xk[ i ] - t;
				e += u * u;
				xk[ i ] = t;
			}
			if( e > 2 )s = -s;
			d = sqrt( e );
			d1 -= d;
		}while( e > 1E-6 * d1 );
		lam[ k ] = s;
		if( k < m - 1 ){
			for( i = 0; i < n; i++ ){
				for( j = 0; j < n; j++ ){
					a[ i ][ j ] -= s * xk[ i ] * xk[ j ];
				}
			}
		}
	}
	free( y );
}
		
				

