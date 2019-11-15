#include <stdio.h> // for IO
#include <stdlib.h>  // for random numbers
#include <time.h> // for seeding RNG

// global variables and useful structures
int number_of_cards_each = 10;
int number_of_players = 2;

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

  // srand(time(NULL)); // seeding RNG with current time
  for(int current_card = 0; current_card <= number_of_cards_to_make; current_card++)
  {
    (*(pointer_to_block_of_cards + current_card)).charm = rand() % 255; // Pointer arithmetic here was hard earned! rand docs mention RAND_MAX - should I be messing with this?
    (*(pointer_to_block_of_cards + current_card)).strangeness = rand() % 255; // [TODO] make it positive
    (*(pointer_to_block_of_cards + current_card)).cheerfullness = rand() % 255;
    (*(pointer_to_block_of_cards + current_card)).sadness = rand() % 255;
  }

  return pointer_to_block_of_cards; // Messing with multidimensional arrays taught me that pointer_to_block_of_cards != Card. Should I be doing this differently?
}

void print_all_cards(Card* pointer_to_block_of_cards, int number_of_cards_to_print)
{
  for(int current_card = 0; current_card <= number_of_cards_to_print; current_card++)
  {
    printf("Card %d: Charm %d, Strangeness %d, Cheerfullness %d, Sadness %d\n",current_card, (*(pointer_to_block_of_cards + current_card)).charm, (*(pointer_to_block_of_cards + current_card)).strangeness, (*(pointer_to_block_of_cards + current_card)).cheerfullness, (*(pointer_to_block_of_cards + current_card)).sadness); // this line is very long = would a perimeta engineer split off into multiple variables, or multiple calls? I could have a printf() for each property...
  }
}

int main(void)
{
  Card* pointer_to_block_of_cards; // I know I could do this all in one line, I just want to be very explicit for now

  pointer_to_block_of_cards = make_cards(number_of_cards_each * number_of_players);

  print_all_cards(pointer_to_block_of_cards, number_of_cards_each * number_of_players);

  // allocate_cards();

  // play_a_round();

  return 0;
}
