#include "tictactoe.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

Tictactoe::Tictactoe() {
  board = new char *[GRID_SIZE];
  for (int i = 0; i < GRID_SIZE; i++) {
    board[i] = new char[GRID_SIZE];
    for (int j = 0; j < GRID_SIZE; j++) {
      board[i][j] = ' ';
    }
  }
  // Gets number of columns of the terminal window in which the program was run
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  screenWidth = size.ws_col;
}

Tictactoe::Tictactoe(const Tictactoe &source) {
  board = new char *[GRID_SIZE];
  for (int i = 0; i < GRID_SIZE; i++) {
    board[i] = new char[GRID_SIZE];
    for (int j = 0; j < GRID_SIZE; j++) {
      board[i][j] = source.board[i][j];
    }
  }

  screenWidth = source.screenWidth;
}

Tictactoe::~Tictactoe() {
  for (int i = 0; i < GRID_SIZE; i++) {
    delete[] board[i];
  }
  delete[] board;
}

void Tictactoe::drawScreen() { drawBoard(); }

bool Tictactoe::takeTurn(char piece, int x, int y, bool &won) {
  if (board[x][y] == ' ') {
    board[x][y] = piece;
    return true;
  } else {
    return false;
  }
}

bool Tictactoe::checkWinner(char piece) {
  // row/column verification
  for (int i = 0; i < GRID_SIZE; i++) {
    int rowMatches = 0;
    int colMatches = 0;
    for (int j = 0; j < GRID_SIZE; j++) {
      if (board[i][j] != piece)
        rowMatches++;
      else if (board[j][i] != piece)
        colMatches++;
    }
    if (rowMatches == GRID_SIZE || colMatches == GRID_SIZE)
      return true;
  }
  return false;
}

// There's probably a better way to do this, but I don't think I should be
// worrying about optimizing my ascii art routines at this point in my life.
//
// Also I don't care that it doesnt look like a normal tictactoe board, I have
// just spent 2 hours doing this and will not change it :)
void Tictactoe::drawBoard() {
  int spaceCount = (screenWidth - ((GRID_SIZE * CELL_SIZE) + 2)) / 2;
  string spaces;
  for (int i = 0; i < spaceCount; i++) {
    spaces += " ";
  }

  cout << spaces;
  for (int i = 0; i < GRID_SIZE; i++) {
    cout << "   " << i;
  }
  cout << endl;
  for (int i = 0; i < GRID_SIZE; i++) {
    cout << spaces;
    for (int j = 0; j < GRID_SIZE; j++) {
      if (j == 0)
        cout << " +———";
      else if (j != GRID_SIZE - 1)
        cout << "+———";
      else
        cout << "+———+";
    }
    cout << endl;
    cout << spaces;
    for (int j = 0; j < GRID_SIZE; j++) {
      if (j == 0)
        cout << " |   ";
      else if (j != GRID_SIZE - 1)
        cout << "|   ";
      else
        cout << "|   |";
    }
    cout << endl;
    cout << spaces << i;
    for (int j = 0; j < GRID_SIZE; j++) {
      if (j == GRID_SIZE - 1)
        cout << "| " << board[i][j] << " |";
      else
        cout << "| " << board[i][j] << " ";
    }
    cout << endl;
    cout << spaces;
    for (int j = 0; j < GRID_SIZE; j++) {
      if (j == 0)
        cout << " |   ";
      else if (j != GRID_SIZE - 1)
        cout << "|   ";
      else
        cout << "|   |";
    }
    cout << endl;
  }
  cout << spaces;
  for (int i = 0; i < GRID_SIZE; i++) {
    if (i == 0)
      cout << " +———";
    else if (i == GRID_SIZE - 1)
      cout << "+———+";
    else
      cout << "+———";
  }
}
