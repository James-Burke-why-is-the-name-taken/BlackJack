#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

Card deck[DECK_SIZE];
int nextCard = 0;

int buildDeck()
{
    char suits[4] = {'H','D','C','S'};
    char ranks[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    int values[13] = {11,2,3,4,5,6,7,8,9,10,10,10,10};

    int i, j, index = 0;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 13; j++)
        {
            deck[index].rank = ranks[j];
            deck[index].suit = suits[i];
            deck[index].value = values[j];
            index++;
        }
    }

    nextCard = 0;
    return 1;
}

int shuffleDeck()
{
    int i, r;
    Card temp;

    srand(time(NULL));

    for (i = 0; i < DECK_SIZE; i++)
    {
        r = rand() % DECK_SIZE;

        temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }

    nextCard = 0;
    return 1;
}

Card dealCard()
{
    Card empty;
    empty.rank = 'X';
    empty.suit = 'X';
    empty.value = 0;

    if (nextCard >= DECK_SIZE)
        return empty;

    return deck[nextCard++];
}

int cardsLeft()
{
    return DECK_SIZE - nextCard;
}
