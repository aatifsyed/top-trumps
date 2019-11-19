#ifndef PROTOTYPES_H
#define PROTOTYPES_H
#include "structures.h"

Card* make_card(void);
void randomise_card(Card* card);
void print_card(Card* card);
void send_to_top(Player* player, Card* card);
void send_to_bottom(Player* player, Card* card);
Card* bottom_card(Player* player);
Card* pop_card_from_top(Player* player);
int number_of_cards(Player* player);
int best_property_index(Player* player);

#endif