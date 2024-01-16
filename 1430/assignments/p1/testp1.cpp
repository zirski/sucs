// Susan Reeder
// testp1.cpp
// Tests the public methods of Hangman class

#include <cctype>
#include <iostream>
#include <string>

#include "hangman.h"

using namespace std;

int main() {
  Hangman testGame;
  char letter;
  bool gameOver = false;
  bool gameWon = false;
  string filename = "/home/fac/sreeder/class/cs1430/p1input.dat";

  if (!testGame.initializeFile(filename)) {
    cout << "file problem...exiting" << endl;
    return 0;
  } else
    cout << "file loaded OK" << endl << endl;

  testGame.displayStatistics();

  for (int i = 0; i < 2; i++) {
    testGame.newWord();
    testGame.displayGame();
    gameOver = false;
    gameWon = false;

    while (!gameOver) {
      cout << "What letter? ";
      cin >> letter;
      testGame.guess(toupper(letter), gameOver, gameWon);
      testGame.displayGame();
    }

    testGame.revealWord();
    if (gameWon)
      cout << "You won!" << endl;
  }

  testGame.displayStatistics();

  return 0;
}
