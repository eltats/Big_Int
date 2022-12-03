#include "s21_another.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    big_decimal value_1_big_decimal = {0};
    big_decimal value_2_big_decimal = {{10}};
    big_decimal div_result_big_decimal = {0};
    big_decimal div_reminder_big_decimal = {0};
    big_decimal one_big_decimal = {{1}};
    big_decimal five_big_decimal = {{5}};
    big_decimal add_result_big_decimal = {0};
    unsigned int pow_size;
    unsigned int sign;
    bool function_result = 0;

    convert_s21_decimal_to_big_decimal(value, &value_1_big_decimal);
    pow_size = pow_to_int_big_decimal(value_1_big_decimal);
    sign = get_sign_big_decimal(&value_1_big_decimal);
    for (unsigned int i = 0; i < pow_size; i++) {
        div_mantissa_big_decimal(value_1_big_decimal, value_2_big_decimal,
                                 &div_result_big_decimal, &div_reminder_big_decimal);
        copy_big_decimal_value(div_result_big_decimal, &value_1_big_decimal);
    }

    if (pow_size > 0) {
        if (((gt_mantissa_big_decimal(div_reminder_big_decimal, five_big_decimal) ||
         eq_mantissa_big_decimal(div_reminder_big_decimal, five_big_decimal)) && sign == 0)
         || ((gt_mantissa_big_decimal(div_reminder_big_decimal, five_big_decimal) ||
         eq_mantissa_big_decimal(div_reminder_big_decimal, five_big_decimal))
          && sign == 1)) {
            add_mantissa_big_decimal(value_1_big_decimal, one_big_decimal, &add_result_big_decimal);
            copy_big_decimal_value(add_result_big_decimal, &value_1_big_decimal);
        }
    }

    value_1_big_decimal.bits[6] = value_1_big_decimal.bits[6] >> 30 << 30;
    convert_big_decimal_to_s21_decimal(value_1_big_decimal, result);

    return function_result;
}
