#pragma once

bool checkForEmptySlot(uint8_t & emptyBoxIndex)
{
  Pawn checkedBox;
  for (uint8_t index = 0; index < 32; ++index)
  {
    emptyBoxIndex = index;
    unpackPawn(checkedBox, index);
    if (checkedBox.zodiac == Zodiac::None)
      return true;
  }
  emptyBoxIndex = invalidBoxIndex;
  return false;
}

void updateCatch()
{
  createStats(pawn[3]);
  pawn[3].energy = pawn[3].maxEnergy;

  if (checkForEmptySlot(emptyBoxIndex))
  {
    if (arduboy.justPressed(A_BUTTON))
    {
      boxSelectionX = emptyBoxIndex % 4;
      boxSelectionScroll = (emptyBoxIndex < 12) ? 0 : ((emptyBoxIndex - 8) / 4) * 4;
      boxSelectionY = ((emptyBoxIndex / 4) * 4) - boxSelectionScroll;
      packAndSavePawn(pawn[3], emptyBoxIndex);
      saveDestination = SaveDestination::PawnBox;
      gameState = GameState::Save;
    }
    if (arduboy.justPressed(B_BUTTON))
      gameState = GameState::Overworld;
  } else gameState = GameState::Overworld;
}