/*
 * GameClass.hpp
 *
 *  Created on: Jul 30, 2014
 *      Author: brandon
 */

#ifndef GAMECLASS_HPP_
#define GAMECLASS_HPP_

#include <set>
#include "SwansonLibs/swansonInput.hpp"
#include "SwansonLibs/swansonString.hpp"
#include "SwansonLibs/swansonUtils.hpp"
using namespace std;

template <typename Type>
class GuessGame{
protected:
   Type secret;
   set<Type> guessSet;
   string inputPrompt,welcomeMessage,correctGuess,IncorectGuess;
   static string YouWin, YouLoose;
   string nextGuessInput;
   Type nextGuess;
   string badInputMsg;
   int guessRemaining, MaxGuesses;
   static const int MaxGuessDefault = 6;
   bool ComputerGeneratedSecret;

   //refresh terminal screen
   void (*ClearScreen) ();

   virtual Type GenerateSecret(bool computerGen)=0;
   virtual void Display(string message)=0;
   virtual bool ValidGuess(string guess, string &message, Type &nextGuess)=0;
   virtual bool GuessCorrect(Type guess)=0;
   virtual bool GameWon() = 0;
   virtual void GameOverDisplay(bool won) = 0;

public:

   GuessGame():ClearScreen(swansonUtil::ClearScreen),
      MaxGuesses(MaxGuessDefault){};

   void SetMaxGuesses(int maxGuesses){
      MaxGuesses=maxGuesses;
   }

   void SetClearScreen(void(*clrScrn)()){
      ClearScreen = clrScrn;
   }

   void PlayGame(){
      guessRemaining = MaxGuesses;
      guessSet.clear();
      secret=GenerateSecret(ComputerGeneratedSecret);

      Display(welcomeMessage);

      do {
         //get a guess from user
         nextGuessInput = swansonInput::GetString(inputPrompt);
         swansonString::LowerCasePreserve(nextGuessInput);

         //ensure it is a proper guess
         while(!ValidGuess(nextGuessInput, badInputMsg, nextGuess)){
            Display( badInputMsg );
            nextGuessInput = swansonInput::GetString(inputPrompt);
            swansonString::LowerCasePreserve(nextGuessInput);
         }

         bool correct = GuessCorrect(nextGuess);
         guessSet.insert(nextGuess);

         //check guess
         if(correct){
            Display(correctGuess);
         }else{
            guessRemaining--;
            Display(IncorectGuess);
         }

         //keep guessing if not solved, or remaining guesses
      } while ( !GameWon() && guessRemaining > 0 );

      GameOverDisplay(GameWon());

   }


   void SetComputerGeneratedSecret(bool compGen){
      ComputerGeneratedSecret = compGen;
   }

};

template <class Type>
string GuessGame<Type>::YouWin = "Congratulations you have guessed the secret";
template <class Type>
string GuessGame<Type>::YouLoose = "You ran out of guesses before guessing the secret";


#endif /* GAMECLASS_HPP_ */
