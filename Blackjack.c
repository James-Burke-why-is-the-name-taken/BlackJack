/*
 * File Blackjack.c
 * Authors: Jakob Flores and James Burke
 * Purpose: This is a working blackjack loop with a gamelog and check for blackjacks.
 * Resources: Google Gemini
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cardFuncStruc.h"

int main() {
    srand(time(NULL));

    time_t now;

    FILE* f = fopen("BlackjackLog.txt", "a");

    time(&now);

    fprintf(f, "%s\n", ctime(&now));

    int rounds = 0;
    float money = 100;
    float bet;

    Card deck[52];
    //create(deck);

    printf("Welcome to blackjack. The goal is to get as close as possible to 21 without going over, aces are 1 or 11, faces are 10, dealer stands on 17.\n");
    printf("To start, you will be given 100$\n");

    while (money > 0) {  // this part that does the loop was added after the game was made and im too lazy to indent everything.
        if (rounds % 5 == 0 )
            create(deck);
        printf("Current Bank: %.2f\n", money);
        printf("Enter your bet: ");
        bet = getInteger();
        printf("\n");

        if (bet > money || bet <= 0) {
            printf("Invalid, try again\n");
            continue;
        }

        int h;

        rounds++;

        printf("Round %d\n", rounds);

        fprintf(f, "Round %d is beginning.\n", rounds);

        Hand player[2];

        int active_hands = 1;

        int split_bet = 0;

        player[0].amount = 0;
        player[1].amount = 0;

        Hand dealer;

        dealer.amount = 0;

        add_to_hand(draw(deck), &player[0], deck);
        add_to_hand(draw(deck), &player[0], deck);
        add_to_hand(draw(deck), &dealer, deck);
        add_to_hand(draw(deck), &dealer, deck);  // hidden card.

        printf("Your hand:\n");
        printHand(player[0], player[0].amount);
        printf("Your score: %d\n", scoring(player[0]));

        // Hand splitting
        // 2.0 at end of line below just in case so nothing bugs out
        if (player[0].held[0].value == player[0].held[1].value && money >= bet * 2.0) {
            printf("You have a pair! would you like to split (y/n)");
            char split = getCharacter();

            if (split == 'y') {
                active_hands = 2;
                split_bet = bet;
                player[1].held[0] = player[0].held[1];
                player[1].amount = 1;
                player[0].amount = 1;

                printf("Hands have been split!\n");
                fprintf(f, "Player has chosen to split their hands.\n");
            }
        }

        printf("Dealer shows: %s of %s\n", values[dealer.held[0].value], suits[dealer.held[0].suit]);
        fprintf(f, "Dealer shows: %s of %s\n", values[dealer.held[0].value], suits[dealer.held[0].suit]);

        fprintf(f, "Player has %s of %s and %s of %s.\n", values[player[0].held[0].value], suits[player[0].held[0].suit], values[player[0].held[1].value], suits[player[0].held[1].suit]);

        int pscore = scoring(player[0]);

        int dscore = scoring(dealer);

        char choice;

        if (pscore == 21) {
            printHand(player[0], player[0].amount);
            if (dscore == 21) {
                fprintf(f, "Both player and dealer have Blackjack! It's a tie\n");
                printf("Both player and dealer have Blackjack! It's a tie\n");
            }
            else {
                printf("Player has blackjack and wins 1.5x the original bet.\n");
                fprintf(f, "Player has black jack and wins %d dollars.\n", (int)(bet * 1.5));
                money += (bet * 1.5);
            }
            printf("Your money: %.2f. (p)lay again or (c)ash out?", money);
            fprintf(f, "Current Money: %.2f dollars.\n", money);
            choice = getCharacter();
            printf("\n");
            if (choice == 'c')
                break;
            else
                continue;
        }

        if (dscore == 21) {
            printf("Dealer has blackjack!\n");
            printHand(dealer, dealer.amount);
            fprintf(f, "Dealer has Blackjack, player loses %.2f dollars.\n", bet);
            money -= bet;
            printf("Your money: %.2f. (p)lay again or (c)ash out?", money);
            fprintf(f, "Current Money: %.2f dollars.\n", money);
            choice = getCharacter();
            printf("\n");
            if (choice == 'c')
                break;
            else
                continue;
        }
        for (h = 0; h < active_hands; h++) {  // this will loop the entire scoring logic, end will be noted.
            if (active_hands > 1) {
                printf("---- Playing hand %d ----\n", h + 1);
                fprintf(f, "---- Playing hand %d ----\n", h + 1);
            }
            while (scoring(player[h]) < 21) {
                if (player[h].amount == 2 && money >= bet * 2) {
                    printf("Do you want to hit, stand, or double down? (type h for hit, s for stand, d for double down) ");
                }
                else {
                    printf("Do you want to hit or stand? (type h for hit, s for stand) ");
                }

                choice = getCharacter();
                printf("\n");
                if (choice == 'd' && player[h].amount == 2 && money >= bet * 2) {
                    bet *= 2;
                    int i = draw(deck);
                    add_to_hand(i, &player[h], deck);
                    printf("You have chosen to double down!\n");
                    fprintf(f, "Player doubles down! They got %s of %s, Bet is now %.2f. New score is %d.\n", values[deck[i].value], suits[deck[i].suit], bet, scoring(player[h]));
                    break;
                }
                else if (choice == 'h') {
                    int i = draw(deck);
                    add_to_hand(i, &player[h], deck);
                    printf("Your hand:\n");
                    printHand(player[h], player[h].amount);
                    printf("Your score: %d\n", scoring(player[h]));
                    fprintf(f, "Player hits and gets %s of %s. New score is: %d\n", values[deck[i].value], suits[deck[i].suit], scoring(player[h]));
                }
                else {
                    break;
                }
            }
        }  // i think this is the end, i hope it is.

        printf("Dealer's turn.\n");
        // ig this is just how the dealer plays, I mean it's kinda good
        while (scoring(dealer) < 17) {
            add_to_hand(draw(deck), &dealer, deck);
            dscore = scoring(dealer);
        }

        for (h = 0; h < active_hands; h++) {  // more horseshit

            int pscore = scoring(player[h]);
            printf("Your hand:\n");
            printHand(player[h], player[h].amount);
            printf("Your score: %d\n", scoring(player[h]));
            printf("Dealer's hand:\n");
            printHand(dealer, dealer.amount);
            printf("Dealer score: %d\n", scoring(dealer));

            if (pscore > 21) {
                printf("Hand %d: Bust, Dealer wins.\n", h + 1);
                fprintf(f, "Hand %d: Player Busts with a score of %d, losing %2.f dollars.\n", h + 1, pscore, bet);
                money -= bet;
                printf("Loss is %.2f dollars.\n", bet);
            }
            else {  // also added after most of the code was done.

                if (dscore > 21 || pscore > dscore) {
                    printf("Hand %d: You win!\n", h + 1);
                    money += bet;
                    printf("Gain is %.2f dollars.\n", bet);
                    fprintf(f, "Hand %d: Player wins and gains %.2f dollars.\n", h + 1, bet);
                }
                else if (dscore > pscore) {
                    printf("Hand %d: Dealer wins!\n", h + 1);
                    money -= bet;
                    printf("Loss is %.2f dollars.\n", bet);
                    fprintf(f, "Hand %d: Player loses and loses %.2f dollars.\n", h + 1, bet);
                }
                else {
                    printf("Hand %d: Tie.\n", h + 1);
                    fprintf(f, "Hand %d: Tie game.\n", h + 1);
                }
            }  // closes the else

        }  // closes game if out of money
        if (money <= 0) {
            printf("You have no money!\n");
            break;
        }
        printf("Your money: %.2f. (p)lay again or (c)ash out?", money);
        fprintf(f, "Current Money: %.2f dollars.\n", money);
        choice = getCharacter();
        printf("\n");
        if (choice == 'c') {
            break;
        }

    }  // This closes the loop

    printf("You walk away with $%.2f after %d rounds.\n", money, rounds);
    fprintf(f, "Player walked away with $%.2f after %d rounds.\n", money, rounds);
    fprintf(f, "---------------END OF SESSION-----------------\n\n");

    fclose(f);
}
