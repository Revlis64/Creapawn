#pragma once

void renderTitleScreen()
{
  uint8_t logoPositionY = 24;
  switch (titleScreenState)
  {
    case TitleScreenState::LogoScrollUp:
    case TitleScreenState::StillLogo:
    {
      if (titleScreenState == TitleScreenState::LogoScrollUp)
      {
        logoPositionY = titleScreenCounter;
      }

      arduboy.drawBitmap(30, logoPositionY, logo, 68, 16, WHITE);
      break;
    }
    case TitleScreenState::Options:
    {
      arduboy.drawBitmap(30, 0, logo, 68, 16, WHITE);
      if (newGamePlus)
        arduboy.drawBitmap(100, 4, plusSign, 8, 8, WHITE);
      tinyfont.setTextColor(WHITE);
      tinyfont.setCursor(48, 33);
      tinyfont.print(F("(A)NEW"));
      if (checkForSave())
      {
      tinyfont.setCursor(48, 43);
      uint16_t travelDistanceCheck = 0;
      const uint16_t address = 696;
      EEPROM.get(address, travelDistanceCheck);
      tinyfont.print(F("(B)"));
      if ((!newGamePlus) || (travelDistance < 3200))
      tinyfont.print(F("CONTINUE"));
      else tinyfont.print(F("NEW+"));
      }
      break;
    }
    case TitleScreenState::ConfirmNewGame:
    {
      drawTextBox(18, 0, 91, 6, WHITE);
      tinyfont.print(F("DELETE PRIOR SAVE?"));
      drawTextBox(18, 8, 31, 6, WHITE);
      tinyfont.print(F("(A)YES"));
      drawTextBox(18, 16, 31, 6, WHITE);
      tinyfont.print(F("(B)NO!"));
      break;
    }
  }
}