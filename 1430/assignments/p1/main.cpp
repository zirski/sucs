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

  // formatting
  for (int i = 0; i < 19; i++)
    cout << endl;

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
  if (input == 'y') {
    cout << "Enter word file: ";
    cin >> filename;
    if (!game.initializeFile(filename)) {
      cout << "file problem... exiting" << endl;
      return 1;
    } else {
      cout << "File loaded OK" << endl << endl;
    }

    char playAgain; // will either be 'y' or 'n'
    // Main game loop: display statistics at first, then prompt for the user's
    // guess, displaying the updated game after every guess. When the game
    // finishes, prompt them if they want to play again. If they run out of
    // words, tell them thanks for playing and end the program.
    do {
      game.displayStatistics();
      game.displayGame();

      done = false;
      won = false;

      while (!done) {
        cout << "Enter guess: ";
        cin >> letter;
        game.guess(toupper(letter), done, won);
        if (done)
          game.revealWord();
        game.displayGame();
      }

      if (won)
        cout << "You won!" << endl;
      else
        cout << "You lost :(" << endl;

      if (!game.newWord()) {
        cout << "Out of words! Thanks for playing!";
        return 0;
      } else {
        cout << "Play again? (y/n): ";

        fflush(stdin);
        cin.get(playAgain);
        while (playAgain != 'y' && playAgain != 'n') {
          cout << "Please enter a valid choice (y/n): ";
          cin.clear();
          fflush(stdin);
          cin.get(playAgain);
        }
      }
    } while (playAgain == 'y');
  } else
    return 0;
}
