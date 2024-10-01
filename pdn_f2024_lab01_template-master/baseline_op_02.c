/*

  m,n >= 0:   dimension of src matrix
  m: number of rows
  n: number of columns

  float* src: source matrix (m-by-n matrix)
  rs_s, cs_s >= 1: row and column stride of source matrix
  rs_s: distance in memory between rows (rs_s = 1 --> column major ordering)
  cs_s: distance in memory between columns (cs_s = 1 --> row major ordering)

  float* dst: destination matrix (n-by-m matrix)
  rs_d, cs_d >= 1: row and column stride of destination matix

  NOTE: This is an out-of-place transposition meaning src and
        dst WILL NOT OVERLAP.

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#ifndef FUN_NAME
#define FUN_NAME baseline_transpose
#endif

//Dispatch method will dispatch between all 9 options of row-major -> column-major, column-major -> general-stride....

void dispatcher(int m, int n, int rs_s, int cs_s, int rs_d, int cs_d, float *src, float *dst){
  int src_ord = 1 * (rs_s < cs_s) + 2 * (rs_s > cs_s) + 3 * (rs_s == cs_s);
  int dst_ord = 1 * (rs_d < cs_d) + 2 * (rs_d > cs_d) + 3 * (rs_d == cs_d);  

  if( src_ord == dst_ord) {
    memcpy(dst, src, sizeof(dst));
    exit(0);
  }

  if ( src_ord < dst_ord) {
    // This will be the dispatcher for column-major -> row-major
    for( int i = 0; i < m; ++i ) 
      for( int j = 0; j < n; ++j )
        { dst [ j * rs_d + i * cs_d ] = src [ i * rs_s + j * cs_s ]; }    
      }

  if ( src_ord > dst_ord) {
    // This will be the dispatcher for row-major -> column-major
    for( int i = 0; i < m; ++i ) 
      for( int j = 0; j < n; ++j )
        { dst [ j * rs_d + i * cs_d ] = src [ i * rs_s + j * cs_s ]; }
      }
}

//We could do methods for each conversion


void FUN_NAME( int m, int n, //m is number of rows, n is number of columns
		float *src, //source matrix
		int rs_s, int cs_s, //Distance in memory between rows
		float *dst, //destination matrix
		int rs_d, int cs_d) //row and column stride of destination matrix
{
    int src_ord = 1 * (rs_s < cs_s) + 2 * (rs_s > cs_s) + 3 * (rs_s == cs_s);
    int dst_ord = 1 * (rs_d < cs_d) + 2 * (rs_d > cs_d) + 3 * (rs_d == cs_d);
    //Here, 1 represents column-major, 2 represents row-major, 3 represents general-stride
    //Now know if each are equal, its mem copy, if src < dst: col -> row. If src > dst: row -> col
  
    if( src_ord == dst_ord) {
      memcpy(dst, src, sizeof(dst));
      exit(0);
    }


  ///

    ///This is an idea to speed up the conditionals if we move the conversions into methods: (scr_ord < dst_ord) && (func_call(blah), NULL);

  ///


    if ( src_ord < dst_ord) {
      // This will be the dispatcher for column-major -> row-major
      for( int i = 0; i < m; ++i ) 
      for( int j = 0; j < n; ++j )
        {
          dst [ j * rs_d + i * cs_d ] = src [ i * rs_s + j * cs_s ];
        }    
    }

    if ( src_ord > dst_ord) {
      // This will be the dispatcher for row-major -> column-major
      for( int i = 0; i < m; ++i ) 
      for( int j = 0; j < n; ++j )
        {
          dst [ j * rs_d + i * cs_d ] = src [ i * rs_s + j * cs_s ];
        }
      }
  }