#pragma once

void drawPawnStats(Pawn & pawn, bool healthPrintEffect)
{
    drawTextBox(0, 1, 52, 41, WHITE);
  
  if (pawn.zodiac != Zodiac::None)
  {
    tinyfont.print(getName(pawn.species));

    tinyfont.setCursor(1, 7);
    tinyfont.print(getType(pawn.type));

    tinyfont.setCursor(1, 12);
    tinyfont.print(getZodiac(pawn.zodiac));

    tinyfont.setCursor(1, 17);
    tinyfont.print(F("LV"));
    tinyfont.print(pawn.level);

    tinyfont.setCursor(1, 22);
    tinyfont.print(F("XP"));
    determineZeroPrint(pawn.experience);
    tinyfont.print(pawn.experience);
    tinyfont.print(F("/"));
    uint8_t maxExperience = (pawn.level == 9) ? 15 : ((pawn.level - 1) * 2) + 1;
    determineZeroPrint(maxExperience);
    tinyfont.print(maxExperience);

    tinyfont.setCursor(1, 27);
    tinyfont.print(F("EN"));
    if ((gameState == GameState::Box) && (healthPrintEffect) && (pawn.energy < pawn.maxEnergy))
    {

      if (arduboy.everyXFrames(5))
        pawn.draw = (pawn.draw) ? false : true;

      if (pawn.draw)
      {
        pawn.energyPrint = (((pawn.maxEnergy / 2) + pawn.energy) > pawn.maxEnergy) ? pawn.maxEnergy : (pawn.maxEnergy / 2) + pawn.energy;
        determineZeroPrint(pawn.energyPrint);
        tinyfont.print(pawn.energyPrint);
      } else tinyfont.print(F("  "));

    } else
    {
      determineZeroPrint(pawn.energy);
      tinyfont.print(pawn.energy);
    }
    tinyfont.print(F("/"));
    determineZeroPrint(pawn.maxEnergy);
    tinyfont.print(pawn.maxEnergy);
    
    tinyfont.setCursor(9, 37);
    tinyfont.print(pawn.actionCost);
    arduboy.drawBitmap( 1, 33, move, 8, 8, BLACK);
    
    tinyfont.setCursor(23, 32);
    determineZeroPrint(pawn.power + 1);
    tinyfont.print(pawn.power + 1);
    tinyfont.setCursor(23, 37);
    tinyfont.print(pawn.actionCost + 1);
    arduboy.drawBitmap( 15, 33, hit, 8, 8, BLACK);

    tinyfont.setCursor(42, 32);
    if (((pawn.specialAttack == SpecialAttack::Shockwave) || (pawn.specialAttack == SpecialAttack::Blast) || (pawn.specialAttack == SpecialAttack::Strike)) && (pawn.species != Species::Trikurn))
    {
      determineZeroPrint(calculateDamage(pawn, pawn));
      tinyfont.print(calculateDamage(pawn, pawn));
    }
    tinyfont.setCursor(42, 37);
    tinyfont.print(pawn.actionCost + 2);
    uint8_t specialAttackIndex = static_cast <uint8_t> (pawn.specialAttack);
    if (pawn.species == Species::Trikurn)
      arduboy.drawBitmap( 34, 33, questionMark, 8, 8, BLACK);
      else arduboy.drawBitmap( 34, 33, specialAttackSprite[specialAttackIndex], 8, 8, BLACK);
  }
}