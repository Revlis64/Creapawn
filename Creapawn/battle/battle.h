#pragma once

enum class Turn : uint8_t
{
  Player,
  Opponent,
  Neither,
};

enum class BattleAction : uint8_t
{
  PawnAndAction,
  Target,
  Damage,
};

enum class AttackTarget : uint8_t
{
  CloseEmptyTiles,
  CloseEnemy,
  ClosePawn,
  AnyEnemy,
  AllEnemies,
  AllAllies,
  Self,
  None,
};

enum ComputerAction : uint8_t
{
  Move,
  Attack,
  None,
};

const uint8_t playerPawnStart = 0;
const uint8_t playerPawnEnd = 2;
const uint8_t enemyPawnStart = 3;
const uint8_t enemyPawnEnd = 5;
const uint8_t blankTile = 6;
const uint8_t invalidTile = 7;
const uint8_t validTile = 8;
const uint8_t invalidPawnIndex = 6;

bool firstTurn = false;
Turn turn = Turn::Neither;
ComputerAction computerAction = ComputerAction::None;
AttackTarget attackTarget;
uint8_t actionPoints[2] = {5, 5};
BattleAction battleAction;
int8_t selectedSquareX = 0;
int8_t selectedSquareY = 0;
uint8_t selectedPawn = 0;
uint8_t previouslySelectedPawn = invalidPawnIndex;
uint8_t selectedPawnX = 0;
uint8_t selectedPawnY = 0;
uint8_t selectedAction = 0;
uint8_t attackCost = 0;
uint8_t enduredPawn = invalidPawnIndex;
bool typeDamageMultiplier = 1;
bool typeDamageDivider = 1;
uint8_t damage = 0;
uint8_t battleVictory = false;
uint8_t battleResultsCounter = 0;
uint8_t postBattleScreenState = 0;
bool computerActionTaken = 0;
uint8_t skipCounter = 0;
uint8_t computerActionCounter = 0;

#include "updatebattle/updatebattle.h"
#include "renderbattle/renderbattle.h"
