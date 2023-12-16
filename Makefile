all: blackjack

play: blackjack
	./blackjack

blackjack: game
	g++ -o blackjack Blackjack.cpp Art.o Card.o CardSet.o Chip.o Dealer.o Deck.o Game.o Hand.o Input.o Player.o Rank.o Suit.o

art:
	g++ -c Art.cpp

chip: art
	g++ -c Chip.cpp

card: art
	g++ -c Rank.cpp
	g++ -c Suit.cpp
	g++ -c Card.cpp

cardset: card
	g++ -c CardSet.cpp
	g++ -c Deck.cpp
	g++ -c Hand.cpp

game: cardset chip
	g++ -c Dealer.cpp
	g++ -c Game.cpp
	g++ -c Input.cpp
	g++ -c Player.cpp

clean:
	rm blackjack
	rm *.o