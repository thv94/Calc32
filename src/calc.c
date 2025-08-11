#include "calc.h"

#define NUM_BUTTONS 24
#define NO_KEY_BIND -1
BUTTON_ATTRIBUTES BUTTON_TABLE[NUM_BUTTONS] =
{/*   BUTTON_ID            TEXT    ROW    COL    WIDTH                HEIGHT         KEY ID      */
    { SQRT_BUTTON_ID,      "SQR",  ROW_2, COL_1, BUTTON_WIDTH,        BUTTON_HEIGHT, NO_KEY_BIND },
    { SQUARE_BUTTON_ID,    "^2",   ROW_2, COL_2, BUTTON_WIDTH,        BUTTON_HEIGHT, NO_KEY_BIND },
    { INVERSE_BUTTON_ID,   "INV",  ROW_2, COL_3, BUTTON_WIDTH,        BUTTON_HEIGHT, NO_KEY_BIND },
    { POS_NEG_BUTTON_ID,   "+/-",  ROW_2, COL_4, BUTTON_WIDTH,        BUTTON_HEIGHT, NO_KEY_BIND },

    { CLEAR_BUTTON_ID,     "AC",   ROW_3, COL_1, MEDIUM_BUTTON_WIDTH, BUTTON_HEIGHT, VK_ESCAPE   },
    { BACKSPACE_BUTTON_ID, "BSP",  ROW_3, COL_3, BUTTON_WIDTH,        BUTTON_HEIGHT, VK_BACK     },
    { DIVIDE_BUTTON_ID,    "/",    ROW_3, COL_4, BUTTON_WIDTH,        BUTTON_HEIGHT, VK_OEM_2    },

    { SEVEN_BUTTON_ID,     "7",    ROW_4, COL_1, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x37        },
    { EIGHT_BUTTON_ID,     "8",    ROW_4, COL_2, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x38        },
    { NINE_BUTTON_ID,      "9",    ROW_4, COL_3, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x39        },
    { MULTIPLY_BUTTON_ID,  "*",    ROW_4, COL_4, BUTTON_WIDTH,        BUTTON_HEIGHT, NO_KEY_BIND },

    { FOUR_BUTTON_ID,      "4",    ROW_5, COL_1, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x34        },
    { FIVE_BUTTON_ID,      "5",    ROW_5, COL_2, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x35        },
    { SIX_BUTTON_ID,       "6",    ROW_5, COL_3, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x36        },
    { SUBTRACT_BUTTON_ID,  "-",    ROW_5, COL_4, BUTTON_WIDTH,        BUTTON_HEIGHT, VK_OEM_MINUS },
    
    { ONE_BUTTON_ID,       "1",    ROW_6, COL_1, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x31        },
    { TWO_BUTTON_ID,       "2",    ROW_6, COL_2, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x32        },
    { THREE_BUTTON_ID,     "3",    ROW_6, COL_3, BUTTON_WIDTH,        BUTTON_HEIGHT, 0x33        },
    { ADD_BUTTON_ID,       "+",    ROW_6, COL_4, BUTTON_WIDTH,        BUTTON_HEIGHT, VK_OEM_PLUS },

    { ZERO_BUTTON_ID,      "0",    ROW_7, COL_1, LARGE_BUTTON_WIDTH,  BUTTON_HEIGHT, 0x30        },
    { EQUAL_BUTTON_ID,     "=",    ROW_7, COL_4, BUTTON_WIDTH,        BUTTON_HEIGHT, VK_RETURN   },
};

const char WINDOW_TITLE[] = "Calc32";
const char RESULT_FIELD_FONT[] = "Arial";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;
    int client_width;
    int client_height;
    RECT windowRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    /* UNUSED */
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    /* Register the Window Class */
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "WindowClass";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, FALSE, 0);

    client_width  = windowRect.right - windowRect.left;
    client_height = windowRect.bottom - windowRect.top;

    hwnd = CreateWindowEx(
        0,
        "WindowClass",
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        client_width, client_height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (NULL == hwnd)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    calc_render_gui(hwnd, hInstance);

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WORD button_id;
    switch(msg)
    {
        case WM_KEYDOWN:
            button_id = calc_lookup_button_id_from_key_id((int)wParam);
            calc_process_commands(hwnd, button_id);
            break;
        case WM_COMMAND:
            calc_process_commands(hwnd, LOWORD(wParam));
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
            break;
    }

    return 0;
}

