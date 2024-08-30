#ifndef UTILS_H_
#define UTILS_H_

#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

uint8_t is_square_matrix(matrix_t A);
uint8_t inf_or_nan(matrix_t A);
uint8_t is_incorrect_matrix(matrix_t *A);
double matrix_determinant(double **matrix, int size);
void get_matrix_without_row_and_col(double **matrix, int size, int row, int col,
                                    double **new_matrix);

void print_matrix(matrix_t *A);

#endif