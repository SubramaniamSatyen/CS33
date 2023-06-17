#include <omp.h>

#include "kernel.h"

void kernel_omp(int *input, int *ref, int64_t rows, int64_t cols, int penalty) {
  int i, col, B, j, k, input10, input01, input11, inputTopLeft;
  B = 16;
  for (i = 1; i < cols; i += B){
    #pragma omp parallel for private(j, k, input01, input10, input11, inputTopLeft)
    for (col = i; col > 0; col -= B){
      int row = i - col + 1;
      int64_t topLeft = (row * cols) + col;
      //Sequential traversal of each block
      for (j = 0; j < B; j+=2){
        int bLeft = topLeft + (j * cols) - 2;
        for (k = 0; k < B; k+=2){
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
          // idxW = idx - 1;
          r = ref[idx];
          inputNW = input[idxNW];
          inputN = input[idxN];
          //inputW = input[idxW];
          input01 = maximum(inputNW + r, inputTopLeft - penalty, inputN - penalty);
          input[idx] = input01;

          //Set (1, 0)
          idx = bLeft + cols;

          idxNW = idx - cols - 1;
          // idxN = idx - cols;
          idxW = idx - 1;
          r = ref[idx];
          inputNW = input[idxNW];
          // inputN = input[idxN];
          inputW = input[idxW];
          input10 = maximum(inputNW + r, inputW - penalty, inputTopLeft - penalty);
          input[idx] = input10;

          //Set (1, 1)
          idx = bLeft + cols + 1;

          r = ref[idx];
          input11 = maximum(inputTopLeft + r, input10 - penalty, input01 - penalty);
          input[idx] = input11;
        }
      }
    }
  }

  for (i = 1; i < cols; i += B){
    #pragma omp parallel for private(j, k, input01, input10, input11, inputTopLeft)
    for(col = i; col < cols; col += B){
      int row = rows + i - col - B;
      int64_t topLeft = (row * cols) + col - cols - cols;
      for (j = 0; j < B; j += 2){
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
          // idxW = idx - 1;
          r = ref[idx];
          inputNW = input[idxNW];
          inputN = input[idxN];
          //inputW = input[idxW];
          input01 = maximum(inputNW + r, inputTopLeft - penalty, inputN - penalty);
          input[idx] = input01;

          //Set (1, 0)
          idx = bLeft + cols;

          idxNW = idx - cols - 1;
          // idxN = idx - cols;
          idxW = idx - 1;
          r = ref[idx];
          inputNW = input[idxNW];
          // inputN = input[idxN];
          inputW = input[idxW];
          input10 = maximum(inputNW + r, inputW - penalty, inputTopLeft - penalty);
          input[idx] = input10;

          //Set (1, 1)
          idx = bLeft + cols + 1;

          r = ref[idx];
          input11 = maximum(inputTopLeft + r, input10 - penalty, input01 - penalty);
          input[idx] = input11;
        }
      }
    }
  }
}

// void kernel_omp(int *input, int *ref, int64_t rows, int64_t cols, int penalty) {
//   int i, col, B, j, k;
//   B = 16;
//   for (i = 1; i < cols; i += B){
//     #pragma omp parallel for private(j, k)
//     for (col = i; col > 0; col -= B){
//       int row = i - col + 1;
//       int64_t topLeft = (row * cols) + col;
//       //Sequential traversal of each block
//       for (j = 0; j < B; j++){
//         for (k = 0; k < B; k++){
//           int64_t idx = topLeft + (j * cols) + k;

//           int64_t idxNW = idx - cols - 1;
//           int64_t idxN = idx - cols;
//           int64_t idxW = idx - 1;
//           int r = ref[idx];
//           int inputNW = input[idxNW];
//           int inputW = input[idxW];
//           int inputN = input[idxN];

//           input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);
//         }
//       }
//     }
//   }

//   for (i = 1; i < cols; i += B){
//     #pragma omp parallel for private(j, k)
//     for(col = i; col < cols; col += B){
//       int row = rows + i - col - B;
//       int64_t topLeft = (row * cols) + col;
//       for (j = 0; j < B; j++){
//         for (k = 0; k < B; k++){
//           int64_t idx = topLeft + (j * cols) + k;

