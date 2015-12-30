#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "data.h"

#define EXIT	close(sockfd); return child

int main(int argc, char* argv[]) {
	int sockfd, serverfd, len, i, last_dummy[2], tmp, ftmp;
	unsigned int user_number = 0, p1_number, p2_number;
	struct game_data recv_data, send_data;
	struct timeval p1_start, p1_end, p2_start, p2_end;
	struct timeval timeout = { 0, 10000 }, timewait = { 86400, 0 };
	struct timeval p1con_last, p2con_last;	
	struct sockaddr_in server, server_2, client, client1, client2, client3, client4;

	char port_list[ROOM_NUMBER] = { 0 };
	int child = 0;

	srand(time(NULL));

	len = sizeof(client1);
	if ((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket error : ");
		exit(0);
	}

	bzero(&server_2, sizeof(server_2));
	server_2.sin_family = AF_INET;
	server_2.sin_addr.s_addr = htonl(INADDR_ANY);
	server_2.sin_port = htons(PORT_NUMBER);

	if (bind(serverfd, (struct sockaddr*)&server_2, sizeof(server)) == -1) {
		perror("bind error : ");
		exit(0);
	}

	user_number = (rand() & ~(0x1));
	p2_number = p1_number = user_number - 1;

	while (TRUE) {
		// initialize data
		last_dummy[0] = last_dummy[1] = -1;
		bzero(&recv_data, sizeof(recv_data));
		bzero(&send_data, sizeof(send_data));

		if (setsockopt(serverfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == -1) printf("setsockopt error\n");
		for (i = 0; i < 10; i++)
			recvfrom(serverfd, (void*)&recv_data, sizeof(recv_data), 0, NULL, NULL);

		if (setsockopt(serverfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timewait, sizeof(timewait)) == -1) printf("setsockopt1 error\n");

		for (i = 0; i < 10; i++)
			if (port_list[i])
				if (waitpid(port_list[i], NULL, WNOHANG))
					port_list[i] = 0;			

		while (port_list[child = (rand() % ROOM_NUMBER)]);;

		printf("server initailzing. ");
//		sleep(1);
		puts("ok.");

		// get client info
		puts("waiting for palyer 1");
		recvfrom(serverfd, (void*)&recv_data, sizeof(recv_data), 0, (struct sockaddr*)&client3, &len);
		p1_number = user_number++;
//		printf("connect client 1 (number: %d)\n", p1_number);
		puts("waiting for palyer 2");
		recvfrom(serverfd, (void*)&recv_data, sizeof(recv_data), 0, (struct sockaddr*)&client4, &len);
		p2_number = user_number++;
//		printf("connect client 2 (number: %d)\n", p2_number);


		if (ftmp = port_list[child] = fork()) {
//			close(sockfd);
			continue;
		}

		if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			perror("socket error : ");
			exit(0);
		}

		printf("sockfd: %d\n", sockfd);

		do {
			while (port_list[child = (rand() % ROOM_NUMBER)]) ;
			port_list[child] = ftmp;
			bzero(&server, sizeof(server));
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = htonl(INADDR_ANY);
			server.sin_port = htons( tmp = (PORT_START + child) );
		} while ((bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1) && printf("re bind\n") && !(port_list[child] = 0));

		// send game start
		send_data.mode = MODE_CONNECT;
		send_data.data = tmp;
		send_data.user_number = p1_number;
		sendto(serverfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client3, len);
		send_data.user_number = p2_number;
		sendto(serverfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client4, len);

		close(serverfd);
	
		if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timewait, sizeof(timewait)) == -1) printf("setsockopt2 error\n");

		recvfrom(sockfd, (void*)&recv_data, sizeof(recv_data), 0, (struct sockaddr*)&client1, &len);

		recvfrom(sockfd, (void*)&recv_data, sizeof(recv_data), 0, (struct sockaddr*)&client2, &len);

		send_data.mode = MODE_CONNECT;
		send_data.data = CONNECT_OK;
		send_data.user_number = p1_number;
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
		send_data.user_number = p2_number;
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);

		if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == -1) printf("setsockopt2 error\n");

		// send random block
		send_data.user_number = p1_number;
		send_data.mode = MODE_CREATE;
		send_data.data = (rand() % BLOCK_NUM);
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);

		send_data.user_number = p2_number;
		send_data.mode = MODE_CREATE;
		send_data.data = (rand() % BLOCK_NUM);
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);

		send_data.user_number = p1_number;
		send_data.mode = MODE_CREATE;
		send_data.data = (rand() % BLOCK_NUM);
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);

		send_data.user_number = p2_number;
		send_data.mode = MODE_CREATE;
		send_data.data = (rand() % BLOCK_NUM);
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
		sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);

		gettimeofday(&p1_start, NULL);
		gettimeofday(&p2_start, NULL);
		gettimeofday(&p1con_last, NULL);
		gettimeofday(&p2con_last, NULL);

