/*
 * someSum.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: brandon
 */
#include <iostream>
long int sumFun();

int main(){
   long int sum = sumFun();
   std::cout <<
         "the sum of all numbers greater than 0 that are a product of 3 or a product"<<
         std::endl << "of 5 is:" << sum;
}

long int sumFun(){
   long int sum = 0;
   long int fiveSum = 0;
   long int threeSum = 0;

   for(;fiveSum<1000;fiveSum+=5){
      sum+=fiveSum;
   }
   for(;threeSum<1000;threeSum+=5){
      sum+=threeSum;
   }

   return sum;

}
