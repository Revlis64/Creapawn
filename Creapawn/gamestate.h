#pragma once

enum class GameState : uint8_t 
{
  Box,
  BattleSetup,
  Battle,
  Victory,
  Defeat,
  Overworld,
  New,
  Save,
  Catch,
  Load,
  TitleScreen,
  End,

};

GameState gameState = GameState::TitleScreen;

enum class Direction : bool 
{
  Right,
  Left,
};

Direction directionHolder;

bool newGamePlus = false;

#include "universal/pawnelements.h"
#include "universal/text.h"
#include "universal/bitmap.h"

#include "battlesetup/setuppawns.h"
#include "battle/battle.h"
#include "universal/pawnstatsprint.h"
#include "overworld/overworld.h"
#include "victory/victory.h"
#include "newsaveandload/newgame.h"
#include "pawnbox/pawnbox.h"
#include "defeat/defeat.h"
#include "catch/catch.h"
#include "newsaveandload/saveandloadgame.h"
#include "end/end.h"
#include "titlescreen/titlescreen.h"
#include "battlesetup/setupbattle.h"



//updates game state
void updateGameState()
{
  switch (gameState)
  {
    case GameState::BattleSetup:
    {
      encounterTransitionCounter = 0;
      overworldState = OverworldState::Walking;
      setupPawns();
      setupBattle();
      break;
    }

    case GameState::Battle:
    {
      updateBattle();
      renderBattle();
      break;
    }

    case GameState::Victory:
    {
      updateVictory();
      renderVictory();
      break;
    }

    case GameState::Defeat:
    {
      updateDefeat();
      break;
    }

    case GameState::Overworld:
    {
      updateOverworld();
      renderOverworld();
      break;
    }

    case GameState::New:
    {
      updateNewGame();
      break;
    }

    case GameState::Box:
    {
      updatePawnBox();
      renderPawnBox();
      break;
    }

    case GameState::Catch:
    {
      updateCatch();
      renderCatch();
      break;
    }

    case GameState::Save:
    {
      saveGameData();
      break;
    }

    case GameState::Load:
    {
      loadGameData();
      break;
    }

    case GameState::TitleScreen:
    {
      updateTitleScreen();
      renderTitleScreen();
      break;
    }

    case GameState::End:
    {
      updateEnd();
      renderEnd();
      break;
    }

    default:
      break;
  }
}