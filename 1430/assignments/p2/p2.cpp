// Toby Hammond
// p2.cpp
// Purpose: runs tictactoe game; handles game flow, wins, losses, and drawing
// the intro screen. Error handles inputs (not well at all mind you)

#include "tictactoe.h"
#include <iostream>

using std::cout;

using namespace std;

struct Player {
  Player() : wins(0), hasWon(false) {}
  char piece;
  int wins;
  bool hasWon;
};

int main() {
  Player player1;
  player1.piece = 'X';
  Player player2;
  player2.piece = 'O';

  Tictactoe game;
  Player *activePlayer = &player1;
  bool playerBool = true;

  for (int i = 0; i < 25; i++) {
    cout << endl;
  }
  cout << "Welcome to TicTacToe! It's honestly pretty well-known; have fun!"
       << endl;

  game.drawScreen();
  do {
    if (playerBool)
      activePlayer = &player1;
    else
      activePlayer = &player2;
    int r, c;
    cout << endl
         << "Player " << activePlayer->piece
         << ": please take your turn (r c): ";
    cin >> r >> c;
    while (r >= game.getGridSize() || c >= game.getGridSize()) {
      cout << "Please enter a valid cell: ";
      cin >> r >> c;
    }
    while (!game.takeTurn(activePlayer->piece, r, c, activePlayer->hasWon)) {
      cout << "Please choose an empty cell: ";
      cin >> r >> c;
    }
    game.drawScreen();
    if (activePlayer->hasWon) {
      activePlayer->wins++;
      char choice;
      cout << "Good game! Player " << activePlayer->piece << " has won!"
           << endl;
      game.drawStats(player1.wins, player2.wins);
      cout << "Play again? (y/n): ";
      cin >> choice;
      if (choice == 'y' || choice == 'Y') {
        player1.hasWon = false;
        player2.hasWon = false;
        game.refreshGame();
        game.drawScreen();
      } else {
        return 0;
      }
    } else {
      playerBool = !playerBool;
    }
  } while (!activePlayer->hasWon);
}
