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
    Card* deck[MAX_CARDS];
    init_deck(deck);

    for (int i = 0; i < MAX_CARDS; i++) {
        if (deck[i]->suit == DIAMONDS || deck[i]->suit == HEARTS) {
            _Bool isFaceCard = deck[i]->rank < 11;

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
