#pragma once

#include "Dealer.h"
#include "Player.h"
#include "Input.h"
#include "Art.h"

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
	Game() : m_dealer(6), m_player(), m_input(), m_stage(plrChoice), m_zoom(false), m_tot_bought(0)
	{}

	// Destructor
	~Game()
	{}

	/***** Member Functions *****/

	// Welcomes user and has user set card size and dealer delay
	void intro()
	{
		cout << "\n" << title(m_zoom) << "\n"
			<< "\n===================== WELCOME =====================\n"
			<< "\nWelcome to Blackjack! We hope you have fun playing!"
			<< "\n"
			<< "\nBefore you begin, please set up the following. Note"
			<< "\nthat you can use numbers or words to make a choice." << endl;

		// Setting Card Size
		m_input.set_kind(Input::Choice);
		m_input.set_choices({ "Small", "Large" });
		m_input.set_prompt("Choose an option from above >> ");
		m_input.set_condition([](string str) -> bool { return true; });

		Art card_input_art = m_input.art(false);
		Art small_art = Card(1, 3).art(false);
		Art large_art = Card(1, 3).art(true);

		small_art.pad((card_input_art.width() - 3) / 2, large_art.height());
		large_art.pad((card_input_art.width() - 3) / 2, large_art.height());

		for (int i = 0; i < large_art.height(); ++i)
			card_input_art.add_layer(i + 2, "|" + small_art.get_layer(i) + "|" + large_art.get_layer(i) + "|");

		cout << "\n==================== CARD SIZE ====================\n"
			<< "\n" << card_input_art << endl;

		m_input.retrieve();

		if (m_input.value() == 0)
			m_zoom = false;
		else if (m_input.value() == 1)
			m_zoom = true;

		// Setting Dealer Delay
		m_input.set_kind(Input::Number);
		m_input.set_choices({ "Setting Dealer Delay" });
		m_input.set_prompt("Enter seconds to wait for each dealer action >> ");
		m_input.set_condition(in_intvl(0, 60));

		cout << "\n================== DEALER DELAY ===================\n"
			<< "\n" << m_input.art(false) << endl;

		m_input.retrieve();

		m_input.set_delay(m_input.value());
	}

	// Returns current stage of this Game
	bool finished()
	{
		return (m_stage == plrLeave);
	}

	// Displays this Game to console
	void display()
	{
		cout << "\n" << title(m_zoom) << "\n"
			<< "\n" << m_dealer.title(m_zoom) << "\n"
			<< "\n" << m_dealer.art(m_zoom) << "\n"
			<< "\n" << m_player.title(m_zoom) << "\n"
			<< "\n" << m_player.art(m_zoom) << endl;
	}
	
	// Gets input from user for this stage
	void input()
	{
		set_input(m_stage);

		cout << "\n" << m_input.title(m_zoom) << "\n\n"
			<< m_input.art(m_zoom) << endl;

		m_input.retrieve();
	}

	// Evaluates input, performs necessary actions, and increments the stage appropriately
	void process()
	{
		switch (m_stage)
		{
		// Choose whether to continue, add to stack, or leave
		case plrChoice:
			if (m_input.value() == 0) // Continue
				m_stage = plrBet;
			else if (m_input.value() == 1) // Add to Stack
				m_stage = plrBuy;
			else if (m_input.value() == 2) // Leave
				m_stage = plrLeave;
			break;
		// Player adds to stack
		case plrBuy:
			m_player.stack().add(m_input.value());
			m_tot_bought += m_input.value();
			m_stage = plrBet;
			break;
		// Player places bet
		case plrBet:
			m_player.bet().add(m_input.value());
			m_player.stack().sub(m_input.value());
			if (m_dealer.shoe().count() <= 60)
				m_stage = dlrShuffle;
			else
				m_stage = dlrDeal;
			break;
		// Dealer shuffles
		case dlrShuffle:
			m_dealer.shoe().collect(m_dealer.discard());
			m_dealer.shoe().all_down();
			m_dealer.shoe().shuffle();
			m_stage = dlrDeal;
			break;
		// Dealer deals
		case dlrDeal:
			m_dealer.shoe().deal(m_player.hand(), 2, true);
			m_dealer.shoe().deal(m_dealer.hand(), 1, true);
			m_dealer.shoe().deal(m_dealer.hand(), 1, false);
			m_stage = dlrCheckNaturals;
			break;
		// Checking for naturals
		case dlrCheckNaturals:
			if ((m_player.hand().count() == 2 && m_player.hand().score() == 21) || (m_dealer.hand().count() == 2 && m_dealer.hand().score() == 21)) // Natural
			{
				m_dealer.hand().all_up();
				m_stage = dlrSettleBets;
			}
			else // No natural
			{
				if (m_player.hand().splittable())
					m_stage = plrInitialHandYesSplit;
				else
					m_stage = plrInitialHandNoSplit;
			}
			break;
		// Player chooses whether to hit, stand, or double down
		case plrInitialHandNoSplit:
			if (m_input.value() == 0) // Hit
			{
				m_dealer.shoe().deal(m_player.hand(), 1, true);
				if (m_player.hand().score() > 21)
				{
					m_dealer.hand().all_up();
					m_stage = dlrSettleBets;
				}
				else
				{
					m_stage = plrRegularHand;
				}
			}
			else if (m_input.value() == 1) // Stand
			{
				m_dealer.hand().all_up();
				m_stage = dlrHand;
			}
			else if (m_input.value() == 2) // Double Down
			{
				double_down();
				m_dealer.hand().all_up();

				if (m_player.hand().score() > 21)
					m_stage = dlrSettleBets;
				else
					m_stage = dlrHand;
			}
			break;
		// Player chooses whether to hit, stand, split, or double down
		case plrInitialHandYesSplit:
			if (m_input.value() == 0) // Hit
			{
				m_dealer.shoe().deal(m_player.hand(), 1, true);
				if (m_player.hand().score() > 21)
				{
					m_dealer.hand().all_up();
					m_stage = dlrSettleBets;
				}
				else
				{
					m_stage = plrRegularHand;
				}
			}
			else if (m_input.value() == 1) // Stand
			{
				m_dealer.hand().all_up();
				m_stage = dlrHand;
			}
			else if (m_input.value() == 2) // Split
			{
				split();
				m_stage = plrSplitHandOne;
			}
			else if (m_input.value() == 3) // Double Down
			{
				double_down();
				m_dealer.hand().all_up();

				if (m_player.hand().score() > 21)
					m_stage = dlrSettleBets;
				else
					m_stage = dlrHand;
			}
			break;
		// After split, player chooses whether to hit or stand for first hand
		case plrSplitHandOne:
			if (m_input.value() == 0) // Hit
			{
				m_dealer.shoe().deal(m_player.hand(), 1, true);

				if (m_player.hand().score() > 21)
					m_stage = plrSplitHandTwo;
				else
					m_stage = plrSplitHandOne;
			}
			else if (m_input.value() == 1) // Stand
			{
				m_stage = plrSplitHandTwo;
			}
			break;
		// After split, player chooses whether to hit or stand for second hand
		case plrSplitHandTwo:
			if (m_input.value() == 0) // Hit
			{
				m_dealer.shoe().deal(m_player.split_hand(), 1, true);

				if (m_player.split_hand().score() > 21)
				{
					m_dealer.hand().all_up();

					if (m_player.hand().score() > 21)
						m_stage = dlrSettleBets;
					else
						m_stage = dlrHand;
				}
				else
				{
					m_stage = plrSplitHandTwo;
				}
			}
			else if (m_input.value() == 1) // Stand
			{
				m_dealer.hand().all_up();
				m_stage = dlrHand;
			}
			break;
		// After regular hit, player chooses whether to hit or stand
		case plrRegularHand:
			if (m_input.value() == 0) // Hit
			{
				m_dealer.shoe().deal(m_player.hand(), 1, true);

				if (m_player.hand().score() > 21)
				{
					m_dealer.hand().all_up();
					m_stage = dlrSettleBets;
				}
				else
				{
					m_stage = plrRegularHand;
				}
			}
			else if (m_input.value() == 1) // Stand
			{
				m_dealer.hand().all_up();
				m_stage = dlrHand;
			}
			break;
		// Dealer plays hand
		case dlrHand:
			if (m_dealer.hand().score() < 17) // Hit
			{
				m_dealer.shoe().deal(m_dealer.hand(), 1, true);
				if (m_dealer.hand().score() > 21)
					m_stage = dlrSettleBets;
				else
					m_stage = dlrHand;
			}
			else // Stand
			{
				m_stage = dlrSettleBets;
			}
			break;
		// Settling bets
		case dlrSettleBets:
			settle_bets();
			m_stage = dlrResetTable;
			break;
		// Resetting table
		case dlrResetTable:
			reset_table();
			m_stage = plrChoice;
			break;
		}
	}

	// Shows how many chips bought and how many chips at end
	void results()
	{
		Art results_art;
		Art results_title;
		Art message;

		if (m_zoom)
			results_title.add_layer(0, "====================================== RESULTS ======================================");
		else
			results_title.add_layer(0, "===================== RESULTS =====================");

		int change = m_player.stack().value() - m_tot_bought;

		if (change > 0)
			message.add_layer(0, "Great job! You gained " + std::to_string(change) + " chips.");
		else if (change < 0)
			message.add_layer(0, "Too bad! You lost " + std::to_string(-change) + " chips.");
		else
			message.add_layer(0, "Not bad! You came out even.");

		message.pad(results_title.width(), 1);

		Art start_art = Chip(m_tot_bought).art(m_zoom);
		Art end_art = m_player.stack().art(m_zoom);
		Art start_title;
		Art end_title;
		Art arrow_art;

		start_title.add_layer(0, "Input");
		start_title.pad(start_art.width(), 1);
		start_art.add_layer(0, start_title.get_layer(0));
		end_title.add_layer(0, "Output");
		end_title.pad(end_art.width(), 1);
		end_art.add_layer(0, end_title.get_layer(0));

		if (m_zoom)
		{
			arrow_art.add_layer(0, "                ");
			arrow_art.add_layer(1, "          .     ");
			arrow_art.add_layer(2, "          |\\    ");
			arrow_art.add_layer(3, "   .------' \\   ");
			arrow_art.add_layer(4, "   '------. /   ");
			arrow_art.add_layer(5, "          |/    ");
			arrow_art.add_layer(6, "          '     ");
		}
		else
		{
			arrow_art.add_layer(0, "          ");
			arrow_art.add_layer(1, "      .   ");
			arrow_art.add_layer(2, "  .---'\\  ");
			arrow_art.add_layer(3, "  '---./  ");
			arrow_art.add_layer(4, "      '   ");
		}

		start_art.pad(arrow_art.width(), arrow_art.height());
		end_art.pad(arrow_art.width(), arrow_art.height());

		for (int i = 0; i < arrow_art.height(); ++i)
			results_art.add_layer(i, start_art.get_layer(i) + arrow_art.get_layer(i) + end_art.get_layer(i));

		results_art.pad(results_title.width(), results_art.height());

		cout << "\n" << title(m_zoom) << "\n"
			<< "\n" << results_title << "\n"
			<< "\n" << results_art << "\n"
			<< "\n" << message << "\n" << endl;
	}

