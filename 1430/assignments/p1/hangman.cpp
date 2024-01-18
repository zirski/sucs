// Toby Hammond
// hangman.cpp
// Purpose: Implementation for Hangman class.

#include "hangman.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>

using namespace std;

Hangman::Hangman() {
  // Initialize all the variables!
  wins = 0;
  losses = 0;
  wordsGuessed = 0;
  badGuesses = 0;
  state = INTRO;

  // Populate the alphabet array with letters
  char letter = 'A';
  for (int i = 0; i < ALPHA_SIZE; i++) {
    alphabet[i].letter = letter++;
    alphabet[i].guessed = false;
  }
}

bool Hangman::initializeFile(string filename) {
  ifstream in(filename);
  // rng
  mt19937 g(rd());

  // file error handling
  if (!in) {
    return false;
  } else {
    char bufWord[MAX_WORD_SIZE];
    // i here serves both as a counter to iterate through each word, but also to
    // tell shuffle() where the end of our list of words is.
    int i = 0;
    while (in >> bufWord) {
      words[i].refWord = bufWord;
      for (int j = 0; j < MAX_WORD_SIZE; j++) {
        // I'm basically defining a more complicated c-string so that I can keep
        // track of each word's letters and if they have been guessed or not
        //
        // This reads each word from the file, char by char, into our array
        words[i].word[j].letter = bufWord[j];
      }
      i++;
    }
    // randomizes our list of words each time the game boots; since we do this
    // only once per boot, we can run only as many games as there are words in
    // the list.
    shuffle(begin(words), &words[i], g);
    wordsLeft = i;
    activeWord = words[0];
    return true;
  }
}

void Hangman::displayStatistics() {
  state = INTRO;
  cout << "Wins: " << wins << endl;
  cout << "Losses: " << losses << endl;
  cout << "Words guessed: " << wordsGuessed << endl;
  cout << "Words left: " << wordsLeft << endl;
}

bool Hangman::newWord() {
  badGuesses = 0;
  for (int i = 0; i < ALPHA_SIZE; i++) {
    alphabet[i].guessed = false;
  }
  if (wordsLeft == 0)
    return false;
  else {
    int ct = 0;
    // iterates through list of words until it finds one that hasn't been used
    do {
      activeWord = words[++ct];
    } while (activeWord.used);
    words[ct].used = true;
    wordsLeft--;
    wordsGuessed++;
    return true;
  }
}

// Fits perfectly on 80x24 size screen!
void Hangman::displayGame() {
  switch (state) {
  case INTRO:
    for (int i = 0; i < GAME_UPPER_SCREEN_HEIGHT - NUM_STATS_LINES; i++)
      cout << endl;

    displayGallows(badGuesses); // 8 lines

    cout << endl;
    cout << endl;
    cout << endl;

    displayWord(); // one line

    cout << endl;
    cout << endl;
    cout << endl;

    displayAlpha(); // one line

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    break;
  case GAME:
    for (int i = 0; i < GAME_UPPER_SCREEN_HEIGHT; i++)
      cout << endl;

    displayGallows(badGuesses); // 8 lines

    cout << endl;
    cout << endl;
    cout << endl;

    displayWord(); // one line

    cout << endl;
    cout << endl;
    cout << endl;

    displayAlpha(); // one line

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    break;
  case END:
    for (int i = 0; i < GAME_UPPER_SCREEN_HEIGHT; i++)
      cout << endl;

    displayGallows(badGuesses); // 8 lines

    cout << endl;
    cout << endl;
    cout << endl;

    displayWord(); // one line

    cout << endl;
    cout << endl;
    cout << endl;

    displayAlpha(); // one line

    cout << endl;
    cout << endl;
    cout << endl;
    break;
  }
}

bool Hangman::guess(char letter, bool &done, bool &won) {
  state = GAME;
  won = true;
  bool correctGuess = false;
  // Iterate through each letter of the active word
  for (int i = 0; i < (int)activeWord.refWord.length(); i++) {
    // if the current letter hasn't already been typed in previous guesses,
    // compare it with the current guess.
    if (!activeWord.word[i].guessed) {
      // if at any point there's a match, we have a correct guess!
      if (activeWord.word[i].letter == letter) {
        // mark the current letter as already guessed so that we can ignore it
        // in future passes
        activeWord.word[i].guessed = true;
        correctGuess = true;
        // we haven't won only if we've gone through every letter (including one
        // we've just analyzed) and there are still unguessed letters
      } else
        won = false;
    }
  }
  // If game is won
  if (won) {
    state = END;
    wins++;
    // I really don't know another way to end the game even if we have won; in
    // the assignment description it just says that done should be true only if
    // we've run out of guesses; though there is no other way to tell the game
    // to stop in testp1.cpp (ie when we beat the game).
    done = true;
  }
  // this prevents the player from being penalized if they accidentally enter a
  // letter guessed previously.
  if (!correctGuess && !alphabet[letter - 'A'].guessed) {
    badGuesses++;
    // If game is lost
    if (badGuesses == 7) {
      state = END;
      losses++;
      done = true;
    }
    alphabet[letter - 'A'].guessed = true;
    return true;
  } else if (alphabet[letter - 'A'].guessed) {
    return false;
  } else {
    alphabet[letter - 'A'].guessed = true;
    return true;
  }
}

