#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#pragma once
#define MAX_CARDS 44
#define MAX_HAND_SIZE 4

enum Suit {
    SPADES, HEARTS, CLUBS, DIAMONDS
};

struct Card {
    int rank;
    enum Suit suit;
} typedef Card;

struct Deck {
    Card** cards;
    int size;
    int top_card;
} typedef Deck;

struct Player {
    Card** hand;
    int hand_card_count;
    int8_t health;
    Card* weapon;
    Card* current_top_monster;
    bool ran_from_previous;
} typedef Player;

char* enum_to_suit_translation(enum Suit suit_int);
char* rank_to_cardName(int rank_int);

void init_deck(Deck* deck);
void shuffle_deck(Deck* deck);
void print_deck(Deck* deck);
void free_deck(Deck* deck);

void crash_if_player_null(Player* player);

void deal_hand(Player* player, Deck* deck);

void print_player_status(Player* player);

void fight_with_weapon(Player* player, Card* monster);
void fight_with_hands(Player* player, Card* monster);
void fight_monster(Player* player, Card* monster);
void use_healing_potion(Player* player, Card* card);
void take_weapon(Player* player, Card* card);

void use_card(Player* player, int card_index);
char** parse_str_into_tokens(char* user_input);

void run_from_room(Player* player, Deck* deck);

void game_loop();

void print_help();
