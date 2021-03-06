#ifndef __PRINT_DATA_H__
#define __PRINT_DATA_H__

#include "tetris_data.h"

#define BLOCK ("\xa1\xe1") // ■
#define BLOCK_NONE	("  ")
#define BLOCK_HIDE	("")

#define PRINT_NONE 	(1)
#define PRINT_HIDE	(2)

#define BLOCK_SIZE	(2)

#define NEXT_WIDTH	BLOCK_WIDTH
#define NEXT_HEIGHT	BLOCK_HEIGHT

#define MAP_MARGIN_TOP	(1)
#define MAP_MARGIN_LEFT	(2)
#define MAP_MARGIN_RIGHT	(4)
#define NEXT_MARGIN_TOP	(MAP_MARGIN_TOP + MAP_HEIGHT - NEXT_HEIGHT - 1)
#define NEXT_PADDING_LEFT	(1)
#define NEXT_PADDING_RIGHT	(1)

#define NEXT_FULL_WIDTH	(BLOCK_SIZE + NEXT_PADDING_LEFT + (NEXT_WIDTH * BLOCK_SIZE) + NEXT_PADDING_RIGHT + BLOCK_SIZE)

#define	MAP_NEXT_FULL_WIDTH	(MAP_MARGIN_LEFT + BLOCK_SIZE + (MAP_WIDTH * BLOCK_SIZE) + BLOCK_SIZE + MAP_MARGIN_RIGHT + BLOCK_SIZE + NEXT_PADDING_LEFT + (NEXT_WIDTH * BLOCK_SIZE) + NEXT_PADDING_RIGHT + BLOCK_SIZE)

#define MAP_I_POSITION_X	(MAP_MARGIN_LEFT + BLOCK_SIZE)
#define MAP_I_POSITION_Y	(MAP_MARGIN_TOP)
#define MAP_Y_POSITION_X	(MAP_I_POSITION_X + MAP_NEXT_FULL_WIDTH)
#define MAP_Y_POSITION_Y	(MAP_MARGIN_TOP)
#define NEXT_I_POSITION_X	(MAP_MARGIN_LEFT + BLOCK_SIZE + (MAP_WIDTH * BLOCK_SIZE) + BLOCK_SIZE + MAP_MARGIN_RIGHT)
#define NEXT_I_POSITION_Y	(NEXT_MARGIN_TOP)
#define NEXT_Y_POSITION_X	(NEXT_I_POSITION_X + MAP_NEXT_FULL_WIDTH)
#define NEXT_Y_POSITION_Y	(NEXT_MARGIN_TOP)

#define ERROR_LOG_POSITION	(getmaxy(stdscr) - 1),(0)
#define ERROR_LOG(...)	mvprintw(ERROR_LOG_POSITION, __VA_ARGS__)


#endif /* __PRINT_DATA_H__ */