private:

	/***** Member Functions *****/

	// Returns title of this Game
	Art title(bool zoom = true)
	{
		Art game_title;

		if (zoom)
		{
			game_title = Art(67, 3);
			game_title.set_layer(0, string(67, '='));
			game_title.set_layer(1, "||   *   *   *   B   L   A   C   K   J   A   C   K   *   *   *   ||");
			game_title.set_layer(2, string(67, '='));
			game_title.pad(85, 3);
		}
		else
		{
			game_title = Art(35, 3);
			game_title.set_layer(0, string(35, '='));
			game_title.set_layer(1, "|| * * * B L A C K J A C K * * * ||");
			game_title.set_layer(2, string(35, '='));
			game_title.pad(51, 3);
		}

		return game_title;
	}

	// Sets data members for m_input based on stage
	void set_input(Stage stage)
	{
		switch (stage)
		{
		case plrChoice:
			m_input.set_kind(Input::Choice);
			m_input.set_choices({ "Continue", "Add to Stack", "Leave" });
			m_input.set_prompt("Choose an option from above >> ");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case plrBuy:
			m_input.set_kind(Input::Number);
			m_input.set_choices({ "Adding to Stack" });
			m_input.set_prompt("Enter an amount of chips to buy >> ");
			m_input.set_condition(in_intvl(0, 1000000000));
			break;
		case plrBet:
			m_input.set_kind(Input::Number);
			m_input.set_choices({ "Betting" });
			m_input.set_prompt("Enter an amount of chips to bet >> ");
			m_input.set_condition(in_intvl(0, m_player.stack().value()));
			break;
		case dlrShuffle:
			m_input.set_kind(Input::None);
			m_input.set_choices({ "Shuffling" });
			m_input.set_prompt("Please wait for the dealer...");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case dlrDeal:
			m_input.set_kind(Input::None);
			m_input.set_choices({ "Dealing" });
			m_input.set_prompt("Please wait for the dealer...");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case dlrCheckNaturals:
			m_input.set_kind(Input::None);
			m_input.set_choices({ "Checking for Naturals" });
			m_input.set_prompt("Please wait for the dealer...");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case plrInitialHandNoSplit:
			m_input.set_kind(Input::Choice);
			m_input.set_choices({ "Hit", "Stand", "Double Down" });
			m_input.set_prompt("Choose an option from above >> ");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case plrInitialHandYesSplit:
			m_input.set_kind(Input::Choice);
			m_input.set_choices({ "Hit", "Stand", "Split", "Double Down" });
			m_input.set_prompt("Choose an option from above >> ");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case plrSplitHandOne:
			m_input.set_kind(Input::Choice);
			m_input.set_choices({ "Hit", "Stand" });
			m_input.set_prompt("Choose an option for your first hand >> ");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case plrSplitHandTwo:
			m_input.set_kind(Input::Choice);
			m_input.set_choices({ "Hit", "Stand" });
			m_input.set_prompt("Choose an option for your second hand >> ");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case plrRegularHand:
			m_input.set_kind(Input::Choice);
			m_input.set_choices({ "Hit", "Stand" });
			m_input.set_prompt("Choose an option from above >> ");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case dlrHand:
			m_input.set_kind(Input::None);
			m_input.set_choices({ "Dealer is Playing" });
			m_input.set_prompt("Please wait for the dealer...");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case dlrSettleBets:
			m_input.set_kind(Input::None);
			m_input.set_choices({ "Settling Bets" });
			m_input.set_prompt("Please wait for the dealer...");
			m_input.set_condition([](string str) -> bool { return true; });
			break;
		case dlrResetTable:
			m_input.set_kind(Input::None);
			m_input.set_choices({ "Resetting Table" });
			m_input.set_prompt("Please wait for the dealer...");
			m_input.set_condition([](string str) -> bool { return true; });
		}
	}

	// Splits player's hand into two hands and deals one more card to each hand
	void split()
	{
		// Adding second bet
		m_player.split_bet().add(m_player.bet().value());
		m_player.stack().sub(m_player.bet().value());

		// Adding second hand
		m_player.hand().deal(m_player.split_hand(), 1, true);
		m_dealer.shoe().deal(m_player.hand(), 1, true);
		m_dealer.shoe().deal(m_player.split_hand(), 1, true);
	}

	// Doubles player's bet and deals them one more card
	void double_down()
	{
		int add_bet = m_player.bet().value();
		m_player.bet().add(add_bet);
		m_player.stack().sub(add_bet);
		m_dealer.shoe().deal(m_player.hand(), 1, true);
	}

	// Determine who wins and settle bets appropriately
	void settle_bets()
	{
		if (m_player.split_hand().count() > 0) // Split
		{
			// Evaluate first hand and bet
			if (m_player.hand().score() > 21) // Player busts
			{
				int loss = m_player.bet().value();
				m_player.bet().sub(loss);
			}
			else if (m_dealer.hand().score() > 21) // Dealer busts (but player does not)
			{
				int gain = m_player.bet().value();
				m_player.bet().add(gain);
			}
			else if (m_dealer.hand().score() > m_player.hand().score()) // No busts, dealer's score is higher
			{
				int loss = m_player.bet().value();
				m_player.bet().sub(loss);
			}
			else if (m_dealer.hand().score() < m_player.hand().score()) // No busts, player's score is higher
			{
				int gain = m_player.bet().value();
				m_player.bet().add(gain);
			}

			// Evaluate second hand and bet
			if (m_player.split_hand().score() > 21) // Player busts
			{
				int loss = m_player.split_bet().value();
				m_player.split_bet().sub(loss);
			}
			else if (m_dealer.hand().score() > 21) // Dealer busts (but player does not)
			{
				int gain = m_player.split_bet().value();
				m_player.split_bet().add(gain);
			}
			else if (m_dealer.hand().score() > m_player.split_hand().score()) // No busts, dealer's score is higher
			{
				int loss = m_player.split_bet().value();
				m_player.split_bet().sub(loss);
			}
			else if (m_dealer.hand().score() < m_player.split_hand().score()) // No busts, player's score is higher
			{
				int gain = m_player.split_bet().value();
				m_player.split_bet().add(gain);
			}
		}
		else // No split
		{
			if ((m_player.hand().count() == 2 && m_player.hand().score() == 21) && !(m_dealer.hand().count() == 2 && m_dealer.hand().score() == 21)) // Player has natural blackjack
			{
				int gain = m_player.bet().value() * 3 / 2;
				m_player.bet().add(gain);
			}
			else if (m_player.hand().score() > 21) // Player busts
			{
				int loss = m_player.bet().value();
				m_player.bet().sub(loss);
			}
			else if (m_dealer.hand().score() > 21) // Dealer busts (but player does not)
			{
				int gain = m_player.bet().value();
				m_player.bet().add(gain);
			}
			else if (m_dealer.hand().score() > m_player.hand().score()) // No busts, dealer's score is higher
			{
				int loss = m_player.bet().value();
				m_player.bet().sub(loss);
			}
			else if (m_dealer.hand().score() < m_player.hand().score()) // No busts, player's score is higher
			{
				int gain = m_player.bet().value();
				m_player.bet().add(gain);
			}
		}
	}

	// Discards all cards and moves bets to stack
	void reset_table()
	{
		// Collect cards to discard pile
		m_dealer.discard().collect(m_player.hand());
		m_dealer.discard().collect(m_player.split_hand());
		m_dealer.discard().collect(m_dealer.hand());

		// Collect bets to stack
		int payout = m_player.bet().value();
		int split_playout = m_player.split_bet().value();
		m_player.stack().add(payout + split_playout);
		m_player.bet().sub(payout);
		m_player.split_bet().sub(split_playout);
	}

	// Returns a funtion which takes string input, tries to convert it to int, and tests whether it is between min and max
	function<bool(string)> in_intvl(int min, int max)
	{
		return
			[min, max](string str) -> bool
			{
				bool results = false;

				try
				{
					int numb = stoi(str);

					if (numb >= min && numb <= max)
						results = true;
					else
						results = false;
				}
				catch (...)
				{
					results = false;
				}
			
				return results;
			};
	}

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