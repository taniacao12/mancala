// functions for server ------------------------------------------------------------
void subserver(int player1, int player2);
void process(char * name);

// functions for client ------------------------------------------------------------
void instructions(); // display instructions
void game();
void turn(); // play turn;

// helper functions
void print (int * board); // display board
void update (char bucket, int * board); // update board based on user input
void flip (int * board); // flip the board
void stringify (char * string, int * board); // convert int array into string
void listify (char * string, int * board); // convert string into int array
int convert (char bucket); // convert user bucket of choice into integer

// might not be necessary unless we implement restart game
void make(); // make new board
