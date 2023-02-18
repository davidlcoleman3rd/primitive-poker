# primitive-poker
A simple text-based poker game WIP.

**Version 0.2.0**
- Merged the deckAndHandTest branch with main
- Implemented the circularlList class and the Player class to allow for mulitple players to draw hands of cards from the same deck, printing all hands in order with their score values
- Fixed logic issues with this implementation in order to print all hands without error

**Version 0.1.0**
- Created a graphical display of a player’s hand when showing hand
- Added sorting to the hand as well as point counting
- Created a separate point counter that allows the program to output any “winning” hands they have 
   -– This includes pair, 2 pair, 3 of a kind, 4 of a kind, full house, flush, straight, straight flush, and royal flush
- Fully defined and implemented shuffle function and hand print function. Deck can be created, shuffled, and deal a full hand of cards to a player, whose hand can then be displayed on the screen correctly 
   -– This was fixed by using heap allocation of the vector vTemp instead of stack allocation, which originally caused undefined behavior 
- Began to perform isolated tests on hand and deck. 
- While dealing cards to a hand and displaying the hand works, shuffling the deck currently has bugs 
- Defined and implemented a sorting algorithm for sorting hands 
- Added files for the discard and pot class 
- Began to implement functionality for sorting player hands to estimate the value of the player’s hand 
- Began to layout the structure of the Game class, which connects the bulk of classes together in one single “playspace” for the gameplay 
- Began to define and implement various functionality of the Hand class and its interactions with Deck and Card classes 
- Fully defined and implemented the Card class with all basic features, including a copy constructor 
- Began to define and add features to the Deck class, including shuffling and dealing 
- Tweaked errors and syntax issues with cod
