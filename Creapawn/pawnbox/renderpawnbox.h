#pragma once

bool checkTeam(uint8_t boxIndex, uint8_t & teamNumber)
{
  for (uint8_t index = 0; index < 3; ++index)
    if (team[index] == boxIndex)
    {
      teamNumber = index;
      return true;
    }

  return false;
}



void printMainOptions()
{
  for(uint8_t index = 0; index < 3; ++index)
  {
    uint8_t boxBump = (optionSelection == index) ? 3 : 0;
    drawTextBox(0 + boxBump, 43 + (7 * index), 41, 6, WHITE);
    switch (index)
    {
      case 0:
      {
        //if (boxIndex == checkTeam())
        tinyfont.print(F("TEAM"));
        break;
      }
      case 1:
      {
        tinyfont.print(F("HERB "));
        tinyfont.print(herb);
        tinyfont.print(F("/9"));
        break;
      }
      case 2:
      {
        tinyfont.print(F("RELEASE"));
        break;
      }
      default:
        break;
    }
  }
}



void printReleaseConfirmation()
{
    drawTextBox(0, 43, 41, 6, WHITE);
      tinyfont.print(F("RELEASE?"));
  for(uint8_t index = 0; index < 2; ++index)
  {
    drawTextBox(0, 50 + (7 * index), 31, 6, WHITE);
    switch (index)
    {
      case 0:
      {
        //if (boxIndex == checkTeam())
        tinyfont.print(F("(A)YES"));
        break;
      }
      case 1:
      {
        tinyfont.print(F("(B)NO!"));
        break;
      }
      default:
        break;
    }
  }
}

void printTeamSlots()
{

  drawTextBox(0, 43, 21, 11, WHITE);
  tinyfont.print(F("PICK"));
  tinyfont.setCursor(1, 49);
  tinyfont.print(F("SLOT"));

  for(uint8_t index = 0; index < 3; ++index)
  {
    if ((index == 0) || ((index == 1) && (team[0] != invalidTeamSlot)) || ((index == 2) && (team[1] != invalidTeamSlot)))
    {
      uint8_t boxBump = (optionSelection == index) ? 3 : 0;
      drawTextBox(25 - boxBump, 43 + (7 * index), 26, 6, WHITE);
      tinyfont.print(F("SLOT"));
      switch (index)
      {
        case 0:
        {
          tinyfont.print(F("1"));
          break;
        }
        case 1:
        {
          tinyfont.print(F("2"));
          break;
        }
        case 2:
        {
          tinyfont.print(F("3"));
          break;
        }
        default:
          break;
      }
    }
  }
}


void renderPawnBox()
{
    uint8_t cursorIndex = boxSelectionX + boxSelectionY + boxSelectionScroll;
    if (boxSelectionScroll > 0)
      arduboy.drawBitmap(88, 0, upTriangle, 8, 8, WHITE);
    if (boxSelectionScroll < 20)
      arduboy.drawBitmap(88, 61, downTriangle, 8, 8, WHITE);

    Pawn displayedPawn;

    for (uint8_t column = 0; column < 3; ++column)
    for (uint8_t row = 0; row < 4; ++row)
    {
       arduboy.drawRoundRect(53 + (19 * row), 4 + (19 * column), 18, 18, true, WHITE);
       uint8_t boxIndex = row + (column * 4) + boxSelectionScroll;
       unpackPawn(displayedPawn, boxIndex);
       if (displayedPawn.zodiac != Zodiac::None)
         drawPawn(displayedPawn.species, 54 + (19 * row), 5 + (19 * column), BLACK, Direction::Right);
       uint8_t teamNumber = 0;
       if (checkTeam(boxIndex, teamNumber))
       {
         drawTextBox(65 + (19 * row), 16 + (19 * column), 6, 6, WHITE);
         tinyfont.print(teamNumber + 1);
       }

       if (cursorIndex == boxIndex)
       {
         arduboy.drawBitmap(54 + (19 * row), 5 + (19 * column), boardCursorBackground, 16, 16, BLACK);
         arduboy.drawBitmap(54 + (19 * row), 5 + (19 * column), boardCursorForeground, 16, 16, WHITE);
       }
         
    }

  bool healthPrintEffect = false;
  if ((boxState == BoxState::Options) && (optionSelection == 1))
    healthPrintEffect = true;
  drawPawnStats(unpackedPawn, healthPrintEffect);

  switch (boxState)
  {
    default:
    {
        printMainOptions();
        break;
    }

    case BoxState::ConfigureTeam:
    {
        printTeamSlots();
        break;
    }

    case BoxState::ConfirmRelease:
    {
        printReleaseConfirmation();
        break;
    }

    case BoxState::CannotDoAction:
    {
        drawTextBox(0, 43, 51, 16, WHITE);
        tinyfont.print(F("YOU CANNOT"));
        tinyfont.setCursor(1, 49);
        tinyfont.print(F("DO THIS"));
        tinyfont.setCursor(1, 54);
        tinyfont.print(F("ACTION!"));
        break;
    }

    case BoxState::NeedTeam:
    {
        drawTextBox(0, 43, 51, 16, WHITE);
        tinyfont.print(F("YOU CANNOT"));
        tinyfont.setCursor(1, 49);
        tinyfont.print(F("LEAVE WITH"));
        tinyfont.setCursor(1, 54);
        tinyfont.print(F("OUT PAWNS!"));
        break;
    }
  }

}