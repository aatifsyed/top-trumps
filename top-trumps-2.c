#include <stdio.h> // for IO
#include <stdlib.h>  // for random numbers
#include <time.h> // for seeding RNG
#include "prototypes.h" // prototypes
#include "structures.h" // this should be blocked by the include guard anyway

Card* make_card(void)
{
  Card* card = (Card*) calloc(1, sizeof(Card));
  randomise_card(card);
  return card;
}

void randomise_card(Card* card)
{
  int current_property;
  for(current_property = 0; current_property <4; current_property++)
  {
    card->properties[current_property] = rand() % 9999;
  }
}

void print_card(Card* card)
{
  if(card == NULL)
  {
    printf("Null pointer passed to print_card\n");
    return;
  }
  
  printf("Card at %9p: next_card %9p, %4d, %4d, %4d, %4d\n", 
  card, card->next_card, 
  card->properties[0], card->properties[1], card->properties[2], card->properties[3]);
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

int best_property_index(Player* player)
{
  Card* card = player->top_card;

  int best_property_index;
  int current_property_index;
  int best_property_value = 0;

  for(current_property_index = 0; current_property_index < 4; current_property_index++)
  {
    if (card->properties[current_property_index] > best_property_value)
    {
      best_property_index = current_property_index;
      best_property_value = card->properties[current_property_index];
    }
  }

  return best_property_index;
}

void give_player_cards(Player* player, int number_to_give)
{
  while(number_of_cards(player) < number_to_give)
  {
    send_to_top(player, make_card());
  }
}

void print_player_cards(Player* player)
{
  Card* current_card = player->top_card;

  printf("Printing %d cards\n", number_of_cards(player));
  while(current_card != NULL)
  {
    print_card(current_card);
    current_card = current_card->next_card;
  }
}

int main(void)
{
  int number_of_cards_each;
  number_of_cards_each = 10; // number_of_cards_each = get_number_of_cards(maximum_number_of_cards);

  Player* player_1 = (Player*) calloc(1, sizeof(Player));
  Player* player_2 = (Player*) calloc(1, sizeof(Player));

  printf("Player 1 has %d cards\n", number_of_cards(player_1));
  printf("Player 2 has %d cards\n", number_of_cards(player_2));
  
  give_player_cards(player_1, number_of_cards_each);
  print_player_cards(player_1);
  
  
  return 0;
}