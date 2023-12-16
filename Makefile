all: blackjack

play: blackjack
	./blackjack

blackjack: headers
	g++ -o blackjack Blackjack.cpp Art.o Card.o Rank.o Suit.o CardSet.o Deck.o Hand.o Chip.o Dealer.o Input.o Player.o Game.o

headers:
	g++ -c components/Art.cpp
	g++ -c components/Rank.cpp
	g++ -c components/Suit.cpp
	g++ -c components/Card.cpp
	g++ -c components/CardSet.cpp
	g++ -c components/Deck.cpp
	g++ -c components/Hand.cpp
	g++ -c components/Chip.cpp
	g++ -c game/Dealer.cpp
	g++ -c game/Input.cpp
	g++ -c game/Player.cpp
	g++ -c game/Game.cpp

clean:
	rm -f blackjack
	rm -f *.o