#include <stdio.h> // for IO
#include <stdlib.h>  // for random numbers
#include <time.h> // for seeding RNG

// global variables and useful structures
const int number_of_cards_each = 10;
const int number_of_players = 2;

typedef struct card // I wanted to put this in the make_cards function...
{
  char charm;
  char strangeness;
  char cheerfullness; // "Up" ~= "Cheery", no?
  char sadness;
  struct card *next_card; // using simply "Card" will confuse the compiler
} Card;

Card *make_cards(int number_of_cards_to_make) // returns a pointer to the first card
{
  Card *pointer_to_block_of_cards; 

  pointer_to_block_of_cards = (Card *) malloc(sizeof(Card) * number_of_cards_to_make);

  // randomise card properties. Should this be its own function?
  srand(time(NULL)); // seeding RNG with current time
  for(int current_card = 0; current_card < number_of_cards_to_make; current_card++)
  {
    (*(pointer_to_block_of_cards + current_card)).charm = rand() % 255; // Pointer arithmetic here was hard earned! rand docs mention RAND_MAX - should I be messing with this?
    (*(pointer_to_block_of_cards + current_card)).strangeness = rand() % 255; // [TODO] make it positive. Surely there's data being lost if I'm going from signed to char...?
    (*(pointer_to_block_of_cards + current_card)).cheerfullness = rand() % 255;
    (*(pointer_to_block_of_cards + current_card)).sadness = rand() % 255;
  }

  return pointer_to_block_of_cards; // Messing with multidimensional arrays taught me that pointer_to_block_of_cards != Card. Should I be doing this differently?
}

void print_cards(Card* pointer_to_block_of_cards, int number_of_cards_to_print) // Prints cards to screen
{
  for(int current_card = 0; current_card < number_of_cards_to_print; current_card++)
  {
    printf("Card %3d: Charm %4d, Strangeness %4d, Cheerfullness %4d, Sadness %4d\n",current_card, (*(pointer_to_block_of_cards + current_card)).charm, (*(pointer_to_block_of_cards + current_card)).strangeness, (*(pointer_to_block_of_cards + current_card)).cheerfullness, (*(pointer_to_block_of_cards + current_card)).sadness); // this line is very long = would a perimeta engineer split off into multiple variables, or multiple calls? I could have a printf() for each property...
  }
}

typedef struct player
{
  Card* top_card;
  Card* bottom_card;
  int wins;
  // is it a bad idea to refer to player 1 as *(pointer_to_players + 0)? I'd love to do player1.top_card etc, but to dynamically allocate players, this is the only way I can think of.
} Player;

Player *make_players(int number_of_players)
{
  Player *pointer_to_block_of_players;

  pointer_to_block_of_players = (Player *) malloc(sizeof(Player) * number_of_players);

  for (int current_player = 0; current_player < number_of_players; current_player++)
  {
    (*(pointer_to_block_of_players + current_player)).wins = 0;
  }

  return pointer_to_block_of_players;
}

void print_players(Player* pointer_to_list_of_players, int number_of_players)
{
  for (int current_player = 0; current_player < number_of_players; current_player++)
  {
    printf("Player %d ", current_player);
    printf("has %d wins. ", (*(pointer_to_list_of_players + current_player)).wins);
    printf("Top card at %p, ",(*(pointer_to_list_of_players + current_player)).top_card);
    printf("bottom card at %p\n",(*(pointer_to_list_of_players + current_player)).bottom_card);
  }
}

int main(void)
{
  Card* pointer_to_block_of_cards; // I know I could do this all in one line, I just want to be very explicit for now
  Player* pointer_to_list_of_players;

  pointer_to_block_of_cards = make_cards(number_of_cards_each * number_of_players);

  print_cards(pointer_to_block_of_cards, number_of_cards_each * number_of_players);

  pointer_to_list_of_players = make_players(number_of_players);

  print_players(pointer_to_list_of_players, number_of_players);

  // allocate_cards();

  // play_a_round();

  return 0;
}
