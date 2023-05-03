/*   
//By Revlis, released April 12th, 2023

   Copyright (C) 2023 Revlis

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

  Credits
  @Revlis
  @Pharap
*/

#include <Arduboy2.h>
#include <Tinyfont.h>
#include <EEPROM.h>

Arduboy2Base arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

#include "gamestate.h"

void setup() {
  // put your setup code here, to run once:
  arduboy.beginDoFirst();
  arduboy.setFrameDuration(20);
  arduboy.initRandomSeed();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!arduboy.nextFrame())
    return;
  arduboy.clear();
  arduboy.pollButtons();
  updateGameState();
  arduboy.display();
}
