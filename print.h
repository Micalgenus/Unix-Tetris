#ifndef __PRINT_H__
#define __PRINT_H__

#include <ncurses.h>

#include "print_data.h"
#include "tetris_data.h"

#define ENDING_TIME	2

void init_win(void);
void SetColor(void);
void Print(tetris_map* map);
void PrintBlockCell(int y, int x, int num, int mode);
void PrintMap(int play_num, tetris_map* map);
void PrintMapData(int play_num, tetris_map* map);
void PrintMapBlock(int play_num, tetris_map* map);
void PrintNext(int play_num, int block_num);
void PrintNextBorder(int play_num);
void PrintNextBlock(int play_num, int block_num);

void PrintLose(void);
void PrintWin(void);

#endif /* __PRINT_H__ */
