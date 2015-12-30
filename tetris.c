#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <ncurses.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data.h"
#include "print.h"
#include "tetris_data.h"

#define PRINT printw

extern const block game_block[BLOCK_NUM][4];
unsigned int width, height, px[2], py[2], protate[2], pblock[2], pnext[2];
extern tetris_map game_map[2];

int main(int argc, char* argv[]) {
	int sockfd, len, clear_count;
	int key, i, j, num, check, tmp;
	char buf[256], addr[16] = "127.0.0.1";
	int x, y;

	struct sockaddr_in server, server_2;
	struct game_data send_data, recv_data;
	struct timeval timeout = { 0, 20000 };

	init_win();

	pblock[0] = pblock[1] = -1;

	getmaxyx(stdscr, height, width);
	PRINT("require console size: %d * %d\n",
		((((MAP_WIDTH + BLOCK_WIDTH + 4) * 2) + MAP_PADDING_LEFT + MAP_PADDING_RIGHT) * 2),
		(MAP_HEIGHT + MAP_PADDING_TOP)
	);
	while ( !(width > ((((MAP_WIDTH + BLOCK_WIDTH + 4) * 2) + MAP_PADDING_LEFT + MAP_PADDING_RIGHT) * 2) && height > (MAP_HEIGHT + 1 + MAP_PADDING_TOP)) ) {
		mvprintw(1, 0, "My Size: %d * %d\n", width, height);
		getmaxyx(stdscr, height, width);
		refresh();
	}
	clear();

	bzero(&buf, sizeof(buf));
	bzero(&send_data, sizeof(send_data));
	bzero(&recv_data, sizeof(recv_data));
	len = sizeof(server);
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket error : ");
		exit(0);
	}

	if (argc < 2) strcpy(addr, "127.0.0.1");
	else strcpy(addr, argv[1]);

	bzero(&server_2, sizeof(server_2));
	server_2.sin_family = AF_INET;
	server_2.sin_addr.s_addr = inet_addr(addr);
	server_2.sin_port = htons(PORT_NUMBER);

	sendto(sockfd, (void *)&send_data, sizeof(send_data), 0, (struct sockaddr *)&server_2, len);
	// wait other user
	mvprintw((height / 2), ((width / 2) - 4), "wait...");

	refresh();
	recvfrom(sockfd, (void *)&recv_data, sizeof(recv_data), 0, NULL, NULL);

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(addr);
	server.sin_port = htons(recv_data.data);

	sendto(sockfd, (void *)&send_data, sizeof(send_data), 0, (struct sockaddr *)&server, len);
	recvfrom(sockfd, (void *)&recv_data, sizeof(recv_data), 0, NULL, NULL);

	send_data.user_number = game_map[0].player = recv_data.user_number;
	game_map[1].player = (game_map[0].player ^ 0x1);
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

//	printf("number: %d, mode: %x, data: %x\n", recv_data.user_number, recv_data.mode, recv_data.data);
	clear();
	MapInitialize(game_map);
