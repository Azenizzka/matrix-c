#include "utils.h"

void print_matrix(matrix_t *A) {
  printf("\n[%d][%d]\n", A->rows, A->columns);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) printf("%.1lf ", A->matrix[i][j]);
    printf("\n");
  }
}

uint8_t is_square_matrix(matrix_t A) { return A.rows == A.columns; }

uint8_t is_incorrect_matrix(matrix_t *A) {
  if (A == NULL) return INCORRECT_MATRIX;

  if (A->columns <= 0 || A->rows <= 0) return INCORRECT_MATRIX;

  return OK;
}

uint8_t inf_or_nan(matrix_t A) {
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++)
      if (isinf(A.matrix[i][j]) || isnan(A.matrix[i][j]))
        return CALCULATION_ERROR;

  return OK;
}

double **create_matrix(int rows, int cols) {
  double **matrix = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++)
    matrix[i] = (double *)malloc(cols * sizeof(double));
  return matrix;
}

void free_matrix(double **matrix, int rows) {
  for (int i = 0; i < rows; i++) free(matrix[i]);

  free(matrix);
}

void get_matrix_without_row_and_col(double **matrix, int size, int row, int col,
                                    double **new_matrix) {
  int newRow = 0, newCol = 0;
  for (int i = 0; i < size; i++) {
    if (i != row) {
      for (int j = 0; j < size; j++) {
        if (j != col) {
          new_matrix[newRow][newCol++] = matrix[i][j];
        }
      }
      newRow++;
      newCol = 0;
    }
  }
}

double matrix_determinant(double **matrix, int size) {
  double det = 0;
  int degree = 1;

  if (size == 1) return matrix[0][0];
  if (size == 2)
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

  double **new_matrix = create_matrix(size - 1, size - 1);

  for (int j = 0; j < size; j++) {
    get_matrix_without_row_and_col(matrix, size, 0, j, new_matrix);

    det += (degree * matrix[0][j] * matrix_determinant(new_matrix, size - 1));
    degree = -degree;
  }

  free_matrix(new_matrix, size - 1);

  return det;
}