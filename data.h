#ifndef __DATA_H__
#define __DATA_H__

#ifndef TRUE
#define TRUE !0
#endif /* TRUE */
#ifndef FALSE
#define FALSE 0
#endif /* FALSE */

#define BLOCK_HEIGHT 4
#define MAP_PADDING_LEFT 2
#define MAP_PADDING_RIGHT 4
#define MAP_PADDING_TOP 1
#define BLOCK_PADDING_WIDTH 1

#define PORT_NUMBER	(15892)
#define ROOM_NUMBER	(30)
#define PORT_START (PORT_NUMBER + 1)
#define PORT_END	(PORT_NUMBER + ROOM_NUMBER)

#define DATA_CLEAR	0

#define MODE_CONNECT	0
#define MODE_CREATE	1
#define MODE_MOVE	2
#define MODE_ATTACK	3
#define MODE_END	4
#define MODE_CLEAR 5
#define MODE_NONE	6
#define MODE_ROTATE	7
// MODE_BOTTOM = Blocks reach the bottom
#define MODE_BOTTOM	8

#define CONNECT_OK	0x100
#define GAME_WIN	0x200
#define GAME_LOSE	0x300
#define BLOCK_DATA 0x400

#define MOVE_DOWN	0x10
#define MOVE_LEFT	0x20
#define MOVE_RIGHT	0x30
#define MOVE_ROTATE_L	0x40
#define MOVE_ROTATE_R	0x50
#define MOVE_DROP	0x60

#define MY_KEY_LEFT 0x44
#define MY_KEY_DOWN 0x42
#define MY_KEY_RIGHT 0x43
#define MY_KEY_UP	0x41

#define BLOCK_NUM	7

// 1000000usec = 1sec
#define DISCON_TIME_SEC	5
#define DISCON_TIME_USEC	0

#define DOWN_TIME_SEC	1
#define DOWN_TIME_USEC	0

#define U_SEC 1000000

struct game_data {
	unsigned int user_number;
	unsigned char mode;
	unsigned int data;
};

#endif /* __DATA_H__ */
