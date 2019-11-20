#include <stdio.h> // for IO
#include <stdlib.h>  // for random numbers
#include <time.h> // for seeding RNG
#include "prototypes.h"
#include "structures.h"
#include "functions.h"

Player* player_1;
Player* player_2;

int main(void)
{
  srand(time(NULL));

  int number_of_cards_each = 10;
  number_of_cards_each = get_number_of_cards();

  player_1 = (Player*) calloc(1, sizeof(Player));
  player_2 = (Player*) calloc(1, sizeof(Player));

  give_player_cards(player_1, number_of_cards_each);
  give_player_cards(player_2, number_of_cards_each);

  Player* first_player = player_1;
  Player* second_player = player_2;

  while(number_of_cards(second_player) != 0)
  {
    first_player = play_round(first_player, second_player);
    second_player = other_player(first_player);
  }

  printf("Player %d won, with %d wins\n",player_number(first_player), first_player->wins);
  printf("Player %d lost, but had %d wins\n",player_number(second_player), second_player->wins);

  press_to_exit();

  clean_cards(player_1);
  clean_cards(player_2);
  clean_players();

  return 0;
}
