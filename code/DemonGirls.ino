// "Demon Girls" (previously "Hellmaker" or "Pancaker")
// A "Helltaker" demake (unofficial)
// for Gamebuino Meta
// by Juice Lizard.

// Original game by VanRipper.
// Original music by Mittsies.

// With this beautiful source code
// you can change the levels
// or anything you want
// to make your own version of the game.

#include <Gamebuino-Meta.h>

extern const uint8_t font5x7[];

#include "settings.h"
#include "assets.h"
#include "levels.h"

// 0: intro, 1: Hell levels, 2: Hell dialogues, 3: BAD END
int gamestate = 0;

// the hero
uint8_t rowPlayer = 2;
uint8_t columnPlayer = 7;
bool heroKicks = false;
// Our hero faces right or left.
bool heroTurnsRight = true;


// HUD variables
int levelNumber = 0;
uint8_t remainingMoves = 23;

// death animation
bool death = false;
uint8_t deathCounter = 0;
uint8_t skullCounter = 0;

// DEMON GIRLS animation
bool resetLevel = false;
bool clap = false;
uint8_t clapCounter = 0;

// Does the hero get a key?
bool hasKey = false;

// Usefull for moving teeth
bool evenNumber = true;

// for dialogue animation
uint8_t bigDemon = 8;

bool levelFinished = false;
uint8_t goDialogues = 0;

bool topAnswer = true;
bool goodAnswer = false;
uint8_t answered = 0;

uint8_t whatTheFoxSays = 0;

// secret letters hidden under some blocks
bool hasSecretB = false;
bool hasSecretA = false;
bool hasSecretD = false;

// Usefull for LEDs at the back of the Gamebuino Meta
// when the hero is hurt by teeth
uint8_t redFlash = 0;

// Badger logo animation
int xLogo = 80;
int yLogo = 80;
int logoTrouble = 120;
uint8_t frames = 0;
bool logoSide = true;
bool logoReduces = true;
bool anim = true;
uint8_t beforePress = 0;

// This part runs once at the start of the game.
void setup() {
  gb.begin();

}


void drawRemainingMoves() {

  // This instance is created in memory only as long as necessary.
  // There is no need to keep this instance outside this function.
  Image digit(NB_DATA);

  // Then we convert `remainingMoves` in a string to be able
  // to browse each of its characters one by one.
  char moves[3]; // 2 + 1 (for the string termination character `\0`)
  snprintf(moves, 3, "%02u", remainingMoves);

  // It is assumed that `remainingMoves` will always be less than 100
  // and therefore be expressed by 1 or 2 characters.
  if (remainingMoves < 10 ) {
    digit.setFrame(moves[1] - '0');
    gb.display.drawImage(7, 115, digit);
  } else {
    digit.setFrame(moves[0] - '0');
    gb.display.drawImage(4, 115, digit);
    digit.setFrame(moves[1] - '0');
    gb.display.drawImage(10, 115, digit);
  }

}

void drawLevelNumber() {
  // This instance is created in memory only as long as necessary.
  // There is no need to keep this instance outside this function.
  Image level(LEVEL_NB_DATA);
  level.setFrame(levelNumber - 1);
  gb.display.drawImage(144, 114, level);
}

void drawHUD() {

  drawRemainingMoves();
  drawLevelNumber();

}


// This is the death animation,
// when the hero moves once too often.
void drawDeath() {
  if(deathCounter == 0) {
    gb.lights.fill(WHITE);
  }

  if(deathCounter < 3) {
    gb.display.fill(DARKGRAY);
    gb.display.setColor(WHITE);
    gb.display.fillCircle(columnPlayer*16, (rowPlayer*16)-8, 16);
  }

  if((deathCounter > 2) && (deathCounter < 6)) {
    gb.display.fill(BLACK);
    gb.display.drawImage((columnPlayer*16)-24, (rowPlayer*16)-16, deathHoleBig);
    gb.display.setColor(WHITE);
    gb.display.fillRect((columnPlayer*16)-14, 0, 28, (rowPlayer*16)-16);
  }

  if(deathCounter > 5) {
    gb.display.fill(BLACK);
    gb.display.drawImage((columnPlayer*16)-24, (rowPlayer*16)-16, deathHoleSmall);
    gb.display.setColor(WHITE);
    gb.display.fillRect((columnPlayer*16)-8, 0, 16, (rowPlayer*16)-16);
    if(heroTurnsRight) {
      gb.display.drawImage((columnPlayer*16)-8, (rowPlayer*16)-20-(skullCounter/2), heroDeadRight);
    } else {
      gb.display.drawImage((columnPlayer*16)-8, (rowPlayer*16)-20-(skullCounter/2), heroDeadLeft);
    }
    skullCounter = skullCounter + 1;
  }

  if(deathCounter == 10) {
    clap = true;
  }

  deathCounter = deathCounter + 1;
  if(deathCounter > 20) {
    deathCounter = 0;
    skullCounter = 0;
//    changeLevel();
  }
}

// Title clap animation
// (after we die or when we reset a level)
void drawClap() {
  if(clapCounter < 7) {
    gb.display.drawImage(0, (clapCounter*11)-64, DEMON80x32, 160, 64);
    gb.display.drawImage(0, 128-(clapCounter*11), GIRLS80x32, 160, 64);
  }
  if((clapCounter > 6) && (clapCounter < 18)) {
    gb.display.drawImage(0, 0, DEMON80x32, 160, 64);
    gb.display.drawImage(0, 64, GIRLS80x32, 160, 64);
    gamestate = 1;
    if(clapCounter == 10) {
      changeLevel();
      heroKicks = false;
    }
    answered = 0;
  }

  if(clapCounter > 17) {
    gb.display.drawImage(0, 0-((clapCounter-18)*11), DEMON80x32, 160, 64);
    gb.display.drawImage(0, 64+((clapCounter-18)*11), GIRLS80x32, 160, 64);
  }

  clapCounter = clapCounter + 1;

  if(clapCounter > 22) {
    clapCounter = 0;
    clap = false;
    bigDemon = 8;
  }
}

