#include "computations.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_RESULT_LENGTH 10 /* Includes null terminator */
#define MAX_RESULT_VALUE  999999999

OPERATOR operator;
double x_reg;
double y_reg;

/*********************************************************
 * Function: computations_process_num
 * 
 * Description:
 *     Processes the number key presses.
 *
 ********************************************************/
void computations_process_num(HWND hwnd, int num)
{
    x_reg = (x_reg * 10) + num;
    computations_write_result(hwnd, x_reg);
}

/*********************************************************
 * Function: computations_process_zero
 * 
 * Description:
 *     Processes the zero key press. Will only add a
 *     zero if there is no leading zero (x register != 0)
 *
 ********************************************************/
void computations_process_zero(HWND hwnd)
{
    if (x_reg != 0)
    {
        x_reg = (x_reg * 10);
        computations_write_result(hwnd, x_reg);
    }
}

/*********************************************************
 * Function: computations_process_operator
 * 
 * Description:
 *     Processes the operator key press. This will set
 *     the y register value to the x register, clear
 *     the x register, and set the operator enum value.
 *
 ********************************************************/
void computations_process_operator(HWND hwnd, OPERATOR op_input)
{
    if (OP_NONE == operator)
    {
        y_reg = x_reg;
        x_reg = 0;
        SetDlgItemText(hwnd, RESULT_FIELD_ID, "");
        operator = op_input;
    }
}

/*********************************************************
 * Function: computations_process_special_key
 * 
 * Description:
 *     Processes the special key press. This includes
 *     the equals key and any computation keys.
 *
 ********************************************************/
void computations_process_special_key(HWND hwnd, SPECIAL_KEY special_key)
{
    bool valid_key = true;
    double result = 0;

    if (x_reg != 0)
    {
        switch (special_key)
        {
            case KEY_EQUAL:
                switch(operator)
                {
                    case OP_ADD:      result = x_reg + y_reg; break;
                    case OP_SUBTRACT: result = y_reg - x_reg; break;
                    case OP_MULTIPLY: result = x_reg * y_reg; break;
                    case OP_DIVIDE:   result = y_reg / x_reg; break;
                    default:          valid_key = false;      break;
                }
                break;
            case KEY_INV:       result = 1 / x_reg;         break;
            case KEY_SQRT:      result = sqrt(x_reg);       break;
            case KEY_SQUARE:    result = x_reg * x_reg;     break;
            case KEY_BACKSPACE: result = floor(x_reg / 10); break;
            case KEY_POS_NEG:   result = x_reg * -1;        break;
            default:            valid_key = false;          break;
        }

        if (valid_key)
        {
            if (result < MAX_RESULT_VALUE)
            {
                x_reg = result;
                computations_write_result(hwnd, x_reg);
            }
            else
            {
                SetDlgItemText(hwnd, RESULT_FIELD_ID, "OVERLFOW");
                computations_clear_registers();
            }
        }
            
        operator    = OP_NONE;
        special_key = KEY_NONE;
    }
}
    
/*********************************************************
 * Function: computations_process_clear
 * 
 * Description:
 *     Processes the clear key press.
 *
 ********************************************************/
void computations_process_clear(HWND hwnd)
{
    SetDlgItemText(hwnd, RESULT_FIELD_ID, "");
    computations_clear_registers();
}

/*********************************************************
 * Function: computations_clear_registers
 * 
 * Description:
 *     Sets the x and y register values to 0.
 *
 ********************************************************/
void computations_clear_registers()
{
    x_reg = 0;
    y_reg = 0;
}

/*********************************************************
 * Function: computations_write_result
 * 
 * Description:
 *     Writes the value of the x register to the result
 *     field.
 *
 ********************************************************/
void computations_write_result(HWND hwnd, double result_fl)
{
    char result_str[MAX_RESULT_LENGTH];
    snprintf(result_str, MAX_RESULT_LENGTH, "%0.9g", result_fl);
    SetDlgItemText(hwnd, RESULT_FIELD_ID, result_str);
}