//		if (fork() == 0) {
//			printf("game start %d\n", PORT_START + child);
			printf("%d: p1: %d, p2: %d\n", child, p1_number, p2_number);
			while (TRUE) {
				bzero(&send_data, sizeof(send_data));
				gettimeofday(&p1_end, NULL);
				gettimeofday(&p2_end, NULL);
//				printf("%d.%06d\n", p1_end.tv_sec, p1_end.tv_usec);
				if (p1con_last.tv_sec <= (p1_end.tv_sec - DISCON_TIME_SEC - (p1_end.tv_usec - DISCON_TIME_USEC < 0 ? 1 : 0)) &&
				    p1con_last.tv_usec <= (p1_end.tv_usec - DISCON_TIME_USEC + (p1_end.tv_usec - DISCON_TIME_USEC < 0 ? U_SEC : 0))) {
					// 1 player disconnect
					send_data.user_number = p2_number;
					send_data.mode = MODE_END;
					send_data.data = GAME_WIN;
					sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);
//					printf("1 player disconnect (start: %d.%06d, end: %d.%06d)\n", p1con_last.tv_sec, p1con_last.tv_usec, p1_end.tv_sec, p1_end.tv_usec);
					puts("player 1 disconnect");
					EXIT;
				}
	
				if (p2con_last.tv_sec <= (p2_end.tv_sec - DISCON_TIME_SEC - (p2_end.tv_usec - DISCON_TIME_USEC < 0 ? 1 : 0)) &&
				    p2con_last.tv_usec <= (p2_end.tv_usec - DISCON_TIME_USEC + (p2_end.tv_usec - DISCON_TIME_USEC < 0 ? U_SEC : 0))) {
					// 2 player disconnect
					send_data.user_number = p1_number;
					send_data.mode = MODE_END;
					send_data.data = GAME_WIN;
					sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
//					printf("2 player disconnect (start: %d.%06d, end: %d.%06d)\n", p2con_last.tv_sec, p2con_last.tv_usec, p2_end.tv_sec, p2_end.tv_usec);
					puts("player 2 disconnect");
					EXIT;
				}
	
				if (p1_start.tv_sec <= (p1_end.tv_sec - DOWN_TIME_SEC - (p1_end.tv_usec - DOWN_TIME_USEC < 0 ? 1 : 0)) &&
				    p1_start.tv_usec <= (p1_end.tv_usec - DOWN_TIME_USEC + (p1_end.tv_usec - DOWN_TIME_USEC < 0 ? U_SEC : 0))) {
					// 1 player move down
					send_data.user_number = p1_number;
					send_data.mode = MODE_MOVE;
					send_data.data = MOVE_DOWN;
					sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
					sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);
					gettimeofday(&p1_start, NULL);
//					puts("send: 1 player move down");
				}
	
				if (p2_start.tv_sec <= (p2_end.tv_sec - DOWN_TIME_SEC - (p2_end.tv_usec - DOWN_TIME_USEC < 0 ? 1 : 0)) &&
				    p2_start.tv_usec <= (p2_end.tv_usec - DOWN_TIME_USEC + (p2_end.tv_usec - DOWN_TIME_USEC < 0 ? U_SEC : 0))) {
					// 2 player move down
					send_data.user_number = p2_number;
					send_data.mode = MODE_MOVE;
					send_data.data = MOVE_DOWN;
					sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
					sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);
					gettimeofday(&p2_start, NULL);
//					puts("send: 2 player move down");
				}
	
				if (recvfrom(sockfd, (void*)&recv_data, sizeof(recv_data), 0, (struct sockaddr*)&client, &len) < 0) continue;
//				printf("%d:%d, %x, %x\n", child, recv_data.user_number, recv_data.mode, recv_data.data);
	
				if (recv_data.user_number == p1_number) {
					send_data.user_number = p1_number;
					gettimeofday(&p1con_last, NULL);
				} else if (recv_data.user_number == p2_number) {
					send_data.user_number = p2_number;
					gettimeofday(&p2con_last, NULL);
				} else {
					printf("%d:wrong user number (user_number: %d)\n", child, recv_data.user_number);
					continue;
				}
	
				if (recv_data.mode == MODE_NONE) continue;
				else if (recv_data.mode == MODE_MOVE) {
					// Move Send
					if (recv_data.data == MOVE_DOWN) {
						if (recv_data.user_number == p1_number) {
							gettimeofday(&p1_start, NULL);
						} else if (recv_data.user_number == p2_number) {
							gettimeofday(&p2_start, NULL);
						}
					}
//					printf("%d player move %x\n", (recv_data.user_number & 0x1) + 1, recv_data.data);

					send_data.mode = MODE_MOVE;
					send_data.data = recv_data.data;
				} else if (recv_data.mode == MODE_CREATE) {
					// New Block Send
					send_data.mode = MODE_CREATE;
					send_data.data = (rand() % BLOCK_NUM);
					printf("%d:create data: %d, create, %d\n", child, send_data.user_number, send_data.data);
					if ((recv_data.data >> 4) == MODE_CLEAR) {
						send_data.data |= (MODE_ATTACK << 12);
						send_data.data |= (((recv_data.data & 0xF) - 1) << 8);
						i = (rand() % 10);
						while (last_dummy[recv_data.user_number & 0x1] == i) i = (rand() % 10);
						last_dummy[recv_data.user_number & 0x1] = i;
						send_data.data |= (last_dummy[recv_data.user_number & 0x1] << 4);
						printf("%d:clear: %d, data: %x\n", child, send_data.user_number, send_data.data);
					}
/*				} else if (recv_data.mode == MODE_CLEAR) {
					// Attack Send
					if (recv_data.data != 1) {
						send_data.mode = MODE_ATTACK;
						send_data.data = ((recv_data.data - 1) << 4);
						send_data.data |= (rand() % 10);
						printf("clear: %d, data: %x\n", send_data.user_number, send_data.data);
					}*/
				} else if (recv_data.mode == MODE_END) {
					// End Send
					send_data.mode = MODE_END;
					send_data.data = GAME_LOSE;
					sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
					sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);
					EXIT;
				} else {
					printf("wrong mode (user_number: %d, mode: %x, data: %x)\n", recv_data.user_number, recv_data.mode, recv_data.data);
					continue;
				}
	
				sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client1, len);
				sendto(sockfd, (void*)&send_data, sizeof(send_data), 0, (struct sockaddr*)&client2, len);
			}
//		}
	}
	close(sockfd);

	return 0;
}
