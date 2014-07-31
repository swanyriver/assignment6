/***********************************************************
 *
 * * Author: Brandon Swanson
 *
 * * Date Created: 07-30-2014
 *
 * * Last Modification Date: 07-30-2014
 *
 * * Filename:
 *
 *
 * * Overview: Week 6 Exercise Component #4
 * *
 * * Input:
 * *
 * * Output:
 * *
 * ***********************************************************/

#include <iostream>
#include <string>
#include <string>
#include "SwansonObjects/menu.hpp"
#include "SwansonLibs/swansonInput.hpp"
#include "SwansonLibs/swansonUtils.hpp"
#include "SwansonLibs/swansonString.hpp"

using namespace std;

void demonstrateComponent ();

int main () {

   string intro = "This is the matrix product of 2 matrixes of 10X10 \n"
         "they were filled with random numbers from [0-99]";

   swansonUtil::SeedRandom();

   GoItem myExerciseComp( demonstrateComponent , "" , intro );

   myExerciseComp.ItemSelected();

   return 0;

}

//////////////////////////////////////////////////
////////////[ROW] [COLLUMN] /////////////////////
/////////////////////////////////////////////////

const int MatrixSize = 10;

void MatrixProduct ( const int matrixA[][MatrixSize] ,
      const int matrixB[][MatrixSize] , int product[][MatrixSize] );

string MatrixPrint ( const int matrix[][MatrixSize] );
int getlargestNumber ( const int matrix[][MatrixSize] );
int NumberLength ( int number );

void FillMatrix ( int emptyMatrix[][MatrixSize] );

void demonstrateComponent () {
   int matrixOne[MatrixSize][MatrixSize];
   int matrixTwo[MatrixSize][MatrixSize];
   int matrixThree[MatrixSize][MatrixSize];

   //randomly generate 2 matrixes
   FillMatrix( matrixOne );
   FillMatrix( matrixTwo );
   //print them
   cout << "MATRIX ONE \n" << MatrixPrint( matrixOne ) << endl;
   cout << "MATRIX TWO \n" << MatrixPrint( matrixTwo ) << endl;
   //pass them to function
   MatrixProduct( matrixOne , matrixTwo , matrixThree );
   //print result
   cout << "MATRIX THREE (product of one and two) \n"
         << MatrixPrint( matrixThree ) << endl;
}

void MatrixProduct ( const int matrixA[][MatrixSize] ,
      const int matrixB[][MatrixSize] , int product[][MatrixSize] ) {

   int sum;

   for ( int row = 0 ; row < MatrixSize ; row++ ) { //ROW
      for ( int collumn = 0 ; collumn < MatrixSize ; collumn++ ) { //COLLUMN
         /////////////calculate value for matrix product////
         sum = 0;
         for ( int i = 0 ; i < MatrixSize ; i++ ) {
            sum += matrixA[row][i] * matrixB[i][collumn];
         }
         //put it in the product matrix
         product[row][collumn] = sum;
      }
   }
}

string MatrixPrint ( const int matrix[][MatrixSize] ) {
   string matrixString;
   string lineStr;

   const int spacing = NumberLength(getlargestNumber(matrix))+1;

   for ( int row = 0 ; row < MatrixSize ; row++ ) { //ROW
      //fill lineStr with spaces
      lineStr.append( spacing * MatrixSize , ' ' );
      for ( int collumn = 0 ; collumn < MatrixSize ; collumn++ ) { //COLLUMN
         //add number to string
         string nextNumber = swansonString::GetString( matrix[row][collumn] );
         lineStr.replace( spacing * collumn , nextNumber.length() ,
               nextNumber );
      }
      //add single line to matrix output string
      matrixString += lineStr + "\n";
      lineStr.clear();
   }

   return matrixString;
}

void FillMatrix ( int emptyMatrix[][MatrixSize] ) {

   for ( int row = 0 ; row < MatrixSize ; row++ ) { //ROW
      for ( int collumn = 0 ; collumn < MatrixSize ; collumn++ ) { //COLLUMN
         emptyMatrix[row][collumn] = swansonUtil::GetRandomInRange( 99 );
      }
   }
}

int getlargestNumber ( const int matrix[][MatrixSize] ) {
   int largestNumber = 0;
   for ( int row = 0 ; row < MatrixSize ; row++ ) { //ROW
      for ( int collumn = 0 ; collumn < MatrixSize ; collumn++ ) { //COLLUMN
         if (matrix[row][collumn]>largestNumber)
            largestNumber = matrix[row][collumn];
      }
   }
   return largestNumber;
}
int NumberLength ( int number ) {
   int numberLenght = 1;
   while(number>10){
      number = number/10;
      numberLenght++;
   }
   return numberLenght;
}

//replaced with more straightforward method
////////////////////////////////////////
/*string MatrixPrint(const int matrix[][MatrixSize]){
 const int spacing = 4;
 int spacePadding;
 string matrixString;
 string lineStr;

 for(int row = 0; row<MatrixSize; row++){ //ROW
 for( int collumn = 0; collumn<MatrixSize; collumn++){ //COLLUMN
 //add number to string
 lineStr += swansonString::GetString(matrix[row][collumn]);
 //calculate spacing for next number
 spacePadding = ((collumn+1)*spacing)-lineStr.length();
 //lineStr.append(' ',spacePadding);
 lineStr.append(spacePadding,' ');
 }
 //add single line to matrix output string
 matrixString += lineStr + "\n";
 lineStr.clear();
 }

 return matrixString;
 }*/
