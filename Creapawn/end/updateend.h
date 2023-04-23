#pragma once

void updateEnd()
{
  if (arduboy.everyXFrames(10))
  {
    pawnHop = (pawnHop == 0) ? 1 : 0;
    determninePlayerWalkCycle();
  }

  if ((arduboy.justPressed(A_BUTTON)) || (arduboy.justPressed(B_BUTTON)))
  {
    for (uint8_t index = 0; index < 3; ++index)
      if (pawn[index].zodiac != Zodiac::None)
        pawn[index].energy = pawn[index].maxEnergy;

    saveDestination = SaveDestination::Title;
    gameState = GameState::Save;
  }
}