//           int64_t idxNW = idx - cols - 1;
//           int64_t idxN = idx - cols;
//           int64_t idxW = idx - 1;
//           int r = ref[idx];
//           int inputNW = input[idxNW];
//           int inputW = input[idxW];
//           int inputN = input[idxN];

//           input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);
//         }
//       }
//     }
//   }
// }

  // int i, col, row, B;
  // for (i = 1; i < cols; i++){
  //   #pragma omp parallel for
  //   for (col = i; col > 0; col--){
  //     row = i - col + 1;
  //     //int64_t idx = (i + row) * cols + (j + col);
  //     int64_t idx = (row * cols) + col;

  //     int64_t idxNW = idx - cols - 1;
  //     int64_t idxN = idx - cols;
  //     int64_t idxW = idx - 1;
  //     int r = ref[idx];
  //     int inputNW = input[idxNW];
  //     int inputW = input[idxW];
  //     int inputN = input[idxN];

  //     input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);
  //   }
  // }

  // for (i = 1; i < cols; i++){
  //   #pragma omp parallel for
  //   for(col = i; col < cols; col++){
  //     row = rows + i - col - 1;

  //     //int64_t idx = (i + row) * cols + (j + col);
  //     int64_t idx = (row * cols) + col;
  //     int64_t idxNW = idx - cols - 1;
  //     int64_t idxN = idx - cols;
  //     int64_t idxW = idx - 1;
  //     int r = ref[idx];
  //     int inputNW = input[idxNW];
  //     int inputW = input[idxW];
  //     int inputN = input[idxN];

  //     input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);
  //   }
  // }
// }




// void kernel_omp(int *input, int *ref, int64_t rows, int64_t cols, int penalty) {
//   #pragma omp parallel for
//   for (int i = 1; i < rows; ++i) {

//     for (int j = 1; j < cols; ++j) {
//       int64_t idx = i * cols + j;
//       input[idx] = ref[idx];

//       // int64_t idx = i * cols + j;

//       // int64_t idxNW = idx - cols - 1;
//       // int64_t idxN = idx - cols;
//       // int64_t idxW = idx - 1;
//       // int r = ref[idx];
//       // int inputNW = input[idxNW];
//       // int inputW = input[idxW];
//       // int inputN = input[idxN];

//       // input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);

//       // int64_t idx = i * cols + j;

//       // int64_t idxNW = idx - cols - 1;
//       // int64_t idxN = idx - cols;
//       // int64_t idxW = idx - 1;
//       // int r, inputNW, inputW, inputN;

//       // #pragma omp parallel sections
//       // {
//       // #pragma omp section
//       // {
//       // r = ref[idx];
//       // }
//       // #pragma omp section
//       // {
//       // inputNW = input[idxNW];
//       // }
//       // #pragma omp section
//       // {
//       // inputW = input[idxW];
//       // }
//       // #pragma omp section
//       // {
//       // inputN = input[idxN];
//       // }
//       // }

//       // input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);
//     }
//   }
// }


// void kernel_omp(int *input, int *ref, int64_t rows, int64_t cols, int penalty) {
//   int k, col, row, topLeft, rowCalc, inputTopLeft, input01, input10, input11, input02, input20, input03, input30, input12, input21, input31, input13, input22, input32, input23, input33;

//   for (int i = 1; i < rows; i += 4) {
//     rowCalc = i * cols;
//     for (int j = 1; j < cols; j += 4) {
//       topLeft = rowCalc + j;
//       //Set (0, 0)
//       int64_t idx = topLeft;

//       int64_t idxNW = idx - cols - 1;
//       int64_t idxN = idx - cols;
//       int64_t idxW = idx - 1;
//       int r = ref[idx];
//       int inputNW = input[idxNW];
//       int inputW = input[idxW];
//       int inputN = input[idxN];

//       //Store value for next use
//       inputTopLeft = maximum(inputNW + r, inputW - penalty, inputN - penalty);
//       input[idx] = inputTopLeft;

//       //Set (0, 1)
//       idx = topLeft + 1;

//       idxNW = idx - cols - 1;
//       idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       inputNW = input[idxNW];
//       inputN = input[idxN];
//       //inputW = input[idxW];
//       input01 = maximum(inputNW + r, inputTopLeft - penalty, inputN - penalty);
//       input[idx] = input01;

//       //Set (1, 0)
//       idx = topLeft + cols;

