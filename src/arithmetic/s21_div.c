#include "s21_arithmetic.h"

//  common division s21_decimal
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    big_decimal value_1_big_decimal = {0};
    big_decimal value_2_big_decimal = {0};
    s21_decimal zero_s21_decimal = {0};
    big_decimal div_result_big_decimal = {0};
    s21_decimal div_result_s21_decimal = {0};
    int function_result = NORMAL;

    if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
      function_result = ZERO_DIVISION;
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
      function_result = NORMAL;
      *result =  zero_s21_decimal;
    } else {
        convert_s21_decimal_to_big_decimal(value_1, &value_1_big_decimal);
        convert_s21_decimal_to_big_decimal(value_2, &value_2_big_decimal);

        div_big_decimal(value_1_big_decimal, value_2_big_decimal, &div_result_big_decimal);

        function_result = convert_big_decimal_to_s21_decimal(div_result_big_decimal,
                                                             &div_result_s21_decimal);
        if (function_result == NORMAL) {
            copy_s21_decimal(div_result_s21_decimal, result);
        }
    }
    return function_result;
}
