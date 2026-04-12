#pragma once

//Values
static const char* suits[4] = { "Clubs", "Diamonds", "Spades", "Hearts" };

static const char* values[13] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

//Structs
typedef struct card{
    int suit;
    int value;
    int dealt;
    char lines[8][12];
} Card;

typedef struct hand {
    Card held[20];
    int amount;
}Hand;

//Functions

void createCard(Card* c);

void create(Card deck[]);

void printHand(Hand h, int amount);

int draw(Card deck[]);

void add_to_hand(int num, Hand* held, Card deck[]);

int scoring(Hand held);

char getCharacter();

int getInteger();
