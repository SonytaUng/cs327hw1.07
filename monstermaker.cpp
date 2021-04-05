#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <ncurses.h>
#include <algorithm>

#include "monstermaker.h"

int print = 0;
int parse = 0;

monsterObject monsterTemplates[16];
   
std::string truncate(std::string line){
    return line.substr(line.find(" ")+1, line.length());
}

void readDescript(){
  
  int index=0;
  int count;
  std::string stats[9];
  std::string out;
  std::string NAME, COLOR, SYMB,DESC,SPEED,DAM,HP,ABIL,RRTY;
  std::ifstream infile("monster_desc.txt");
  while(getline(infile,out)){
    if(out.find("RLG327") != std::string::npos){
      continue;
    }
    if(out.find("BEGIN") != std::string::npos){
      count++;
      print = 0;
    }
    if(out.find("NAME") != std::string::npos){
      NAME = truncate(out);
      stats[0] = NAME;
    }
    if(out.find("SYMB") != std::string::npos){
      SYMB = truncate(out);
      stats[1] = SYMB;
    }
    if(out.find("COLOR") != std::string::npos){
      COLOR = truncate(out);
      stats[2] = COLOR;
    }
    if(out.find("DESC") != std::string::npos){
      getline(infile, out);
      while(out.compare(".") != 0){
        if(out.find("\0") != std::string::npos){
          DESC += "\n";
        }
        DESC += out;
        getline(infile, out);
      }
      stats[3] = DESC;
      DESC="";
     }
    if(out.find("SPEED") != std::string::npos){
      SPEED = truncate(out);
      stats[4] = SPEED;
    }
    if(out.find("DAM") != std::string::npos){
      DAM = truncate(out);
      stats[5] = DAM;
    }
    if(out.find("HP") != std::string::npos){
      HP = truncate(out);
      stats[6] = HP;
    }
    if(out.find("ABIL") != std::string::npos){
      ABIL = truncate(out);
      if(ABIL == "SMART"){
        monsterTemplates[count].abil.push_back(1);
      }
      if(ABIL == "TELE"){
       monsterTemplates[count].abil.push_back(2);
      }
      if(ABIL == "TUNNEL"){
        monsterTemplates[count].abil.push_back(4);
      }
      if(ABIL == "ERRACTIC"){
        monsterTemplates[count].abil.push_back(8);
      }
      if(ABIL == "PASS"){
        monsterTemplates[count].abil.push_back(16);
      }
      if(ABIL == "PICKUP"){
        monsterTemplates[count].abil.push_back(32);
      }
      if(ABIL == "DESTROY"){
        monsterTemplates[count].abil.push_back(64);
      }
      if(ABIL == "UNIQ"){
        monsterTemplates[count].abil.push_back(128);
      }
      if(ABIL == "BOSS"){
       monsterTemplates[count].abil.push_back(256);
      }    
      stats[7] = ABIL;
    }
    if(out.find("RRTY") != std::string::npos){
      RRTY = truncate(out);
      stats[8] = RRTY;
    }
    if(stats[8].length() > 0 && print == 0){
      createMonster(index, stats);
      ability(index,stats);
      index++;
     stats[0] = "";
     stats[1] = "";
     stats[2] = "";
     stats[3] = "";
     stats[4] = "";
     stats[5] = "";
     stats[6] = "";
     stats[7] = "";
     stats[8] = ""; 
  }
}
     stats[0] = NAME;
     stats[1] = SYMB;
     stats[2] = COLOR;
     stats[3] = DESC;
     stats[4] = SPEED;
     stats[5] = DAM;
     stats[6] = HP;
     stats[7] = ABIL;
     stats[8] = RRTY; 

  infile.close();
}
void ability(int index, std::string stats[]){

 
  int num =0;
  
  parse = 0;
  std::string compare;
  for(int i =0; i < 9; i++){
    compare = stats[7];
    if(stats[7].length() <= 0){ // short circut 
      break;
    }
    switch(i){
      case 0: stats[7] = removeColors(stats[7], "SMART" , parse);
      num =1;
        break;
      case 1: stats[7] = removeColors(stats[7], "TELE" , parse);
      num = 2;
        break;
      case 2: stats[7] = removeColors(stats[7], "TUNNEL" , parse);
      num = 4;
        break;
      case 3: stats[7] = removeColors(stats[7], "ERRACTIC" , parse);
      num = 8;
        break;
      case 4: stats[7] = removeColors(stats[7], "BOSS" , parse);
       num = 256;
        break;
      case 5: stats[7] = removeColors(stats[7], "UNIQ" , parse);
      num = 128;
      
        break;
      case 6: stats[7] = removeColors(stats[7], "DESTROY" , parse);
      num = 64;
       
        break;
      case 7: stats[7] = removeColors(stats[7], "PICKUP" , parse);
      num = 32;
      
        break;
        case 8: stats[7] = removeColors(stats[7], "PASS" , parse);
        num = 16;
        break;
    }
    if(compare != stats[7]){
      monsterTemplates[index].abil.push_back(num);
    }
  }     
}

