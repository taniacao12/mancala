#include "networking.h"
#include "functions.c"

int main(int argc, char ** argv) {
  int server_socket;
  int start = 0; // has the game started? 0 = false, 1 = true
  char input[BUFFER_SIZE]; // user input
  char data[BUFFER_SIZE]; // data received from server

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  // welcome user and give or skip instructions
  printf("WELCOME TO TEAMANCALA!\n");
  instructions();
  
  // conncect user to server and wait for other player
  printf("Waiting for other player to join...\n");
  char receive[100];
  read(server_socket, receive, 100);
  printf("%s\n", receive);
  
  // start game if user is ready
  start = game();
  int board[14];
  int sum;
  
  while (start == 1) {
    // player waits for confirmation from the server to start
    read(server_socket, data, BUFFER_SIZE);

    // check whose turn it is
    if (data == 'gameOver')
      start = 0;
    else {
      // process data recieved from server
      listify(data, board);
      flip(board);
      printf("-----------------------------------------------------\n");
      print(board);
	
      // process board based on user input
      process(board);
      print(board);
	
      // check if game is over
      sum = 0;
      for (int i = 7; i < 14; n++)
	sum += board[i];
      if (sum == 0)
	start = 0;

      // convert results (board data) into a string
      char results[BUFFER_SIZE];
      stringify(results, board);

      // send string to the server
      write(server_socket, results, BUFFER_SIZE);
    }
  }
  return 0;
}