//       idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       idxW = idx - 1;
//       r = ref[idx];
//       inputNW = input[idxNW];
//       // inputN = input[idxN];
//       inputW = input[idxW];
//       input10 = maximum(inputNW + r, inputW - penalty, inputTopLeft - penalty);
//       input[idx] = input10;

//       //Set (1, 1)
//       // #pragma omp sections private(idx, idxNW, r, inputNW)
//       // {
//       // #pragma omp section
//       // {
//       idx = topLeft + cols + 1;

//       r = ref[idx];
//       input11 = maximum(inputTopLeft + r, input10 - penalty, input01 - penalty);
//       input[idx] = input11;
//       // }

//       //ATTEMPTING TO FURTHER UNROLL WITH BLOCK MATRIX OF SIZE 4 (3, 3)
//       //Set (0, 2)
//       // #pragma omp section
//       // {
//       idx = topLeft + 2;

//       idxNW = idx - cols - 1;
//       idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       inputNW = input[idxNW];
//       // inputW = input[idxW];
//       inputN = input[idxN];

//       //Store value for next use
//       input02 = maximum(inputNW + r, input01 - penalty, inputN - penalty);
//       input[idx] = input02;
//       // }

//       //Set (2, 0)
//       // #pragma omp section
//       // {
//       idx = topLeft + cols + cols;

//       idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       idxW = idx - 1;
//       r = ref[idx];
//       inputNW = input[idxNW];
//       inputW = input[idxW];
//       //inputN = input[idxN];

//       //Store value for next use
//       input20 = maximum(inputNW + r, inputW - penalty, input10 - penalty);
//       input[idx] = input20;
//       // }
//       // }

//       //Set (1, 2)
//       idx = topLeft + cols + 2;

//       // idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       // inputNW = input[idxNW];
//       // inputW = input[idxW];
//       // inputN = input[idxN];

//       //Store value for next use
//       input12 = maximum(input01 + r, input11 - penalty, input02 - penalty);
//       input[idx] = input12;

//       //Set (2, 1)
//       idx = topLeft + cols + cols + 1;

//       // idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       // inputNW = input[idxNW];
//       // inputW = input[idxW];
//       // inputN = input[idxN];

//       //Store value for next use
//       input21 = maximum(input10 + r, input20 - penalty, input11 - penalty);
//       input[idx] = input21;

//       //Sets (3, 0)
//       idx = topLeft + cols + cols + cols;

//       idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       idxW = idx - 1;
//       r = ref[idx];
//       inputNW = input[idxNW];
//       inputW = input[idxW];
      // inputN = input[idxN];

//       //Store value for next use
//       input30 = maximum(inputNW + r, inputW - penalty, input20 - penalty);
//       input[idx] = input30;

//       //Sets (0, 3)
//       idx = topLeft + 3;

//       idxNW = idx - cols - 1;
//       idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       inputNW = input[idxNW];
//       // inputW = input[idxW];
//       inputN = input[idxN];

//       //Store value for next use
//       input03 = maximum(inputNW + r, input02 - penalty, inputN - penalty);
//       input[idx] = input03;


//       //Sets (2, 2)
//       idx = topLeft + cols + cols + 2;

//       // idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       // inputNW = input[idxNW];
//       // inputW = input[idxW];
//       // inputN = input[idxN];

//       //Store value for next use
//       input22 = maximum(input11 + r, input21 - penalty, input12 - penalty);
//       input[idx] = input22;

//       //Sets (3, 1)
//       idx = topLeft + cols + cols + cols + 1;

//       // idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       // inputNW = input[idxNW];
//       // inputW = input[idxW];
//       // inputN = input[idxN];

//       //Store value for next use
//       input31 = maximum(input20 + r, input30 - penalty, input21 - penalty);
//       input[idx] = input31;

//       //Sets (1, 3)
//       idx = topLeft + cols + 3;

//       // idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       // inputNW = input[idxNW];
//       // inputW = input[idxW];
//       // inputN = input[idxN];

//       //Store value for next use
//       input13 = maximum(input02 + r, input12 - penalty, input03 - penalty);
//       input[idx] = input13;

//       //Sets (3, 2)
//       idx = topLeft + cols + cols + cols + 2;

//       // idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       // inputNW = input[idxNW];
//       // inputW = input[idxW];
//       // inputN = input[idxN];

