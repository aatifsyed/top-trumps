
typedef struct player
{
  int wins;
  struct card* top_card;
} Player;

typedef struct card
{
  int properties[4];
  struct card* next_card;
} Card;

Card* make_card(void);
void randomise_card(Card* card);
void send_to_top(Player* player, Card* card);
void send_to_bottom(Player* player, Card* card);
Card* bottom_card(Player* player);
Card* pop_card_from_top(Player* player);
int number_of_cards(Player* player);