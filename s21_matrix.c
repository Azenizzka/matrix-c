#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL) return NOT_EQUAL;
  if (A->columns != B->columns || A->rows != B->rows) return NOT_EQUAL;

  for (int row = 0; row < A->rows; row++)
    for (int column = 0; column < A->columns; column++)
      if (fabs(A->matrix[row][column] - B->matrix[row][column]) >
          PRECISION_OF_COMPARISON)
        return NOT_EQUAL;

  return EQUAL;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows < 1 || columns < 1) return INCORRECT_MATRIX;

  result->matrix = (double **)calloc(rows, sizeof(double *));

  for (int i = 0; i < rows; i++)
    result->matrix[i] = (double *)calloc(columns, sizeof(double));

  result->rows = rows;
  result->columns = columns;

  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL) return;

  if (A->matrix != NULL && A->columns > 0) {
    A->rows = 0;
    A->columns = 0;

    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);

    free(A->matrix);
  }
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_incorrect_matrix(A) || is_incorrect_matrix(B) || result == NULL)
    return INCORRECT_MATRIX;

  if (A->columns != B->columns || A->rows != B->rows || inf_or_nan(*A) ||
      inf_or_nan(*B))
    return CALCULATION_ERROR;

  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return INCORRECT_MATRIX;

  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      result->matrix[row][column] =
          A->matrix[row][column] + B->matrix[row][column];
    }
  }

  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_incorrect_matrix(A) || is_incorrect_matrix(B) || result == NULL)
    return INCORRECT_MATRIX;

  if (A->columns != B->columns || A->rows != B->rows || inf_or_nan(*A) ||
      inf_or_nan(*B))
    return CALCULATION_ERROR;

  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return INCORRECT_MATRIX;

  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      result->matrix[row][column] =
          A->matrix[row][column] - B->matrix[row][column];
    }
  }

  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (is_incorrect_matrix(A) || result == NULL) return INCORRECT_MATRIX;

  if (inf_or_nan(*A) || isinf(number) || isnan(number))
    return CALCULATION_ERROR;

  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return INCORRECT_MATRIX;

  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      result->matrix[row][column] = A->matrix[row][column] * number;
    }
  }

  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_incorrect_matrix(A) || is_incorrect_matrix(B) || result == NULL)
    return INCORRECT_MATRIX;

  if (A->columns != B->rows || inf_or_nan(*A) || inf_or_nan(*B))
    return CALCULATION_ERROR;

  if (s21_create_matrix(A->rows, B->columns, result) != OK)
    return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      double res = 0;
      for (int k = 0; k < A->columns; k++) {
        res += A->matrix[i][k] * B->matrix[k][j];
      }
      result->matrix[i][j] = res;
    }
  }

  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) return INCORRECT_MATRIX;
  if (s21_create_matrix(A->columns, A->rows, result) != OK)
    return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return OK;
}

int s21_determinant(matrix_t *A, double *result) {
  if (is_incorrect_matrix(A) || result == NULL) return INCORRECT_MATRIX;

  if (!is_square_matrix(*A) || inf_or_nan(*A)) return CALCULATION_ERROR;

  *result = matrix_determinant(A->matrix, A->columns);

  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (is_incorrect_matrix(A) || result == NULL) return INCORRECT_MATRIX;
  if (!is_square_matrix(*A)) return CALCULATION_ERROR;

  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor = {0};

      if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != OK) {
        s21_remove_matrix(result);
        return INCORRECT_MATRIX;
      }

      get_matrix_without_row_and_col(A->matrix, A->rows, i, j, minor.matrix);

      double det;
      if (s21_determinant(&minor, &det) != OK) {
        s21_remove_matrix(&minor);
        s21_remove_matrix(result);
        return CALCULATION_ERROR;
      }

      result->matrix[i][j] = pow(-1, i + j) * det;

      s21_remove_matrix(&minor);
    }
  }

  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_incorrect_matrix(A) || result == NULL) return INCORRECT_MATRIX;

  matrix_t temp = {0};

  double determinant = 0;
  if (s21_determinant(A, &determinant)) return CALCULATION_ERROR;
  if (determinant == 0) return CALCULATION_ERROR;

  s21_calc_complements(A, result);
  s21_transpose(result, &temp);
  s21_remove_matrix(result);
  s21_mult_number(&temp, (1 / determinant), result);
  s21_remove_matrix(&temp);

  return OK;
}