// graphic function of the game part
void drawGraphics() {
// We paint all the screen in purple.
  gb.display.clear(PURPLE);

// We draw the secret letters hidden under some blocks
  secretLetters();

// The back lights flash in purple if teeth hurt
  if(redFlash == 1) {
    gb.lights.fill(PURPLE);
  }

// 'M' wall, '@' player, ' ' ground, 'S' Skeleton,
// 'B' block, 'D' demon girl, 'K' key, 'L' lock, 'H' holes

// Each of the level boxes is displayed.
  for (int row=0; row<NB_ROWS_LEVELS; row++) {
    for (int column=0; column<NB_COLUMNS_LEVELS; column++) {
      switch (level[row][column]) {
        case 'M':
          drawWall(row, column);
          break;
        case '@':
          drawPlayer(row, column);
          break;
        case 'S':
          drawSkeleton(row, column);
          break;
        case 'B':
          drawBlock(row, column);
          break;
        case 'D':
          drawDemon(row, column);
          break;
        case 'K':
          drawKey(row, column);
          break;
        case 'L':
          drawLock(row, column);
          break;
        case 'T': // those don't move
          drawTeeth(row, column);
          break;
        case ' ':
// If ground, we draw nothing (gb.display.clear() color).
          break;
        case 'a': // those teeth don't move
          drawPlayerOnTeeth(row, column);
          break;
        case 'b':
          if(evenNumber == true) {
            drawPlayerOnTeeth(row, column);
          } else {
            drawPlayerOnHoles(row, column);
          }
          break;
        case 'c':
          if(evenNumber == false) {
            drawPlayerOnTeeth(row, column);
          } else {
            drawPlayerOnHoles(row, column);
          }
          break;
        case 'd':
          drawBlockOnTeeth(row, column);
          break;
        case 'e':
          if(evenNumber == true) {
            drawBlockOnTeeth(row, column);
          } else {
            drawBlockOnHoles(row, column);
          }
          break;
        case 'f':
          if(evenNumber == false) {
            drawBlockOnTeeth(row, column);
          } else {
            drawBlockOnHoles(row, column);
          }
          break;
        case 'g':
          drawHoles(row, column);
          drawSkeleton(row, column);
          break;
        case 'h':
          drawHoles(row, column);
          drawSkeleton(row, column);
          break;
        case 'i':
          drawBlockOnKey(row, column);
          break;
        case 'j':
          drawKey(row, column);
          drawSkeleton(row, column);
          break;
        case 'k':
          if(evenNumber == true) {
            drawTeeth(row, column);
          } else {
            drawHoles(row, column);
          }
          break;
        case 'l':
          if(evenNumber == false) {
            drawTeeth(row, column);
          } else {
            drawHoles(row, column);
          }
          break; 
        default:
          break;
      }
    }
  }

// We draw the HUD
  drawHUD();
  
}

// Graphics in the levels
void drawWall(int row, int column) {
  switch (walls[row][column]) {
    case 'a':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_a);
    break;
    case 'b':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_b);
    break;
    case 'c':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_c);
    break;
    case 'd':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_d);
    break;
    case 'e':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_e);
    break;
    case 'f':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_f);
    break;
    case 'g':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_g);
    break;
    case 'h':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_h);
    break;
    case 'i':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_i);
    break;
    case 'j':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_j);
    break;
    case 'k':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_k);
    break;
    case 'l':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_l);
    break;
    case 'm':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_m);
    break;
    case 'n':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_n);
    break;
    case 'o':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_o);
    break;
    case 'p':
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_p);
    break;
    default:
      gb.display.drawImage(column*16 - 8, row*16 - 16, wall_a);
    break;
  }
}

void drawPlayer(int row, int column) {
  if (heroTurnsRight) {
    if(heroKicks == true) {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroKicksRight);
    } else {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroRight);
    }
  } else {
    if(heroKicks == true) {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroKicksLeft);
    } else {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroLeft);
    }
  }
}

void drawPlayerOnTeeth(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, teeth_down);
  if(redFlash > 0) {
    if (heroTurnsRight) {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroRightRed);
    } else {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroRightRed, -16, 16);
    }
  } else {
  if (heroTurnsRight) {
    if(heroKicks == true) {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroKicksRight);
    } else {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroRight);
    }
  } else {
    if(heroKicks == true) {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroKicksLeft);
    } else {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroLeft);
    }
  }
  }
  gb.display.drawImage(column*16 - 8, row*16 - 16, teeth_down);
}

void drawPlayerOnHoles(int row, int column) {
    gb.display.drawImage(column*16 - 8, row*16 - 16, holes_up);
  if (heroTurnsRight) {
    if(heroKicks == true) {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroKicksRight);
    } else {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroRight);
    }
  } else {
    if(heroKicks == true) {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroKicksLeft);
    } else {
      gb.display.drawImage(column*16 - 8, row*16 - 16, heroLeft);
    }
  }
  gb.display.drawImage(column*16 - 8, row*16 - 16, holes_down);
}

void drawSkeleton(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, Skeleton);
}

void drawSkeletonAndKey(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, key);
  gb.display.drawImage(column*16 - 8, row*16 - 16, Skeleton);
}

void drawBlock(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, block);
}

void drawBlockOnTeeth(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, block);
  gb.display.drawImage(column*16 - 8, row*16 - 16, teeth_down);
}

void drawBlockOnHoles(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, block);
  gb.display.drawImage(column*16 - 8, row*16 - 16, holes_down);
}

void drawBlockOnKey(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, key);
  gb.display.drawImage(column*16 - 8, row*16 - 16, block);
}

void drawKey(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, key);
}

void drawBlockAndKey(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, key);
  gb.display.drawImage(column*16 - 8, row*16 - 16, block);
}

void drawLock(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, lock);
}

void drawTeeth(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, teeth_up);
  gb.display.drawImage(column*16 - 8, row*16 - 16, teeth_down);
}

void drawHoles(int row, int column) {
  gb.display.drawImage(column*16 - 8, row*16 - 16, holes_up);
  gb.display.drawImage(column*16 - 8, row*16 - 16, holes_down);
}

void drawDemon(int row, int column) {
// The ten demon girls match to each level.
  switch (levelNumber) {
    case 1:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Pandemonica);
    break;
    case 2:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Modeus);
    break;
    case 3:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Cerberus);
    break;
    case 4:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Malina);
    break;
    case 5:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Zdrada);
    break;
    case 6:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Azazel);
    break;
    case 7:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Justice);
    break;
    case 8:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Lucifer);
    break;
    case 9:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Judgement);
    break;
    case 10:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Beelzebub);
    break;
    default:
      gb.display.drawImage(column*16 - 8, row*16 - 16, Beelzebub);
    break;
  }
}

// Inputs

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

// Next row function
int nr(int Direction, int nb) {
  switch (Direction) {
    case UP:
    return rowPlayer - nb;
    break;
    case DOWN:
    return rowPlayer + nb;
    break;
    default:
    return rowPlayer;
    break;
  }
}

// Next column function
int nc(int Direction, int nb) {
  switch (Direction) {
    case RIGHT:
    return columnPlayer + nb;
    break;
    case LEFT:
    return columnPlayer - nb;
    break;
    default:
    return columnPlayer;
    break;
  }
}

// shortcut next box
#define NEXT(DIR,NB) level[nr(DIR,NB)][nc(DIR,NB)]

// We update the box that the player just leaves
void previousBox() {
        if(level[rowPlayer][columnPlayer] == '@') {
          level[rowPlayer][columnPlayer] = ' ';
        }
        if(level[rowPlayer][columnPlayer] == 'a') {
          level[rowPlayer][columnPlayer] = 'T';
        }
        if(level[rowPlayer][columnPlayer] == 'b') {
          level[rowPlayer][columnPlayer] = 'k';
        }
        if(level[rowPlayer][columnPlayer] == 'c') {
          level[rowPlayer][columnPlayer] = 'l';
        }
}

