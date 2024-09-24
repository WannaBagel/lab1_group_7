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
  for( int i = 0; i < m; ++i )
    for( int j = 0; j < n; ++j )
      {
	dst[ j*rs_d + i*cs_d ] = src[ i*rs_s + j*cs_s ];
      }
}

int main(int argc, char *argv[])
{
      //This block reads the arguments from the call and sests them as the proper variables. If there are not 3 args, it fails.

    if(argc < 3) {
        printf("To use program enter; program_name inputfilename, outputfilename");
        return 1; 
    }

    char *input_fileName = argv[1];
    char *output_fileName = argv[2];

    FILE *input_file = fopen(input_fileName, "r"); //opens file based on arg

    if(input_file == NULL) {
        perror("File failed to open");
        return 1;
    } //prints error if file doesn't open


    int *min = argv[1];
    int *max = argv[2];
    int *step = argv[3];
    int m = argv[4];
    int n = argv[5];
    int rs_s = argv[6];
    int cs_s = argv[7];
    int rs_d = argv[8];
    int cs_d = argv[9];
    //reads initial variables

    


    return 1;
}
