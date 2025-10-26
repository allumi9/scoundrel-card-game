#include<stdio.h>
#include <stdlib.h>

enum Suit {
    SPADES, HEARTS, CLUBS, DIAMONDS
};

struct Card {
    int rank;
    enum Suit suit;
} typedef Card;

char* enum_to_suit_translation(enum Suit suit_int) {
    switch (suit_int) {
        case SPADES: return "Spades";
        case HEARTS: return "Hearts";
        case CLUBS: return "Clubs";
        case DIAMONDS: return "Diamonds";
        default: printf("Suit isn't a default one.");
    }
}

char* rank_to_cardName(int rank_int) {
    char string_number[2];
    sprintf(string_number, "%d", rank_int);
    char* string_ref = string_number;
    switch (rank_int) {
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        case 14: return "A";
        default: return string_ref;
    }
}

void init_deck(Card** deck) {
    int card_counter = 0;
    for (int suit_ind=1; suit_ind < 5; suit_ind++) {
        enum Suit curr_suit = suit_ind - 1;
        for (int card_rank=2; card_rank < 15; card_rank++) {
            if (curr_suit == HEARTS || curr_suit == DIAMONDS ) {
                const int FACE_CARD_START = 11;
                if (card_rank >= FACE_CARD_START) {
                    break;
                }
            }

            Card *newCard = malloc(sizeof(Card));
            newCard->rank = card_rank;
            newCard->suit = curr_suit;
            deck[card_counter] = newCard;
            card_counter++;

        }
    }
}

void print_deck(Card** deck) {
    for (int i=0; i<44; i++) {
        printf("%s of %s; ", rank_to_cardName(deck[i]->rank), enum_to_suit_translation(deck[i]->suit));
    }
}

int main() {
    Card* deck[44];
    init_deck(deck);
    // print_deck(deck);

    return 0;
}