// We hurt the player if he is on teeth
void teethHurt() {
  if(((level[rowPlayer][columnPlayer] == 'a') || ((level[rowPlayer][columnPlayer] == 'b') && (evenNumber == true)) || ((level[rowPlayer][columnPlayer] == 'c') && (evenNumber == false))) && (remainingMoves > 0)) {
      remainingMoves = remainingMoves - 1;
      redFlash = 2;
//      gb.lights.fill(RED);
    }
}

// We move the player and the other items in the levels
void moveTo(int dir) {

// If next box is wall…
  if(NEXT(dir,1) == 'M') {
// … we don't move the player.
  return;
  }
  
// If the two next boxes are blocks…
  if( ( (NEXT(dir,1) == 'B') || (NEXT(dir,1) == 'd') || (NEXT(dir,1) == 'e') || (NEXT(dir,1) == 'f') || (NEXT(dir,1) == 'i') ) && ( (NEXT(dir,2) == 'B') || (NEXT(dir,2) == 'd') || (NEXT(dir,2) == 'e') || (NEXT(dir,2) == 'f') || (NEXT(dir,2) == 'i') || (NEXT(dir,2) == 'L') || (NEXT(dir,2) == 'D') || (NEXT(dir,2) == 'S') ) ) {
// … we don't move the player, but he kicks the block and counts a move.
    heroKicks = true;
    gb.sound.playTick();
    if(remainingMoves > 0) {
      remainingMoves = remainingMoves - 1;
      if(evenNumber == true) {
        evenNumber = false;
      } else {
        evenNumber = true;
      }
    } else {
      death = true;
      drawDeath();
      gb.sound.playCancel();
    }
// We check if the player is hurted by teeth
    teethHurt();
// If the remaining moves counter is zero, we lose.
  if(remainingMoves == 0) {
    death = true;
    drawDeath();
    gb.sound.playCancel();
    return;
  }
    return;    
  }

// If the two next boxes are a block and a wall…
  if( ( (NEXT(dir,1) == 'B')  || (NEXT(dir,1) == 'd') || (NEXT(dir,1) == 'e') || (NEXT(dir,1) == 'f') || (NEXT(dir,1) == 'i') ) && (NEXT(dir,2) == 'M') ) {
// … we don't move the player, but he kicks the block and counts a move.
    heroKicks = true;
    gb.sound.playTick();
    if(remainingMoves > 0) {
      remainingMoves = remainingMoves - 1;
      if(evenNumber == true) {
        evenNumber = false;
      } else {
        evenNumber = true;
      }
    } else {
      death = true;
      drawDeath();
      gb.sound.playCancel();
    }
// We check if the player is hurted by teeth
    teethHurt();
// If the remaining moves counter is zero, we lose.
  if(remainingMoves == 0) {
    death = true;
    drawDeath();
    gb.sound.playCancel();
    return;
  }
    return;    
  }

// If the two next boxes are a block and a skeleton…
  if( (NEXT(dir,1) == 'B') && (NEXT(dir,2) == 'S') ) {
// … we don't move the player, but he kicks the block and counts a move.
    heroKicks = true;
    gb.sound.playTick();
    if(remainingMoves > 0) {
      remainingMoves = remainingMoves - 1;
      if(evenNumber == true) {
        evenNumber = false;
      } else {
        evenNumber = true;
      }
    } else {
      death = true;
      drawDeath();
      gb.sound.playCancel();
    }
// We check if the player is hurted by teeth
    teethHurt();
// If the remaining moves counter is zero, we lose.
  if(remainingMoves == 0) {
    death = true;
    drawDeath();
    gb.sound.playCancel();
    return;
  }
    return;    
  }

// If next box is lock and we don't have the key…
  if( (NEXT(dir,1) == 'L') && (hasKey == false) ) {
// … we don't move the player, but he kicks the lock and counts a move.
    heroKicks = true;
    gb.sound.playTick();
    if(remainingMoves > 0) {
      remainingMoves = remainingMoves - 1;
      if(evenNumber == true) {
        evenNumber = false;
      } else {
        evenNumber = true;
      }
    } else {
      death = true;
      drawDeath();
      gb.sound.playCancel();
    }
// We check if the player is hurted by teeth
    teethHurt();
// If the remaining moves counter is zero, we lose.
  if(remainingMoves == 0) {
    death = true;
    drawDeath();
    gb.sound.playCancel();
    return;
  }
  return;
  }

// If the remaining moves counter is zero, we lose.
  if(remainingMoves == 0) {
    death = true;
    drawDeath();
    gb.sound.playCancel();
    return;
  }

// We know that movement is allowed.

  if(remainingMoves > 0) {
    remainingMoves = remainingMoves - 1;
    if(evenNumber == true) {
      evenNumber = false;
    } else {
      evenNumber = true;
    }
  }

// If next box is a block…
  if((NEXT(dir,1) == 'B') || (NEXT(dir,1) == 'd') || (NEXT(dir,1) == 'e') || (NEXT(dir,1) == 'f') || (NEXT(dir,1) == 'i')) {
    {
// … the player kicks it…
      heroKicks = true;
      gb.sound.playTick();
// … we move the block to the next box…
      if(NEXT(dir,2) == ' ') {
        NEXT(dir,2) = 'B';
      } else if(NEXT(dir,2) == 'K') {
        NEXT(dir,2) = 'i';
      } else if(NEXT(dir,2) == 'T') {
        NEXT(dir,2) = 'd';
      } else if(NEXT(dir,2) == 'k') {
        NEXT(dir,2) = 'e';
      } else if(NEXT(dir,2) == 'l') {
        NEXT(dir,2) = 'f';
      }
    }

// … and we take off the block from its previous location.
    if(NEXT(dir,1) == 'B') {
      NEXT(dir,1) = ' ';
    } else if (NEXT(dir,1) == 'i') {
      NEXT(dir,1) = 'K';
    } else if (NEXT(dir,1) == 'd') {
      NEXT(dir,1) = 'T';
    } else if (NEXT(dir,1) == 'e') {
      NEXT(dir,1) = 'k';
    } else if (NEXT(dir,1) == 'f') {
      NEXT(dir,1) = 'l';
    }

// We check if the player is hurted by teeth
    teethHurt();
// If the remaining moves counter is zero, we lose.
  if(remainingMoves == 0) {
    death = true;
    drawDeath();
    gb.sound.playCancel();
    return;
  }
    return;
  }

// If next box is a skeleton…
    if(NEXT(dir,1) == 'S') {
// … the player kicks it…
      heroKicks = true;
      gb.sound.playTick();
    {
// … and if the box after it is empty…
      if(NEXT(dir,2) == ' ') {
// … we move the skeleton to this next box.
        NEXT(dir,2) = 'S';
      }
    }
// We take off the skeleton from its previous location.
    if(NEXT(dir,1) == 'S') {
      NEXT(dir,1) = ' ';
    }
// We check if the player is hurted by teeth
    teethHurt();
// If the remaining moves counter is zero, we lose.
  if(remainingMoves == 0) {
    death = true;
    drawDeath();
    gb.sound.playCancel();
    return;
  }
    return;
    }
    
// If next box is empty…
      if(NEXT(dir,1) == ' ') {
        gb.sound.playTick();
// … we put a player to this next box…
        NEXT(dir,1) = '@';
// … and we take off the player from its previous location.
        previousBox();
// We update the player coordinates.
        rowPlayer = nr(dir,1);
        columnPlayer = nc(dir,1);
        return;
      }

// If next box is teeth…
      if(NEXT(dir,1) == 'T') {
        gb.sound.playTick();
// The backlights flash in red
        redFlash = 2;
//        gb.lights.fill(RED);
// … we put a player to this next box…
        NEXT(dir,1) = 'a';
// … and we take off the player from its previous location.
        previousBox();
// We update the player coordinates.
        rowPlayer = nr(dir,1);
        columnPlayer = nc(dir,1);
// The teeth hurt the player
        if(remainingMoves > 0) {
          remainingMoves = remainingMoves - 1;
        } else if(remainingMoves == 0) {
          death = true;
          drawDeath();
          gb.sound.playCancel();
          return;
        }
        return;
      }

// If next box is even number teeth…
      gb.sound.playTick();
      
      if(NEXT(dir,1) == 'k') {

// … we put a player to this next box…
        NEXT(dir,1) = 'b';
// … and we take off the player from its previous location.
        previousBox();
// We update the player coordinates.
        rowPlayer = nr(dir,1);
        columnPlayer = nc(dir,1);
// The teeth hurt the player
        if((remainingMoves > 0) && (evenNumber == true)) {
          remainingMoves = remainingMoves - 1;
// The backlights flash in red
          redFlash = 2;
//          gb.lights.fill(RED);
        } else if((remainingMoves == 0) && (evenNumber == true)) {
          death = true;
          drawDeath();
          gb.sound.playCancel();
          return;
        }
        return;
      }

// If next box is odd number teeth…
      gb.sound.playTick();
      
      if(NEXT(dir,1) == 'l') {
// … we put a player to this next box…
        NEXT(dir,1) = 'c';
// … and we take off the player from its previous location.
        previousBox();
// We update the player coordinates.
        rowPlayer = nr(dir,1);
        columnPlayer = nc(dir,1);
// The teeth hurt the player
        if((remainingMoves > 0) && (evenNumber == false)) {
          remainingMoves = remainingMoves - 1;
// The backlights flash in red
          redFlash = 2;
//          gb.lights.fill(RED);
        } else if((remainingMoves == 0) && (evenNumber == false)) {
          death = true;
          drawDeath();
          gb.sound.playCancel();
          return;
        }
        return;
      }
      
// If next box is key…
      gb.sound.playOK();
      if(NEXT(dir,1) == 'K') {
// … we put the player to the next box…
        NEXT(dir,1) = '@';
// … and we take off the player from its previous location.
        previousBox();
// We update the player coordinates.
        rowPlayer = nr(dir,1);
        columnPlayer = nc(dir,1);
// And we tell the game the player has the key.
        hasKey = true;
// Yellow flash with LEDs
        gb.lights.fill(YELLOW);
        return;
      }

// If next box is lock and we have key…
      gb.sound.playOK();
      if( (NEXT(dir,1) == 'L') && (hasKey == true) ) {
// … we put the player to the next box…
        NEXT(dir,1) = '@';
// … and we take off the player from its previous location.
        previousBox();
// We update the player coordinates.
        rowPlayer = nr(dir,1);
        columnPlayer = nc(dir,1);
// Yellow flash with LEDs
        gb.lights.fill(YELLOW);
        return;
      }
}