//	PrintMap();
	refresh();
	while (TRUE) {
		send_data.mode = MODE_NONE;
		send_data.data = DATA_CLEAR;

		if (recvfrom(sockfd, (void *)&recv_data, sizeof(recv_data), 0, NULL, NULL) >= 0) {
//			mvprintw(height - 1, 0, "%d %x %x", recv_data.user_number, recv_data.mode, recv_data.data);
			refresh();
			if (recv_data.user_number == game_map[0].player) num = 0;
			else if (recv_data.user_number == game_map[1].player) num = 1;
			else {
				PRINT("wrong player number: %d\n", recv_data.user_number);
				continue;
			}
			switch (recv_data.mode) {
				case MODE_CREATE:
//					sleep(1);
					game_map[num].now = game_map[num].next;
					game_map[num].next = (recv_data.data & 0xF);
					game_map[num].x = 3;
					game_map[num].y = 0;
					game_map[num].rotate = 0;
					if (EndCheck(num, game_map) & GAME_LOSE) send_data.mode = MODE_END;
					if ((recv_data.data >> 12) == MODE_ATTACK) {
						tmp = num ^ 0x1;
						game_map[tmp].y -= ((recv_data.data & 0xF00) >> 8);
						if (game_map[tmp].y < 0) game_map[tmp].y = 0;
						AddBlockDummy(tmp, game_map, (recv_data.data & 0xF00) >> 8, (recv_data.data & 0xF0) >> 4);
						for (i = 1; i < ((recv_data.data & 0xF00) >> 8) && (MoveBlock(tmp, game_map, MOVE_DOWN) & MOVE_OK); i++) ;
						if (MoveBlock(tmp, game_map, MOVE_DOWN) & MOVE_OK) game_map[tmp].y++;
						else {
							clear_count = ClearCheck(tmp, game_map);
							if (clear_count && recv_data.user_number == game_map[0].player) {
								send_data.data = (MODE_CLEAR << 4);
								send_data.data += clear_count;
							}
						}
					}

					break;
				case MODE_MOVE:
					check = TRUE;
					switch (recv_data.data) {
						case MOVE_DOWN:
							if (MoveBlock(num, game_map, MOVE_DOWN) & MOVE_OK) game_map[num].y++;
							else {
								if (recv_data.user_number == game_map[0].player) send_data.mode = MODE_CREATE;
								InsertData(num, game_map);
								clear_count = ClearCheck(num, game_map);
								if (clear_count && recv_data.user_number == game_map[0].player) {
									send_data.data = (MODE_CLEAR << 4);
									send_data.data += clear_count;
								}
							}
							break;
						case MOVE_LEFT:
							if (MoveBlock(num, game_map, MOVE_LEFT) & MOVE_OK) game_map[num].x--;
							break;
						case MOVE_RIGHT:
							if (MoveBlock(num, game_map, MOVE_RIGHT) & MOVE_OK) game_map[num].x++;
							break;
						case MOVE_ROTATE_R:
							if (MoveBlock(num, game_map, MOVE_ROTATE_R) & MOVE_OK)
								game_map[num].rotate += (game_map[num].rotate == 3 ? -3 : 1);
							break;
						case MOVE_ROTATE_L:
							if (MoveBlock(num, game_map, MOVE_ROTATE_L) & MOVE_OK)
								game_map[num].rotate += (game_map[num].rotate == 0 ? 3 : -1);
							break;
						case MOVE_DROP:
							while (MoveBlock(num, game_map, MOVE_DOWN) & MOVE_OK)
								game_map[num].y++;
							if (recv_data.user_number == game_map[0].player) send_data.mode = MODE_CREATE;
							InsertData(num, game_map);
							clear_count = ClearCheck(num, game_map);
							if (clear_count && recv_data.user_number == game_map[0].player) {
								send_data.data = (MODE_CLEAR << 4);
								send_data.data += clear_count;
							}
							break;
					}
					break;
			}
			if (recv_data.mode == MODE_END) {
				if (game_map[0].player == recv_data.user_number)
					if (recv_data.data == GAME_WIN) PrintWin();
					else PrintLose();
				else if (game_map[1].player == recv_data.user_number)
					if (recv_data.data == GAME_WIN) PrintLose();
					else PrintWin();
				break;
			}
			sendto(sockfd, (void *)&send_data, sizeof(send_data), 0, (struct sockaddr *)&server, len);
			send_data.mode = MODE_NONE;
			send_data.data = DATA_CLEAR;
		}

		if (kbhit() && (key = getch())) {
			if (key == 0x1b && kbhit() && (getch() == 0x5b)) key = getch();
			switch (key) {
				case MY_KEY_UP:
					send_data.mode = MODE_MOVE;
					send_data.data = MOVE_ROTATE_R;
					break;
				case MY_KEY_LEFT:
					send_data.mode = MODE_MOVE;
					send_data.data = MOVE_LEFT;
					break;
				case MY_KEY_RIGHT:
					send_data.mode = MODE_MOVE;
					send_data.data = MOVE_RIGHT;
					break;
				case MY_KEY_DOWN:
					send_data.mode = MODE_MOVE;
					send_data.data = MOVE_DOWN;
					break;
				case ' ':
					send_data.mode = MODE_MOVE;
					send_data.data = MOVE_DROP;
					break;
				case '\n':
					send_data.mode = MODE_MOVE;
					send_data.data = MOVE_ROTATE_L;
					break;
			}
		}

		Print(game_map);

		sendto(sockfd, (void *)&send_data, sizeof(send_data), 0, (struct sockaddr *)&server, len);
		refresh();
	}

	endwin();
	close(sockfd);

	return 0;
}
