// Toby Hammond
// tictactoe.cpp
// Purpose: Tictactoe class implementation; runs game apart from control flow
// (handled in main). I don't know how to document this lol.

#include "tictactoe.h"
#include <functional>
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

Tictactoe &Tictactoe::operator=(const Tictactoe &source) {
  if (this != &source) {
    this->screenWidth = source.screenWidth;
    for (int i = 0; i < GRID_SIZE; i++) {
      for (int j = 0; j < GRID_SIZE; j++) {
        this->board[i][j] = source.board[i][j];
      }
    }
  }
  return *this;
}

Tictactoe::~Tictactoe() {
  for (int i = 0; i < GRID_SIZE; i++) {
    delete[] board[i];
  }
  delete[] board;
}

void Tictactoe::drawScreen() { drawBoard(); }

void Tictactoe::refreshGame() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      board[i][j] = ' ';
    }
  }
}

bool Tictactoe::takeTurn(char piece, int x, int y, bool &won) {
  if (board[x][y] == ' ') {
    board[x][y] = piece;
    won = checkWinner(piece);
    return true;
  } else {
    return false;
  }
}

int Tictactoe::getGridSize() { return GRID_SIZE; }

bool Tictactoe::checkWinner(char piece) {
  // row/column verification
  for (int i = 0; i < GRID_SIZE; i++) {
    int rowMatches = 0;
    for (int j = 0; j < GRID_SIZE; j++) {
      if (board[i][j] == piece)
        rowMatches++;
    }
    if (rowMatches == GRID_SIZE)
      return true;
  }

  for (int i = 0; i < GRID_SIZE; i++) {
    int colMatches = 0;
    for (int j = 0; j < GRID_SIZE; j++) {
      if (board[j][i] == piece)
        colMatches++;
    }
    if (colMatches == GRID_SIZE)
      return true;
  }

  int posDiagMatches = 0;
  int negDiagMatches = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    if (board[i][i] == piece)
      posDiagMatches++;
    else if (board[i][GRID_SIZE - i])
      negDiagMatches++;
  }
  if (posDiagMatches == GRID_SIZE || negDiagMatches == GRID_SIZE)
    return true;

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
  cout << endl;
}

void Tictactoe::drawStats(int p1Wins, int p2Wins) {
  cout << "-----------Wins-----------" << endl;
  cout << "Player X: " << p1Wins << endl;
  cout << "Player O: " << p2Wins << endl;
}