// We decide which sprite goes with which wall.
void updateWalls() {
  for (int row=1; row<(NB_ROWS_LEVELS-1); row++) {
    for (int column=1; column<(NB_COLUMNS_LEVELS-1); column++) {
      if(level[row-1][column] == 'M') {
        if(level[row][column+1] == 'M') {
          if(level[row+1][column] == 'M') {
            if(level[row][column-1] == 'M') {
              walls[row][column] = 'a';
            } else {
              walls[row][column] = 'b';
            }
          } else {
            if(level[row][column-1] == 'M') {
              walls[row][column] = 'c';
            } else {
              walls[row][column] = 'd';
            }
          }
        } else {
          if(level[row+1][column] == 'M') {
            if(level[row][column-1] == 'M') {
              walls[row][column] = 'e';
            } else {
              walls[row][column] = 'f';
            }
          } else {
            if(level[row][column-1] == 'M') {
              walls[row][column] = 'g';
            } else {
              walls[row][column] = 'h';
            }
          }
        }
      } else {
        if(level[row][column+1] == 'M') {
          if(level[row+1][column] == 'M') {
            if(level[row][column-1] == 'M') {
              walls[row][column] = 'i';
            } else {
              walls[row][column] = 'j';
            }
          } else {
            if(level[row][column-1] == 'M') {
              walls[row][column] = 'k';
            } else {
              walls[row][column] = 'l';
            }
          }
        } else {
          if(level[row+1][column] == 'M') {
            if(level[row][column-1] == 'M') {
              walls[row][column] = 'm';
            } else {
              walls[row][column] = 'n';
            }
          } else {
            if(level[row][column-1] == 'M') {
              walls[row][column] = 'o';
            } else {
              walls[row][column] = 'p';
            }
          }
        }
      }
    }
  }

// Set the border walls.
// Left line.
  for (int row=0; row<(NB_ROWS_LEVELS); row++) {
    if(level[row][1] == 'M') {
      walls[row][0] = 'a';
    } else {
      walls[row][0] = 'e';
    }
  }
// Right line.
  for (int row=0; row<(NB_ROWS_LEVELS); row++) {
    if(level[row][NB_COLUMNS_LEVELS - 2] == 'M') {
      walls[row][NB_COLUMNS_LEVELS - 1] = 'a';
    } else {
      walls[row][NB_COLUMNS_LEVELS - 1] = 'b';
    }
  }
// Top line.
  for (int column=0; column<(NB_COLUMNS_LEVELS); column++) {
    if(level[1][column] == 'M') {
      walls[0][column] = 'a';
    } else {
      walls[0][column] = 'c';
    }
  }
// Bottom line.
  for (int column=0; column<(NB_COLUMNS_LEVELS); column++) {
    if(level[NB_ROWS_LEVELS - 2][column] == 'M') {
      walls[NB_ROWS_LEVELS - 1][column] = 'a';
    } else {
      walls[NB_ROWS_LEVELS - 1][column] = 'i';
    }
  }
}

