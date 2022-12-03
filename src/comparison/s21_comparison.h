#ifndef SRC_COMPARISON_S21_COMPARISON_H_
#define SRC_COMPARISON_S21_COMPARISON_H_

#include "../s21_decimal.h"
#include "../additional/s21_helpers.h"

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

#endif  // SRC_COMPARISON_S21_COMPARISON_H_
