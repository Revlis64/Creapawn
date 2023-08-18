#pragma once

uint8_t findSelectedPawn()
{
   for (uint8_t pawnPreselect = 0; pawnPreselect < 3; ++pawnPreselect)
  {
    if ((pawn[pawnPreselect].zodiac != Zodiac::None) && (pawn[pawnPreselect].energy > 0))
    {
      return pawnPreselect;
    }
  }
  return invalidPawnIndex;
}

void setupBattle()
{
  turn = Turn::Player;
  firstTurn = true;
  actionPoints[0] = 6;
  actionPoints[1] = 6;
  gameState = GameState::Battle;
  selectedPawn = findSelectedPawn();
  selectedAction = 0;
  postBattleScreenState = 0;
  skipCounter = 0;
  computerActionTaken = false;
  computerActionCounter = 0;
  endure = false;
}