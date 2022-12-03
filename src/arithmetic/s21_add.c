#include "s21_arithmetic.h"

//  common addition s21_decimal
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    big_decimal value_1_big_decimal = {0};
    big_decimal value_2_big_decimal = {0};
    big_decimal common_result_big_decimal = {0};
    s21_decimal common_result_s21_decimal = {0};
    s21_decimal empty_array = {0};
    int function_result = 0;

    convert_s21_decimal_to_big_decimal(value_1, &value_1_big_decimal);
    convert_s21_decimal_to_big_decimal(value_2, &value_2_big_decimal);

    add_big_decimal(value_1_big_decimal, value_2_big_decimal, &common_result_big_decimal);

    function_result = convert_big_decimal_to_s21_decimal(common_result_big_decimal,
                                                         &common_result_s21_decimal);

    if (function_result == 0) {
        copy_s21_decimal(common_result_s21_decimal, result);
    } else {
        copy_s21_decimal(empty_array, result);
    }

    return function_result;
}
