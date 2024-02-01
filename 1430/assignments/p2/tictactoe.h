// Toby Hammond
// tictactoe.h
// Purpose: Tictactoe class

#ifndef TICTACTOE_H
#define TICTACTOE_H

class Tictactoe {
public:
  Tictactoe();
  Tictactoe(const Tictactoe &source);
  Tictactoe &operator=(const Tictactoe &source);
  ~Tictactoe();
  void drawScreen();
  void refreshGame();
  bool takeTurn(char piece, int x, int y, bool &won);
  int getGridSize();
  void drawStats(int p1Wins, int p2Wins);

private:
  // Constants
  static const int GRID_SIZE = 3;
  static const int CELL_SIZE = 4;

  // Defined types

  // Variables
  int screenWidth;
  char **board;
  bool checkWinner(char piece);
  void drawBoard();
};

#endif