// We reset the level or go to the next one.
void changeLevel() {
// Go to next level or reset level if dead.
  if((death == false) && (resetLevel == false)) {
    levelNumber = levelNumber + 1;
  }
  resetLevel = false;
// Go back to level 1 if the last level is passed.
  if(levelNumber > TOTAL_LEVELS) {
//    levelNumber = 1;
// Go to end screen
    gamestate = 4;
  }

// We copy the selected constant level table to the variable level table.
  switch (levelNumber) {
    case 0:
    case 1:
      memcpy(level, level1, sizeof(level));
      rowPlayer = 2;
      columnPlayer = 7;
      remainingMoves = 23;
    break;
    case 2:
      memcpy(level, level2, sizeof(level));
      rowPlayer = 6;
      columnPlayer = 2;
      remainingMoves = 24;
    break;
    case 3:
      memcpy(level, level3, sizeof(level));
      rowPlayer = 4;
      columnPlayer = 9;
      remainingMoves = 32;
    break;
    case 4:
      memcpy(level, level4, sizeof(level));
      rowPlayer = 3;
      columnPlayer = 2;
      remainingMoves = 23;
    break;
    case 5:
      memcpy(level, level5, sizeof(level));
      rowPlayer = 4;
      columnPlayer = 2;
      remainingMoves = 23;
    break;
    case 6:
      memcpy(level, level6, sizeof(level));
      rowPlayer = 1;
      columnPlayer = 4;
      remainingMoves = 43;
    break;
    case 7:
      memcpy(level, level7, sizeof(level));
      rowPlayer = 6;
      columnPlayer = 8;
      remainingMoves = 32;
    break;
    case 8:
      memcpy(level, level8, sizeof(level));
      rowPlayer = 8;
      columnPlayer = 5;
      remainingMoves = 8;
    break;
    case 9:
      memcpy(level, level9, sizeof(level));
      rowPlayer = 7;
      columnPlayer = 2;
      remainingMoves = 33;
    break;
    case 10:
      memcpy(level, level10, sizeof(level));
      rowPlayer = 6;
      columnPlayer = 8;
      remainingMoves = 42;
    break;
    default:
    break;
  }

// Walls sprites function
  updateWalls();

// The player faces right.
  heroTurnsRight = true;

// We revive the player.
  death = false;

// The player has not the key
  hasKey = false;

// Set the even number for the moving teeth
  if((remainingMoves % 2) == 0) {
    evenNumber = true;
  } else {
    evenNumber = false;
  }
}

// We check if a button is pressed and do something.
void inputs() {
  if(gb.buttons.pressed(BUTTON_UP)) {
    moveTo(UP);
  }

  if(gb.buttons.pressed(BUTTON_DOWN)) {
    moveTo(DOWN);
  }

  if(gb.buttons.pressed(BUTTON_RIGHT)) {
    heroTurnsRight = true;
    moveTo(RIGHT);
  }

  if(gb.buttons.pressed(BUTTON_LEFT)) {
    heroTurnsRight = false;
    moveTo(LEFT);
  }

// If direction buttons are released,
// the player stops to kick.
  if((gb.buttons.released(BUTTON_UP)) || (gb.buttons.released(BUTTON_DOWN)) || (gb.buttons.released(BUTTON_RIGHT)) || (gb.buttons.released(BUTTON_LEFT))) {
    heroKicks = false;
  }

// If hero next to a demon girl, go to dialogue
  if(((NEXT(1,1) == 'D') || (NEXT(2,1) == 'D') || (NEXT(3,1) == 'D') || (NEXT(4,1) == 'D') ) && (clap == false)) {
    if(levelFinished == false) {
      gb.sound.playOK();
    }
    levelFinished = true;
  }

// If B button is pressed, reset the level
  if(gb.buttons.pressed(BUTTON_B)) {
    resetLevel = true;
    clap = true;
  }
  
}

// draw free RAM
/*
void drawFreeRam() {
  gb.display.setFontSize(1);
  gb.display.setColor(WHITE);
  gb.display.printf(2, 2, "RAM: %u", gb.getFreeRam());
//  gb.display.printf(2, 2, "%u", redFlash);
}
*/

// draw the demon girls in Hell dialogues
void drawBigDemon () {
  switch (levelNumber) {
    case 0:
      if((answered > 0) && (answered < 4)) {
        gb.display.drawImage(bigDemon*4 + 64, 0, theGreatFly, 32, 32);
      }
      if(answered > 4) {
        gb.display.drawImage(bigDemon*4 + 64, 0, heroRight, 32, 32);
      }
      break;
    case 1:
      gb.display.drawImage(bigDemon*4 + 64, 0, Pandemonica, 32, 32);
      break;
    case 2:
      gb.display.drawImage(bigDemon*4 + 64, 0, Modeus, 32, 32);
      break;
    case 3:
      gb.display.drawImage(bigDemon*4 + 32, 0, Cerberus, 32, 32);
      gb.display.drawImage(bigDemon*4 + 64, 0, Cerberus, 32, 32);
      gb.display.drawImage(bigDemon*4 + 96, 0, Cerberus, 32, 32);
      break;
    case 4:
      gb.display.drawImage(bigDemon*4 + 64, 0, Malina, 32, 32);
      break;
    case 5:
      gb.display.drawImage(bigDemon*4 + 64, 0, Zdrada, 32, 32);
      break;
    case 6:
      gb.display.drawImage(bigDemon*4 + 64, 0, Azazel, 32, 32);
      break;
    case 7:
      gb.display.drawImage(bigDemon*4 + 64, 0, Justice, 32, 32);
      break;
    case 8:
      gb.display.drawImage(bigDemon*4 + 64, 0, Lucifer, 32, 32);
      if(answered < 5) {
        gb.display.drawImage(bigDemon*4 + 32, 0, SkeletonStill, 32, 32);
        gb.display.drawImage(bigDemon*4 + 96, 0, SkeletonStill, -32, 32);
      } else {
        gb.display.drawImage(bigDemon*4 + 32, 0, SkeletonLove, 32, 32);
        gb.display.drawImage(bigDemon*4 + 96, 0, SkeletonLove, -32, 32);
      }
      break;
    case 9:
      gb.display.drawImage(bigDemon*4 + 64, 0, Judgement, 32, 32);
      break;
    case 10:
      gb.display.drawImage(bigDemon*4 + 64, 0, Beelzebub, 32, 32);
      break;
  }
}