void Hangman::revealWord() {
  for (int i = 0; i < (int)activeWord.refWord.length(); i++) {
    activeWord.word[i].guessed = true;
  }
}

// To any future readers of this method, I apologize in advance.
//
// All methods in this class print line by line (this would be way easier with
// matrices and a bitmap, but that's a problem for another time). since for a
// given line printed, there's a variable amount of ways it could look (for
// example on line 2, there could be an empty space, a neck, a neck and
// and arm, or a neck and two arms). Thus, for the amount of bad guesses we've
// guessed in a given refresh of the screen, we need to display the appropriate
// "state" of every line. That could be the same no matter the guess number
// (lines 1, 2, 7, and 8) or different depending on it.
void Hangman::displayGallows(int guess) {
  int spaces = (SCREEN_WIDTH - HANGMAN_LINE_WIDTH) / 2;

  gallows[0].ascii[0] = " +---+ ";
  gallows[0].numModifiedStates = 0;

  gallows[1].ascii[0] = " |   | ";
  gallows[1].numModifiedStates = 0;

  gallows[2].ascii[0] = "     | ";
  gallows[2].ascii[1] = " 0   | ";
  gallows[2].numModifiedStates = 1;

  gallows[3].ascii[0] = "     | ";
  gallows[3].ascii[1] = " |   | ";
  gallows[3].ascii[2] = "/|   | ";
  gallows[3].ascii[3] = "/|\\  | ";
  gallows[3].numModifiedStates = 3;

  gallows[4].ascii[0] = "     | ";
  gallows[4].ascii[1] = " |   | ";
  gallows[4].numModifiedStates = 1;

  gallows[5].ascii[0] = "     | ";
  gallows[5].ascii[1] = "/    | ";
  gallows[5].ascii[2] = "/ \\  | ";
  gallows[5].numModifiedStates = 2;

  gallows[6].ascii[0] = "     | ";
  gallows[6].numModifiedStates = 0;

  gallows[7].ascii[0] = "_____|__";
  gallows[7].numModifiedStates = 0;

  for (int i = 0; i < NUM_LINES; i++) {
    for (int j = 0; j < spaces; j++) {
      cout << " ";
    }
    // Grab the most modified "state" of the current line
    int currentHighestState = gallows[i].numModifiedStates;
    // only deal with variable lines
    if (currentHighestState > 0) {
      // if our amount of bad guesses is larger than the current line's
      // capacity, that line is fully expended and we can just print the most
      // modified version
      if (guess >= currentHighestState) {
        // - 1 because of indexing
        cout << gallows[i].ascii[currentHighestState] << endl;
        // shave off the amount of modified lines from our counter of bad
        // guesses
        guess -= currentHighestState;
      } else {
        // Otherwise, print the "worst" line (whatever's left in guess after
        // we've printed our fully-expended lines)
        cout << gallows[i].ascii[guess] << endl;
        guess = 0;
      }

      // Otherwise just print the only state of the line
    } else {
      cout << gallows[i].ascii[0] << endl;
    }
  }
}

void Hangman::displayWord() {
  // center the word on the screen
  int spaces = (SCREEN_WIDTH - (activeWord.refWord.length() * 2)) / 2;
  for (int i = 0; i < spaces; i++) {
    cout << " ";
  }

  int i = 0;
  // I'm using the null character to fill excess elements in each word array
  while (activeWord.word[i].letter != 0) {
    if (activeWord.word[i].guessed)
      cout << activeWord.word[i].letter << " ";
    else
      cout << UNDERSCORE << " ";
    i++;
  }
}

void Hangman::displayAlpha() {
  int spaces = (SCREEN_WIDTH - (ALPHA_SIZE * 2)) / 2;
  for (int i = 0; i < spaces; i++) {
    cout << " ";
  }
  for (int i = 0; i < ALPHA_SIZE; i++) {
    if (!alphabet[i].guessed)
      cout << alphabet[i].letter << " ";
    else
      cout << UNDERSCORE << " ";
  }
}
