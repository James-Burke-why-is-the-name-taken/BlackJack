/****************************************************************************

File: cardDefs.c

Author: Jakob Flores

Purpose: Holds all function definitions

Resources: GEMINI, heavy amounts of Google Gemini

*******************************************************************************/
#include "cardFuncStruc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void createCard(Card* c) {
    //Suit mapping
    char suitSymbol;
    if (c->suit == 0) suitSymbol = '&'; // Clubs
    else if (c->suit == 1) suitSymbol = 'o'; // Diamonds
    else if (c->suit == 2) suitSymbol = '^'; // Spades
    else if (c->suit == 3) suitSymbol = 'v'; // Hearts
    else                suitSymbol = '?';

    //Bottom value mapping
    char botVal[4];
    if (c->value == 0) strcpy(botVal, "V");   // Ace
    else if (c->value == 1) strcpy(botVal, "Z");   // 2
    else if (c->value == 2) strcpy(botVal, "E");   // 3
    else if (c->value == 3) strcpy(botVal, "h");   // 4
    else if (c->value == 4) strcpy(botVal, "S");   // 5
    else if (c->value == 5) strcpy(botVal, "9");   // 6
    else if (c->value == 6) strcpy(botVal, "L");   // 7
    else if (c->value == 7) strcpy(botVal, "8");   // 8
    else if (c->value == 8) strcpy(botVal, "6");   // 9
    else if (c->value == 9) strcpy(botVal, "0I");  // 10
    else if (c->value == 10) strcpy(botVal, "[");  // Jack
    else if (c->value == 11) strcpy(botVal, "O");  // Queen
    else if (c->value == 12) strcpy(botVal, ">|"); // King
    else                  strcpy(botVal, " "); // Error

    //Card values for each value possibly given
    char* topNames[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

    //Drawing logic
    strcpy(c->lines[0], "  _____  ");


    if (strlen(topNames[c->value]) > 1)
        sprintf(c->lines[1], " |%s   | ", topNames[c->value]);
    else
        sprintf(c->lines[1], " |%s    | ", topNames[c->value]);

    // Suit symbols
    sprintf(c->lines[2], " |  %c  | ", suitSymbol);
    strcpy(c->lines[3], " |     | ");
    sprintf(c->lines[4], " |  %c  | ", suitSymbol);
    strcpy(c->lines[5], " |     | ");
    sprintf(c->lines[6], " |  %c  | ", suitSymbol);

    // Bottom value (padding logic)
    if (strlen(botVal) == 3)      sprintf(c->lines[7], " |__%s| ", botVal);
    else if (strlen(botVal) == 2) sprintf(c->lines[7], " |___%s| ", botVal);
    else                          sprintf(c->lines[7], " |____%s| ", botVal);

}

void create(Card deck[]) {
    int s;
    int v;
    int i = 0;
    for (s = 0; s < 4; s++) {
        for (v = 0; v < 13; v++) {
            deck[i].suit = s;
            deck[i].value = v;
            deck[i].dealt = 0;
            createCard(&deck[i]);
            i++;
        }
    }
}

void printHand(Hand h, int amount) {
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < amount; j++) {
            printf("%s", h.held[j].lines[i]);
        }
        printf("\n");
    }
}
//This function and the one below do not ask, they just get
char getCharacter() {
    char result;
    while (scanf(" %c", &result) != 1) {
        //Just in case
        while (getchar() != '\n');
        printf("Invalid input. Try again: ");
    }
    return result;
}

int getInteger() {
    int result;
    while (scanf("%d", &result) != 1) {
        //Just in case
        int c;
        while ((c= getchar()) != '\n' && c != EOF);
        printf("Invalid input. Try again: ");
    }
    return result;
}



int draw(Card deck[]) {

    int i;
    int count = 0;
    i = rand() % 52;
    while (deck[i].dealt == 2) {
        i = rand() % 52;
        count++;
        if (count == 104) {
            create(deck);
            printf("Deck has been re shuffled.");
        }
    }
    deck[i].dealt++;
    return i;
}

void add_to_hand(int num, Hand* held, Card deck[]) {
    held->held[held->amount] = deck[num];
    held->amount++;
}

int scoring(Hand held) {
    int aces = 0;
    int total_score = 0;
    int i;

    for (i = 0; i < held.amount; i++) {
        int value = held.held[i].value;

        if (value == 0) {
            total_score += 11;
            aces++;
        }
        else if (value >= 10) {
            total_score += 10;
        }
        else {
            total_score += (value + 1);
        }
    }
    while (total_score > 21 && aces > 0) {
        total_score -= 10;
        aces--;
    }
    return total_score;
}
