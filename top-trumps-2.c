#include <stdio.h> // for IO
#include <stdlib.h>  // for random numbers
#include <time.h> // for seeding RNG

// making and printing cards
typedef struct card 
{
  int properties[4];
  struct card *next_card;
} Card;

Card *make_cards(int number_of_cards_to_make) // returns a pointer to the first card
{
  Card *pointer_to_block_of_cards; 
  pointer_to_block_of_cards = (Card *) malloc(sizeof(Card) * number_of_cards_to_make);

  // randomise card properties
  srand(time(NULL)); // seeding RNG 
  for(int current_card = 0; current_card < number_of_cards_to_make; current_card++)
  {
    for(int current_property = 0; current_property < 4; current_property++)
    {
        (*(pointer_to_block_of_cards + current_card)).properties[current_property] = rand() % 9999;
    }
    (*(pointer_to_block_of_cards + current_card)).next_card = pointer_to_block_of_cards + current_card + 1; 
    // point each card to next card. Final card will point to garbage, but this is fixed in allocate_cards()
  }
  return pointer_to_block_of_cards;
}

void print_cards(Card* pointer_to_block_of_cards, int number_of_cards_to_print) // Prints cards to screen
{
  for(int current_card = 0; current_card < number_of_cards_to_print; current_card++)
  {
    printf("Card %3d at %9p, pointing to %9p: %4d, %4d, %4d, %4d\n",
    current_card, 
    (pointer_to_block_of_cards + current_card), 
    (*(pointer_to_block_of_cards + current_card)).next_card, 
    (*(pointer_to_block_of_cards + current_card)).properties[0], 
    (*(pointer_to_block_of_cards + current_card)).properties[1], 
    (*(pointer_to_block_of_cards + current_card)).properties[2], 
    (*(pointer_to_block_of_cards + current_card)).properties[3]);
  }
}



int main(void)
{
    int number_of_cards_each;
    number_of_cards_each = 10; // number_of_cards_each = get_number_of_cards(maximum_number_of_cards);


    
    return 0;
}