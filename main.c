#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CARDS 44
#define MAX_HAND_SIZE 4

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
        default: fprintf(stderr, "Error: Suit for translation isn't 0 to 3.");
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

struct Player {
    Card** hand;
    int hand_card_count;
    int8_t health;
    Card* weapon;
    Card* current_top_monster;
} typedef Player;

void crash_if_player_null(Player* player) {
    if (player == 0) {
        fprintf(stderr, "Error: Player was null on use, idk where");
    }
}

void deal_hand(Player* player, int* deck_top, Card** deck) {
    crash_if_player_null(player);
    if (player->hand_card_count == MAX_HAND_SIZE) {
        fprintf(stderr, "Error: Tried dealing hand when hand is full.");
        exit(1);
    }
    if (player->hand == 0) {
        player->hand = malloc(MAX_HAND_SIZE * sizeof(Card));
    }

    for (int i=0; i < MAX_HAND_SIZE - player->hand_card_count; i++) {
        player->hand[i + player->hand_card_count] = deck[*deck_top + i];
        deck_top++;
    }
}

void print_currentHand(Player* player) {
    crash_if_player_null(player);
    for(int i=0; i<MAX_HAND_SIZE; i++) {
        printf("%s of %s; ", rank_to_cardName(player->hand[i]->rank), enum_to_suit_translation(player->hand[i]->suit));
        // TODO: Change confusing naming "hand.hand"
    }
}

void fight_with_weapon(Player* player, Card* monster) {
    int damage = player->weapon->rank - monster->rank;

    if (player->health <= damage) {
        printf("\nh i j k Lost\n");
        exit(0);
    }

    player->health = player->health - damage;
}
void fight_with_hands(Player* player, Card* monster) {
    int damage = monster->rank;

    if (player->health <= damage) {
        printf("\nh i j k Lost\n");
        exit(0);
    }

    player->health = player->health - damage;
}

void fight_monster(Player* player, Card* monster) {
    Card* weapon_top_monster = player->current_top_monster;

    if (weapon_top_monster != 0) {
        if (weapon_top_monster->rank > monster->rank) {
            fight_with_hands(player, monster);
            return;
        } else {
            fight_with_weapon(player, monster);
        }
    }

    if (player->weapon == 0 || player->weapon->rank < monster->rank ) {
        fight_with_hands(player, monster);
        return;
    }

    fight_with_weapon(player, monster);
}

void use_healing_potion(Player* player, Card* card) {}
void take_weapon(Player* player, Card* card) {
    player->weapon = card;
}

void use_card(Player* player, int card_index) {
    crash_if_player_null(player);
    if (card_index <= 0 || card_index >= 5 || player->hand[card_index] == 0) {
        printf("No card there, please choose a valid index for a card.\n");
        return;
    }

    Card* chosen_card = player->hand[card_index];

    switch (chosen_card->suit) {
        case SPADES: fight_monster(player, chosen_card);
        case HEARTS: use_healing_potion(player, chosen_card);
        case CLUBS: fight_monster(player, chosen_card);
        case DIAMONDS: take_weapon(player, chosen_card);
        default: fprintf(stderr, "Error: Suit for translation isn't 0 to 3.");
    }
}

// For MVP idc about managing rooms that player runs from, not a bug, a feature
void game_loop() {
    Card* deck[MAX_CARDS];
    int* deck_top = malloc(sizeof(int));
    *deck_top = 0;
    Player player = {0, 0, 20};
    init_deck(deck);
    shuffle_deck(deck);

    free_deck(deck);
}

void print_help(){} // TODO: Make a tutorial kinda

int main() {

    return 0;
}
