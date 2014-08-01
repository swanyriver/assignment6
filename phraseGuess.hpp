/*
 * phraseGuess.hpp
 *
 *  Created on: Jul 31, 2014
 *      Author: brandon
 */

#ifndef PHRASEGUESS_HPP_
#define PHRASEGUESS_HPP_

#include "wordGuess.hpp"
#include <string>
#include "SwansonLibs/swansonString.hpp"
#include "SwansonLibs/swansonUtils.hpp"

using namespace std;

class PhraseGuess: public WordGuess{
private:
   static const int MIN_WORDS = 3;
   static const int MAX_WORDS = 6; //todo make settable

   static inline bool HasSpaces(string s){
      return (!(s.find( ' ' ) == string::npos));
   }

public:
   PhraseGuess ( void (*clearScreen) () ) :
         WordGuess( clearScreen ) {

      welcomeMessage = "Welcome to phrase guess good luck!";
      inputPrompt =
            "Enter a letter or word or be brave and try to guess the phrase:";
   }

private:

   string GenerateSecret(bool computerGen){
      string newSecret;

      //computer generated
      //use dictionary to make phrase
      string phrase;
      int numWords = swansonUtil::GetRandomInRange( MIN_WORDS , MAX_WORDS );
      for ( int i = 0 ; i < numWords ; ++i ) {
         phrase += myDict.GetRandomWord() + " ";
      }
      phrase.erase( phrase.length() - 1 , 1 ); //remove extra space
      newSecret = phrase;

      //fill secret set
      guessSet.clear();
      secretSet.clear();
      //add secret phrase
      secretSet.insert( newSecret );

      //add words
      list<string> wordsInPhrase;
      swansonString::SeperateWords(newSecret,wordsInPhrase);
      while(!wordsInPhrase.empty()){
         secretSet.insert(wordsInPhrase.front());
         wordsInPhrase.pop_front();
      }

      //add letters
      for ( int i = 0 ; i < newSecret.length() ; i++ ) {
         if(newSecret.at(i)!=' ')
         secretSet.insert( newSecret.substr(i,1) );
      }

      return newSecret;
   }
   //virtual void Display(string message)=0;
   bool ValidGuess(string guess, string &message, string &nextGuess){

      nextGuess=guess;

      if ( swansonUtil::ExistsInSet( guess , guessSet ) ) {
         message = "You have guessed this already";
         return false;
      }

      if(!HasSpaces(guess)) { //single word or letter, check validity
         if(myDict.IsAWord(guess)) return true;
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

      guessSet.insert(guess);
      //todo check that not already revealed word
      //todo remove letters only occuring in guessed words from set
      return true;

   }
   //virtual bool GuessCorrect(string guess)=0;
   /*bool GameWon(){
      return (GetRevealPhrase()==secret);
   }*/
   //virtual void GameOverDisplay(bool won) = 0;

};



#endif /* PHRASEGUESS_HPP_ */
