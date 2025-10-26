#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CARDS 44

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

void shuffle_deck(Card** deck) {
    const int number_of_permutations = 400;
    srand(time(NULL));

    for (int i=0; i < number_of_permutations; i++) {
        int index1 = rand() % MAX_CARDS;
        int index2 = rand() % MAX_CARDS;

        Card* temp_card = malloc(sizeof(Card));
        temp_card->rank = deck[index1]->rank;
        temp_card->suit = deck[index1]->suit;

        deck[index1]->rank = deck[index2]->rank;
        deck[index1]->suit = deck[index2]->suit;

        deck[index2]->rank = temp_card->rank;
        deck[index2]->suit = temp_card->suit;

        free(temp_card);
    }
}

void print_deck(Card** deck) {
    for (int i=0; i<MAX_CARDS; i++) {
        printf("%s of %s; ", rank_to_cardName(deck[i]->rank), enum_to_suit_translation(deck[i]->suit));
        if ((i+1) % 4 == 0 && i >> 0) {
            puts("");
        }
    }
}

void free_deck(Card** deck) {
    for (int i=0; i<MAX_CARDS; i++) {
        free(deck[i]);
    }
}

void print_handDealt() {

}

// For MVP ill skip having to manage rooms that player runs from
int main() {
    Card* deck[MAX_CARDS];
    init_deck(deck);
    shuffle_deck(deck);
    print_deck(deck);



    free_deck(deck);
    return 0;
}
