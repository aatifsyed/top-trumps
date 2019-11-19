#include <stdio.h> // for IO
#include <stdlib.h>  // for random numbers
#include <time.h> // for seeding RNG
#define CHARM 0 // these are the names of the properties of the card
#define STRANGENESS 1
#define CHEERFULLNESS 2
#define SADNESS 3 // [TODO] allow arbitrary number of properties

// global variables and useful structures
const int number_of_cards_each = 10;
const int number_of_players = 2;

// making and printing cards
typedef struct card 
{
  int properties[4];
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

    (*(pointer_to_block_of_cards + current_card)).properties[CHARM] = rand() % 9999; // Pointer arithmetic here was hard earned! rand docs mention RAND_MAX - should I be messing with this?
    (*(pointer_to_block_of_cards + current_card)).properties[STRANGENESS] = rand() % 9999; // [TODO] make it positive. Surely there's data being lost if I'm going from signed to char...?
    (*(pointer_to_block_of_cards + current_card)).properties[CHEERFULLNESS] = rand() % 9999;
    (*(pointer_to_block_of_cards + current_card)).properties[SADNESS] = rand() % 9999;
    (*(pointer_to_block_of_cards + current_card)).next_card = pointer_to_block_of_cards + current_card + 1; // simplifies allocate_cards() greatly
  }

  return pointer_to_block_of_cards; // Messing with multidimensional arrays taught me that pointer_to_block_of_cards != Card. Should I be doing this differently?
}

void print_cards(Card* pointer_to_block_of_cards, int number_of_cards_to_print) // Prints cards to screen
{
  for(int current_card = 0; current_card < number_of_cards_to_print; current_card++)
  {
    printf("Card %3d at %9p, pointing to %9p: %4d, %4d, %4d, %4d\n",
    current_card, 
    (pointer_to_block_of_cards + current_card), 
    (*(pointer_to_block_of_cards + current_card)).next_card, 
    (*(pointer_to_block_of_cards + current_card)).properties[CHARM], 
    (*(pointer_to_block_of_cards + current_card)).properties[STRANGENESS], 
    (*(pointer_to_block_of_cards + current_card)).properties[CHEERFULLNESS], 
    (*(pointer_to_block_of_cards + current_card)).properties[SADNESS]);
  }
}

// making and printing players
typedef struct player
{
  Card* top_card;
  Card* bottom_card;
  int wins;
  // is it a bad idea to refer to player 1 as *(pointer_to_players + 0)? I'd love to do player1.top_card etc, but to dynamically allocate players, this is the only way I can think of.
} Player;

// compiler was angry so I'm trying prototypes:
int move_cards(int winning_player_index, int losing_player_index, Player* pointer_to_list_of_players);
int other_player(int current_player);

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

// gameplay
int allocate_cards(Card* pointer_to_block_of_cards, int number_of_cards_each, Player* pointer_to_list_of_players, int number_of_players)
{
  for (int current_player = 0; current_player < number_of_players; current_player++)
  {
    (*(pointer_to_list_of_players + current_player)).top_card = pointer_to_block_of_cards + current_player*number_of_cards_each; // set top card
    (*(pointer_to_list_of_players + current_player)).bottom_card = pointer_to_block_of_cards + (((current_player + 1)*number_of_cards_each)-1); // set bottom card
    (*(pointer_to_block_of_cards + (((current_player + 1)*number_of_cards_each)-1))).next_card = NULL; // point bottom card to NULL  
  }
  // Should I copy the pointers to local pointers here. Lets us increment them with impunity...
  // for (int current_player = 0; current_player < number_of_players; current_player++)
  // {
  //   for (int current_card = 0; current_card < number_of_cards_each; current_card++) // setting top card in the for initial step
  //   {
  //     ;
  //   }
  // }
  
  return 0;
}

int best_card_property_index(int player_number, Player* pointer_to_list_of_players) // returns the index of the card.property
{ // my instinct is to make this const Player*. [TODO] make relevant variables consts
  int best_property_index = -1;
  int best_property_value = 0; 

  Player* pointer_to_current_player = pointer_to_list_of_players + player_number;
  Player current_player = *pointer_to_current_player;
  Card* pointer_to_current_card = current_player.top_card;
  Card current_card = *pointer_to_current_card; // as opposed to having it all on one line...
  
  for (int current_property_index = 0; current_property_index < 4; current_property_index++)
  {
    if ( current_card.properties[current_property_index] > best_property_value )
    {
      best_property_value = current_card.properties[current_property_index];
      best_property_index = current_property_index;
    }
  }
  
  return best_property_index;
}

int play_a_round(int current_player, Player* pointer_to_list_of_players) // returns the winning player's index, or -1 if the other player has no more cards left 
{
  int current_player_best_property_index;
  current_player_best_property_index = best_card_property_index(current_player, pointer_to_list_of_players);
  int current_player_property = (*(*(pointer_to_list_of_players + current_player)).top_card).properties[current_player_best_property_index];
  int other_player_property = (*(*(pointer_to_list_of_players + other_player(current_player))).top_card).properties[current_player_best_property_index];

  int endofgame, winning_player;
  if (other_player_property < current_player_property) // phrased like this so other player will win a draw
  {
    endofgame = move_cards(current_player, other_player(current_player), pointer_to_list_of_players);
    winning_player = current_player;
  }
  else
  {
    endofgame = move_cards(other_player(current_player), current_player, pointer_to_list_of_players);
    winning_player = other_player(current_player);
  }
  
  if (endofgame == 1)
  {
    return -1;
  }
  else 
  {
    return winning_player;
  }
  ;
}

