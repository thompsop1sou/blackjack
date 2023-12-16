#ifndef GAME_H
#define GAME_H

#include "../components/Art.h"
#include "Dealer.h"
#include "Player.h"
#include "Input.h"

class Game
{
	
public:

	// Enum type for the stage of this Game
	enum Stage {
		plrChoice, plrBuy, plrBet,
		dlrShuffle, dlrDeal, dlrCheckNaturals,
		plrInitialHandNoSplit, plrInitialHandYesSplit,
		plrSplitHandOne, plrSplitHandTwo, plrRegularHand,
		dlrHand, dlrSettleBets, dlrResetTable, plrLeave
	};

	/***** Manager Functions *****/

	// Default constructor
	Game();
	// Destructor
	~Game();

	/***** Member Functions *****/

	// Welcomes user and has user set card size and dealer delay
	void intro();
	// Returns true if this Game is in finished state
	bool finished();
	// Displays this Game to console
	void display();
	// Gets input from user for this stage
	void input();
	// Evaluates input, performs necessary actions, and increments the stage appropriately
	void process();
	// Shows how many chips bought and how many chips at end
	void results();

private:

	/***** Member Functions *****/

	// Returns title of this Game
	Art title(bool zoom = true);
	// Sets data members for m_input based on stage
	void set_input(Stage stage);
	// Splits player's hand into two hands and deals one more card to each hand
	void split();
	// Doubles player's bet and deals them one more card
	void double_down();
	// Determine who wins and settle bets appropriately
	void settle_bets();
	// Discards all cards and moves bets to stack
	void reset_table();
	// Returns a funtion which takes string input, tries to convert it to int, and tests whether it is between min and max
	function<bool(string)> in_intvl(int min, int max);

	/***** Data Members *****/

	// Dealer member holding data about shoe, discard, and dealer hand
	Dealer m_dealer;
	// Player member holding data about stack, bet, and player hand
	Player m_player;
	// Input member holding data about input for current stage
	Input m_input;
	// Current stage of game
	Stage m_stage;
	// Zoom level of game, large if true, small if false
	bool m_zoom;
	// Total value of chips bought
	int m_tot_bought;
};

#endif