#pragma once
const uint16_t divider = 800;
const uint16_t halfDivider = 400;
const uint8_t wildBattle = 1;
const uint8_t castleBattle = 2;
uint8_t menuCursor = 0;
uint8_t speciesNumber[3];
uint8_t level[3];
uint8_t zodiacNumber[3];
uint8_t entitySpeciesNumber = 0;
Species entitySpecies = Species::Voidismal;
uint8_t walkCycle = 0;
uint8_t priorEnemyWalkCycle = 0;
uint8_t priorWalkCycle = 0;
uint8_t enemyWalkCycle = 0;
uint8_t overworldCounter = 0;
uint16_t travelDistance = 0;
int8_t entityX = 0;
uint8_t entityY = 0;
const uint8_t playerX = 0;
const uint8_t playerY = 24;
bool presentEntity = false;
bool buildingInteracted = false;
uint8_t enemyTeamSize = 0;
uint8_t herb = 0;
bool wildPawnBattle = false;
uint8_t encounterTransitionCounter = 0;
Zodiac wildPawnZodiac = Zodiac::None;

enum class SaveDestination : uint8_t
{
  World,
  PawnBox,
  Title,
};

enum class Identity : uint8_t
{
  Inn,
  Lair,
  Pawn,
  Enemy,
  Herb,
  None,
};

enum class OverworldState : uint8_t
{
  Inn,
  Lair,
  Pawn,
  Enemy,
  Herb,
  Walking,
  Saved,
  Encounter,
};

OverworldState overworldState = OverworldState::Walking;
Identity entityIdentity = Identity::None;
SaveDestination saveDestination = SaveDestination::World;

#include "updateoverworld.h"
#include "renderoverworld.h"