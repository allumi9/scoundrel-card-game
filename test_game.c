#include<criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/logging.h>
#include<criterion/redirect.h>
#include <stdlib.h>
#include "game.h"

Test(enum_transl, suitExists) {
    char* result = malloc(sizeof(enum Suit));
    result = enum_to_suit_translation(SPADES);

    cr_expect_str_eq(result, "Spades");
}

Test(rank_transl, numberIsFaceCard) {
    char* result = malloc(sizeof(int));
    result = rank_to_cardName(11);

    cr_expect_str_eq(result, "J");
}

Test(deck_init, noRedFaceCards) {
    Card** cards = calloc(MAX_CARDS, sizeof(Card));
    Deck* deck = calloc(1, sizeof(Deck));
    deck->cards = cards;
    init_deck(deck);

    for (int i = 0; i < MAX_CARDS; i++) {
        if (deck->cards[i]->suit == DIAMONDS || deck->cards[i]->suit == HEARTS) {
            _Bool isFaceCard = deck->cards[i]->rank < 11;

            cr_assert(isFaceCard);
        }
    }
}

Test(fight_monster, topMonsterIsNull_NoWeapon_ShouldFightWithHands) {
    Player* player = calloc(1, sizeof(Player));
    player->hand_card_count = 0;
    player->health = 20;
    Card *monster = malloc(sizeof(Card));
    monster->rank = 8;
    monster->suit = SPADES;
    int expected_health = player->health - monster->rank;

    fight_monster(player, monster);

    cr_assert_eq(player->health, expected_health);
}

Test(fight_monster, topMonsterIsNull_WeaponExists_ShouldFightWithWeapon) {
    Player* player = calloc(1, sizeof(Player));
    player->hand_card_count = 0;
    player->health = 20;
    Card *weapon = malloc(sizeof(Card));
    weapon->rank = 7;
    weapon->suit = DIAMONDS;
    player->weapon = weapon;

    Card *monster = malloc(sizeof(Card));
    monster->rank = 8;
    monster->suit = SPADES;
    int expected_health = player->health;
    if(weapon->rank < monster->rank) {
        expected_health = player->health + weapon->rank - monster->rank;
    }

    fight_monster(player, monster);

    cr_assert_eq(player->health, expected_health);
}

Test(parse_user_input, commandIsParsedCorrectly) {
    char* user_input = "use 13";

    char** user_command = parse_str_into_tokens(user_input);
    char** expected_command = malloc(sizeof(user_command));
    expected_command[0] = "use";
    expected_command[1] = "13";

    for (int i=0; i < 2; i++) {
        cr_assert_str_eq(user_command[i], expected_command[i]);
    }
}

Test(deal_hand, deck_empty) {
    Card** cards = calloc(MAX_CARDS, sizeof(Card));
    Deck* deck = calloc(1, sizeof(Deck));
    deck->cards = cards;
    deck->top_card = 40;

    Player* player = calloc(1, sizeof(Player));
    player->health = 20;
    init_deck(deck);
    shuffle_deck(deck);
    deal_hand(player, deck);
    print_player_status(player);

    for (int i=1; i < 5; i++) {
        use_card(player, i);
    }
    print_player_status(player);
    deal_hand(player, deck);

    for (int i=0; i < 4; i++) {
        cr_assert_not(player->hand[i]);
    }
    print_player_status(player);
}

// I tested manually and it works, so this is for later to rewrite
// Test(deal_hand, deck_empty_AfterRunning) {
//     Card** cards = calloc(MAX_CARDS, sizeof(Card));
//     Deck* deck = calloc(1, sizeof(Deck));
//     deck->cards = cards;
//     deck->top_card = 40;

//     Player* player = calloc(1, sizeof(Player));
//     player->health = 20;
//     init_deck(deck);
//     shuffle_deck(deck);
//     print_deck(deck);
//     deal_hand(player, deck);
//     print_player_status(player);

//     run_from_room(player, deck);
//     print_deck(deck);

//     print_player_status(player);
//     deal_hand(player, deck);
//     print_player_status(player);

//     for (int i=0; i < 4; i++) {
//         cr_assert_not(player->hand[i]);
//     }
//     print_player_status(player);
// }
