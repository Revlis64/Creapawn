#pragma once

bool checkForSave()
{
  uint16_t travelDistanceCheck = 0;
  uint8_t overworldCounterCheck = 0;
  uint16_t address = 696;
  EEPROM.get(address, travelDistanceCheck);
  overworldCounterCheck = EEPROM.read(address + 2);

  if ((travelDistanceCheck <= 3200) && (overworldCounterCheck < 10))
    return true;
  return false;
}


void updateTitleScreen()
{
  switch (titleScreenState)
  {
    case TitleScreenState::StillLogo:
    {
      titleScreenCounter += 1;
      if (titleScreenCounter == 25)
      {
        titleScreenCounter = 24;
        titleScreenState = TitleScreenState::LogoScrollUp;
      }
      break;
    }
    case TitleScreenState::LogoScrollUp:
    {
      titleScreenCounter -= 1;
      if (titleScreenCounter == 0)
      {
        titleScreenState = TitleScreenState::Options;
        uint16_t address = 707;
        uint8_t newGamePlusCheck = EEPROM.read(address);
        newGamePlus = (newGamePlusCheck == 1) ? true : false;
      }
      break;
    }
    case TitleScreenState::Options:
    {
      if (arduboy.justPressed(A_BUTTON))
        {
          if (checkForSave())
            titleScreenState = TitleScreenState::ConfirmNewGame;
            else gameState = GameState::New;
        }

      if ((arduboy.justPressed(B_BUTTON)) && (checkForSave()))
        gameState = GameState::Load;
      break;
    }
    case TitleScreenState::ConfirmNewGame:
    {
      if (arduboy.justPressed(A_BUTTON))
        gameState = GameState::New;
      if (arduboy.justPressed(B_BUTTON))
        titleScreenState = TitleScreenState::Options;
    }
    default:
      break;
  }
}