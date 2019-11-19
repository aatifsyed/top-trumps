#include <stdio.h> // for IO
#include <stdlib.h>  // for random numbers
#include <time.h> // for seeding RNG
#include "prototypes.h" // prototypes

Card* make_card(void)
{
  return (Card*) calloc(1, sizeof(Card));
}

void randomise_card(Card* card)
{
  int current_property;
  for(current_property = 0; current_property <4; current_property++)
  {
    card->properties[current_property] = rand() % 9999;
  }
}

void send_to_top(Player* player, Card* card)
{
  Card* previous_top_card = player->top_card;
  player->top_card = card;
  player->top_card->next_card = previous_top_card;
}

void send_to_bottom(Player* player, Card* card)
{
  bottom_card(player)->next_card = card;
  card->next_card = NULL;
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

Card* pop_card_from_top(Player* player)
{
  Card* popped_top_card = player->top_card;
  player->top_card = player->top_card->next_card;
  popped_top_card->next_card = NULL;
  return popped_top_card;
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

    printf("Player 1 has %d cards\n", number_of_cards(player_1));
    printf("Player 2 has %d cards\n", number_of_cards(player_2));
    

    
    
    return 0;
}