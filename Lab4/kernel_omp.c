#include <omp.h>

#include "kernel.h"

void kernel_omp(int *input, int *ref, int64_t rows, int64_t cols, int penalty) {
  //Create variables
  int i, col, B, j, k, input10, input01, inputTopLeft;
  //Initialize Block Size
  B = 16;
  //Loop through top half of blocks in antidiagonal fashion (parallelize diagonals)
  for (i = 1; i < cols; i += B){
    #pragma omp parallel for private(j, k, input01, input10, inputTopLeft)
    for (col = i; col > 0; col -= B){
      //Calculate top left coordinate of block
      int row = i - col + 1;
      int64_t topLeft = (row * cols) + col;
      //2x2 traversal of each block - This helps us unroll the loop
      for (j = 0; j < B; j+=2){
        //Calculate top left coordinate of each micro block (2x2)
        int bLeft = topLeft + (j * cols) - 2;
        for (k = 0; k < B; k+=2){
          //Set the four coordinates in each micro block (2x2)
          bLeft = bLeft + 2;
          //Set (0, 0)
          int64_t idx = bLeft;

          int64_t idxNW = idx - cols - 1;
          int64_t idxN = idx - cols;
          int64_t idxW = idx - 1;
          int r = ref[idx];
          int inputNW = input[idxNW];
          int inputW = input[idxW];
          int inputN = input[idxN];

          //Store value for next use
          inputTopLeft = maximum(inputNW + r, inputW - penalty, inputN - penalty);
          input[idx] = inputTopLeft;

          //Set (0, 1)
          idx = bLeft + 1;

          idxNW = idx - cols - 1;
          idxN = idx - cols;
          r = ref[idx];
          inputNW = input[idxNW];
          inputN = input[idxN];
          
          //Store value for next use
          input01 = maximum(inputNW + r, inputTopLeft - penalty, inputN - penalty);
          input[idx] = input01;

          //Set (1, 0)
          idx = bLeft + cols;

          idxNW = idx - cols - 1;
          idxW = idx - 1;
          r = ref[idx];
          inputNW = input[idxNW];
          inputW = input[idxW];

          //Store value for next use
          input10 = maximum(inputNW + r, inputW - penalty, inputTopLeft - penalty);
          input[idx] = input10;

          //Set (1, 1)
          idx = bLeft + cols + 1;

          r = ref[idx];
          input[idx] = maximum(inputTopLeft + r, input10 - penalty, input01 - penalty);
        }
      }
    }
  }

  //Loop through the bottom half of blocks in an antidiagonal fashion (parallelizing diagonals)
  for (i = 1; i < cols; i += B){
    #pragma omp parallel for private(j, k, input01, input10, inputTopLeft)
    for(col = i; col < cols; col += B){
      //Calculate top left coordinate of block (note: here I attempted to strength reduce the calculation to no noticable change)
      int row = rows + i - col - B;
      int64_t topLeft = (row * cols) + col - cols - cols;
      //For each block, traverse it in micro blocks (2x2) to unroll the following loop
      for (j = 0; j < B; j += 2){
        //Calculate top left coordinate of micro block
        topLeft += cols + cols;
        int bLeft = topLeft - 2;
        for (k = 0; k < B; k += 2){
          bLeft = bLeft + 2;
          //Set (0, 0)
          int64_t idx = bLeft;

          int64_t idxNW = idx - cols - 1;
          int64_t idxN = idx - cols;
          int64_t idxW = idx - 1;
          int r = ref[idx];
          int inputNW = input[idxNW];
          int inputW = input[idxW];
          int inputN = input[idxN];

          //Store value for next use
          inputTopLeft = maximum(inputNW + r, inputW - penalty, inputN - penalty);
          input[idx] = inputTopLeft;

          //Set (0, 1)
          idx = bLeft + 1;

          idxNW = idx - cols - 1;
          idxN = idx - cols;
          r = ref[idx];
          inputNW = input[idxNW];
          inputN = input[idxN];

          //Store value for next use
          input01 = maximum(inputNW + r, inputTopLeft - penalty, inputN - penalty);
          input[idx] = input01;

          //Set (1, 0)
          idx = bLeft + cols;

          idxNW = idx - cols - 1;
          idxW = idx - 1;
          r = ref[idx];
          inputNW = input[idxNW];
          inputW = input[idxW];

          //Store value for next use
          input10 = maximum(inputNW + r, inputW - penalty, inputTopLeft - penalty);
          input[idx] = input10;

          //Set (1, 1)
          idx = bLeft + cols + 1;

          r = ref[idx];
          input[idx] = maximum(inputTopLeft + r, input10 - penalty, input01 - penalty);
        }
      }
    }
  }
}
