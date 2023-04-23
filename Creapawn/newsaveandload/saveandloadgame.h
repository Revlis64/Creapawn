#pragma once


void determinePostsaveDestination()
{
  switch (saveDestination)
  {
    case SaveDestination::World:
    {
      gameState = GameState::Overworld;
      break;
    }

    case SaveDestination::Title:
    {
      gameState = GameState::TitleScreen;
      break;
    }

    case SaveDestination::PawnBox:
    {
      gameState = GameState::Box;
      break;
    }
    default:
      break;
  }
}


void saveGameData()
{
  for (uint8_t index = 0; index < 3; ++index)
  {
    if (team[index] != invalidTeamSlot)
      packAndSavePawn(pawn[index], team[index]);
  }
  if (saveDestination == SaveDestination::Title)
    newGamePlus = true;
  uint16_t address = 696;
  EEPROM.put(address, travelDistance);
  EEPROM.update(address + 2, overworldCounter);
  EEPROM.update(address + 3, presentEntity);
  EEPROM.update(address + 4, static_cast <uint8_t> (entityIdentity));
  EEPROM.update(address + 5, entityX);
  EEPROM.update(address + 6, entityY);
  EEPROM.update(address + 7, herb);
  EEPROM.update(address + 8, team[0]);
  EEPROM.update(address + 9, team[1]);
  EEPROM.update(address + 10, team[2]);
  EEPROM.update(address + 11, newGamePlus);
  
  determinePostsaveDestination();
}

void loadGameData()
{
  uint16_t address = 696;
  EEPROM.get(address, travelDistance);
  overworldCounter = EEPROM.read(address + 2);
  presentEntity = EEPROM.read(address + 3);
  entityIdentity = static_cast <Identity> (EEPROM.read(address + 4));
  entityX = EEPROM.read(address + 5);
  entityY = EEPROM.read(address + 6);
  herb = EEPROM.read(address + 7);
  team[0] = EEPROM.read(address + 8);
  team[1] = EEPROM.read(address + 9);
  team[2] = EEPROM.read(address + 10);
  for (uint8_t index = 0; index < 3; ++index)
  {
    unpackPawn(pawn[index], team[index]);
    createStats(pawn[index]);
  }
  if ((travelDistance == 3200) && (newGamePlus))
  {
    presentEntity = false;
    travelDistance = 0;
    overworldCounter = 0;
  }
  gameState = GameState::Overworld;
}