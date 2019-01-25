#include "functions.h"
#include "networking.h"

int check (int * board, int server_socket) {
  int user1 = 0;
  int user2 = 0;
    
  for (int i = 0; i < 6; i++) {
    user1 += board[i];
    user2 += board[i+7];
  }
  if (user1 == 0 || user2 == 0) {
    user1 += board[6];
    user2 += board[13];
    if (user1 > user2)
      write(server_socket, "lose", BUFFER_SIZE);
    else
      write(server_socket, "win", BUFFER_SIZE);
    return 0;
  }
  return 1;
}

void listify (char * string, int * board) {
  for (int i = 0; i < 14; i++)
    board[i] = string[i] - '0';
}

void stringify (char * string, int * board) {
  sprintf(string, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d", board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8], board[9], board[10], board[11], board[12], board[13]);
}

void flip (int * board) {
  int temp[14];
  for (int i = 0; i < 14; i++) {
    if (i > 6)
      temp[i] = board[i - 7];
    else{
      temp[i] = board[i + 7];
    }
  }
  for (int i = 0; i < 14; i++)
    board[i] = temp[i];
}

int convert (char bucket) {
  char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F'};
  for (int i = 0; i < 6; i++) {
    if (bucket == alpha[i])
      return i;
  }
  return 0;
}

int update (char bucket, int * board) {
  int cup = convert(bucket) + 7;
  if (cup == 0)
    return 0;
  else {
    for (int i = cup; i < 14 && board[cup] > 0; i++) {
      board[i] += 1;
      board[cup] -= 1;
      if (i == 13 && board[cup] > 0)
	i = -1;
    }
    for (int i = cup; i < 14 && board[cup] > 0; i++)
      if (board[i] == 10)
	board[i] = 0;
    return 1;
  }
}

void process (int * board) {
  char input[BUFFER_SIZE];
  int num;
  printf("Which cup would you like to choose? ");
  fgets(input, BUFFER_SIZE, stdin);
  num = update(*input, board);
  if (num == 0)
    process(board);
}

void print (int * board) {
  for (int i = 6; i >= 0; i--)
    printf("{%d} ", board[i]);
  printf("\n    ");
  for (int i = 7; i < 14; i++)
    printf("{%d} ", board[i]);
  printf("\n");
  printf("     A   B   C   D   E   F   \n"); 
}

void make(int * board) {
  for (int i = 0; i < 14; i++) {
    if (i == 6 || i == 13)
      board[i] = 0;
    else
      board[i] = 4;
  }
}

int game() {
  char input[BUFFER_SIZE];
  printf("Press ENTER to start the game or input \"quit\" to quit the game. ");  
  fgets(input, BUFFER_SIZE, stdin);
  if (strcmp(input, "\n") == 0)
    return 1;
  else if (strcmp(input, "quit\n") == 0) {
    printf("We are sorry to see you go. Please come back soon!\n");
    return -1;
  }
  else
    game();
}

void instructions() {
  char input[BUFFER_SIZE];
  printf("Do you want the game instructions? (y/n) ");
  fgets(input, BUFFER_SIZE, stdin);
  if (strcmp(input, "y\n") == 0) {
    printf("-----------------------------------------------------\n");
    printf("1.  Each player gets six buckets and one mancala(M).\n");
    printf("    The buckets and mandala (located at the ends) will be formatted as shown below.\n");
    printf("           { } { } { } { } { } { } { }  M   <-- opponent side\n");
    printf("            M  { } { } { } { } { } { } { }  <-- your side\n");
    printf("2.  At the start of the game, each bucket has 4 marbles.\n");
    printf("           { } {4} {4} {4} {4} {4} {4}\n");
    printf("               {4} {4} {4} {4} {4} {4} { }\n");
    printf("3.  On your turn, each player you will be asked to input your bucket of choice.\n");
    printf("    All the marbles in that bucket will then be distributed counter-clockwise\n");
    printf("    into the other buckets and to your mancala (one per bucket).\n");
    printf("      a) If the last marble distributed lands in your mancala, you get an extra play.\n");
    printf("      b) If the last marble distributed lands in an empty bucket on your side of the\n");
    printf("         board, all marbles in the current bucket and the bucket directly above will be\n");
    printf("         placed in your mancala. Here's an example:\n");
    printf("           {6} {3} {5} {1} {3} {6} {2}\n");
    printf("               {0} {4} {2} {3} {1} {8} {4}\n");
    printf("                A   B   C   D   E   F\n");
    printf("           [Player A] Bucket of Choice: F\n");
    printf("           ----------- Current Board -----------\n");
    printf("           {6} {0} {6} {2} {4} {7} {3}\n");
    printf("               {0} {4} {2} {3} {1} {0} {10}\n");
    printf("4.  The game ends when all six buckets on either side of the board are empty.\n");
    printf("    The player with remaining marbles in their buckets automatically places the\n");
    printf("    remaining marbles into their own mancala. The player with the most marbles\n");
    printf("    in their mancala is the winner of the game.\n");
  }
  else if (strcmp(input,"n\n") == 0)
    return;
  else instructions();
}
