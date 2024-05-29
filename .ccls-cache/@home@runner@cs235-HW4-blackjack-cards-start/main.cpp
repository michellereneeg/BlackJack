#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Hand.h"
#include "Card.h"
#include "BlackJack.h"
#include "testMe.h"

int main() {
  //Card queenOfHearts(45);      // This should work already with no changes since Card.h and Card.cpp are done
  //std::cout << queenOfHearts;  // This works because we have implemented

  //Hand myHand( { 0, 1, 2, 3 } ) ;
  //myHand.printMe();
  
  // LAST: When everything is working (below), rename "testMe.cpp.rename" to "testMe.cpp", then call the testMe() function
  testMe();   // call  testMe() to test all class and methods (input will be redirected)
  
  // First: test the Hand class below to be sure you have it working before you move on to BlackJack at bottom

  //Hand oneCardHand({ 0 });   // Hand with one card indicated via ID == 0 (ace of spades)
  //oneCardHand.printMe();     // print the hand

  //Hand twoCardHand({ 0, 7});  // Hand with two cards indicated via ID == 0, and ID == 7 (two of clubs)
  //twoCardHand.printMe();      // print the hand

  // Second: uncomment and test a "large" hand - the full deck of cards
  srand(time(NULL));                                   // set the random number seed based on current time  , for the shuffle
  std::vector<int> cardIDs;                            // we'll fill this up with card ids zero to 51
  for(int i=0; i<52; i++)  cardIDs.push_back(i);       // here we are pushing integers which represent card IDS (not cards!)
  random_shuffle(cardIDs.begin(), cardIDs.end());      // user iterators to shuffle the vector of cardIDs

  Hand myDeck(cardIDs);    // now we are giving the Hand constructor a vector of INTEGERS (not cards!)
  //myDeck.printMe();       // print the Hand we constructed
  //std::cout << myDeck.size();

  // Next: uncomment and test this below when you are sure your Hand class is fully implemented, to test your game

  BlackJack game({ "Player A", "Dealer" }, cardIDs);   // specify both arguments; constructor should build full deck from provided ids
  game.play();                                         // play the game 

  return 0; 
}