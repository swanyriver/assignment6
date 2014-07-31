/*
 * GameClass.hpp
 *
 *  Created on: Jul 30, 2014
 *      Author: brandon
 */

#ifndef GAMECLASS_HPP_
#define GAMECLASS_HPP_

#include <list>
#include "SwansonLibs/swansonInput.hpp"
using namespace std;

template <typename Type>
class GuessGame{
protected:
   Type secret;
   list<Type> guessesMade;
   string inputPrompt,welcomeMessage,correctGuess,IncorectGuess;
   static string YouWin, YouLoose;
   string nextGuessInput;
   Type nextGuess;
   string badInputMsg;
   int guessRemaining;
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

   GuessGame(void(*clearScreen)()):ClearScreen(clearScreen){};

   void PlayGame(int MaxGuesses){
      guessRemaining = MaxGuesses;
      guessesMade.clear();
      secret=GenerateSecret(ComputerGeneratedSecret);

      Display(welcomeMessage);

      do {
         //get a guess from user
         nextGuessInput = swansonInput::GetString(inputPrompt);

         //ensure it is a proper guess
         while(!ValidGuess(nextGuessInput, badInputMsg, nextGuess)){
            Display( badInputMsg );
            nextGuessInput = swansonInput::GetString(inputPrompt);
         }

         guessesMade.push_back(nextGuess);

         //check guess
         if(GuessCorrect(nextGuess)){
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
