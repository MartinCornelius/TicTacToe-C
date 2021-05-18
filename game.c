#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random(min, max);
void newGame(void);
void clearBoard(void);
void printBoard(void);
void playerMove(void);
void computerMove(void);
void validMove(spot);
void placeMove(spot);
void checkForWin(void);
char aiCheckForWin();
int minimax(board, depth, isMax);
void gameover(winner);

static char currentPlayer;
char board[9];

int main(void) {
  printf("----Tic Tac Toe----\n");

  clearBoard();

  srand(time(NULL));
  int number = rand() % 2;
  switch(number) {
    case 0:
      currentPlayer = 'X';
      playerMove();
      break;
    case 1:
      currentPlayer = 'O';
      computerMove();
      break;
  }
}

void newGame(void) {
  printf("\nStarting a new game...\n");
  clearBoard();

  srand(time(NULL));
  int number = rand() % 2;
  switch(number) {
    case 0:
      currentPlayer = 'X';
      playerMove();
      break;
    case 1:
      currentPlayer = 'O';
      computerMove();
      break;
  }
}

void clearBoard(void) {
  for (int i = 0; i < 9; i++) {
    board[i] = ' ';
  }
}

void printBoard(void) {
  printf(" %c | %c | %c \n", board[0], board[1], board[2]);
  printf("---|---|---\n");
  printf(" %c | %c | %c \n", board[3], board[4], board[5]);
  printf("---|---|---\n");
  printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

void playerMove(void) {
  int spot;
  printBoard();
  printf("Choose your spot (1-9): ");
  scanf("%d", &spot);
  validMove(spot);
}

void computerMove(void) {
  int bestScore = -1000;
  int bestMove;
  for (int i = 0; i < 9; i++) {
    if (board[i] == ' ') {
      board[i] = 'O';
      int score = minimax(board, 5, 0); // minimax takes in depth, isMax (1 or 0) 
      board[i] = ' ';

      if (score > bestScore) {
        bestScore = score;
        bestMove = i;
      }
    }
  }
  validMove(bestMove + 1);
}

void validMove(spot) {
  if (board[spot - 1] == ' ') {
    placeMove(spot);
  }
  else {
    printf("Spot is not avaible. Choose another!\n");
    currentPlayer == 'X' ? playerMove() : computerMove();
    return;
  }
}

void placeMove(spot) {
  board[spot - 1] = currentPlayer;
  checkForWin();

  switch (currentPlayer) {
    case 'X':
      currentPlayer = 'O';
      computerMove();
      break;
    case 'O':
      currentPlayer = 'X';
      playerMove();
      break;
  }
}

void checkForWin(void) {
  if (board[0] == board[1] && board[1] == board[2]) gameover(board[0]);
  if (board[3] == board[4] && board[4] == board[5]) gameover(board[3]);
  if (board[6] == board[7] && board[7] == board[8]) gameover(board[6]);

  if (board[0] == board[3] && board[3] == board[6]) gameover(board[0]);
  if (board[1] == board[4] && board[4] == board[7]) gameover(board[1]);
  if (board[2] == board[5] && board[5] == board[8]) gameover(board[2]);

  if (board[0] == board[4] && board[4] == board[8]) gameover(board[0]);
  if (board[2] == board[4] && board[4] == board[6]) gameover(board[2]);

  if (board[0] != ' ' && board[1] != ' ' && board[2] != ' ' && board[3] != ' ' && board[4] != ' ' && board[5] != ' ' && board[6] != ' ' && board[7] != ' ' && board[8] != ' ') gameover('D');
}

char aiCheckForWin() {
  if (board[0] == board[1] && board[1] == board[2]) return board[0];
  if (board[3] == board[4] && board[4] == board[5]) return board[3];
  if (board[6] == board[7] && board[7] == board[8]) return board[6];

  if (board[0] == board[3] && board[3] == board[6]) return board[0];
  if (board[1] == board[4] && board[4] == board[7]) return board[1];
  if (board[2] == board[5] && board[5] == board[8]) return board[2];

  if (board[0] == board[4] && board[4] == board[8]) return board[0];
  if (board[2] == board[4] && board[4] == board[6]) return board[2]; 

  if (board[0] != ' ' && board[1] != ' ' && board[2] != ' ' && board[3] != ' ' && board[4] != ' ' && board[5] != ' ' && board[6] != ' ' && board[7] != ' ' && board[8] != ' ') return 'D';
  return ' ';
}

int minimax(char board[9], int depth, int isMax) {
  if (depth >= 0) {
    char res = aiCheckForWin();
    if (res == 'O') {
      return +10;
    }
    else if (res == 'X') {
      return -10;
    }
    else if (res == 'D') {
      return 0;
    }
    if (isMax == 1) {
      int bestScore = -1000;

      for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
          board[i] = 'O';
          int score = minimax(board, depth - 1, 0);
          board[i] = ' ';

          if (score > bestScore) {
            bestScore = score;
          }
        }
      }
      return bestScore;
    }
    else {
      int bestScore = 1000;

      for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
          board[i] = 'X';
          int score = minimax(board, depth - 1, 1);
          board[i] = ' ';

          if (score < bestScore) {
            bestScore = score;
          }
        }
      }
      return bestScore;
    }
  }
  return 0;
}

void gameover(winner) {
  switch (winner) {
    case 'X':
      printBoard();
      printf("\nPlayer Wins!!\n");
      newGame();
      break;
    case 'O':
      printBoard();
      printf("\nComputer Wins!!\n");
      newGame();
      break;
    case 'D':
      printBoard();
      printf("\nDRAW\n");
      newGame();
      break;
  }
}
