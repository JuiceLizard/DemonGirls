#pragma once

#include "settings.h"

// 'M' wall, '@' player, ' ' ground, 'S' skeleton, 'B' block,
// 'D' demon girl, 'K' key, 'L' lock, 'T' teeth,
// 'k' even number teeth, 'l' odd number teeth

// 'a' player on teeth, 'b' player on even number teeth, 'c' player on odd number teeth,
// 'd' bloc on teeth, 'e' bloc on even number teeth, 'f' bloc on odd number teeth
// 'g' skeleton on even number holes, 'h' skeleton on odd number holes
// 'i' block and key, 'j' skeleton and key

// Here is stored the elements of the level.
// It changes when the player moves.
// The graphics parts of the code take the data from here at each frame.

char level[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', ' ', '@', 'M', 'M', 'M'},
  {'M', 'M', 'M', ' ', ' ', 'S', ' ', ' ', 'M', 'M', 'M'},
  {'M', 'M', 'M', ' ', 'S', ' ', 'S', 'M', 'M', 'M', 'M'},
  {'M', 'M', ' ', ' ', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', ' ', 'B', ' ', ' ', 'B', ' ', 'M', 'M', 'M'},
  {'M', 'M', ' ', 'B', ' ', 'B', ' ', ' ', 'D', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// Here are stored all the levels of the game.
// We copy this data to the previous table
// when we change the level or reset the current level.

// level 1 Pandemonica
const char level1[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', ' ', '@', 'M', 'M', 'M'},
  {'M', 'M', 'M', ' ', ' ', 'S', ' ', ' ', 'M', 'M', 'M'},
  {'M', 'M', 'M', ' ', 'S', ' ', 'S', 'M', 'M', 'M', 'M'},
  {'M', 'M', ' ', ' ', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', ' ', 'B', ' ', ' ', 'B', ' ', 'M', 'M', 'M'},
  {'M', 'M', ' ', 'B', ' ', 'B', ' ', ' ', 'D', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 2 Modeus
const char level2[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', ' ', ' ', ' ', ' ', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'S', 'M', 'T', 'T', ' ', ' ', 'M', 'M'},
  {'M', 'M', ' ', 'T', 'M', 'M', 'd', 'd', 'B', 'M', 'M'},
  {'M', 'M', ' ', ' ', 'M', 'M', ' ', 'T', ' ', 'M', 'M'},
  {'M', 'M', '@', ' ', 'M', 'M', ' ', 'S', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'D', ' ', 'S', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 3 Cerberus
const char level3[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'D', 'D', 'D', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'L', 'M', 'M'},
  {'M', 'M', 'M', 'M', ' ', 'T', 'T', ' ', ' ', '@', 'M'},
  {'M', 'M', 'M', 'M', 'T', 'M', 'T', 'M', ' ', ' ', 'M'},
  {'M', 'M', 'M', 'M', ' ', ' ', 'S', 'T', 'T', 'M', 'M'},
  {'M', 'M', 'K', 'M', 'T', 'M', 'T', 'M', ' ', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', ' ', ' ', 'S', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 4 Malina
const char level4[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', '@', 'M', 'K', ' ', 'B', 'M', ' ', 'M', 'M'},
  {'M', 'M', ' ', 'B', 'T', 'd', ' ', 'L', ' ', 'M', 'M'},
  {'M', 'M', 'B', ' ', 'B', ' ', 'B', 'B', ' ', 'D', 'M'},
  {'M', 'M', ' ', 'B', ' ', 'B', ' ', 'B', 'B', ' ', 'M'},
  {'M', 'M', 'M', ' ', 'B', ' ', 'B', ' ', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 5 Zdrada
const char level5[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ { 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  { 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  { 'M', 'M', 'M', 'M', 'M', ' ', 'D', 'M', 'M', 'M', 'M'},
  { 'M', 'M', 'M', 'M', ' ', 'L', 'B', ' ', 'M', 'M', 'M'},
  { 'M', 'M', '@', 'M', 'k', ' ', 'B', ' ', 'M', 'M', 'M'},
  { 'M', 'M', ' ', 'M', ' ', 'k', ' ', 'k', 'M', 'M', 'M'},
  { 'M', 'M', 'S', 'M', 'B', 'B', 'B', 'B', 'M', 'M', 'M'},
  { 'M', 'M', 'k', ' ', 'k', ' ', ' ', 'k', 'M', 'M', 'M'},
  { 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'K', 'M', 'M', 'M'},
  { 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 6 Azazel
const char level6[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', ' ', '@', ' ', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'B', 'B', 'B', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', 'K', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'k', 'e', ' ', ' ', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'S', 'M', 'B', 'B', ' ', ' ', 'M', 'M'},
  {'M', 'M', 'M', ' ', ' ', 'B', ' ', 'S', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'L', 'B', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', ' ', 'D', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 7 Justice
const char level7[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'D', ' ', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', ' ', 'L', ' ', 'M', 'M'},
  {'M', 'M', 'M', ' ', 'K', 'M', 'B', 'B', 'B', 'M', 'M'},
  {'M', 'M', 'M', 'S', 'B', ' ', 'S', 'B', ' ', 'M', 'M'},
  {'M', 'M', 'M', ' ', 'M', 'S', ' ', ' ', '@', 'M', 'M'},
  {'M', 'M', 'M', 'k', 'M', 'M', 'l', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'l', 'k', 'l', 'k', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 8 Lucifer
const char level8[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', ' ', 'M', 'M', 'D', 'M', 'M', ' ', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', 'S', ' ', ' ', ' ', 'M', 'M'},
  {'M', 'M', ' ', 'M', ' ', 'S', ' ', 'M', ' ', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', 'S', ' ', ' ', ' ', 'M', 'M'},
  {'M', 'M', ' ', 'M', ' ', 'S', ' ', 'M', ' ', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', ' ', '@', ' ', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 9 Judgement
const char level9[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'D', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', ' ', ' ', ' ', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'B', 'L', 'B', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'B', 'M', 'B', ' ', ' ', 'M', ' ', 'M', 'M'},
  {'M', 'B', ' ', ' ', 'B', 'B', 'B', ' ', ' ', 'K', 'M'},
  {'M', ' ', 'B', 'B', 'B', ' ', ' ', 'B', 'B', ' ', 'M'},
  {'M', 'M', '@', ' ', 'B', ' ', ' ', 'B', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

/*
// level 10 Beelzebub
const char level10[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'S', 'M', 'M', 'S', ' ', 'B', 'M', 'B', 'B', 'M'},
  {'M', ' ', ' ', ' ', 'T', 'T', 'T', 'M', ' ', '@', 'M'},
  {'M', 'L', 'M', 'M', 'T', 'i', 'T', 'M', ' ', 'M', 'M'},
  {'M', ' ', 'B', 'M', 'T', 'T', 'T', 'S', ' ', 'B', 'M'},
  {'M', ' ', 'D', 'M', 'S', ' ', ' ', ' ', ' ', 'S', 'M'},
  {'M', ' ', ' ', 'M', 'B', 'K', 'B', 'B', ' ', 'B', 'M'},
  {'M', 'M', 'M', 'M', 'B', 'S', 'B', 'B', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };

// level 10 Beelzebub
const char level10[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', ' ', 'B', ' ', ' ', 'B', ' ', 'M', ' ', ' ', 'M'},
  {'M', 'S', ' ', ' ', ' ', 'i', '@', 'M', ' ', ' ', 'M'},
  {'M', 'k', 'M', 'M', 'M', ' ', 'M', 'M', ' ', ' ', 'M'},
  {'M', 'l', 'B', ' ', ' ', 'B', 'L', ' ', ' ', ' ', 'M'},
  {'M', ' ', 'B', 'T', ' ', ' ', 'M', 'D', ' ', ' ', 'M'},
  {'M', ' ', 'B', 'M', 'M', 'M', 'M', ' ', ' ', ' ', 'M'},
  {'M', 'M', 'M', ' ', ' ', ' ', ' ', ' ', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };


// level 10
const char level10[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', 'M', ' ', ' ', ' ', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', ' ', ' ', ' ', 'D', 'M', 'M'},
  {'M', 'M', 'M', ' ', ' ', 'M', ' ', ' ', 'M', 'M', 'M'},
  {'M', 'M', 'M', ' ', ' ', 'M', ' ', ' ', 'M', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', ' ', ' ', ' ', '@', 'M', 'M'},
  {'M', 'M', ' ', ' ', ' ', 'M', ' ', ' ', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };
*/

const char level10[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'K', 'T', ' ', 'M', ' ', 'T', ' ', 'M', 'M'},
  {'M', 'M', ' ', 'B', 'i', ' ', 'S', 'B', 'D', 'M', 'M'},
  {'M', 'M', 'M', ' ', 'M', 'M', 'M', 'L', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'S', 'M', 'M', 'M', ' ', 'M', 'M', 'M'},
  {'M', 'M', 'S', 'B', 'k', 'l', 'k', 'B', '@', 'M', 'M'},
  {'M', 'M', ' ', 'T', 'T', 'M', ' ', ' ', ' ', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'},
  {'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'} };


// Here are stored the sprites display of the walls
char walls[NB_ROWS_LEVELS][NB_COLUMNS_LEVELS] =
{ {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'c', 'c', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'c', 'c', 'g', ' ', ' ', 'b', 'a', 'a'},
  {'a', 'a', 'e', ' ', ' ', ' ', ' ', ' ', 'b', 'a', 'a'},
  {'a', 'a', 'g', ' ', ' ', ' ', ' ', 'j', 'a', 'a', 'a'},
  {'a', 'e', ' ', ' ', 'l', 'k', 'k', 'c', 'a', 'a', 'a'},
  {'a', 'e', ' ', ' ', ' ', ' ', ' ', ' ', 'd', 'a', 'a'},
  {'a', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'a'},
  {'a', 'a', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'} };
