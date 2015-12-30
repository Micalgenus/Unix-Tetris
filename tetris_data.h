#ifndef __TETRIS_DATA_H__
#define __TETRIS_DATA_H__

#include "data.h"

#define BLOCK_WIDTH	4
#define BLOCK_HEIGHT	4
#define MAP_HEIGHT	21
#define MAP_WIDTH	10

typedef char block[BLOCK_WIDTH][BLOCK_HEIGHT];

typedef struct {
	char data[MAP_HEIGHT + 1][MAP_WIDTH + 2];
	int player;
	int now;
	int next;
	int rotate;
	int x;
	int y;
} tetris_map;

#define DATA_T	1
#define DATA_L	2
#define DATA_J	3
#define DATA_S	4
#define DATA_2	5
#define DATA_N	6
#define DATA_I	7
#define DATA_NONE	0
#define DATA_WALL	8
#define DATA_DUMMY	8

#define BLOCK_NUM	7

#define MOVE_OK	0x100

int kbhit(void);
void MapInitialize(tetris_map* map);
int ClearCheck(int play_num, tetris_map* map);
void AddBlockDummy(int play_num, tetris_map* map, int dummy_size, int dummy_position);
int MoveBlock(int play_num, tetris_map* map, int direction);
void InsertData(int num, tetris_map* map);
int EndCheck(int num, tetris_map* map);

#endif /* __TETRIS_DATA_H__ */
