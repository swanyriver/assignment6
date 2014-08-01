/*
 * wordGuess.hpp
 *
 *  Created on: Jul 31, 2014
 *      Author: brandon
 */

#ifndef WORDGUESS_HPP_
#define WORDGUESS_HPP_

#include "SwansonObjects/Dictionary.hpp"
#include "PreFabDictionary.hpp"

#include <string>
#include <set>
#include <iostream>
#include <cstdio>

using namespace std;

class WordGuess: public GuessGame<string> {
protected:
   static const int MAX_WORD_LENGTH = 7;
   Dictionary myDict;
   set<string> secretSet;
   set<string> guessSet;
   string correctGuessDefault;

   void usePreFabDict () {
      myDict = Dictionary( PreFabDict::getSet() );

      if ( myDict.Filled() ) {
         cout << endl
               << "something strange has happend, we had an empty dictionary"
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

public:
   WordGuess ( void (*clearScreen) () ) :
         GuessGame( clearScreen ) {
      myDict = Dictionary( MAX_WORD_LENGTH );
      if ( !myDict.Filled() )
         usePreFabDict();
      myDict.AddAlphabet();

      this->welcomeMessage = "Welcome to word guess good luck!";
      this->inputPrompt = "Enter a letter or be brave and try to guess the word:";
      this->IncorectGuess = "That was incorrect";
      correctGuessDefault = "Good Job that was in the secret";
   }

protected:
   virtual string GenerateSecret ( bool computerGen ) {
      string newSecret;

      //computer generated
      newSecret = myDict.GetRandomWord();

      //fill secret set
      guessSet.clear();
      secretSet.clear();
      secretSet.insert( newSecret );
      for ( int i = 0 ; i < newSecret.length() ; i++ ) {
         secretSet.insert( swansonString::GetString( newSecret.at( i ) ) );
      }

      return newSecret;
   }

   virtual bool ValidGuess ( string guess , string &message ,
         string &nextGuess ) {
      if ( !myDict.IsAWord( guess ) ) {
         if(guess.length()>MAX_WORD_LENGTH)
           message = "this word is too long";
        else
           message = "That was not a letter or a word";
         return false;
      } else if ( swansonUtil::ExistsInSet( guess , guessSet ) ) {
         message = "You have guessed this already";
         return false;
      } else {
         nextGuess = guess;
         guessSet.insert( guess );
         return true;
      }
   }

   virtual bool GuessCorrect ( string guess ) {
      if ( swansonUtil::ExistsInSet( guess , secretSet ) ) {
         int occurances=swansonString::NumOccurances(secret,guess);
         correctGuess=correctGuessDefault;
         if(occurances>1) this->correctGuess=this->correctGuessDefault +
               " " + swansonString::GetString(occurances) + " times";
         return true;
      } else {
         return false;
      }
   }

   virtual bool GameWon () {
      return (GetRevealPhrase()==secret);
   }

   void LostGameDisplay();
   void GameOverDisplay ( bool won ) {
      if ( won )
         Display( YouWin );
      else{
         Display( YouLoose );
         LostGameDisplay();
      }


   }
   void Display ( string message );
   string LineWrap ( string output , int sideBarWidth , int DisplayWidth );
   string GetRevealPhrase();


};

///special display/////////////////

const int WIDTH_DISPLAY = 75;
const int SIDEBAR_DISPLAY = 21;

#define LINE_SEPERATE "***************************************************************************"
#define SECRET_PHRASE_LABEL   "*      SECRET       * "
#define GUESS_MADE_LABEL      "*   GUESSES MADE    * "
#define LETTERS_LABEL "* LETTERS AVAILABLE * "
#define GUESS_REMAINING_LABEL "* GUESSES REMAINING * "

#define LETTERS_UNREAVEALED_LABEL "*  WHAT'S MISSING   * "
#define REVEAL_WORD_LABEL         "*    SECRET WAS     * "

//////////////////////////////

/**************************************************************
 *
 * Entry: string with ' ' as delimiter
 *
 * Exit: multi line strings
 *
 * Purpose: format strings to word wrap on multi lines
 *
 * ***************************************************************/

string WordGuess::LineWrap ( string output , int sideBarWidth , int DisplayWidth ) {
   //cout << "coming into linewrap with:" << output << endl;

   if ( output.length() < DisplayWidth ) {
      output.append( DisplayWidth - output.size() - 1 , ' ' );
      output += "*";
      return output;
   } else {
      int lastSpace = output.find_last_of( ' ' , DisplayWidth - 1 );
      string thisLine = output.substr( 0 , lastSpace );
      output.erase( 0 , lastSpace );

      //cout << "output:" << output << endl << "thisline:" << thisLine << endl;
      //cout << "remaining space:" << DisplayWidth -  thisLine.size() - 1;
      //getchar();

      thisLine.append( DisplayWidth - thisLine.size() - 1 , ' ' );
      thisLine += "*\n";

      output.insert( 0 , sideBarWidth , '*' );

      return thisLine + LineWrap( output , sideBarWidth , DisplayWidth );
   }
}

/**************************************************************
 *
 * Entry: none
 *
 * Exit: outputs the letters reveled in the secret word and guesses remaining
 *
 * Purpose: inform player 2 of his status in the game
 *
 * ***************************************************************/

void WordGuess::Display ( string message ) {

   string secretPhraseLine, lettersLine, guessesLine, guessRemainingLine;
   string lettersRemainingLine, phraseRevealLine;
   string messageLine;
   string wordGuessesMadeLine;

   //build secret word string
   secretPhraseLine = SECRET_PHRASE_LABEL;
   string revealPhrase = GetRevealPhrase();


   secretPhraseLine = LineWrap( secretPhraseLine + revealPhrase ,
         SIDEBAR_DISPLAY , WIDTH_DISPLAY );

   /*cout << endl << secretPhraseLine << endl;
    getchar();*/

   //build letters available & guesses made string
   lettersLine = LETTERS_LABEL;
   guessesLine = GUESS_MADE_LABEL;
   for ( char currentChar = 'a' ; currentChar <= 'z' ; currentChar++ ) {

      //for each letter place a letter or empty space, acording to guesses
      if ( swansonUtil::ExistsInSet( swansonString::GetString( currentChar ) ,
            guessSet ) ) {
         guessesLine.push_back( currentChar );
         guessesLine += " ";
         lettersLine += "  ";
      } else {
         lettersLine.push_back( currentChar );
         lettersLine += " ";
         guessesLine += "  ";
      }
   }
   guessesLine += "*";
   lettersLine += "*";

   /*cout << endl << guessesLine << endl;
    cout << endl << lettersLine << endl;
    getchar();*/

   wordGuessesMadeLine.append( SIDEBAR_DISPLAY , '*' );
   string guesses;

   for ( list<string>::iterator lookup = guessesMade.begin();
         lookup!=guessesMade.end() ; lookup++ ) {
      if ( (*lookup).size() > 1 )
         guesses += *lookup + ", ";
   }
   if ( guesses.empty() )
      wordGuessesMadeLine.append( WIDTH_DISPLAY - SIDEBAR_DISPLAY , '*' );
   else {
      guesses.erase( guesses.size() - 2 , 2 ); //remove final ", "
      wordGuessesMadeLine = LineWrap( wordGuessesMadeLine + " " + guesses ,
            SIDEBAR_DISPLAY , WIDTH_DISPLAY );
   }
   //allow display to grow if words get larger than one line

   //build guesses remaining string
   guessRemainingLine = GUESS_REMAINING_LABEL;
   for ( int i = 0 ; i < guessRemaining ; i++ ) {
      guessRemainingLine += "? ";
   }
   guessRemainingLine = LineWrap( guessRemainingLine , SIDEBAR_DISPLAY ,
         WIDTH_DISPLAY );

   /* cout << endl << guessRemainingLine << endl;
    getchar();*/

   //build message line
   messageLine = LINE_SEPERATE;
   if ( !message.empty() ) {
      message = "  " + message + "  ";
      int pos = WIDTH_DISPLAY / 2.0 - message.length() / 2.0;
      messageLine.replace( pos , message.size() , message );
   }

   /*cout << endl << messageLine << endl;
    getchar();*/

   //output display
   ClearScreen();
   cout << LINE_SEPERATE << endl;
   cout << LINE_SEPERATE << endl;
   cout << secretPhraseLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << lettersLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << guessesLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << wordGuessesMadeLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << guessRemainingLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << messageLine << endl;
   cout << LINE_SEPERATE << endl;



}


void WordGuess::LostGameDisplay(){


   string LettersMissedLine = LETTERS_UNREAVEALED_LABEL;
   string secretPhraseLine = REVEAL_WORD_LABEL + secret;

   //set<string> missed = GuessChecker::ElementsMissed( secretPhrase , guesses );


   for ( char letter = 'a' ; letter <= 'z' ; letter++ ) {
      string charString = swansonString::GetString(letter);
      if(swansonUtil::ExistsInSet(charString,secretSet) &&
            !swansonUtil::ExistsInSet(charString,guessSet))
      LettersMissedLine += charString + " ";
   }

   LettersMissedLine = LineWrap( LettersMissedLine , SIDEBAR_DISPLAY ,
         WIDTH_DISPLAY );
   secretPhraseLine = LineWrap( secretPhraseLine , SIDEBAR_DISPLAY ,
         WIDTH_DISPLAY );

   cout << secretPhraseLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << LettersMissedLine << endl;
   cout << LINE_SEPERATE << endl;

}

string WordGuess::GetRevealPhrase(){
   string revealPhrase;
   for(int i=0;i<this->secret.length();i++){
      if(secret.at(i)==' ') revealPhrase += " ";
      else revealPhrase += "-";
   }
   for(list<string>::iterator it=guessesMade.begin();it!=guessesMade.end();it++){
      int foundPos = 0;
      while(foundPos!=string::npos){
         foundPos = secret.find(*it,foundPos);
         if(foundPos!=string::npos){
            revealPhrase.replace(foundPos,it->length(),*it);
            foundPos++;
         }
      }
   }
   return revealPhrase;
}

#endif /* WORDGUESS_HPP_ */
