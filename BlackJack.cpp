#include<iostream>
#include "Card.h"
#include "Hand.h"
#include "BlackJack.h"
#include <string>

//
// PLAY
//

// DONE: the method below has been written for you to help you understand how your methods will be used
// uncomment when you are ready to test the game
  void BlackJack :: play() {
    std::cout << "Let's Play BlackJack!" << std::endl;

    bool gameOver = false; // Bust means >21
    this->printInstructions(); // print instructions
    this->printBoard(); // print the board

    while( !gameOver ) { // keep playing as long as the game is not won by either player
    
      gameOver = this->takePlayerTurn(); // current player takes a turn

      if (gameOver){
        break;
      }

      this->printBoard(); // print the board if that was a good move


      gameOver = this->takeDealerTurn(); // AI takes a turn

      if (gameOver)
        break;

    } // end while: game over

    // note below that the winning player is who we want, not the current player
    if (getWinningPlayerId() != -1)
      std::cout << ((getWinningPlayerId() == 0) ? "Congratulations! "  : "Sorry! ") << playerNames[getWinningPlayerId()] << " has won the game!" << std::endl;
    else 
      std::cout << "Looks like the game was a tie" << std::endl;

    std::cout << "Keep betting away your college fund!" << std::endl;

  } // end play()


// Implement the rest of your out-of-class constructors and methods below here

// constructor
//std::vector<std::string> -  the characters that describe the players, defaults to "Player" and "Dealer"
// std::vector<int> cardIDs - vector of card IDs we want in the  deck; defaults to empty (player and dealer hands will be empty)
BlackJack :: BlackJack( std::vector<std::string>  _playerNames, std::vector<int> cardIDs) : playerNames(_playerNames) {
  deck = Hand(cardIDs);
}//end constructor

// print instructions for the game
void BlackJack:: printInstructions(){
  std::cout << "Try to get closest to 21 without going over" << std::endl << "The Player goes first, and then the Dealer" << std::endl;
  std::cout << " Each hand is scored by adding up each card's point value, where Card values will be assigned as shown below:" << std::endl <<
  "\tA) Aces will be treated as 1" << std::endl <<
    "\tB) 2 through 9 will have the corresponding values 2 through 9" << std::endl <<
    "\tC) Jack, King, and Queen will have a value of 10 always" << std::endl << std::endl; 
} 

// print the state of the game: player hand (all cards up), and dealer hand (all cards up)
void BlackJack:: printBoard() {
  std:: cout << "Dealer's Hand: ";
  dealerHand.printMe();
  std:: cout << getDealerPoints() << " points\n";
  std:: cout << "Players's Hand: ";
  playerHand.printMe();
  std:: cout << getPlayerPoints() << " points\n\n";
} 

// return the value of the private winningPlayerId, as set by isWin()
int BlackJack:: getWinningPlayerId() {
  return winningPlayerId;
}

// return the points for the player's hand by calling Hand::playerHand->getPoints()
int BlackJack:: getPlayerPoints() {
  return playerHand.getPoints();
}

// return the points for the dealer's hand by calling Hand::dealerHand->getPoints()
int BlackJack::getDealerPoints() {
  return dealerHand.getPoints();
}

// Player takes their turn, setting winningPlayerId to -1, 0, or 1, and returning true if the game is over
bool BlackJack::takePlayerTurn(){
  std::string playerChoice;
  std::cout << "Player's turn: Hit (h) or Stand (s)? ";
  int sumWithAce = 0; //variable to hold new total if Ace value is 11 instead of 1
  int aceCount = 0; //variable to keep track of number of Aces in the hand
  while(true) {
    std::cin >> playerChoice; //get player's choice to hit or stand
    std:: cout << ((playerChoice == "h") ? "Player hits..." : "Player stands.") << std:: endl;
    if (playerChoice == "s") {
      winningPlayerId = -1; //player stands, game is not over until dealer also goes
      return false;
    }
    
    else { //if player hits...
      Card newCard = deck.dealACard();
      playerHand.addACard(newCard);

      //keep track of number of Aces in the hand
      if(newCard.name == "Ace") {
         aceCount++;
       }

      //determine how many Aces to "transform" from 1 to 11

      //case 1: the player hand has 0 or 1 Aces
      if((getPlayerPoints()+10*aceCount < 22)) {
        sumWithAce = (getPlayerPoints() + 10*aceCount); //if Ace count is 0, basically, don't change the player's points. if Ace count is 1, add 10
      }
      //case 2: the player hand has 1 or 2 Aces
      else if ((getPlayerPoints()+10*(aceCount-1) < 22)) {
          sumWithAce = (getPlayerPoints() + 10*(aceCount-1)); //With 1 Ace, you add 10, with 2 Aces, if still under 22, add 20.
      }
      //case 3: Player has 2 or 3 Aces
      else if ((getPlayerPoints()+10*(aceCount-2) < 22)) {
          sumWithAce = (getPlayerPoints() + 10*(aceCount-2));
      }
      //case 4: Player has 3 or 4 Aces
      else if ((getPlayerPoints()+10*(aceCount-3) < 22)) {
          sumWithAce = (getPlayerPoints() + 10*(aceCount-3));
      }
      
      printBoard();
      //If at any time after taking a card (a Hit) the Player has an Ace and any other single card that is worth 10 points, for a total of 21 points, that player wins immediately (and the Dealer loses).
      if (playerHand.hasAnAce() && sumWithAce == 21) {
        std::cout << "Player wins with an Ace and ten!" << std:: endl;
        winningPlayerId = 0;
        return true;
      }

        // If the player "busts" by going over 21, set the `winningPlayerId` value to 1 for the dealer and return true.
      else if (getPlayerPoints() > 21) {
        std::cout << "Player busts!" << std:: endl;
        winningPlayerId = 1;
        return true;
      }

        // If the player's total hand value after a hit is  exactly == 21, the player's turn is over (they must stand), and the turn passes to the dealer (return false and set `winningPlayerId` to -1, because the game is not over).
      else if (getPlayerPoints() == 21) {
        std::cout << "Player must stand." << std:: endl;
        winningPlayerId = -1;
        return false;
      }
    }
    // The player can hit as many times as they like until they win or bust
    std::cout << "Player's turn again: Hit (h) or Stand (s)? ";
  }
}

// Dealer takes a turn, setting winnningPlayerId to -1, 0, or 1, and returning true if the game is over
bool BlackJack:: takeDealerTurn() {
  //As long as the value of the dealer's hand is <=16, the Dealer MUST hit. (the dealer CANNOT take a card if the dealer has >=17)
  while (getDealerPoints() <= 16) {
    std::cout << "Dealer Hits." << std::endl;
    dealerHand.addACard(deck.dealACard());
    printBoard();
  }
  // If the Dealer's hand exceeds a value of 21, the dealer loses, and you should set the `winningPlayerId` to 0 and return true, indicating that the game is over.
  if (getDealerPoints() > 21) {
    winningPlayerId = 0;
  }
  //Otherwise if the dealer's hand value > 16, and also >= the Player's hand value, the dealer wins; so set the `winningPlayerId` to 1, and return true (game over).
  else if (getDealerPoints() > 16 && getDealerPoints() >= getPlayerPoints()) {
    winningPlayerId = 1;
  }
  // If the Dealer's hand exceeds 16 but is still less than the Player's hand, the Player wins: set `winningPlayerId` accordingly and return true (game over).
  else if (getDealerPoints() > 16 && getDealerPoints() < getPlayerPoints()) {
    winningPlayerId = 0;
  }
  return true;
}