void calc_render_gui(HWND hwnd, HINSTANCE hInstance)
{
    HWND hwnd_result_field;
    int i;

    HFONT result_field_font =
        CreateFont(
            RESULT_FIELD_FONT_SIZE,
            0,
            0,
            0,
            FW_DONTCARE,
            FALSE,
            FALSE,
            FALSE,
            ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH,
            RESULT_FIELD_FONT
        );

    hwnd_result_field = 
        CreateWindowEx(
            0,
            "EDIT",
            0,
            WS_CHILD | WS_VISIBLE | WS_DISABLED | ES_RIGHT,
            COL_1, ROW_1,
            RESULT_FIELD_WIDTH, RESULT_FIELD_HEIGHT,
            hwnd,
            (HMENU)RESULT_FIELD_ID,
            hInstance,
            NULL
    );
    SendMessage(hwnd_result_field, WM_SETFONT, (WPARAM)result_field_font, TRUE);

    for (i= 0; i < NUM_BUTTONS; i++)
    {
        CreateWindow(
            "BUTTON",
            BUTTON_TABLE[i].text,
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            BUTTON_TABLE[i].col, BUTTON_TABLE[i].row,
            BUTTON_TABLE[i].width, BUTTON_TABLE[i].height,
            hwnd,
            (HMENU)(UINT_PTR)BUTTON_TABLE[i].button_id,
            hInstance,
            NULL
        );
    }
}

void calc_process_commands(HWND hwnd, WORD wParam)
{
    switch (wParam)
    {
        case ONE_BUTTON_ID:       computations_process_num(hwnd, 1); break;
        case TWO_BUTTON_ID:       computations_process_num(hwnd, 2); break;
        case THREE_BUTTON_ID:     computations_process_num(hwnd, 3); break;
        case FOUR_BUTTON_ID:      computations_process_num(hwnd, 4); break;
        case FIVE_BUTTON_ID:      computations_process_num(hwnd, 5); break;
        case SIX_BUTTON_ID:       computations_process_num(hwnd, 6); break;
        case SEVEN_BUTTON_ID:     computations_process_num(hwnd, 7); break;
        case EIGHT_BUTTON_ID:     computations_process_num(hwnd, 8); break;
        case NINE_BUTTON_ID:      computations_process_num(hwnd, 9); break;
        case ZERO_BUTTON_ID:      computations_process_zero(hwnd);   break;
        case CLEAR_BUTTON_ID:     computations_process_clear(hwnd);  break;
        case BACKSPACE_BUTTON_ID: computations_process_special_key(hwnd, KEY_BACKSPACE); break;
        case POS_NEG_BUTTON_ID:   computations_process_special_key(hwnd, KEY_POS_NEG);   break;
        case SQUARE_BUTTON_ID:    computations_process_special_key(hwnd, KEY_SQUARE);    break;
        case INVERSE_BUTTON_ID:   computations_process_special_key(hwnd, KEY_INV);       break;
        case SQRT_BUTTON_ID:      computations_process_special_key(hwnd, KEY_SQRT);      break;
        case ADD_BUTTON_ID:       computations_process_operator(hwnd, OP_ADD);           break;
        case SUBTRACT_BUTTON_ID:  computations_process_operator(hwnd, OP_SUBTRACT);      break;
        case DIVIDE_BUTTON_ID:    computations_process_operator(hwnd, OP_DIVIDE);        break;
        case MULTIPLY_BUTTON_ID:  computations_process_operator(hwnd, OP_MULTIPLY);      break;
        case EQUAL_BUTTON_ID:     computations_process_special_key(hwnd, KEY_EQUAL);     break;
        default:                  /* Invalid */ break;
    }

    SetFocus(hwnd);
}

WORD calc_lookup_button_id_from_key_id(int search_key_id)
{
    int i;

    /* Linear search should be good enough for this small of a table */
    for (i = 0; i < NUM_BUTTONS; i++)
    {
        if (BUTTON_TABLE[i].key_id == search_key_id)
        {
            return (WORD)BUTTON_TABLE[i].button_id;
        }
    }

    return (WORD)NO_KEY_BIND;
}
