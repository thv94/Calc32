#ifndef CALC_H
#define CALC_H

#include "global.h"
#include "grid_layout.h"
#include "computations.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void calc_render_gui(HWND hwnd, HINSTANCE hInstance);
void calc_process_commands(HWND hwnd, WORD wParam);
WORD calc_lookup_button_id_from_key_id(int search_key_id);

#endif /* CALC_H */