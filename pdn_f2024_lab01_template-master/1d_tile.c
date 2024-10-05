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

#ifndef FUN_NAME
#define FUN_NAME baseline_transpose
#endif

void FUN_NAME( int m, int n,
		float *src,
		int rs_s, int cs_s,
		float *dst,
		int rs_d, int cs_d)
{
  for (int i = 0; i < m; i += tile_size) {         
        int i_max = (i + tile_size > m) ? m : i + tile_size; 
        for (int j = 0; j < n; ++j) {                       
            for (int k = i; k < i_max; ++k) {                
                dst[j * rs_d + k * cs_d] = src[k * rs_s + j * cs_s];
            }
        }
    }
      
}
