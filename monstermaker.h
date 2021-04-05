#ifndef MONSTERMAKER_H
#define MONSTERMAKER_H

#include <bits/stdc++.h>

#include <string>
#include <vector>

class Dice{
  public:
  int base;     // base value 
  int num_dice; // number of dice to roll 
  int sides;    // how many sides that dice has 
};

class monsterObject{
  public:
  std::string symbol;
  std::vector <int> m_color;
  Dice speed;
  std::vector<int> abil;
  Dice hitpoint;
  Dice damage;
  std::string name;
  std::string descript;
  int RRTY;
};

void readDescript();
void createMonster(int index, std::string stats[]);
std::string removeColors(std::string buffer,std::string color, int bufferIndex);

void ability(int index, std::string stats[]);


#endif