int other_player(int current_player) // returns index of not current player
{
  switch (current_player)
  {
  case 0:
    return 1;
    break;
  case 1:
    return 0;
    break;
  default:
    return -1; //error
    break;
  }
}

int move_cards(int winning_player_index, int losing_player_index, Player* pointer_to_list_of_players) // returns 1 if losing player has no more cards
{
  printf("moving cards\n");
  Player* winning_player = pointer_to_list_of_players + winning_player_index; // for consistency, I should have named this pointer_to_winning_player...
  Player* losing_player = pointer_to_list_of_players + losing_player_index;

  // point bottom card to top card
  (*(*winning_player).bottom_card).next_card = (*winning_player).top_card; 
  // winning player's top card points to next card
  (*winning_player).top_card = (*(*winning_player).top_card).next_card;
  // winning player's former top card points to losing player's top card
  (*(*(*winning_player).bottom_card).next_card).next_card = (*losing_player).top_card;
  // losing player's top card points to next card
  (*losing_player).top_card = (*(*losing_player).top_card).next_card;
  // winning player's bottom card points to new bottom card
  (*winning_player).bottom_card = (*(*(*winning_player).bottom_card).next_card).next_card;
  // winning player's new bottom card points to null
  (*(*winning_player).bottom_card).next_card = NULL;

  if ((*losing_player).top_card == NULL) 
  {
    return 1; 
  }
  else
  {
    return 0;
  }

//   // this code is too hard to read...
//   // winning player
//   //  point bottom card to top card
//   (*(pointer_to_list_of_players + winning_player_index)).bottom_card = (*(pointer_to_list_of_players + winning_player_index)).top_card;
//   //  make winning_player.top_card point to the top card's .next_card
//   (*(pointer_to_list_of_players + winning_player_index)).top_card = (*((*(pointer_to_list_of_players + winning_player_index)).top_card)).next_card;
//   //  point top card to losing player's top card
//   (*((*(pointer_to_list_of_players + winning_player_index)).top_card)).next_card = (*(pointer_to_list_of_players + losing_player_index)).top_card;
//   //  point losing player's top card to null
//   change_card_pointers((*((*(pointer_to_list_of_players + losing_player_index)).top_card)).next_card, NULL);
//   // make winning_player.bottom_card point to losing player's top card
//   (*(pointer_to_list_of_players + winning_player_index)).bottom_card = (*(pointer_to_list_of_players + losing_player_index)).top_card;
}

int get_top_card_property(int card_property_index, int player_index, Player* pointer_to_list_of_players)
{
  Card* pointer_to_top_card = (*(pointer_to_list_of_players + player_index)).top_card;
  int top_card_property = (*(pointer_to_top_card)).properties[card_property_index];
  return top_card_property;
}

int change_card_pointers(Card* pointer_to_source_card, Card* pointer_to_destination_card) // changes card.next_card. can point to NULL
{
  (*(pointer_to_source_card)).next_card = pointer_to_destination_card;
  return 0;
}

int main(void)
{
  Card* pointer_to_block_of_cards; // I know I could do this all in one line, I just want to be very explicit for now
  Player* pointer_to_list_of_players;

  pointer_to_block_of_cards = make_cards(number_of_cards_each * number_of_players);
  print_cards(pointer_to_block_of_cards, number_of_cards_each * number_of_players);

  pointer_to_list_of_players = make_players(number_of_players);
  print_players(pointer_to_list_of_players, number_of_players);

  allocate_cards(pointer_to_block_of_cards, number_of_cards_each, pointer_to_list_of_players, number_of_players);
  print_cards(pointer_to_block_of_cards, number_of_cards_each * number_of_players);
  print_players(pointer_to_list_of_players, number_of_players);

  printf("Player 0's best card property is index %d\n",best_card_property_index(0,pointer_to_list_of_players));
  printf("Player 0's top card property is %d\n", get_top_card_property(best_card_property_index(0,pointer_to_list_of_players), 0, pointer_to_list_of_players));
  printf("Player 1's best card property is index %d\n",best_card_property_index(1,pointer_to_list_of_players));
  printf("Player 1's top card property is %d\n", get_top_card_property(best_card_property_index(1,pointer_to_list_of_players), 1, pointer_to_list_of_players));
  
  int current_player = rand() % number_of_players; // flip a coin to see who starts
  printf("Player %d will start\n",current_player);

  // change_card_pointers(pointer_to_block_of_cards,NULL);
  // print_cards(pointer_to_block_of_cards, number_of_cards_each*number_of_players);

  // for(int number_of_movements = 0; number_of_movements < 9; number_of_movements++)
  // {
  //   move_cards(0,1,pointer_to_list_of_players);
  //   print_cards(pointer_to_block_of_cards, number_of_cards_each * number_of_players);
  //   print_players(pointer_to_list_of_players, number_of_players);
  // }

  // play_a_round();

  int endofgame;
  while (current_player != -1)
  {
    current_player = play_a_round(current_player, pointer_to_list_of_players);
  }

  return 0;
}
