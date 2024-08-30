#include <check.h>

#include "s21_matrix.h"

START_TEST(create_1) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(5, 5, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(equal_1) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = B.matrix[0][0] = 1;
  A.matrix[1][0] = B.matrix[1][0] = 2;
  A.matrix[0][1] = B.matrix[0][1] = 3;
  A.matrix[1][1] = B.matrix[1][1] = 4;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), EQUAL);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_2) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = B.matrix[0][0] = 1;
  A.matrix[1][0] = B.matrix[1][0] = 2;
  A.matrix[0][1] = B.matrix[0][1] = 3;
  A.matrix[1][1] = B.matrix[1][1] = 4;
  A.matrix[0][0] = 1.00000003f;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), EQUAL);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_3) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = B.matrix[0][0] = 1;
  A.matrix[1][0] = B.matrix[1][0] = 2;
  A.matrix[0][1] = B.matrix[0][1] = 3;
  A.matrix[1][1] = B.matrix[1][1] = 4;
  A.matrix[0][0] = 1.0000003f;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), NOT_EQUAL);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

//
//
//

START_TEST(sum_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t expected = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  expected.matrix[0][0] = 2;
  expected.matrix[1][0] = 4;
  expected.matrix[0][1] = 6;
  expected.matrix[1][1] = 8;

  A.matrix[0][0] = B.matrix[0][0] = 1;
  A.matrix[1][0] = B.matrix[1][0] = 2;
  A.matrix[0][1] = B.matrix[0][1] = 3;
  A.matrix[1][1] = B.matrix[1][1] = 4;

  int code = s21_sum_matrix(&A, &B, &R);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t expected = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  expected.matrix[0][0] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[0][1] = 7;
  expected.matrix[1][1] = 0;

  A.matrix[0][0] = B.matrix[0][0] = 1;
  A.matrix[1][0] = B.matrix[1][0] = 2;
  A.matrix[0][1] = B.matrix[0][1] = 3;
  A.matrix[1][1] = B.matrix[1][1] = 4;

  A.matrix[0][1] = 10;

  int code = s21_sub_matrix(&A, &B, &R);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_1) {
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t expected = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  expected.matrix[0][0] = 2;
  expected.matrix[1][0] = 4;
  expected.matrix[0][1] = 6;
  expected.matrix[1][1] = 8;

  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[0][1] = 3;
  A.matrix[1][1] = 4;

  int code = s21_mult_number(&A, 2, &R);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t expected = {0};

  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;
  A.matrix[0][1] = 4;
  A.matrix[1][1] = 5;
  A.matrix[2][1] = 6;

  s21_create_matrix(2, 3, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;

  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 9;
  expected.matrix[1][0] = 12;
  expected.matrix[2][0] = 15;
  expected.matrix[0][1] = 11;
  expected.matrix[1][1] = 13;
  expected.matrix[2][1] = 15;
  expected.matrix[0][2] = 17;
  expected.matrix[1][2] = 22;
  expected.matrix[2][2] = 27;

  int code = s21_mult_matrix(&A, &B, &R);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_1) {
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t expected = {0};

  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;
  A.matrix[0][1] = 4;
  A.matrix[1][1] = 5;
  A.matrix[2][1] = 6;

  s21_create_matrix(2, 3, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = 5;
  expected.matrix[1][2] = 6;

  int code = s21_transpose(&A, &R);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(determinant_1) {
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t expected = {0};

  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;
  A.matrix[0][1] = 4;
  A.matrix[1][1] = 5;
  A.matrix[2][1] = 6;

  s21_create_matrix(2, 3, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = 5;
  expected.matrix[1][2] = 6;

  int code = s21_transpose(&A, &R);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);
}
END_TEST

// START_TEST(sum_1) {
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t R = {0};
//   matrix_t expected = {0};

//   s21_create_matrix(2, 2, &A);
//   s21_create_matrix(2, 2, &B);
//   s21_create_matrix(2, 2, &expected);

//   expected.matrix[0][0] = 2;
//   expected.matrix[1][0] = 4;
//   expected.matrix[0][1] = 6;
//   expected.matrix[1][1] = 8;

//   A.matrix[0][0] = B.matrix[0][0] = 1;
//   A.matrix[1][0] = B.matrix[1][0] = 2;
//   A.matrix[0][1] = B.matrix[0][1] = 3;
//   A.matrix[1][1] = B.matrix[1][1] = 4;

//   int code = s21_sum_matrix(&A, &B, &R);

//   ck_assert_int_eq(code, OK);
//   ck_assert_int_eq(s21_eq_matrix(&R, &expected), EQUAL);

//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
//   s21_remove_matrix(&R);
//   s21_remove_matrix(&expected);
// }
// END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, create_1);

  tcase_add_test(tc1_1, equal_1);
  tcase_add_test(tc1_1, equal_2);
  tcase_add_test(tc1_1, equal_3);

  tcase_add_test(tc1_1, sum_1);

  tcase_add_test(tc1_1, sub_1);

  tcase_add_test(tc1_1, mult_number_1);

  tcase_add_test(tc1_1, mult_matrix_1);

  tcase_add_test(tc1_1, transpose_1);

  tcase_add_test(tc1_1, determinant_1);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