void demonText() {
  gb.display.setColor(RED);
  gb.display.setCursor(0, 40);
  gb.display.setFont(font5x7);
  gb.display.setFontSize(1);

  switch (levelNumber) {

// the Great Fly
    case 0:
      switch (answered) {
        case 0:
          gb.display.setColor(GRAY);
          gb.display.setCursorX(3);
          gb.display.print("    You find yourself\n");
          gb.display.setCursorX(3);
          gb.display.print(" surrounded by the void.");
          break;
        case 1:
          gb.display.setCursorX(3);
          gb.display.print("  Greetings little one.\n Please don't mind me. It\n");
          gb.display.setCursorX(3);
          gb.display.print("   is just I, good old\n        Beelzebub.");
          break;
        case 2:
          gb.display.print(" Story of the demon girls\n");
          gb.display.setCursorX(3);
          gb.display.print("  again? Interesting...");
          break;
        case 3:
          gb.display.print("  Do you, by any chance,\n     need a narrator?");
          break;
        case 4:
          gb.display.print(" Why please, allow me. It\n");
          gb.display.setCursorX(3);
          gb.display.print("   will be a pleasure.");
          break;
        case 5:
          gb.display.print("You woke up one day with a\ndream. Harem full of demon\n          girls.");
          break;
        case 6:
          gb.display.setCursorX(3);
          gb.display.print(" It was, however, not an\n");
          gb.display.setCursorX(3);
          gb.display.print("easy dream to achieve. It\n");
          gb.display.setCursorX(3);
          gb.display.print("could cost you your life.");
          break;
      }
      if(answered > 6) {
        gb.display.setColor(WHITE);
        gb.display.setCursorX(3);
        gb.display.print("  \"When demon girls are\ninvolved, no price is high\n         enough.\"");
        gb.display.setColor(RED);
        gb.display.setCursorX(3);
        gb.display.print("\n\nYou said, as you ventured\n");
        gb.display.setCursorX(3);
        gb.display.print("      down to hell.");
        if(gb.buttons.pressed(BUTTON_A)) {
          clap = true;
        }
      }
      break;

// Pandemonica
    case 1:
    if(answered == 0) {
      gb.display.print("Name's Pandemonica. Hell's\n");
      gb.display.setCursorX(3);
      gb.display.print("Customer Service. How may\n       I serve you?\n\n\n");
    } else {
      if(goodAnswer == true) {
        gb.display.print(" You have your own house?\n  You don't live by your\n  parents? That's a good\n          point.");
      } else {
        gb.display.setCursorX(3);
        gb.display.print("No way! I only date tough\n");
        gb.display.setCursorX(3);
        gb.display.print("  guys. Go back to your\n");
        gb.display.setCursorX(3);
        gb.display.print("     little flowers.");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.setCursorX(3);
      gb.display.print(" We can figure something\n     out at my place.\n\n");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.setCursorX(3);
      gb.display.print("  Maybe I can serve YOU\n         instead?");
    }
    goodAnswer = topAnswer?true:false;
    break;

// Modeus
    case 2:
    if(answered == 0) {
      gb.display.print("     You and me. Now.");
    } else {
      if(goodAnswer == true) {
        gb.display.print("You take the black pieces.\n I take the white ones. I\n");
        gb.display.setCursorX(3);
        gb.display.print(" feel this chess game is\n");
        gb.display.setCursorX(3);
        gb.display.print("    going to be wild!");
      } else {
        gb.display.print("Other girls? I am the only\n");
        gb.display.setCursorX(3);
        gb.display.print("    one, remember it!");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.print("\n\n\n\n\n Deal. No question asked.\n\n\n");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.setCursorX(3);
      gb.display.print(" No time. Busy gathering\n          girls.");
    }
    goodAnswer = topAnswer?true:false;
    break;

// Cerberus
    case 3:
    if(answered == 0) {
      gb.display.setCursorX(3);
      gb.display.print("  Are you human? A real\n  human? Please, take us\n");
      gb.display.setCursorX(3);
      gb.display.print("        with you.");
    } else {
      if(goodAnswer == true) {
        gb.display.print("Great! We love to talk. Do\n");
        gb.display.setCursorX(3);
        gb.display.print("  you have an unlimited\n      phone package?");
      } else {
        gb.display.setCursorX(3);
        gb.display.print(" Don't be in a hurry. We\n");
        gb.display.setCursorX(3);
        gb.display.print(" have to know each other\n");
        gb.display.setCursorX(3);
        gb.display.print("         before.");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.print("\n\n\n Deal. No question asked.\n\n\n");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.setCursorX(3);
      gb.display.print("This is getting too easy.\n");
      gb.display.setCursorX(3);
      gb.display.print("    I have questions.");
    }
    goodAnswer = topAnswer?false:true;
    break;

// Malina
    case 4:
    if(answered == 0) {
      gb.display.setCursorX(3);
      gb.display.print("  Great, more braindead\n");
      gb.display.setCursorX(3);
      gb.display.print("idiots... Never seen your\nugly face before. What are\n");
      gb.display.setCursorX(3);
      gb.display.print("     you playing at?");
    } else {
      if(goodAnswer == true) {
        gb.display.setCursorX(3);
        gb.display.print("Like what... video games?\n");
        gb.display.setCursorX(3);
        gb.display.print("Sure, why not. As long as\n  you're okay with first\n     person shooters.");
      } else {
        gb.display.print("Fantastic. Just my luck to\n  find another masochist\n          creep.");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.print("\n\nI'd sure love to play with\n           you.");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.print("\n\nThis is delicious. Please,\n");
      gb.display.setCursorX(3);
      gb.display.print("     insult me more.");
    }
    goodAnswer = topAnswer?true:false;
    break;

// Zdrada
    case 5:
    if(answered == 0) {
      gb.display.setCursorX(3);
      gb.display.print("Yo. I've heard about your\n      harem. I'm in.");
    } else {
      if(goodAnswer == true) {
        gb.display.print("Really? That's my favorite\n");
        gb.display.setCursorX(3);
        gb.display.print("game category! Let's turn\n          it ON!");
      } else {
        gb.display.setCursorX(3);
        gb.display.print("Do you mean I am not good\n  enough for you? That's\n        unberable!");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.print("\n\n\n\n  Wait. I have a feeling\n");
      gb.display.setCursorX(3);
      gb.display.print("     I'll regret it.\n\n");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.setCursorX(3);
      gb.display.print(" It's not really a harem\nanymore. We just play FPS.");
    }
    goodAnswer = topAnswer?false:true;
    break;

// Azazel
    case 6:
    if(answered == 0) {
      gb.display.setColor(LIGHTBLUE);
      gb.display.setCursorX(3);
      gb.display.print("Oh my heavens! What would\na living human be doing in\n");
      gb.display.setCursorX(3);
      gb.display.print("   hell? Most unusual.\n\n\n");
    } else {
      gb.display.setColor(LIGHTBLUE);
      if(goodAnswer == true) {
        gb.display.print("Oh, you too? Let me guess,\n thesis on Modern Sin? Or\n   is it Demonology? We\n");
        gb.display.setCursorX(3);
        gb.display.print("   should join forces.");
      } else {
        gb.display.setCursorX(3);
        gb.display.print(" You could search in the\n");
        gb.display.setCursorX(3);
        gb.display.print("source code. But cheating\n  is really getting away\n     from perfection.");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.setCursorX(3);
      gb.display.print("   Looking for demons.");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.print("\n\n\n Looking for cheat codes.");
    }
    goodAnswer = topAnswer?true:false;
    break;

// Justice
    case 7:
    if(answered == 0) {
      gb.display.print("  Yo, did you just solve\n");
      gb.display.setCursorX(3);
      gb.display.print("   that puzzle? That's\n         awesome!");
    } else {
      if(goodAnswer == true) {
        gb.display.setCursorX(3);
        gb.display.print("You don't have to ask me.\n");
        gb.display.setCursorX(3);
        gb.display.print(" I'd never miss a party.");
      } else {
        gb.display.print("You failed the gaming law!\n        How petty!");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.print("\n\n\n It took some work. Wanna\n      join my harem?\n\n");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.setCursorX(3);
      gb.display.print("I just used a cheat code.\n   Wanna join my harem?");
    }
    goodAnswer = topAnswer?true:false;
    break;

// Lucifer
    case 8:
    if(answered == 0) {
      gb.display.setCursorX(3);
      gb.display.print(" We meet at last. You've\n");
      gb.display.setCursorX(3);
      gb.display.print("proved yourself worthy by\n  passing all my trials.");
    }
    if(answered == 1) {
      gb.display.print("Pledge your soul to me and\n");
      gb.display.setCursorX(3);
      gb.display.print("  I'll make you my most\n     treasured slave.\n\n\n");

      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.setCursorX(3);
      gb.display.print("      Yes my queen!\n\n\n");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.setCursorX(3);
      gb.display.print(" No, thanks. But you can\n      join my harem.");
    }
    if(answered == 2) {
      goodAnswer = topAnswer?false:true;
       if(goodAnswer == false) {
        gb.display.print("   Eager little soul...");
      } else {
        answered = 3;
        topAnswer = true;
      }
    }
    if(answered == 3) {
      gb.display.print("  What are you trying to\n");
      gb.display.setCursorX(3);
      gb.display.print("accomplish? You think you\ncan enslave demons to your\n");
      gb.display.setCursorX(3);
      gb.display.print("          will?");
       
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.print("\n\nCall me Badger. An read my\n");
      gb.display.setCursorX(3);
      gb.display.print(" book to know the Truth.");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.print("\n\n I can offer fruit juices\n");
      gb.display.setCursorX(3);
      gb.display.print(" and chocolate pancakes.");
    }
    if(answered == 4) {
      goodAnswer = topAnswer?false:true;
      if(goodAnswer == true) {
        gb.display.setCursorX(3);
        gb.display.print(" Really? Is that it? You\n");
        gb.display.setCursorX(3);
        gb.display.print("come here, and try to buy\n  me over with pancakes?");
      } else {
        gb.display.setCursorX(3);
        gb.display.print(" You really think I have\n");
        gb.display.setCursorX(3);
        gb.display.print("   time to read books,\n running hell and dealing\n");
        gb.display.setCursorX(3);
        gb.display.print("   with all this mess?");
      }
    }
    if(answered > 4) {
      gb.display.print("  You're lucky, I have a\n");
      gb.display.setCursorX(3);
      gb.display.print("   thing for pancakes.");
    }
    break;

// Judgement
    case 9:
    if(answered == 0) {
      gb.display.print("  Hello trespasser. Make\n yourself at home. You're\n");
      gb.display.setCursorX(3);
      gb.display.print(" just in time to test my\n  new suffering machine.\n\n");
    } else {
      if(goodAnswer == true) {
        gb.display.setCursorX(3);
        gb.display.print(" Oh, you like it? Do you\n");
        gb.display.setCursorX(3);
        gb.display.print("  want to help me build\n    more in my fablab?");
      } else {
        gb.display.print(" Are you kidding me? Only\nhumans deserve to feel the\n");
        gb.display.setCursorX(3);
        gb.display.print("    unrelenting pain.");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.setCursorX(3);
      gb.display.print("   Did you built it by\n");
      gb.display.setCursorX(3);
      gb.display.print("yourself? You're a maker?");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.print("\n\n    Did you test it on\n");
      gb.display.setCursorX(3);
      gb.display.print("     animals before?");
    }
    goodAnswer = topAnswer?true:false;
    break;

// Beelzebub (human shape)
    case 10:
    if(answered == 0) {
      gb.display.print("Are you going to follow me\n to the farest? And leave\n");
      gb.display.setCursorX(3);
      gb.display.print(" the other girls behind?");
    } else {
      if(goodAnswer == true) {
        gb.display.setCursorX(3);
         gb.display.print("Great. I like people with\n    high expectations.");
      } else {
        gb.display.setCursorX(3);
        gb.display.print("Who will make us food and\n");
        gb.display.setCursorX(3);
        gb.display.print("bring some champagne? I'm\n");
        gb.display.setCursorX(3);
        gb.display.print(" expecting boring times.");
      }
    }
    if(answered == 0) {
      gb.display.setColor(topAnswer?WHITE:GRAY);
      gb.display.print("\n\n\n     Only you and me.");
      gb.display.setColor(topAnswer?GRAY:WHITE);
      gb.display.print("\n\n\n I stopped counting but I\n  need a full set harem.");
    }
    goodAnswer = topAnswer?false:true;
    break;
  }

// draw SUCCESS (not for Lucifer)
  if((answered > 0) && (goodAnswer == true) && (levelNumber != 8) && (levelNumber != 0)) {
    gb.display.drawImage(50, 100, SUCCESS);
    if(clap == false) {
      gb.lights.drawImage(0, 0, rainbow);
    }
    if((answered > 1) && (levelNumber != 8)) {
      clap = true;
    }
  }

// draw SUCCESS for Lucifer
  if(levelNumber == 8) {
    if((answered > 4) && (goodAnswer == true)) {
      gb.display.drawImage(50, 100, SUCCESS);
      if(clap == false) {
        gb.lights.drawImage(0, 0, rainbow);
      }
    }
    if(answered > 5) {
      clap = true;
    }
  }
}

void docTeaches() {
  if(gb.buttons.repeat(BUTTON_A, 0)) {
    if(whatTheFoxSays == 0) {
      if(gb.buttons.pressed(BUTTON_UP)) {
        whatTheFoxSays = whatTheFoxSays + 1;
      } else if((gb.buttons.pressed(BUTTON_DOWN)) || (gb.buttons.pressed(BUTTON_LEFT)) || (gb.buttons.pressed(BUTTON_RIGHT))) {
        whatTheFoxSays = 0;
      }
    } else if(whatTheFoxSays == 1) {
      if(gb.buttons.pressed(BUTTON_DOWN)) {
        whatTheFoxSays = whatTheFoxSays + 1;
      } else if((gb.buttons.pressed(BUTTON_UP)) || (gb.buttons.pressed(BUTTON_LEFT)) || (gb.buttons.pressed(BUTTON_RIGHT))) {
        whatTheFoxSays = 0;
      }
    } else if(whatTheFoxSays == 2) {
      if(gb.buttons.pressed(BUTTON_LEFT)) {
        whatTheFoxSays = whatTheFoxSays + 1;
      } else if((gb.buttons.pressed(BUTTON_DOWN)) || (gb.buttons.pressed(BUTTON_UP)) || (gb.buttons.pressed(BUTTON_RIGHT))) {
        whatTheFoxSays = 0;
      }
    } else if(whatTheFoxSays == 3) {
      if(gb.buttons.pressed(BUTTON_RIGHT)) {
        whatTheFoxSays = whatTheFoxSays + 1;
      } else if((gb.buttons.pressed(BUTTON_DOWN)) || (gb.buttons.pressed(BUTTON_LEFT)) || (gb.buttons.pressed(BUTTON_UP))) {
        whatTheFoxSays = 0;
      }
    }
  }

  if(whatTheFoxSays == 4) {
    levelFinished = true;
    whatTheFoxSays = false;
  }
}

// There are three secret letters to find in the game
// Level 4: "B", level 5: "A" and level 6: "D"
void secretLetters() {
  if((levelNumber == 4) && (hasSecretB == false)) {
    gb.display.drawImage(8*16 - 8, 6*16 - 16, secretB);
    if((columnPlayer == 8) && (rowPlayer == 6)) {
      hasSecretB = true;
      gb.lights.fill(WHITE);
    }
  }
  
  if((levelNumber == 5) && (hasSecretA == false)) {
    gb.display.drawImage(6*16 - 8, 3*16 - 16, secretA);
    if((columnPlayer == 6) && (rowPlayer == 3)) {
      hasSecretA = true;
      gb.lights.fill(WHITE);
    }
  }
  
  if((levelNumber == 6) && (hasSecretD == false)) {
    gb.display.drawImage(7*16 - 8, 7*16 - 16, secretD);
    if((columnPlayer == 7) && (rowPlayer == 7)) {
      hasSecretD = true;
      gb.lights.fill(WHITE);
    }
  } 
}

void HellLevels() {
  drawGraphics();

// Test draw the three secret letters "BAD"
/*
  gb.display.drawImage(4*16 - 8, 3*16 - 16, secretB);
  gb.display.drawImage(5*16 - 8, 3*16 - 16, secretA);
  gb.display.drawImage(6*16 - 8, 3*16 - 16, secretD);
*/
  
// We fill the back lights in RED if teeth hurt.
  if(redFlash > 0) {
    redFlash = redFlash - 1;
  }

  if(death == true){
    drawDeath();
  }
  
  if(clap == true){
     drawClap();
  }

//  drawFreeRam();

  if((clap == false) && (death == false)) {
    inputs();
  }

  if(levelFinished == true) {
    goDialogues = goDialogues + 1;
  }

  if(goDialogues > 4) {
    gamestate = 2;
    goDialogues = 0;
    levelFinished = false;
    topAnswer = true;
  }

  docTeaches();

}

void HellDialogues() {
  if(!((levelNumber == 0) && ((answered == 0) || (answered == 4)))) {
    gb.display.setColor(PURPLE);
    gb.display.fillRect(0, bigDemon, 160, 32 - bigDemon*2);
  }

  if(bigDemon > 0) {
    bigDemon = bigDemon - 1;
  } else {
    bigDemon = 0;
    demonText();
  }
      
  drawBigDemon();

  if(levelNumber != 0) {
  if(levelNumber != 8) {
    if(answered == 0) {
      if(gb.buttons.pressed(BUTTON_DOWN)) {
        topAnswer = false;
      }
      if(gb.buttons.pressed(BUTTON_UP)) {
        topAnswer = true;
      }
    } else {
      if((gb.buttons.pressed(BUTTON_A)) && (goodAnswer == false)) {
        gamestate = 3;
      }
    }
  } else {
    if((answered == 1) || (answered == 3)) {
      if(gb.buttons.pressed(BUTTON_DOWN)) {
        topAnswer = false;
      }
      if(gb.buttons.pressed(BUTTON_UP)) {
        topAnswer = true;
      }
    } else if((answered == 2) || (answered == 4)) {
      if((gb.buttons.pressed(BUTTON_A)) && (goodAnswer == false)) {
      gamestate = 3;
      }
    }
  }
  }

  if(gb.buttons.pressed(BUTTON_A)) {
// The sounds don't work fine but I don't know why.
/*    
    if((answered == 0) && (levelNumber != 0)) {
      if(goodAnswer == true) {
        gb.sound.playOK();
      } else {
        gb.sound.playCancel();
      }
    }
*/
    answered = answered + 1;
    if((levelNumber == 0) && ((answered == 1) || (answered == 5))) {
      bigDemon = 8;  
    }
  }
  
  if(clap == true){
    drawClap();
  }
}

void drawBadEnd() {
  gb.display.drawImage(17+(random(0,3)), 53+(random(0,3)), BAD_END, 124, 20);
    
  if(gb.buttons.pressed(BUTTON_A) && (clap == false)) {
    clap = true;
    resetLevel = true;
  }

  if(clap == true){
    drawClap();
  }
}

void intro() {
  if(((anim == true) || (logoReduces == false)) && (logoTrouble < 101)) {
    gb.display.drawImage(56+xLogo, 44+yLogo, logoBadger, 48, 40);
  }

  if((frames%2 == 0) && (anim == true)) {
    if(logoSide == true) {
      logoSide = false;
    } else {
      logoSide = true;
    }

    xLogo = random(-logoTrouble, logoTrouble);
    yLogo = random(-logoTrouble, logoTrouble);
  }

  if(anim == true) {
    if(logoReduces==true) {
      logoTrouble=logoTrouble-2;
    } else {
      logoTrouble=logoTrouble+2;
    }
  }

  frames = frames + 1;

  if(frames > 29) {
    frames = 0;
  }

  if(logoTrouble < 1) {
    logoReduces = false;
    anim = false;
    logoTrouble = 0;
    xLogo = 0;
    yLogo = 0;
  }

  if(logoTrouble > 120) {
    logoReduces = true;
    anim = false;
    gamestate = 2;
  }

  if((gb.buttons.pressed(BUTTON_A)) && (logoTrouble == 0)) {
    anim = true;
    beforePress = 0;
    gb.sound.playOK();
  }

  if(logoTrouble == 0) {
    beforePress = beforePress + 1;
    if(beforePress > 29) {
      beforePress = 0;
    }
    gb.display.setFont(font5x7);
    gb.display.setCursor(26, 103);
    gb.display.setColor(RED);
    if(beforePress > 14) {
      gb.display.print("PRESS [A] TO START");
    }
  }
}

void drawEnd() {
  gb.display.setFont(font5x7);
  gb.display.setFontSize(1);
  gb.display.setColor(RED);
  gb.display.print("\n\n\n");
  gb.display.print("      DEMON GIRLS by\n\n");
  gb.display.setColor(WHITE);
  gb.display.print("       Juice Lizard\n\n\n");
  gb.display.setColor(RED);
  gb.display.print("       HELLTAKER by\n\n");
  gb.display.setColor(WHITE);
  gb.display.print("      Lukasz Piskorz\n\n\n");
  gb.display.setColor(GRAY);
  gb.display.setCursorX(3);
  gb.display.print("   www.juicelizard.com");
}

void loop() {
  while(!gb.update());

  gb.display.clear();
  gb.lights.clear();

  switch (gamestate) {
// Logo Badger intro
    case 0:
      intro();
      break;
// Hell levels
    case 1:
      HellLevels();
      break;

// Hell dialogues
    case 2:
      HellDialogues();
      break;

// BAD END
    case 3:
      drawBadEnd();
    break;

// the end (WIP)
    case 4:
      drawEnd();
    break;
  }
}
