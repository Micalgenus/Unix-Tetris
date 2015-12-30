#include <ncurses.h>

#include "tetris_data.h"

tetris_map game_map[2];

const block game_block[BLOCK_NUM][4] = {
	//{ // T
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_T, DATA_NONE, DATA_NONE,
		DATA_T, DATA_T, DATA_T, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	//} ,

	,//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_T, DATA_NONE, DATA_NONE, 
		DATA_NONE, DATA_T, DATA_T, DATA_NONE,
		DATA_NONE, DATA_T, DATA_NONE, DATA_NONE 
	//},

	,//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_T, DATA_T, DATA_T, DATA_NONE,
		DATA_NONE, DATA_T, DATA_NONE, DATA_NONE 
	//},

	,//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_T, DATA_NONE, DATA_NONE,
		DATA_T, DATA_T, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_T, DATA_NONE, DATA_NONE 
	//},

	,//{// L
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_L, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_L, DATA_L, DATA_L, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	//},

	,//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_L, DATA_L, DATA_NONE,
		DATA_NONE, DATA_L, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_L, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_L, DATA_L, DATA_L, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_L, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_L, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_L, DATA_NONE,
		DATA_NONE, DATA_L, DATA_L, DATA_NONE 
	,//},

	//{// J
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_J, DATA_NONE,
		DATA_J, DATA_J, DATA_J, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_J, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_J, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_J, DATA_J, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_J, DATA_J, DATA_J, DATA_NONE,
		DATA_J, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_J, DATA_J, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_J, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_J, DATA_NONE, DATA_NONE 
	,//},

	//{// S
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_S, DATA_S, DATA_NONE,
		DATA_S, DATA_S, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_S, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_S, DATA_S, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_S, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_S, DATA_S, DATA_NONE,
		DATA_S, DATA_S, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_S, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_S, DATA_S, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_S, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{// 2
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_2, DATA_2, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_2, DATA_2, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_2, DATA_NONE, DATA_NONE,
		DATA_2, DATA_2, DATA_NONE, DATA_NONE,
		DATA_2, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_2, DATA_2, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_2, DATA_2, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_2, DATA_NONE,
		DATA_NONE, DATA_2, DATA_2, DATA_NONE,
		DATA_NONE, DATA_2, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{// N
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_N, DATA_N, DATA_NONE,
		DATA_NONE, DATA_N, DATA_N, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_N, DATA_N, DATA_NONE,
		DATA_NONE, DATA_N, DATA_N, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_N, DATA_N, DATA_NONE,
		DATA_NONE, DATA_N, DATA_N, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_N, DATA_N, DATA_NONE,
		DATA_NONE, DATA_N, DATA_N, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{// I
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_I, DATA_I, DATA_I, DATA_I,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_I, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_I, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_I, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_I, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_I, DATA_I, DATA_I, DATA_I,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_NONE, DATA_NONE 
	,//},

	//{
		DATA_NONE, DATA_NONE, DATA_I, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_I, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_I, DATA_NONE,
		DATA_NONE, DATA_NONE, DATA_I, DATA_NONE 
	//}
};

int kbhit(void) {
	int ch = getch();
	if (ch != ERR) {
		ungetch(ch);
		return 1;
	} else {
		return 0;
	}
}

void MapInitialize(tetris_map* map) {
	int i, j, num;
	for (num = 0; num < 2; num++)
		for (i = 0; i <= MAP_HEIGHT; i++)
			for (j = 0; j <= MAP_WIDTH + 1; j++)
				map[num].data[i][j] = ( ((i == MAP_HEIGHT) || (j == 0) || (j == (MAP_WIDTH + 1))) ? DATA_WALL : DATA_NONE );
}

int ClearCheck(int play_num, tetris_map* map) {
	int i, j, x = 0, y = 0, count = 0;
	for (i = MAP_HEIGHT - 1; i >= 0; i--) {
		for (j = 1; j <= MAP_WIDTH; j++)
			if (map[play_num].data[i][j] == DATA_NONE) break;

		if (j == (MAP_WIDTH + 1)) {
			count++;
			for (y = i; y > 0; y--)
				for (x = 1; x <= MAP_WIDTH; x++)
					map[play_num].data[y][x] = map[play_num].data[y - 1][x];

			i++;
		}
	}
	return count;
}

void AddBlockDummy(int play_num, tetris_map* map, int dummy_size, int dummy_position) {
	int i, j;
	for (i = 0; i < MAP_HEIGHT; i++)
		for (j = 1; j <= MAP_WIDTH; j++)
			map[play_num].data[i][j] = map[play_num].data[i + dummy_size][j];

	for (i = 1; i <= dummy_size; i++)
		for (j = 1; j <= MAP_WIDTH; j++)
			map[play_num].data[MAP_HEIGHT - i][j] = (j == (dummy_position + 1) ? DATA_NONE : DATA_DUMMY);

//	mvprintw(getmaxy(stdscr) - 1, 0, "dummy-size: %d, dummy-position: %d", dummy_size, dummy_position);
}

int MoveBlock(int num, tetris_map* map, int d) {
	int i, j, x = 0, y = 0, rotate = 0, result = 0;
	int check = TRUE;

	switch (d) {
		case MOVE_DOWN:
			rotate = 0;
			x = 0;
			y = 1;
			break;
		case MOVE_LEFT:
			rotate = 0;
			x = -1;
			y = 0;
			break;
		case MOVE_RIGHT:
			rotate = 0;
			x = 1;
			y = 0;
			break;
		case MOVE_ROTATE_R:
			rotate = (map[num].now == 3 ? -3 : 1);
			x = 0;
			y = 0;
			break;
		case MOVE_ROTATE_L:
			rotate = (map[num].now == 0 ? 3 : -1);
			x = 0;
			y = 0;
			break;
	}

	for (i = 0; i < BLOCK_HEIGHT; i++)
		for (j = 0; j < BLOCK_WIDTH; j++)
			if (game_block[map[num].now][map[num].rotate + rotate][i][j] != DATA_NONE)
				if (map[num].data[map[num].y + i + y][map[num].x + j + 1 + x] != DATA_NONE)
					check = FALSE;

	if (check == TRUE) result = MOVE_OK;

	return result;
}

void InsertData(int num, tetris_map* map) {
	int i, j;
	for (i = 0; i < BLOCK_HEIGHT; i++)
		for (j = 0; j < BLOCK_WIDTH; j++)
			if (game_block[map[num].now][map[num].rotate][i][j] != DATA_NONE)
				map[num].data[map[num].y + i][map[num].x + j + 1] = game_block[map[num].now][map[num].rotate][i][j];
}

int EndCheck(int num, tetris_map* map) {
	int i, j;
	if (num == 0) return DATA_NONE;
	for (i = 0; i < BLOCK_HEIGHT; i++)
		for (j = 0; j < BLOCK_WIDTH; j++)
			if (game_block[map[num].now][map[num].rotate][i][j] != DATA_NONE)
				if (map[num].data[map[num].y + i][map[num].x + j + 1] != DATA_NONE)
					return GAME_LOSE;
}
