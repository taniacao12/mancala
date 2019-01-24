// functions for server ------------------------------------------------------------
void subserver(int player1, int player2);

// functions for client ------------------------------------------------------------
int game(); // game status
void instructions(); // display instructions
void process(int * board); // process board based on user input

// helper functions
void print (int * board); // display board
int convert (char bucket); // convert user bucket of choice into integer
int update (char bucket, int * board); // update board based on user input
void flip (int * board); // flip the board
void stringify (char * string, int * board); // convert int array into string
void listify (char * string, int * board); // convert string into int array

// might not be necessary unless we implement restart game
void make(); // make new board
