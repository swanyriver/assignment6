/*

 * testGame.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: brandon
 */

#include <iostream>
#include <string>
#include <iterator>
#include "GameClass.hpp"
#include "SwansonLibs/swansonUtils.hpp"

#include "NumberGuess.hpp"
#include "wordGuess.hpp"
#include "phraseGuess.hpp"
using namespace std;


/*class simpleWord:public GuessGame<string>{
public:
   simpleWord(void(*clearScreen)()):GuessGame(clearScreen){
      cout << "simpleword constructed" << endl;
      inputPrompt = "what is your guess:";
   }
private:
   string GenerateSecret(){
      return "secret";
   }
   void Display(string message){
      cout << "secret is:" << secret << endl;
      cout << "guesses";
      for(list<string>::iterator it=guessesMade.begin(); it!=guessesMade.end();it++){
         cout << *it << " ";
      }
   }
   bool ValidGuess(string guess, string &message, string &nextGuess){
      nextGuess=guess;
      return true;
   }
   bool GuessCorrect(string guess){return false;}
   bool GameWon(){
      return false;
   }
   void GameOverDisplay(bool won){
      cout << "game over";
   }
};*/

int main(){
   //NumberGuess myGame(swansonUtil::ClearScreen, 100);
   //WordGuess myGame(swansonUtil::ClearScreen);
   PhraseGuess myGame(swansonUtil::ClearScreen);
   myGame.PlayGame(4);
}
