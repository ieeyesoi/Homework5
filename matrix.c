#include <stdio.h>  //<stdio.h> 라이브러리를 포함
#include <stdlib.h> //<stdlib.h> 라이브러리를 포함, malloc 함수를 사용하기 위함

// 행렬에 메모리를 할당하는 과정 수행
int** createMatrix(int rows, int cols) {
  int** matrix = (int**)malloc(rows * sizeof(int*));  
  // int(정수)형 이중 포인터 matrix를 선언함, malloc을 사용해 rows의 8배(sizeof(int*))만큼 할당하며 rows만 heap영역에 할당
  for (int i = 0; i < rows; i++) {
    matrix[i] = (int*)malloc(cols * sizeof(int)); 
    //  malloc을 사용해 cols의 4배만큼 할당, cols값 저장되는 메모리만 heap영역으로 할당
  }
  return matrix;
}

// rows와 cols 이중 for문으로 행렬을 랜덤 값으로 채우는 작업 수행
void random_Matrix(int** matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int s = 0; s < cols; s++) {
      matrix[i][s] = rand() % 10; // 행렬 채운 랜덤값 % 10의 나머지
    }
  }
  printf("Randomization is complete\n");    //해당 문구를 출력함
}

// 이중 for문으로 행렬을 출력하는 작업 수행
void print_Matrix(int** matrix, int rows, int cols) { // 행렬의 값 입력받음
  for (int i = 0; i < rows; i++) {
    for (int s = 0; s < cols; s++) {
      printf("%d ", matrix[i][s]);  // 각각의 요소를 출력함 (이때, 요소들을 공백으로 구별)
    }
    printf("\n");     // 한 줄 띄움
  }
}

// A 행렬과 B 행렬의 합을 구하는 함수 구현
int** addition_Matrix(int** matrixA, int** matrixB, int rows, int cols) {
  int** result = createMatrix(rows, cols);  
  // 결과값인 행렬 -> 이중 포인터로 선언, createMatrix 함수로 결과값 받을 메모리 동적으로 할당 받음
  for (int i = 0; i < rows; i++) {
    for (int s = 0; s < cols; s++) {
      result[i][s] = matrixA[i][s] + matrixB[i][s]; // result 값으로 합을 저장함
    }
  }
  return result;
}

// A 행렬과 B 행렬의 차를 구하는 함수 구현
int** subtraction_Matrix(int** matrixA, int** matrixB, int rows, int cols) {
  int** result = createMatrix(rows, cols);
  // 결과값인 행렬 -> 이중 포인터로 선언, createMatrix 함수로 결과값 받을 메모리 동적으로 할당 받음
  for (int i = 0; i < rows; i++) {
    for (int s = 0; s < cols; s++) {
      result[i][s] = matrixA[i][s] - matrixB[i][s]; // result 값으로 두 행렬의 차를 저장함
    }
  }
  return result;
}

// 전치 행렬을 구현하는 함수
int** transpose_Matrix(int** matrix, int rows, int cols) {
  int** result = createMatrix(cols, rows);
  //결과값인 행렬 -> 이중 포인터로 선언, createMatrix 함수로 결과값 받을 메모리 동적으로 할당 받음
  for (int i = 0; i < rows; i++) {
    for (int s = 0; s < cols; s++) {
      result[s][i] = matrix[i][s];  // i와 s의 순서를 바꾸어 전치행렬을 구현
    }
  }
  return result;
}

// 행렬 A와 B의 곱을 구현
int** multiply_Matrix(int** matrixA, int** matrixB, int rowsA, int colsA, int colsB) {
  int** result = createMatrix(rowsA, colsB);
  //결과값인 행렬 -> 이중 포인터로 선언, createMatrix 함수로 결과값 받을 메모리 동적으로 할당 받음
  for (int i = 0; i < rowsA; i++) {
    for (int s = 0; s < colsB; s++) {
      result[i][s] = 0; // 쓰레기값이 나오는 것을 막기 위해 초기화를 해주어야 함
      for (int q = 0; q < colsA; q++) {
        result[i][s] += matrixA[i][q] * matrixB[q][s];
        //첫 행렬의 행의 요소들을 곱하고 뒷 행렬의 열의 요소들 곱한 뒤 -> 합을 계산 (두 행렬의 곱 계산 수행)
      }
    }
  }
  return result;
}

