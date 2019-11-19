#ifndef STRUCTURES_H
#define STRUCTURES_H

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

#endif