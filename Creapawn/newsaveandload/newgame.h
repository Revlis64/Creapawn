#pragma once

const uint8_t invalidTeamSlot = 32;

void updateNewGame()
{
  for (uint8_t index = 0; index < 108; ++index)
    EEPROM.update(600 + index, 0);

  generatePawn(pawn[0], 5, 1, 3);
  createStats(pawn[0]);
  pawn[0].energy = pawn[0].maxEnergy;
  pawn[1].zodiac = Zodiac::None;
  pawn[2].zodiac = Zodiac::None;
  packAndSavePawn(pawn[0], 0);
  team[0] = 0;
  team[1] = invalidTeamSlot;
  team[2] = invalidTeamSlot;
  herb = 5;
  saveDestination = SaveDestination::World;
  gameState = GameState::Save;
  newGamePlus = false;

}