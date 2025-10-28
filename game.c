#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"


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

    int init_card_count = player->hand_card_count;
    int init_deck_top = *deck_top;
    for (int i=0; i < MAX_HAND_SIZE; i++) {
        if (player->hand[i] != 0) {
            continue;
        }
        player->hand[i] = deck[init_deck_top + i];
        player->hand_card_count = player->hand_card_count + 1;
        *deck_top = *deck_top + 1;
    }
}

void print_player_status(Player* player) {
    crash_if_player_null(player);
    printf("Player: HP %d", player->health);
    if (player->weapon != 0) {
            printf(" / ATK: %d", player->weapon->rank);
    }
    if (player->current_top_monster != 0) {
            printf(" / TOP_MONST: %d", player->current_top_monster->rank);
    }

    printf("\nRoom: ");
    for(int i=0; i<MAX_HAND_SIZE; i++) {
        if (player->hand[i] == 0) {
            printf("-none- | ");
            continue;
        }
        printf("%s of %s | ", rank_to_cardName(player->hand[i]->rank), enum_to_suit_translation(player->hand[i]->suit));
    }

    puts("");
}

void fight_with_weapon(Player* player, Card* monster) {
    printf("Fighting DMG:%d with weapon\n\n", monster->rank);
    int damage = monster->rank - player->weapon->rank;

    if (player->health <= damage) {
        printf("\nh i j k Lost\n");
        exit(0);
    }

    if (damage > 0) {
        player->health = player->health - damage;
    }

    player->current_top_monster = monster;
}
void fight_with_hands(Player* player, Card* monster) {
    printf("Fighting DMG:%d with hands\n\n", monster->rank);
    int damage = monster->rank;

    if (player->health <= damage) {
        printf("\nh i j k Lost\n");
        exit(0);
    }

    player->health = player->health - damage;
}

void fight_monster(Player* player, Card* monster) {
    Card* weapon_top_monster = player->current_top_monster;

    if (weapon_top_monster != NULL) {
        if (weapon_top_monster->rank < monster->rank) {
            fight_with_hands(player, monster);
        } else {
            fight_with_weapon(player, monster);
        }
        return;
    }

    if (player->weapon == 0) {
        fight_with_hands(player, monster);
        return;
    }

    fight_with_weapon(player, monster);
}

void use_healing_potion(Player* player, Card* card) {
    printf("Taking potion HP:%d.\n\n", card->rank);
    int final_health = player->health + card->rank;

    if (player->health + card->rank >= 20) {
        player->health = 20;
        return;
    }

    player->health = player->health + card->rank;
}

void take_weapon(Player* player, Card* card) {
    printf("Taking new weapon ATK:%d.\n\n", card->rank);
    player->weapon = card;
    player->current_top_monster = 0;
}

void use_card(Player* player, int card_index) {
    crash_if_player_null(player);
    if (card_index <= 0 || card_index >= 5 || player->hand[card_index - 1] == 0) {
        printf("No card there, please choose a valid index for a card.\n");
        return;
    }

    card_index = card_index - 1;
    Card* chosen_card = player->hand[card_index];

    switch (chosen_card->suit) {
        case SPADES:
            fight_monster(player, chosen_card);
            break;
        case HEARTS:
            use_healing_potion(player, chosen_card);
            break;
        case CLUBS:
            fight_monster(player, chosen_card);
            break;
        case DIAMONDS:
            take_weapon(player, chosen_card);
            break;
    }

    player->hand[card_index] = 0;
    player->hand_card_count = player->hand_card_count - 1;
}

char** parse_str_into_tokens(char* user_input) {
    char *token = malloc(sizeof(user_input));
    char* user_input_copy = strdup(user_input);
    char** user_command = calloc(2, sizeof(user_input));

    for (int i=0; i < 2; i++) {
        token = strsep(&user_input_copy, " ");
        if (token != NULL) {
            user_command[i] = token;
        }
    }
    if (user_command[0] == 0) {
        fprintf(stderr, "Error: user_command is null, tokenizing didn't work probably\n");
        exit(1);
    }

    return user_command;
}

// For MVP idc about managing rooms that player runs from, not a bug, a feature
void game_loop() {
    Card* deck[MAX_CARDS];
    int* deck_top = malloc(sizeof(int));
    *deck_top = 0;
    Player* player = calloc(1, sizeof(Player));
    player->health = 20;
    init_deck(deck);
    shuffle_deck(deck);
    deal_hand(player, deck_top, deck);

    printf("Hello, this is Scoundrel(Original concept by Zach Gage and Kurt Bieg).\n Just go online for rules, if youre not familiar, i ain't explainin shit\n\n");

    char *user_input = NULL;
    size_t buff_size = 32;
    char* end_phrase = "exit\n";

    do {
        printf("-------------------\n");
        print_player_status(player);

        printf("Your move: ");
        getline(&user_input, &buff_size, stdin);

        char** user_command = parse_str_into_tokens(user_input);

        if (strcmp(user_command[0], "use") == 0) {
            use_card(player, user_command[1][0] - '0');
        } else {
            if (strcmp(user_command[0], end_phrase) == 0) {
                break;
            }
            puts("I don't understand, try again. E.g. \'use 1\'");
        }

        if (player->hand_card_count == 1) {
            deal_hand(player, deck_top, deck);
        }

        free(user_command);
    } while (strcmp(user_input, end_phrase) != 0);

    free_deck(deck);
    free(user_input);
}
