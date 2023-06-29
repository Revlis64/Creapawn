#pragma once

void renderVictory()
{
  for (uint8_t index = 0; index < 3; ++index)
  {
    uint8_t maxExperience = (pawn[index].level < 9) ? (2 * (pawn[index].level - 1)) + 1 : 15;
    if (pawn[index].zodiac != Zodiac::None)
    {
      drawPawn(pawn[index].species, 0, index * 16, BLACK, Direction::Right);

      tinyfont.setTextColor(WHITE);
      tinyfont.setCursor(17, index * 16);
      tinyfont.print("LV");
      tinyfont.print(pawn[index].level);
      tinyfont.setCursor(17, 5 + (index * 16));
      tinyfont.print("XP");
      determineZeroPrint(pawn[index].experience);
      tinyfont.print(pawn[index].experience);
      tinyfont.print("/");
      determineZeroPrint(maxExperience);
      tinyfont.print(maxExperience);

      if (pawn[index].energy > 0)
        switch (postBattleScreenState)
        {
          case 0:
          {
            tinyfont.print(" +");
            if (pawn[index].level < 9)
              tinyfont.print(determineExperienceGain(index));
              else tinyfont.print(F("0"));
            break;
          }
          case 1:
          {
            if (levelUpConfirm[index])
              tinyfont.print(" LEVELED UP!");
          }
        }
    }
  }
}