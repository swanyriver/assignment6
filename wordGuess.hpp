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

class WordGuess:public GuessGame<string>{
private:
   static const int MAX_WORD_LENGTH=7;
   Dictionary myDict;
   set<string> secretSet;
   set<string> guessSet;


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
   WordGuess(void(*clearScreen)()):GuessGame(clearScreen){
      myDict = Dictionary(MAX_WORD_LENGTH);
      if ( !myDict.Filled() )
               usePreFabDict();
      myDict.AddAlphabet();

      welcomeMessage= "Welcome to word guess Good luck!";
      inputPrompt= "Enter a letter or be brave and try to guess the word:";
      this->correctGuess = "correct";
      this->IncorectGuess= "incorrect";
   }

private:
   virtual string GenerateSecret(bool computerGen){
      string newSecret;

      //computer generated
      newSecret = myDict.GetRandomWord();

      //fill secret set
      guessSet.clear();
      secretSet.clear();
      secretSet.insert(newSecret);
      for(int i=0;i<newSecret.length(); i++){
         secretSet.insert(swansonString::GetString(newSecret.at(i)));
      }

      return newSecret;
   }

   virtual bool ValidGuess(string guess, string &message, string &nextGuess){
      if(!myDict.IsAWord(guess)){
         message = "That was not a letter or a word";
         return false;
      }else if(swansonUtil::ExistsInSet(guess,guessSet)){
         message = "You have guessed this already";
         return false;
      }
      else {
         nextGuess=guess;
         guessSet.insert(guess);
         return true;
      }
   }

   virtual bool GuessCorrect(string guess){
      if(swansonUtil::ExistsInSet(guess,secretSet)){
         return true;
      } else {
         return false;
      }
   }

   virtual bool GameWon(){
      if(guessesMade.back()==secret) return true;

      for(int i=0;i<secret.length();i++){
         if(!swansonUtil::ExistsInSet(swansonString::GetString(secret.at(i)),guessSet))
            return false;
      }

      return true;

   }

   virtual void Display(string message){
      ClearScreen();
      cout << "message:" << message << endl;
      cout << "secret is:" << secret << endl;
      cout << "last guess: " << guessesMade.back() << endl; //error on first display
     /* if(GuessCorrect(guessesMade.back())){
         cout << " correct";
      }*/
   }

   virtual void GameOverDisplay(bool won){
      if(won)Display(YouWin);
      else Display(YouLoose);

   }

};



#endif /* WORDGUESS_HPP_ */
