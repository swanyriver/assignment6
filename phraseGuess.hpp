/*
 * phraseGuess.hpp
 *
 *  Created on: Jul 31, 2014
 *      Author: brandon
 */

#ifndef PHRASEGUESS_HPP_
#define PHRASEGUESS_HPP_

#include "stringGuess.hpp"
#include <string>
#include "SwansonLibs/swansonString.hpp"
#include "SwansonLibs/swansonUtils.hpp"

using namespace std;

class PhraseGuess: public StringGuess{
private:
   static const int MIN_WORDS = 3;
   static const int MAX_WORDS = 5; //todo make settable

   static inline bool HasSpaces(string s){
      return (!(s.find( ' ' ) == string::npos));
   }

public:
   PhraseGuess ( void (*clearScreen) (), Dictionary dict , int maxLength ) :
            StringGuess( clearScreen, dict, maxLength ){

      welcomeMessage = "Welcome to phrase guess good luck!";
      inputPrompt =
            "Enter a letter or word or be brave and try to guess the phrase:";
   }

private:

   string GenerateSecret(bool computerGen){
      string newSecret;

      if(!computerGen)
         return UserInputSecret(USER_MIN_LENGTH * MIN_WORDS,
               MAX_WORD_LENGTH * MAX_WORDS);

      //use dictionary to make phrase
      string phrase;
      int numWords = swansonUtil::GetRandomInRange( MIN_WORDS , MAX_WORDS );
      for ( int i = 0 ; i < numWords ; ++i ) {
         phrase += myDict.GetRandomWord() + " ";
      }
      phrase.erase( phrase.length() - 1 , 1 ); //remove extra space
      newSecret = phrase;

      return newSecret;
   }
   //virtual void Display(string message)=0;
   bool ValidGuess(string guess, string &message, string &nextGuess){

      nextGuess=guess;

      //check for already guessed
      //or for words that have been fully revealed
      if(swansonUtil::ExistsInSet( guess , guessSet )||
            (swansonString::NumOccurances(GetRevealPhrase(),guess)>0 &&
                  guess.length()>1)){
         message = "You have guessed this already";
         return false;
      }

      if(!HasSpaces(guess)) { //single word or letter, check validity
         //check that it is a valid word
         if(myDict.IsAWord(guess)){
            return true;
         }
         //determine if it is too long or just not in the dictionary
         else{
            if(guess.length()>MAX_WORD_LENGTH)
               message = "this word is too long";
            else
               message = "this is not a word or letter in my dictionary";
            return false;
         }
      }

      //check that each word in guess is valid
      list<string> wordsInGuess;
      swansonString::SeperateWords(guess,wordsInGuess);
      while(!wordsInGuess.empty()){
         if(!myDict.IsAWord(wordsInGuess.front())){
            if(wordsInGuess.front().length()>MAX_WORD_LENGTH){
               message = "at least one of these words is too long";
            }else{
               message = "at least one of these is not a word in my dictionary";
            }
            return false;
         }
         wordsInGuess.pop_front();
      }

      //each word in guessed phrase is valid
      return true;

   }


};



#endif /* PHRASEGUESS_HPP_ */
