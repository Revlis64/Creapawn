#pragma once

uint8_t getTeamSize()
{
    uint8_t teamSize = 0;
  const uint8_t invalidTeamSlot = 32;
  for (uint8_t index = 1; index < 3; ++index)
    if (team[index] != invalidTeamSlot)
      teamSize += 1;

  return teamSize;
}

void renderEnd()
{
  arduboy.drawBitmap( 34, 0, theText, 25, 16, WHITE);
  arduboy.drawBitmap( 68, 0, endText, 26, 16, WHITE);
  const uint8_t playerEndX = (!newGamePlus) ? 58 : 68 + (8 * (getTeamSize()));
  const uint8_t playerEndY = 24;
  drawPlayer(playerEndX, playerEndY);
  uint8_t pawnX = playerEndX - 17;
  if (newGamePlus)
  for (uint8_t index = 0; index < 3; ++index)
  {
    if (pawn[index].zodiac != Zodiac::None)
    {
      bool yDecrease = (pawnHop + index) % 2;
      drawPawn(pawn[index].species, pawnX - (17 * index), 25 - yDecrease, BLACK, Direction::Right);
    }
  }
}