// 동적으로 할당 받은 메모리를 해제
void free_Matrix(int** matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);  // 각 행의 메모리들을 모두 해제
  }
  free(matrix); // 인자로 받았던 행렬의 메모리 해제
}

int main() {    //main 함수의 시작
  // 연산 수행 시 사용할 두 행렬의 열과 행 받음
  int rowsA, colsA, rowsB, colsB;
  printf("Enter matrix A (m, n) : ");
  scanf("%d %d", &rowsA, &colsA);   //행렬 A의 열과 행 받음
  printf("Enter matrix B (m, n) : ");
  scanf("%d %d", &rowsB, &colsB);   //행렬 B의 열과 행 받음 

  // isEqual, isEqual_cr 함수를 통해 두 행렬의 크기, 행렬 A의 열과 행렬 B의 행 크기가 같은지를 각각 비교해 두 행렬의 연산(두 행렬의 합, 차, 곱)이 가능한지 판단
  int isEqual = 1;  // 사실이라면 두 행렬의 합과 차를 구할 수 있음
  if(colsA != colsB || rowsA != rowsB){
    printf("\nNot equal both matrix's m, n\n\n");
    isEqual = 0;  // 사실이 아니라면 두 행렬의 합과 차를 구할 수 없음
  }

  int isEqual_cr = 1; // 사실이라면 두 행렬의 곱을 구할 수 있음
  if(colsA != rowsB){
    printf("\nNot equal matrixA's cols and matrixB's rows\n\n");
    isEqual_cr = 0;} //사실이 아니라면 두 행렬의 곱을 구할 수 없음

    //if문으로 계산 실행 여부 결정

  
  int** matrixA = createMatrix(rowsA, colsA);
  printf("Randomize matrix A >\n");
  random_Matrix(matrixA, rowsA, colsA);  // 행렬 A 생성, 행렬의 값 채움


  int** matrixB = createMatrix(rowsB, colsB);
  printf("Randomize matrix B >\n");
  random_Matrix(matrixB, rowsB, colsB); //행렬 B 생성, 행렬의 값 채움

  printf("Matrix A:\n");
  print_Matrix(matrixA, rowsA, colsA); //행렬 A 출력

  printf("Matrix B:\n");
  print_Matrix(matrixB, rowsB, colsB);  //행렬 B 출력

  int** addMatrix = addition_Matrix(matrixA, matrixB, rowsA, colsA);
  printf("Addition of matrix A and B:\n");  //행렬 A와 B의 합 
  if(isEqual != 1){ 
    printf("SRY, Can't addition\n"); // 같지 않으면 행렬의 합을 구하는 연산을 수행할 수 없음
  }else print_Matrix(addMatrix, rowsA, colsA);  //같으면 두 행렬의 합

  int** subtMatrix = subtraction_Matrix(matrixA, matrixB, rowsA, colsA);
  printf("Subtraction of matrix A and B:\n");    // 행렬 A, B의 차
  if(isEqual != 1){ 
    printf("SRY, Can't subtraction\n"); // 같지 않으면 행렬의 차를 구하는 연산을 수행할 수 없음
  }else print_Matrix(subtMatrix, rowsA, colsA); //같으면 두 행렬의 차

 
  int** tranMatrixA = transpose_Matrix(matrixA, rowsA, colsA);
  printf("Transpose of matrix A:\n");
  print_Matrix(tranMatrixA, colsA, rowsA);  //전치 행렬을 구하는 작업 수행

  int** multiMatrix = multiply_Matrix(matrixA, matrixB, rowsA, colsA, colsB);
  printf("Multiplication of matrix A and B:\n");    //두 행렬의 곱 구함
  if(isEqual_cr != 1) printf("SRY, Can't Multiplication\n");  
  // A 헹렬의 열과 B 행렬의 행의 크기 다르면 두 행렬의 곱을 구하는 연산을 수행할 수 없음
  else print_Matrix(multiMatrix, rowsA, colsB);

  
  free_Matrix(matrixA, rowsA);
  free_Matrix(matrixB, rowsB);
  free_Matrix(addMatrix, rowsA);
  free_Matrix(subtMatrix, rowsA);
  free_Matrix(tranMatrixA, colsA);
  free_Matrix(multiMatrix, rowsA);
// 각 행렬에 할당했던 메모리를 free함수를 통해 해제

  return 0; //0을 리턴해 프로그램을 확실히 종료시킴
  printf("[----- [leeyesol] [2023070003] -----]");  //학번과 이름 출력
}   //메인 함수의 종료