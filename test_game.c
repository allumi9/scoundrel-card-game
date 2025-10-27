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
