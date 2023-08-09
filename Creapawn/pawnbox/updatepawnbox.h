#pragma once

bool checkTeam(uint8_t boxIndex, uint8_t slotIndex)
{
    if (team[slotIndex] == boxIndex)
      return true;

  return false;
}

void moveBoxCursor()
{
  const uint8_t maxCursorUp = 0;
  const uint8_t maxCursorDown = 8;
  const uint8_t maxCursorLeft = 0;
  const uint8_t maxCursorRight = 3;
  const uint8_t maxScrollUp = 0;
  const uint8_t maxScrollDown = 20;

  if (arduboy.justPressed(UP_BUTTON))
    switch (boxSelectionY)
    {
      default:
      {
        boxSelectionY -= 4;
        break;
      }

      case maxCursorUp:
      {
        if (boxSelectionScroll > maxScrollUp)
          boxSelectionScroll -= 4;
        break;
      }
    }

  if (arduboy.justPressed(DOWN_BUTTON))
    switch (boxSelectionY)
    {
      default:
      {
        boxSelectionY += 4;
        break;
      }

      case maxCursorDown:
      {
        if (boxSelectionScroll < maxScrollDown)
          boxSelectionScroll += 4;
        break;
      }
    }

  if ((arduboy.justPressed(LEFT_BUTTON)) && (boxSelectionX > maxCursorLeft))
    boxSelectionX -= 1;

  if ((arduboy.justPressed(RIGHT_BUTTON)) && (boxSelectionX < maxCursorRight))
    boxSelectionX += 1;

}



void selectOptionsAction(uint8_t downLimit)
{
  if ((arduboy.justPressed(UP_BUTTON)) && (optionSelection > 0))
    optionSelection -= 1;
  if ((arduboy.justPressed(DOWN_BUTTON)) && (optionSelection < downLimit))
    optionSelection += 1;
}

void shiftTeam()
{
  for (uint8_t index = 1; index < 3; ++index)
  if ((team[index] != invalidTeamSlot) && ((team[index - 1] == invalidTeamSlot) || (team[index - 1] == team[index])))
  {
    team[index - 1] = team[index];
    team[index] = invalidTeamSlot;
  }
}

void arrangeTeam(uint8_t slot, uint8_t boxIndex)
{
  const uint8_t invalidSlotNo = 3;
  bool teamPresence = false;
  uint8_t boxIndexHolder = invalidTeamSlot;
  uint8_t teamSlotHolder = invalidSlotNo;

  for (uint8_t index = 0; index < 3; ++index)
    if (checkTeam(boxIndex, index))
      {
        teamSlotHolder = index;
        teamPresence = true;
        break;
      }

   switch (teamPresence)
   {
     case true:
     {
       if (team[slot] == boxIndex)
         team[slot] = invalidTeamSlot;
         else
         {
           boxIndexHolder = team[slot];
           team[slot] = boxIndex;
           team[teamSlotHolder] = boxIndexHolder;
         }
      break;
     }
     case false:
     {
       team[slot] = boxIndex;
       break;
     }
    }
  shiftTeam();
}



bool checkForPawns(uint8_t boxIndex)
{
  Pawn checkedPawn;
  //uint8_t boxIndex = boxSelectionX + boxSelectionY + boxSelectionScroll;
  for (uint8_t index = 0; index < 32; ++index)
  {
    unpackPawn(checkedPawn, index);
    if ((checkedPawn.zodiac != Zodiac::None) && (index != boxIndex) && (checkedPawn.energy > 0))
      return true;
  }

  return false;
}



void createTeam()
{
  for(uint8_t index = 0; index < 3; ++index)
  {
    clearPawn(pawn[index]);
    if (team[index] != invalidTeamSlot)
    {
      unpackPawn(pawn[index], team[index]);
      createStats(pawn[index]);
    }
  }
}



void saveTeamPositions()
{
  uint16_t address = 704;
  for(uint8_t index = 0; index < 3; ++index)
    EEPROM.update(address + index, team[index]);
}



