#ifndef GRID_LAYOUT_H
#define GRID_LAYOUT_H

#define RESULT_FIELD_FONT_SIZE 36

#define NUM_ROWS 6
#define NUM_COLS 4

#define GRID_CELL_WIDTH  50
#define GRID_CELL_HEIGHT 30

#define PADDING 3

/* As the button sizes increase, need to also account for in-between padding */
#define BUTTON_WIDTH         GRID_CELL_WIDTH
#define MEDIUM_BUTTON_WIDTH  (GRID_CELL_WIDTH * 2) + PADDING
#define LARGE_BUTTON_WIDTH   (GRID_CELL_WIDTH * 3) + (PADDING * 2)

#define BUTTON_HEIGHT        GRID_CELL_HEIGHT

/* Result Field is 4 cells wide, which means it will have the equivalent of 3 paddings */
#define RESULT_FIELD_WIDTH   ((GRID_CELL_WIDTH * 4) + (PADDING * 3))
#define RESULT_FIELD_HEIGHT  GRID_CELL_HEIGHT

#define ROW_1 (PADDING * 2)
#define ROW_2 (ROW_1 + GRID_CELL_HEIGHT + (PADDING * 4))
#define ROW_3 (ROW_2 + GRID_CELL_HEIGHT + PADDING)
#define ROW_4 (ROW_3 + GRID_CELL_HEIGHT + PADDING)
#define ROW_5 (ROW_4 + GRID_CELL_HEIGHT + PADDING)
#define ROW_6 (ROW_5 + GRID_CELL_HEIGHT + PADDING)
#define ROW_7 (ROW_6 + GRID_CELL_HEIGHT + PADDING)
#define LAST_ROW ROW_7

#define COL_1 (PADDING * 2)
#define COL_2 (COL_1 + GRID_CELL_WIDTH + PADDING)
#define COL_3 (COL_2 + GRID_CELL_WIDTH + PADDING)
#define COL_4 (COL_3 + GRID_CELL_WIDTH + PADDING)
#define LAST_COL COL_4

#define WINDOW_WIDTH  (NUM_COLS * GRID_CELL_WIDTH) + ((NUM_COLS + 1) * PADDING) + PADDING
#define WINDOW_HEIGHT RESULT_FIELD_HEIGHT + (PADDING * 2) + (NUM_ROWS * GRID_CELL_HEIGHT) + ((NUM_ROWS + 1) * PADDING) + (PADDING * 3)

#endif /* GRID_LAYOUT_H */
