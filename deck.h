#ifndef DECK_H
#define DECK_H

#define DECK_SIZE 52

typedef struct
{
    int value;
    char rank;
    char suit;
} Card;

int buildDeck();
int shuffleDeck();
Card dealCard();
int cardsLeft();

#endif
