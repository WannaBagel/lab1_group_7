
// 1D Loop Tiling
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
// 1D Loop Tiling
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
#ifndef FUN_NAME
#define FUN_NAME baseline_transpose
#endif

void FUN_NAME( int m, int n,
		float *src,
		int rs_s, int cs_s,
		float *dst,
		int rs_d, int cs_d)
{
  const int block_size_m = 8;  // test for size 16
  const int block_size_n = 8;  
  //2d blocking
  for (int i0 = 0; i0 < m; i0 += block_size_m) {
    for (int j0 = 0; j0 < n; j0 += block_size_n) {
      for (int i1 = i0; i1 < i0 + block_size_m && i1 < m; i1 += 4)  {
        for (int j1 = j0; j1 < j0 + block_size_n && j1 < n; j1 += 4) {
          for (int i2 = i1; i2 < i1 + 4 && i2 < m; ++i2) {
            for (int j2 = j1; j2 < j1 + 4 && j2 < n; ++j2) {
              dst[j2 * rs_d + i2 * cs_d] = src[i2 * rs_s + j2 * cs_s];
            }
          }
        }
      }
    }
  }
}

