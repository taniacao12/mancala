#include <sys/socket.h>
#include "networking.h"
#include "functions.h"

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("main");
    printf("wkp removed\n");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int listen_socket;
  int f;
  listen_socket = server_setup();
	
  while (1) {
    int player1; 
    int player2;

	// connect with players
    player1 = server_connect(listen_socket);
    printf("[server] player1 connected... waiting for player2\n");
	player2 = server_connect(listen_socket);
    printf("[server] player2 connected!\n");
    
	char send1[100];
    char send2[100];
    strcpy(send1, "Connected! You are player 1.\n");
    strcpy(send2, "Connected! You are player 2.\n");
    write(player1, send1, 100);
    write(player2, send2, 100);
		
    f = fork();
    if (f == 0)
      subserver(player1, player2);
    else {
      close(player1);
	  close(player2);
	}
  }
}

void subserver(int player1, int player2) {
  char buffer[BUFFER_SIZE];
  
  while(1){
    strcpy(buffer, "hello");
	
    // permits player1 to play
    write(player1, buffer, sizeof(buffer));
	
    // gets player1's board response (a string instead of an array)
    read(player1, buffer, sizeof(buffer));
    printf("[subserver %d] received [%s] from player 1\n", getpid(), buffer);
	
    // sends the string to player two 	
    // permits player2 to play
    write(player2, buffer, sizeof(buffer));
	printf("[subserver %d] sent [%s] to player 2\n", getpid(), buffer);
	
    // gets player2's board response (a string instead of an array)
    read(player2, buffer, sizeof(buffer));
    printf("[subserver %d] received [%s] from player 2\n", getpid(), buffer);
	
    //sends the updated, processed board to player 2 so they can print it
    write(player2, buffer, sizeof(buffer));
	printf("[subserver %d] sent [%s] to player 1\n", getpid(), buffer);
		
    while (read(player2, buffer, sizeof(buffer))) {
		printf("[subserver %d] received [%s]\n", getpid(), buffer);
		// process(buffer);
		
		// sends the updated, processed board to player 2 so they can print it
		write(player2, buffer, sizeof(buffer));
    }
  }
  close(player1);
  close(player2);
  exit(0);
}	
		
