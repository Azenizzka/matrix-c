#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <inttypes.h>
#include <stdlib.h>

#include "math.h"

// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

#define EQUAL 1
#define NOT_EQUAL 0

#define PRECISION_OF_COMPARISON 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#include "utils.h"

// TESTME
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// TESTME
int s21_create_matrix(int rows, int columns, matrix_t *result);

// TESTME
void s21_remove_matrix(matrix_t *A);

// TESTME
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// TESTME
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// TESTME
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// TESTME
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// TESTME
int s21_transpose(matrix_t *A, matrix_t *result);

// TESTME
int s21_determinant(matrix_t *A, double *result);

// TODO
int s21_calc_complements(matrix_t *A, matrix_t *result);

// TODO
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif