#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for seeding RNG

typedef struct card
{
    int properties[4];
    struct card *next_card;
} Card;

Card *make_card(void)
{
    return (Card *)calloc(1, sizeof(Card));
}

void randomise_card(Card *card)
{
    int current_property;
    for (current_property = 0; current_property < 4; current_property++)
    {
        card->properties[current_property] = rand() % 9999;
    }
}

void print_card(Card* card)
{
  printf("Card at %p: next_card %p, %d, %d, %d, %d\n", card, card->next_card, card->properties[0], card->properties[1], card->properties[2], card->properties[3]);
}

int best_property_index(Card* card)
{
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

int main()
{   
    srand(time(NULL));

    Card* card = make_card();
    randomise_card(card);
    print_card(card);
    printf("best property at index %d\n", best_property_index(card));
    print_card(NULL);
    
    
    

    // for (int i = 0; i < 10; i++)
    // {
    //     printf("%d\n", ((int)rand()) % 255);
    // }
    // return 0;

    // int empty;
    // printf("%d\n", empty);

    // char a = '\0', b=-1;

    // if (b > a)
    // {
    //     printf("your life is slightly easier");
    // }

    // printf("%d\n",rand() % 2);

    // if (NULL == 0)
    // {
    //     printf("NULL=0\n");
    // }
}