#include <stdio.h>
#include "deck.h"

int main()
{
    Card c;
    int i;

    buildDeck();
    shuffleDeck();

    printf("Testing\n\n");

    for (i = 0; i < 5; i++)
    {
        c = dealCard();
        printf("Card %d: %c%c\n", i + 1, c.rank, c.suit);
    }

    printf("\nCards left: %d\n", cardsLeft());

    return 0;
}
