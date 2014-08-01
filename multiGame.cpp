/*
 * multiGame.cpp
 *
 *  Created on: Aug 1, 2014
 *      Author: brandon
 */

#include <iostream>
#include <string>

#include "SwansonLibs/swansonUtils.hpp"

#include "SwansonObjects/menu.hpp"
#include "SwansonObjects/Dictionary.hpp"
#include "PreFabDictionary.hpp"

#include "NumberGuess.hpp"
#include "wordGuess.hpp"
#include "phraseGuess.hpp"


using namespace std;

void usePreFabDict (Dictionary &myDict);


int main(){

   const int MAX_WORD_LENGTH = 7;

   Dictionary myDict(MAX_WORD_LENGTH);
   if ( !myDict.Filled() )
      usePreFabDict(myDict);

   NumberGuess myNumberGame(swansonUtil::ClearScreen,50);
   WordGuess myWordGame(swansonUtil::ClearScreen,myDict,MAX_WORD_LENGTH);
   PhraseGuess myPhraseGame(swansonUtil::ClearScreen,myDict,MAX_WORD_LENGTH);

   myNumberGame.PlayGame();
   myWordGame.PlayGame();
   myPhraseGame.PlayGame();


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
