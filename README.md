# Blackjack

A CLI blackjack game with ASCII graphics.

## Functionality

This is a blackjack game that runs in the command line. It uses ASCII graphics to display the
dealer's and the player's hands. The game can be compiled with `make`, which produces an executable
called `blackjack`. It can also be compiled and then immediately run with `make play`.

When the game is first started, the player must make a few choices about how the game will run.
This includes deciding on the size of the graphics and how long to wait for the dealer. Here is
what that process looks like:

```
        ===================================
        || * * * B L A C K J A C K * * * ||
        ===================================

===================== WELCOME =====================

Welcome to Blackjack! We hope you have fun playing!

Before you begin, please set up the following. Note
that you can use numbers or words to make a choice.

==================== CARD SIZE ====================

.------------------------.------------------------.
|         Small          |         Large          |
|                        |      .---------.       |
|                        |      | A       |       |
|         .---.          |      |    .    |       |
|         |A  |          |      |   / \   |       |
|         | {>|          |      |  (_ _)  |       |
|         '---'          |      |    ^    |       |
|                        |      |       A |       |
|                        |      '---------'       |
'------------------------'------------------------'

Choose an option from above >> large

================== DEALER DELAY ===================

.-------------------------------------------------.
|              Setting Dealer Delay               |
'-------------------------------------------------'

Enter seconds to wait for each dealer action >> 1
```

After this initial setup, the game commences in a regular loop of adding to the stack (or leaving),
betting, dealing, playing a hand, and settling bets. Here's an example of what the game might look
like right after the hands have been dealt (using small graphics):

```
        ===================================
        || * * * B L A C K J A C K * * * ||
        ===================================

===================== DEALER ======================

.- Shoe -.- Dscd -.------------ Hand -------------.
| ..---. | ..---. |          .---. .---.          |
| ||///| | ||7  | |          |4  | |///|          |
| ||\\\| | || <>| |          | <3| |\\\|          |
| ''---' | ''---' |          '---' '---'          |
'--------'--------'-------------------------------'

===================== PLAYER ======================

.- Stck -.- Bet --.------------ Hand -------------.
|  .--.  |  .--.  |          .---. .---.          |
| | 80 | | | 10 | |          |K  | |K  |          |
| |.__.| | |.__.| |          | <3| | <>|          |
|  '--'  |  '--'  |          '---' '---'          |
'--------'--------'-------------------------------'

====================== INPUT ======================

.------------.------------.-----------.-----------.
|    Hit     |   Stand    |   Split   |Double Down|
'------------'------------'-----------'-----------'

Choose an option from above >> split
```

The game will continue until the player opts to leave, at which point it will summarize the
player's winnings (or losses):

```
        ===================================
        || * * * B L A C K J A C K * * * ||
        ===================================

===================== RESULTS =====================

            Input               Output
             .--.         .      .--.
            |100 |    .---'\    |110 |
            |.__.|    '---./    |.__.|
             '--'         '      '--'

          Great job! You gained 10 chips.
```