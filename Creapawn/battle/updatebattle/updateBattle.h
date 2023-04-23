#pragma once

#include "attack.h"
#include "board.h"
#include "playerbattleaction.h"
#include "computerbattleaction.h"

void updateBattle()
{

  switch (turn)
  {
    case Turn::Player:
    {
      updatePlayerBattleAction();
      break;
    }

    case Turn::Opponent:
    {
      ++computerActionCounter;
      if ((computerActionCounter == 10) || (skipCounter > 0))
      {
        computerActionCounter = 0;
        updateComputerBattleAction();
      }
      break;
    }

    case Turn::Neither:
    {
      if (arduboy.justPressed(A_BUTTON))
      {
         if (battleVictory == true)
            gameState = GameState::Victory;
            else gameState = GameState::Defeat;
      }
      break;
    }
  }

  updateBoard();
}