void updatePawnBox()
{

  switch (boxState)
  {
    case BoxState::Setup:
    {
      for (uint8_t index = 0; index < 3; ++index)
      {
        if ((pawn[index].energy == 0) || (pawn[index].zodiac == Zodiac::None))
          team[index] = invalidTeamSlot;
      }
      shiftTeam();
      if (team[0] == invalidTeamSlot)
        shiftTeam();
      saveTeamPositions();
      boxState = BoxState::SelectPawn;
      break;
    }

    case BoxState::SelectPawn:
    {
      moveBoxCursor();
      boxIndex = boxSelectionX + boxSelectionY + boxSelectionScroll;
      unpackPawn(unpackedPawn, boxIndex);
      createStats(unpackedPawn);

      if ((arduboy.justPressed(A_BUTTON)) && (unpackedPawn.zodiac != Zodiac::None))
      {
        optionSelection = 0;
        boxState = BoxState::Options;
      }

      if (arduboy.justPressed(B_BUTTON))
      {
        if (team[0] != invalidTeamSlot)
        {
          createTeam();
          gameState = GameState::Overworld;
          overworldState = OverworldState::Saved;
          boxState = BoxState::Setup;
        } else boxState = BoxState::NeedTeam;
       }

      break;
    }
    
    case BoxState::Options:
    {
      selectOptionsAction(2);

      if (arduboy.justPressed(A_BUTTON))
        boxState = static_cast <BoxState> (optionSelection + 2);
        
      if (arduboy.justPressed(B_BUTTON))
      {
          optionSelection = 3;
          boxState = BoxState::SelectPawn;
      }

      break;
    }

    case BoxState::ConfigureTeam:
    {
      uint8_t downLimit = 0;

      for (uint8_t index = 0; index < 2; ++index)
      {
        if (team[index] != invalidTeamSlot)
          downLimit += 1;
          else break;
      }


      selectOptionsAction(downLimit);
      if (arduboy.justPressed(A_BUTTON))
      {
        if (unpackedPawn.energy > 0)
        {
          arrangeTeam(optionSelection, boxIndex);
          saveTeamPositions();
          optionSelection = 0;
          boxState = BoxState::Options;
        } else boxState = BoxState::CannotDoAction;

      }
      if (arduboy.justPressed(B_BUTTON))
      {
        optionSelection = 0;
        boxState = BoxState::Options;
      }
      break;
    }

    case BoxState::UseHerb:
    {
      //uint8_t boxIndex = boxSelectionX + boxSelectionY + boxSelectionScroll;
      if ((herb > 0) && (unpackedPawn.maxEnergy > unpackedPawn.energy))
      {
        herb -= 1;
        unpackedPawn.energy = (((unpackedPawn.maxEnergy / 2) + unpackedPawn.energy) > unpackedPawn.maxEnergy) ? unpackedPawn.maxEnergy : (unpackedPawn.maxEnergy / 2) + unpackedPawn.energy;
        packAndSavePawn(unpackedPawn, boxIndex);
        uint16_t address = 703;
        EEPROM.update(address, herb);
        boxState = BoxState::Options;
      } else boxState = BoxState::CannotDoAction;
      break;
    }

    case BoxState::ConfirmRelease:
    {
      if (arduboy.justPressed(A_BUTTON))
      {
        if (checkForPawns(boxIndex))
        {
          const uint16_t eepromAddressStart = 600;
          //uint8_t boxIndex = boxSelectionX + boxSelectionY + boxSelectionScroll;
          uint16_t address = eepromAddressStart + (boxIndex * 3);
          EEPROM.update(address, 0);
          EEPROM.update(address + 1, 0);
          EEPROM.update(address + 2, 0);
          for(uint8_t index = 0; index < 3; ++index)
          {
            if (boxIndex == team[index])
            {
              arrangeTeam(index, boxIndex);
              break;
            }
          }
          optionSelection = 3;
          boxState = BoxState::SelectPawn;
        } else boxState = BoxState::CannotDoAction;
      }
      if (arduboy.justPressed(B_BUTTON))
        boxState = BoxState::Options;
      break;
    }
  
    case BoxState::CannotDoAction:
    case BoxState::NeedTeam:
    {
      optionSelection = 3;
      if ((arduboy.justPressed(A_BUTTON)) || (arduboy.justPressed(B_BUTTON)))
        boxState = BoxState::SelectPawn;
      break;
    }

    default:
      break;
  }
}