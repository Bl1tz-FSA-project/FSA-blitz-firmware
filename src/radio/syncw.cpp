#include<Arduino.h>
#include "hardware.h"
#include<vector>

struct Sword
{
  int word;
  String output;
};

Sword simple = {0x00, "UNKNWN"};

//simple.word = 0x00;
//simple.output = "UNKNWN";

std::vector<Sword> words;
//add words!
void drawSync(int detected_word)
{
  for(int i = 0; i < words.size(); i++)
  {
    if(detected_word == words[i].word)
    {
      //output words[i].output with words[i].word
      break;
    }
  }
  //output simple.output with simple.word
}
