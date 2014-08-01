/*
 * wordGuess.hpp
 *
 *  Created on: Jul 31, 2014
 *      Author: brandon
 */

#ifndef STRINGGUESS_HPP_
#define STRINGGUESS_HPP_

#include "SwansonObjects/Dictionary.hpp"
#include "GameClass.hpp"

#include <string>
#include <set>
#include <iostream>
#include <cstdio>

using namespace std;

class StringGuess: public GuessGame<string> {
protected:
   const int MAX_WORD_LENGTH;
   Dictionary myDict;
   string correctGuessDefault;

public:
   StringGuess ( void (*clearScreen) (), Dictionary dict , int maxLength ) :
         GuessGame( clearScreen ), myDict(dict),MAX_WORD_LENGTH(maxLength) {

      myDict.AddAlphabet();

      this->IncorectGuess = "That was incorrect";
      correctGuessDefault = "Good Job that was in the secret";
   }

protected:
   virtual string GenerateSecret ( bool computerGen ) = 0;

   virtual bool ValidGuess ( string guess , string &message ,
         string &nextGuess ) = 0;

   bool GuessCorrect ( string guess ) {
      int phraseOccurances=swansonString::NumOccurances(secret,guess);

      int occurances = phraseOccurances
            -swansonString::NumOccurances(GetRevealPhrase(),guess);

      if ( occurances>0 ) {
         correctGuess=correctGuessDefault;
         if(occurances>1) this->correctGuess=this->correctGuessDefault +
               " " + swansonString::GetString(occurances) + " times";
         return true;
      } else {
         return false;
      }
   }

   bool GameWon () {
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

string StringGuess::LineWrap ( string output , int sideBarWidth , int DisplayWidth ) {
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

void StringGuess::Display ( string message ) {

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

   for ( set<string>::iterator lookup = guessSet.begin();
         lookup!=guessSet.end() ; lookup++ ) {
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


void StringGuess::LostGameDisplay(){


   string LettersMissedLine = LETTERS_UNREAVEALED_LABEL;
   string secretPhraseLine = REVEAL_WORD_LABEL + secret;

   //set<string> missed = GuessChecker::ElementsMissed( secretPhrase , guesses );


   for ( char letter = 'a' ; letter <= 'z' ; letter++ ) {
      string charString = swansonString::GetString(letter);
      if(swansonString::NumOccurances(secret,charString)>0 &&
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

string StringGuess::GetRevealPhrase(){
   string revealPhrase;
   for(int i=0;i<this->secret.length();i++){
      if(secret.at(i)==' ') revealPhrase += " ";
      else revealPhrase += "-";
   }
   for(set<string>::iterator it=guessSet.begin();it!=guessSet.end();it++){
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

#endif /* STRINGGUESS_HPP_ */
