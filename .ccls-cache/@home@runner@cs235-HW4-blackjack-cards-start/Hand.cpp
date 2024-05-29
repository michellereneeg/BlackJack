#include<iostream>
#include "Card.h"
#include "Hand.h"
#include <list>

//construct Card instances based on the vector of integer IDs provided (call the Card constructor with each integer ID).  Then place the new instance of each Card into the Hand's "cards" member. 
Hand:: Hand(std::vector<int> initialCards) {
  for(int i =0; i < initialCards.size(); ++ i)
    cards.push_back( Card(initialCards.at(i))); 
}

// print out the hand from “top to bottom”
void Hand::printMe (){
  std::cout << "{ ";
  for(auto iter=cards.begin(); iter != cards.end(); ++iter) {
    std::cout << *iter << ", "; 
  }
  std::cout << "} ";
}

// return int of how many cards in the Hand
int Hand::size () {
  return cards.size(); 
}

// “deal” a card from the top: remove it and return a copy of it
Card Hand::dealACard() {
  if (cards.size()<=0) return Card(-1); // return a Joker if the deck is empty
  Card topCard = cards.front(); // make a copy of the "top" card
  cards.pop_front(); // pop it off the stack
  return topCard; // return a copy
}    

 // add a new card to the top of a Hand
void Hand::addACard(Card newCard) {
  cards.push_front(newCard);
} 

 // return an integer value that represents the sum of all card values in this Hand
int Hand::getPoints() {
  int sum = 0;
  for(auto iter=cards.begin(); iter != cards.end(); ++iter) {
    sum += iter->value;
  }
  return sum;
} 

// BONUS: return true if the Hand currently contains any Ace card
bool Hand::hasAnAce() {
  for(auto iter=cards.begin(); iter != cards.end(); ++iter) {
    if (iter->name == "Ace") {
      return true;
    }
  }
  return false;
} 



