#ifndef SRC_ANOTHER_S21_ANOTHER_H_
#define SRC_ANOTHER_S21_ANOTHER_H_

#include "../s21_decimal.h"
#include "../additional/s21_big_decimal.h"
#include "../additional/s21_helpers.h"

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  //  SRC_ANOTHER_S21_ANOTHER_H_

