#include "print.h"
#include "tetris_data.h"

extern const block game_block[BLOCK_NUM][4];

void init_win(void) {
	initscr();
	start_color();
	SetColor();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	scrollok(stdscr, TRUE);
	curs_set(0);
}

void SetColor(void) {
	// num, text-color, background-color
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);

	use_default_colors();
}

void PrintBlockCell(int y, int x, int num, int mode) {
	attron(COLOR_PAIR(num));
	mvprintw(y, x, (num ? BLOCK : (mode == PRINT_HIDE ? BLOCK_HIDE : BLOCK_NONE)));
}

void Print(tetris_map* map) {
	PrintMap(0, &(map[0]));
	PrintMap(1, &(map[1]));
	PrintNext(0, map[0].next);
	PrintNext(1, map[1].next);
}

void PrintMap(int play_num, tetris_map* map) {
	PrintMapData(play_num, map);
	PrintMapBlock(play_num, map);
}

void PrintMapData(int play_num, tetris_map* map) {
	int x = 0, y = 0, i, j;
	if (play_num == 0) {
		x = MAP_I_POSITION_X;
		y = MAP_I_POSITION_Y;
	} else if (play_num == 1) {
		x = MAP_Y_POSITION_X;
		y = MAP_Y_POSITION_Y;
	} else {
		ERROR_LOG("Wrong Play Number: %d\n", play_num);
//		mvprintw(ERROR_LOG_POSITION, "Wrong play num: %d", play_num);
		return;
	}

	for (i = 0; i <= MAP_WIDTH + 1; i++)
		for (j = 0; j <= MAP_HEIGHT; j++)
			PrintBlockCell(y + j, x + (i * BLOCK_SIZE), map->data[j][i], PRINT_NONE);
}

void PrintMapBlock(int play_num, tetris_map* map) {
	int x = 0, y = 0, i, j;
	if (play_num == 0) {
		x = MAP_I_POSITION_X + BLOCK_SIZE;
		y = MAP_I_POSITION_Y;
	} else if (play_num == 1) {
		x = MAP_Y_POSITION_X + BLOCK_SIZE;
		y = MAP_Y_POSITION_Y;
	} else {
		ERROR_LOG("Wrong Play Number: %d\n", play_num);
//		mvprintw(ERROR_LOG_POSITION, "Wrong play num: %d", play_num);
		return;
	}

	for (i = 0; i < BLOCK_WIDTH; i++)
		for (j = 0; j < BLOCK_HEIGHT; j++)
			PrintBlockCell(y + j + map->y, x + ((i + map->x) * BLOCK_SIZE), game_block[map->now][map->rotate][j][i], PRINT_HIDE);
}

void PrintNext(int play_num, int block_num){
	PrintNextBorder(play_num);
	PrintNextBlock(play_num, block_num);
}

void PrintNextBorder(int play_num) {
	int x = 0, y = 0, i, j;
	if (play_num == 0) {
		x = NEXT_I_POSITION_X;
		y = NEXT_I_POSITION_Y;
	} else if (play_num == 1) {
		x = NEXT_Y_POSITION_X;
		y = NEXT_Y_POSITION_Y;
	} else {
		ERROR_LOG("Wrong Play Number: %d\n", play_num);
//		mvprintw(ERROR_LOG_POSITION, "Wrong play num: %d", play_num);
		return;
	}

	for (i = 0; i < (NEXT_FULL_WIDTH / BLOCK_SIZE); i++)
		for (j = 0; j <= (NEXT_HEIGHT + 1); j++)
			PrintBlockCell(y + j, x + (i * BLOCK_SIZE),
				(
					(
						(i == 0) ||
						(i == ((NEXT_FULL_WIDTH / BLOCK_SIZE) - 1)) ||
						(j == 0) ||
						(j == NEXT_HEIGHT + 1)
					)
					? DATA_WALL
					: DATA_NONE
				),
				PRINT_NONE
			);

	attron(COLOR_PAIR(8));
	mvprintw(y - 1, x + (NEXT_FULL_WIDTH / 2) - 2, "Next");
}

void PrintNextBlock(int play_num, int block_num) {
	int x = 0, y = 0, i, j;
	if (play_num == 0) {
		x = NEXT_I_POSITION_X + BLOCK_SIZE + NEXT_PADDING_LEFT;
		y = NEXT_I_POSITION_Y + 1;
	} else if (play_num == 1) {
		x = NEXT_Y_POSITION_X + BLOCK_SIZE + NEXT_PADDING_LEFT;
		y = NEXT_Y_POSITION_Y + 1;
	}

	for (i = 0; i < NEXT_WIDTH; i++)
		for (j = 0; j < NEXT_HEIGHT; j++)
			PrintBlockCell(y + j, x + (i * BLOCK_SIZE), game_block[block_num][0][j][i], PRINT_HIDE);
}

void PrintLose(void) {
	clear();
	attron(COLOR_PAIR(4));
	mvprintw(getmaxy(stdscr) / 2, (getmaxx(stdscr) / 2) - 4, "You Lose");
	refresh();
	sleep(ENDING_TIME);
}

void PrintWin(void) {
	clear();
	attron(COLOR_PAIR(2));
	mvprintw(getmaxy(stdscr) / 2, (getmaxx(stdscr) / 2) - 4, "You Win");
	refresh();
	sleep(ENDING_TIME);
}
