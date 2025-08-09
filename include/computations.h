#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "global.h"

void computations_process_num(HWND hwnd, int num);
void computations_process_zero(HWND hwnd);
void computations_process_operator(HWND hwnd, OPERATOR op_input);
void computations_process_special_key(HWND hwnd, SPECIAL_KEY special_key);
void computations_process_clear(HWND hwnd);
void computations_clear_registers(void);
void computations_write_result(HWND hwnd, double result_fl);

#endif /* COMPUTATIONS_H */
