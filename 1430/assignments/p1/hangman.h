// Toby Hammond
// hangman.h
// Purpose: Hangman class. Takes a list of words from a file, and using one word
// at a time, runs a game of hangman.

#include <random>
#include <string>

using namespace std;

#ifndef HANGMAN_H
#define HANGMAN_H

class Hangman {
public:
  Hangman();
  bool initializeFile(string filename);
  void displayStatistics();
  bool newWord();
  void displayGame();
  bool guess(char letter, bool &done, bool &won);
  void revealWord();

private:
  // Constants
  static const int MAX_LIST_SIZE = 100;
  static const int MAX_GUESSES = 7;
  static const char UNDERSCORE = '_';
  static const int ALPHA_SIZE = 26;
  static const int SCREEN_WIDTH = 80;
  static const int NUM_LINES = 8;
  static const int MAX_ASCII_SIZE = 4;
  static const int HANGMAN_LINE_WIDTH = 7;
  static const int MAX_WORD_SIZE = 13;
  static const int GAME_UPPER_SCREEN_HEIGHT = 5;
  static const int NUM_STATS_LINES = 4;

  // Variables
  int wins;
  int losses;
  int wordsGuessed;
  int wordsLeft;
  int badGuesses;

  // Defined Types
  enum gameState { INTRO, GAME, END };
  struct Letter {
    Letter() : letter(0), guessed(false) {}
    char letter;
    bool guessed;
  };

  struct Word {
    Word() : used(false) {}
    string refWord;
    Letter word[MAX_WORD_SIZE];
    bool used;
  };

  struct Hline {
    int numModifiedStates;
    string ascii[MAX_ASCII_SIZE];
  };

  // Type implementations
  gameState state;
  Hline gallows[8];
  Word activeWord;
  Word words[MAX_LIST_SIZE];
  Letter alphabet[ALPHA_SIZE];
  random_device rd;

  // Private Methods
  void displayGallows(int guess);
  void displayWord();
  void displayAlpha();
};

#endif
