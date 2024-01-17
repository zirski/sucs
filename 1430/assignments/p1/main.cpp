#include "hangman.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
  Hangman game;
  char letter;
  bool done = false;
  bool won = false;
  string filename;

  cout << "## Welcome to Hangman! ##" << endl << endl;
  cout << "Here's how it works: the game will choose a word at random (from a "
          "list you"
       << endl;
  cout << "provide) for you to guess. The word will be presented to you, "
          "hidden; each"
       << endl;
  cout << "letter will be represented by an underscore, for you to guess. Each "
          "time you"
       << endl;
  cout << "guess a wrong answer, the man on the noose gets another limb. When "
          "all of his"
       << endl;
  cout << "limbs appear, you lose! Want to play? (y/n): ";

  char input;
  cin.get(input);
  while (input != 'y' && input != 'n') {
    cout << "Please enter a valid choice (y/n): ";
    cin.clear();
    fflush(stdin);
    cin.get(input);
  }
  // main game flow
  if (input == 'y') {
    cout << "Enter word file: ";
    cin >> filename;
    if (!game.initializeFile(filename)) {
      cout << "file problem... exiting" << endl;
      return 1;
    } else {
      cout << "File loaded OK" << endl << endl;
    }

    while (input != 'y' && input != 'n') {
      cout << "Please enter a valid choice (y/n): ";
      cin.clear();
      fflush(stdin);
      cin.get(input);
    }

    char playAgain = 'y'; // will either be 'y' or 'n'
    do {
      game.setState(0);
      game.displayStatistics();
      game.newWord();
      game.displayGame();

      done = false;
      won = false;

      while (!done) {
        game.setState(1);
        cout << "What letter? ";
        cin >> letter;
        game.guess(toupper(letter), done, won);
        game.displayGame();
      }

      game.setState(2);
      game.revealWord();
      if (won)
        cout << "You won!" << endl;
      else
        cout << "You lost :(" << endl;

      cout << "Play again? (y/n): ";

      fflush(stdin);
      cin.get(playAgain);
      while (playAgain != 'y' && playAgain != 'n') {
        cout << "Please enter a valid choice (y/n): ";
        cin.clear();
        fflush(stdin);
        cin.get(playAgain);
      }
    } while (playAgain == 'y');
  } else
    exit(0);
}
