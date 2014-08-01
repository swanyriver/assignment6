/*
 * NumberGuess.hpp
 *
 *  Created on: Jul 30, 2014
 *      Author: brandon
 */

#ifndef NUMBERGUESS_HPP_
#define NUMBERGUESS_HPP_

#include "GameClass.hpp"
#include "SwansonLibs/swansonUtils.hpp"
#include "SwansonLibs/swansonInput.hpp"
#include "SwansonLibs/swansonString.hpp"
#include <cstdlib>
#include <errno.h>

class NumberGuess:public GuessGame<int>{
private:
   int numRange;
   int rangeBegining, rangeEnd;
   string secretNumberPrompt;

public:
   NumberGuess(void(*clearScreen)(), int numrange)
   :GuessGame<int>(clearScreen),numRange(numrange){
      secretNumberPrompt = "What should the secret number between [1-" +
            swansonString::GetString(numRange) + "] be:";
      inputPrompt= "What is your next guess between [1-" +
            swansonString::GetString(numRange) + "]:";
      welcomeMessage= "Welcome to number guess Good luck!";
      rangeBegining=1;
      rangeEnd=numrange;
   }
private:

   int GenerateSecret(bool computerGen){
      if(computerGen){
         return swansonUtil::GetRandomInRange(1,numRange);
      }else{
         return swansonInput::GetInt(secretNumberPrompt,1,numRange);
      }
   }

   bool ValidGuess(string guess, string &message, int &nextGuess){
      long int int_rtrn;
      //check that it is a valid number string
      if(!swansonString::AllNumbers(guess) || guess.empty()){
         message = "lets try to restrain ourselves to only whole numbers";
         return false;
      }
      //convert it to a number type
      int_rtrn = strtol( guess.c_str() , NULL , 0 );
      //check that it is in range
      if( !(int_rtrn >= rangeBegining && int_rtrn <= rangeEnd)
       || (errno == ERANGE && (int_rtrn == LONG_MAX || int_rtrn == LONG_MIN))){
         message = "Please keep the input within these bounds [" +
               swansonString::GetString(rangeBegining) +
               " - " + swansonString::GetString(rangeEnd) + "]";
         return false;
      }else{
         nextGuess = int_rtrn;
         return true;
      }

   }
   bool GuessCorrect(int guess){
      if(guess==secret){
         return true;
      }else{
         if(guess<secret){
            this->IncorectGuess = "That guess was too low";
            rangeBegining = guess+1;
         }else if(guess>secret){
            this->IncorectGuess = "That guess was too high";
            rangeEnd = guess-1;
         }
         inputPrompt= "What is your next guess between [" +
               swansonString::GetString(rangeBegining)+"-" +
               swansonString::GetString(rangeEnd) + "]:";
         return false;
      }
   }

   bool GameWon(){
      if(this->nextGuess==secret){
         return true;
      }
      else return false;
   }

   void GameOverDisplay(bool won){
      if(won)
         Display(this->YouWin+ " it was " + swansonString::GetString(secret));
      else
         Display(this->YouLoose);
   }

   void Display(string message){
      ClearScreen();
      //todo, fix this!!
      cout << "message:" << message << endl;
      cout << "guesses remaining:" << guessRemaining<< endl;

   }

};
#endif /* NUMBERGUESS_HPP_ */
