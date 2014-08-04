/*
 * wordGuess.cpp
 *
 *  Created on: Aug 1, 2014
 *      Author: brandon
 */

#ifndef WORDGUESS_HPP_
#define WORDGUESS_HPP_

#include "SwansonObjects/Dictionary.hpp"
#include "stringGuess.hpp"

class WordGuess: public StringGuess{
public:

   WordGuess ( Dictionary dict ): StringGuess( dict){

      this->welcomeMessage = "Welcome to word guess good luck!";
      this->inputPrompt = "Enter a letter or be brave and try to guess the word:";
   }

private:
   virtual string GenerateSecret ( bool computerGen ) {
      string newSecret;

      //computer generated
      if(computerGen) newSecret = myDict.GetRandomWord();
      else newSecret = UserInputSecret(USER_MIN_LENGTH,MAX_WORD_LENGTH);

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
         return true;
      }
   }

};


#endif /* WORDGUESS_HPP_ */
