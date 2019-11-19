#include <stdio.h> // for IO
#include <stdlib.h>  // for random numbers
#include <time.h> // for seeding RNG

typedef struct player
{
  int wins;
  Card* top_card;
} Player;

typedef struct card
{
  int properties[4];
  struct card* next_card;
} Card;

Card* make_card(void)
{
  return (Card*) calloc(1, sizeof(Card));
}

void randomise_card(Card* card)
{
  for(int current_property = 0; current_property <4; current_property++)
  {
    card->properties[current_property] = rand() % 9999;
  }
}

int send_to_top(Player* player, Card* card)
{
  player->top_card = card;
}

Card* bottom_card(Player* player)
{
  Card* current_card = player->top_card;
  
  while(current_card->next_card != NULL)
  {
    current_card = current_card->next_card;
  }

  return current_card;
}

int number_of_cards(Player* player)
{
  if(player->top_card == NULL)
  {
    return 0;
  }

  Card* current_card = player->top_card;
  int number_of_cards = 0;

  while(current_card->next_card != NULL)
  {
    current_card = current_card->next_card;
    number_of_cards++;
  }

  return number_of_cards;
}

int main(void)
{
    int number_of_cards_each;
    number_of_cards_each = 10; // number_of_cards_each = get_number_of_cards(maximum_number_of_cards);

    Player* player_1 = (Player*) calloc(1, sizeof(Player));
    Player* player_2 = (Player*) calloc(1, sizeof(Player));

    
    
    return 0;
}