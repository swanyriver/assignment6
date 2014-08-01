/*
 * multiGame.cpp
 *
 *  Created on: Aug 1, 2014
 *      Author: brandon
 */

#include <iostream>
#include <string>

#include "SwansonLibs/swansonUtils.hpp"

#include "SwansonObjects/ArgReader.hpp"
#include "SwansonObjects/menu.hpp"
#include "SwansonObjects/Dictionary.hpp"
#include "PreFabDictionary.hpp"

#include "NumberGuess.hpp"
#include "wordGuess.hpp"
#include "phraseGuess.hpp"
#include "GameClass.hpp"


using namespace std;

//command line arguments
const string SIMPLE_MODE = "-s";

//Output Strings
const string INTRO = "Welcome to the Game Console";
const string AGAIN = "Would you like to play again";

//global variables
NumberGuess *myNumberGame;
WordGuess *myWordGame;
PhraseGuess *myPhraseGame;


//function prototypes
void usePreFabDict (Dictionary &myDict);
void PlayNumberGuess();
void PlayWordGuess();
void PlayPhraseGuess();

int main( int argc , char* argv[] ){

   const int MAX_WORD_LENGTH = 7;
   void (*clearScreen)() = swansonUtil::ClearScreen;
   Menu myMenu(INTRO);

   ///process command line arguments//////////////
   //args passed to ARGinAttor
   ARGinAttor myARGinAttor( argc , argv);
   //check Arginators arguement set<string> for -s SIMPLE MODE
   if(myARGinAttor.ArgumentPassedIn(SIMPLE_MODE)){
      clearScreen=swansonUtil::HackClearScreen;
      myMenu.setClear(clearScreen);
   }

   //seed random
   swansonUtil::SeedRandom();


   Dictionary myDict(MAX_WORD_LENGTH);
   if ( !myDict.Filled() )
      usePreFabDict(myDict);

   myNumberGame = new NumberGuess(clearScreen,50);
   myWordGame = new WordGuess(clearScreen,myDict,MAX_WORD_LENGTH);
   myPhraseGame = new PhraseGuess(clearScreen,myDict,MAX_WORD_LENGTH);


  // myMenu.addItem(new GameItem( myNumberGame,"Number Guess"));
  // myMenu.addItem(new GameItem( myWordGame,"Word Guess"));
  // myMenu.addItem(new GameItem( myPhraseGame,"Phrase Guess"));
   myMenu.addItem(new GoItem( PlayNumberGuess,"NumberGuess","",AGAIN));
   myMenu.addItem(new GoItem( PlayWordGuess,"Word Guess","",AGAIN));
   myMenu.addItem(new GoItem( PlayPhraseGuess,"Phrase Guess","",AGAIN));

   myMenu.showMenu();


}

//function definitions
void PlayNumberGuess(){
   myNumberGame->PlayGame();
}
void PlayWordGuess(){
   myWordGame->PlayGame();
}
void PlayPhraseGuess(){
   myPhraseGame->PlayGame();
}

void usePreFabDict (Dictionary &myDict) {
   myDict = Dictionary( PreFabDict::getSet() );

   if ( myDict.Filled() ) {
      cout << endl
            << "something strange has happened, we had an empty dictionary"
            << " but don't worry, we can still play with my limited stored vocabulary";
      cout << endl << "press anything to continue:";
      getchar();
   } else {
      cout << endl
            << "something has gone very wrong here, we have no words, we cannot play";
      cout << endl << "press anything to exit:";
      exit( 1 );
   }
}
