#pragma once

void drawPlayer(uint8_t x, uint8_t y)
{
  arduboy.drawBitmap(x, y, playerWalkCycleBackground[walkCycle], 12, 16, WHITE);
  arduboy.drawBitmap(x, y, playerWalkCycleForeground[walkCycle], 12, 16, BLACK);
}

void drawEntity()
{
  switch (entityIdentity)
  {
    case Identity::Pawn:
    {
      drawPawn(entitySpecies, entityX, entityY, WHITE, Direction::Left);
      break;
    }

    case Identity::Enemy:
    {
      uint8_t gruntIdentity = (travelDistance / divider) * 3;

      arduboy.drawBitmap(entityX, entityY, enemyWalkCycleBackground[gruntIdentity + enemyWalkCycle], 12, 16, WHITE);
      arduboy.drawBitmap(entityX, entityY, enemyWalkCycleForeground[gruntIdentity + enemyWalkCycle], 12, 16, BLACK);
      break;
    }

    case Identity::Lair:
    {
      uint8_t lairIndex = (travelDistance - 16) / divider;
      arduboy.drawBitmap(entityX, entityY, bossLair[lairIndex], 32, 16, WHITE);
      break;
    }

    case Identity::Inn:
    {
      arduboy.drawBitmap(entityX, entityY, inn, 32, 16, WHITE);
      break;
    }

    case Identity::Herb:
    {
      arduboy.drawBitmap(entityX, entityY, plant, 8, 8, WHITE);
      break;
    }

    default:
    break;
  }
}

void drawBackground()
{
  for (uint8_t index = 0; index < 5; ++index)
  {
    int16_t backGroundX = 128 - ((travelDistance % 32) + (index * 32));
    uint8_t direction = (((travelDistance / 32) % 2) + index) % 2;
    uint8_t backgroundIndex = (travelDistance < 160) ? 0 : (travelDistance - (32 + (index * 32))) / divider;
    ardbitmap.drawBitmap(backGroundX, 0, background[backgroundIndex], 32, 8, WHITE, ALIGN_NONE, direction);
  }
}



void renderOverworld()
{
  drawPlayer(playerX, playerY);
  if (presentEntity)
    drawEntity();
  drawBackground();
  arduboy.drawLine(128, 40, 0, 40, WHITE);
  drawTextBox(0, 42, 128, 21, WHITE);
  tinyfont.print(F("DISTANCE TRAVELED"));
  tinyfont.setCursor(1, 48);
  uint16_t variable = 1;
  for (uint8_t index = 0; index < 3; ++index)
  {
    variable *= 10;
    if (travelDistance < variable)
      tinyfont.print(F("0"));
  }
  tinyfont.print(travelDistance);
  tinyfont.print(F("0 METERS"));
  tinyfont.setCursor(1, 53);
  tinyfont.print(F("NEXT DESTINATION"));
  tinyfont.setCursor(1, 58);
  uint16_t destinationDistance = 400 - (travelDistance % 400);
  uint8_t destination = (travelDistance / 400) % 2;
  const uint8_t inn = 0;
  const uint8_t lair = 1;
  switch (destination)
  {
    case inn:
    {
      tinyfont.print(F("INN :"));
      break;
    }
    case lair:
    {
      tinyfont.print(F("LAIR:"));
      break;
    }
    default:
      break;
  }
  uint16_t destinationVariable = 1;
  for (uint8_t index = 0; index < 2; ++index)
  {
    destinationVariable *= 10;
    if (destinationDistance < destinationVariable)
      tinyfont.print(F("0"));
  }
  tinyfont.print(destinationDistance);
  tinyfont.print(F("0 METERS"));

  tinyfont.setCursor(88, 43);
  tinyfont.print(F("(A)PAWNS"));
  tinyfont.setCursor(88, 53);
  tinyfont.print(F("(B)SAVE"));

  switch (overworldState)
  {
    case OverworldState::Saved:
    {
      drawTextBox(38, 14, 53, 8, BLACK);
      drawTextBox(39, 15, 51, 6, WHITE);
      tinyfont.print(F("GAME SAVED"));
      break;
    }
    case OverworldState::Herb:
    {
      drawTextBox(25, 14, 78, 8, BLACK);
      drawTextBox(26, 15, 76, 6, WHITE);
      tinyfont.print(F("YOU GOT AN HERB"));
      break;
    }
    case OverworldState::Inn:
    {
      drawTextBox(27, 14, 73, 13, BLACK);
      drawTextBox(28, 15, 71, 11, WHITE);
      tinyfont.print(F("ALL YOUR PAWNS"));
      tinyfont.setCursor(29, 21);
      tinyfont.print(F("ARE NOW HEALED"));
      break;
    }
    case OverworldState::Encounter:
    {
      arduboy.fillRect(0, 0, 128, (encounterTransitionCounter * 2), BLACK);
      arduboy.fillRect(0, 63 - (encounterTransitionCounter * 2), 128, (encounterTransitionCounter * 2), BLACK);
      break;
    }
    default:
      break;
  }
}