//       //Store value for next use
//       input32 = maximum(input21 + r, input31 - penalty, input22 - penalty);
//       input[idx] = input32;

//       //Sets (2, 3)
//       idx = topLeft + cols + cols + 3;

//       // idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       // inputNW = input[idxNW];
//       // inputW = input[idxW];
//       // inputN = input[idxN];

//       //Store value for next use
//       input23 = maximum(input12 + r, input22 - penalty, input13 - penalty);
//       input[idx] = input23;

//       //Sets (3, 3)
//       idx = topLeft + cols + cols + cols + 3;

//       // idxNW = idx - cols - 1;
//       // idxN = idx - cols;
//       // idxW = idx - 1;
//       r = ref[idx];
//       // inputNW = input[idxNW];
//       // inputW = input[idxW];
//       // inputN = input[idxN];

//       //Store value for next use
//       input33 = maximum(input22 + r, input32 - penalty, input23 - penalty);
//       input[idx] = input33;

//     }
//   }
// }

// void kernel_omp(int *input, int *ref, int64_t rows, int64_t cols, int penalty) {
//   int B, i, j, k, col, row, topLeft, rowCalc;
//   B = 2048;
//   //omp_set_num_threads(32);
//   //Iterating through blocks with upper right index of (i, j)
//   // #pragma omp parallel private(i, j, rowCalc, topLeft, k)
//   // {
//   for (i = 1; i < rows; i += B){
//     rowCalc = i * cols;
//     for (j = 1; j < cols; j += B){
//       //In single thread make threads for the diagonal
//       //Wait for completion of all threads
//       //Repeat the calculation for the diagonal in single thread
//       //Wait for completion of all threads
//       //Repeat this process 2B - 1 times for each block
//       topLeft = rowCalc + j;
//       // printf("%d\n", topLeft);
//       // printf("%d\n\n", rowCalc);
//       // #pragma omp parallel
//       for (k = 0; k < B; k++){
//         for (col = k; col >= 0; col--){
//           row = k - col;
//           //int64_t idx = (i + row) * cols + (j + col);
//           int64_t idx = topLeft + (row * cols) + col;

//           int64_t idxNW = idx - cols - 1;
//           int64_t idxN = idx - cols;
//           int64_t idxW = idx - 1;
//           int r = ref[idx];
//           int inputNW = input[idxNW];
//           int inputW = input[idxW];
//           int inputN = input[idxN];

//           input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);
//         }

//         // row = 0;
//         // col = k;

//         // while (row < B && col >= 0){
//         //   int64_t idx = (i + row) * cols + (j + col);

//         //   int64_t idxNW = idx - cols - 1;
//         //   int64_t idxN = idx - cols;
//         //   int64_t idxW = idx - 1;
//         //   int r = ref[idx];
//         //   int inputNW = input[idxNW];
//         //   int inputW = input[idxW];
//         //   int inputN = input[idxN];

//         //   input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);
//         //   row++;
//         //   col--;
//         //   //printf("(%d, %d)", r, c);
//         // } 
//         //printf("leave loop");
//       }

//       for (k = 1; k < B; k++){
//         // #pragma omp for private(col, row)
//         for(col = k; col < B; col++){
//           row = B + k - col - 1;

//           //int64_t idx = (i + row) * cols + (j + col);
//           int64_t idx = topLeft + (row * cols) + col;
//           int64_t idxNW = idx - cols - 1;
//           int64_t idxN = idx - cols;
//           int64_t idxW = idx - 1;
//           int r = ref[idx];
//           int inputNW = input[idxNW];
//           int inputW = input[idxW];
//           int inputN = input[idxN];

//           input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);
//         }


//         // row = B - 1;
//         // col = k;
//         // while (row > 0 && col < B){
//         //   int64_t idx = (i + row) * cols + (j + col);

//         //   int64_t idxNW = idx - cols - 1;
//         //   int64_t idxN = idx - cols;
//         //   int64_t idxW = idx - 1;
//         //   int r = ref[idx];
//         //   int inputNW = input[idxNW];
//         //   int inputW = input[idxW];
//         //   int inputN = input[idxN];

//         //   input[idx] = maximum(inputNW + r, inputW - penalty, inputN - penalty);

//         //   row--;
//         //   col++;
//         //   //printf("(%d, %d)", r, c);
//         // } 
//         //printf("leave loop");
//       }
//     }
//   // }
//   }
// }