/** createMonster assumes that the array passed in has values that are non 
 *  NULL. 
 *  createMonster populates values of a monsterObject, given the index in 
 *  which it should reside. 
 */
void createMonster(int index, std::string stats[]){
  monsterTemplates[index].name = stats[0];
  monsterTemplates[index].symbol = stats[1];
  
  parse = 0;
  std::string compare;
  for(int i =0; i < 8; i++){
    compare = stats[2];
    if(stats[2].length() <= 0){ // short circut 
      break;
    }
    switch(i){
      case 0: stats[2] = removeColors(stats[2], "BLACK" , parse);
        break;
      case 1: stats[2] = removeColors(stats[2], "RED" , parse);
        break;
      case 2: stats[2] = removeColors(stats[2], "GREEN" , parse);
        break;
      case 3: stats[2] = removeColors(stats[2], "YELLOW" , parse);
        break;
      case 4: stats[2] = removeColors(stats[2], "BLUE" , parse);
        break;
      case 5: stats[2] = removeColors(stats[2], "MAGENTA" , parse);
        break;
      case 6: stats[2] = removeColors(stats[2], "CYAN" , parse); 
        break;
      case 7: stats[2] = removeColors(stats[2], "WHITE" , parse);
        break;
    }
    if(compare != stats[2]){
      monsterTemplates[index].m_color.push_back(i);
    }
  }
  std::cout << "\n";
 

  monsterTemplates[index].descript = stats[3];
  monsterTemplates[index].descript += "\n";
  monsterTemplates[index].speed.base = stats[4].at(0);
  monsterTemplates[index].speed.num_dice = stats[4].at(2);
  monsterTemplates[index].speed.sides = stats[4].at(4);
  monsterTemplates[index].damage.base = stats[5].at(0);
  monsterTemplates[index].damage.num_dice = stats[5].at(2);
  monsterTemplates[index].damage.sides = stats[5].at(4);
  monsterTemplates[index].hitpoint.base = stats[6].at(0);
  monsterTemplates[index].hitpoint.num_dice = stats[6].at(2);
  monsterTemplates[index].hitpoint.sides = stats[6].at(4);
  monsterTemplates[index].RRTY = std::stoi(stats[8]);

  std:: cout << monsterTemplates[index].name + "\n";
    for(int x : monsterTemplates[index].m_color){
      switch(x){
        case 0: std::cout << "BLACK ";
          break;
        case 1: std::cout << "RED ";
          break;
        case 2: std::cout << "GREEN ";
          break;
        case 3: std::cout << "YELLOW ";
          break;
        case 4: std::cout << "BLUE ";
          break;
        case 5: std::cout << "MAGENTA ";
          break;
        case 6: std::cout << "CYAN ";
          break;
        case 7: std::cout << "WHITE ";
          break;
      }
  }
  std::cout<< "\n";
  std:: cout << monsterTemplates[index].symbol + "\n";
  std:: cout << monsterTemplates[index].descript;
  std:: cout << stats[4] + "\n";
  std:: cout << stats[5] + "\n";
  std:: cout << stats[6] + "\n";
  std::cout<<stats[7];

  std:: cout << "\n";
  std:: cout << stats[8];
  std:: cout << "\n";
  print = 1;
}


/** removeColors takes the buffer string and parses it for the color string using 
 *  bufferIndex to keep track of how many times the given buffer has been parsed. 
 */
std::string removeColors(std::string buffer, std::string color, int bufferIndex){
   parse = bufferIndex;
   while(buffer.length() > buffer.length()-color.length()){
    if(buffer.find(color) != std::string::npos){ // if color is in string
       if(buffer.length() > color.length() && parse > 0){ // if the string is longer than color and isnt the first parse
         buffer = buffer.substr(1);
       }
       buffer = buffer.substr(color.length());
       parse++;                                // increment parse, so we know that this isnt our first parse 

    }
    else{
      break;
    }
  }
  if(buffer.length() == 1 ){
    buffer.resize(0);
  }
  return buffer;
}
