#pragma once



void determineEntity()
{

  uint16_t landmarkDistance = travelDistance % 400;
  uint8_t randomIndex = 0;

  if ((overworldCounter == 0) && ((travelDistance % 10) == 9))
    randomIndex = random(0, 16);

    if (landmarkDistance == 389)
    {
      entityY = 8;
      entityX = 127;
      uint8_t landmarkIdentityFinder = (travelDistance / 400) % 2;
      presentEntity = true;
      entityIdentity = static_cast <Identity> (landmarkIdentityFinder);
    } else if ((landmarkDistance < 374) && (randomIndex > 9))
      {
         entityIdentity = static_cast <Identity> ((randomIndex / 3) - 1);
         if ((entityIdentity == Identity::Herb) && (herb == 9))
           entityIdentity = static_cast <Identity> (random(2, 4));
           
         switch (entityIdentity)
         {
            case Identity::Pawn:
            {
              entitySpecies = getSpecies(random(0, 32));
              entityY = 25;
              break;
            }

            case Identity::Enemy:
            {
              entityY = 24;
              break;
            }

            case Identity::Herb:
            {
              entityY = 36;
              break;
            }
            default:
              break;
         }
         presentEntity = true;
         entityX = 127;
      }
}



void determnineEnemyWalkCycle()
{
  uint8_t gruntIdentity = travelDistance / divider;
  const uint8_t cultist = 2;

  switch (gruntIdentity)
  {
    case cultist:
    {
      if (enemyWalkCycle == 1)
        enemyWalkCycle = 0;
        else enemyWalkCycle = 1;
      break;
    }

    default:
    {
      if (enemyWalkCycle == 1)
      {
        if (priorEnemyWalkCycle == 0)
          enemyWalkCycle = 2;
          else enemyWalkCycle = 0;

        priorEnemyWalkCycle = enemyWalkCycle;
      } else 
      {
        priorEnemyWalkCycle = enemyWalkCycle;
        enemyWalkCycle = 1;
      }
      break;
    }
  }

}



void determninePlayerWalkCycle()
{
  if (walkCycle == 1)
  {
    if (priorWalkCycle == 0)
      walkCycle = 2;
      else walkCycle = 0;

    priorWalkCycle = walkCycle;
  } else 
  {
    priorWalkCycle = walkCycle;
    walkCycle = 1;
  }
}



void updateWalking()
{
  overworldCounter += 1;
  if (overworldCounter == 10)
  {
   
    determninePlayerWalkCycle();

    if (presentEntity)
      determnineEnemyWalkCycle();

    overworldCounter = 0;
    travelDistance += 1;
  }

  switch (presentEntity)
  {
    case false:
    {
      entityX = 0;
      entityIdentity = Identity::None;
      determineEntity();
      break;
    }

    case true:
    {
      if (entityX > -33)
        entityX -= 1;
        else presentEntity = false;
      break;
    }
  }

  if ((playerX + 16) == entityX)
    overworldState = static_cast <OverworldState> (entityIdentity);
  
}


void getCastleLevel(uint8_t baseLevel)
{
  for (uint8_t index = 0; index < 3; ++index)
    level[index] = (!newGamePlus) ? baseLevel : 9;
}



void determineCastleTeam()
{
  uint8_t castle = travelDistance / divider;
  const uint8_t mysticCastle = 3;
  const uint8_t natureCastle = 2;
  const uint8_t synthCastle = 1;
  const uint8_t ultimateCastle = 4;
  switch (castle)
  {
    case mysticCastle:
    {
      speciesNumber[0] = 28;
      zodiacNumber[0] = 7;
      speciesNumber[1] = 22;
      zodiacNumber[1] = 6;
      speciesNumber[2] = 26;
      zodiacNumber[2] = 3;
      getCastleLevel(8);
      break;
    }

    case natureCastle:
    {
      speciesNumber[0] = 19;
      zodiacNumber[0] = 12;
      speciesNumber[1] = 11;
      zodiacNumber[1] = 11;
      speciesNumber[2] = 14;
      zodiacNumber[2] = 10;
      getCastleLevel(6);
      break;
    }

    case synthCastle:
    {
      speciesNumber[0] = 1;
      zodiacNumber[0] = 2;
      speciesNumber[1] = 2;
      zodiacNumber[1] = 4;
      speciesNumber[2] = 4;
      zodiacNumber[2] = 8;
      getCastleLevel(4);
      break;
    }

    case ultimateCastle:
    {
      speciesNumber[0] = 31;
      zodiacNumber[0] = 9;
      speciesNumber[1] = 20;
      zodiacNumber[1] = 1;
      speciesNumber[2] = 29;
      zodiacNumber[2] = 5;
      getCastleLevel(9);
      break;
    }
  }
}



void setupEnemyTeam()
{
  uint8_t enemyTeamSize = 0;
  uint8_t difficultyLevel = (!newGamePlus)? (travelDistance / halfDivider) + 2 : 9;

  uint8_t maxTeamSize;
  uint8_t minTeamSize;

  uint8_t teamSizeMinMax = (!newGamePlus) ? travelDistance / divider : 3;
  switch (teamSizeMinMax)
  {
    default:
    {
      minTeamSize = 0;
      maxTeamSize = 1;
      break;
    }

    case 1:
    {
      minTeamSize = 0;
      maxTeamSize = 2;
      break;
    }

    case 2:
    {
      minTeamSize = 1;
      maxTeamSize = 3;
      break;
    }

    case 3:
    {
      minTeamSize = 2;
      maxTeamSize = 3;
      break;
    }
  }

  uint8_t minRandomPawnPossibility = ((travelDistance / divider) >= 3) ? 0 : ((travelDistance / divider) * 10) + 1;
  uint8_t maxRandomPawnPossibility = ((travelDistance / divider) >= 3) ? 32 : (((travelDistance / divider) + 1) * 10) + 1;

  switch (entityIdentity)
  {
    case Identity::Enemy:
    {
      enemyTeamSize = random(minTeamSize, maxTeamSize);
      for (uint8_t index =  0; index <= enemyTeamSize; ++index)
      {
        speciesNumber[index] = random(minRandomPawnPossibility, maxRandomPawnPossibility);
        zodiacNumber[index] = random(1, 13);
        level[index] = difficultyLevel;
      }
      break;
    }

    case Identity::Pawn:
    {
      enemyTeamSize = 0;
      speciesNumber[0] = static_cast <uint8_t> (entitySpecies);
      zodiacNumber[0] = random(1, 13);
      level[0] = difficultyLevel;

      break;
    }
    
    case Identity::Lair:
    {
      enemyTeamSize = 3;
      determineCastleTeam();
      break;
    }

    default:
      break;
  }

  for (uint8_t index = 0; index < 3; ++index)
  {
    uint8_t enemyPawnIndex = index + 3;
    pawn[enemyPawnIndex].zodiac = Zodiac::None;

    if (index <= enemyTeamSize)
      generatePawn(pawn[enemyPawnIndex], speciesNumber[index], zodiacNumber[index], level[index]);

    if (pawn[enemyPawnIndex].zodiac != Zodiac::None)
    {
      createStats(pawn[enemyPawnIndex]);

      pawn[enemyPawnIndex].specialAttack = SpecialAttack::Hit;

      pawn[enemyPawnIndex].energy = pawn[enemyPawnIndex].maxEnergy;

      pawn[enemyPawnIndex].actionCost -= 1;
    }
  }
}


void updateOverworld()
{

  switch (overworldState)
  {
    case OverworldState::Walking:
    {
      updateWalking();
      if (arduboy.justPressed(A_BUTTON))
      {
        saveDestination = SaveDestination::PawnBox;
        gameState = GameState::Save;
      }
      if (arduboy.justPressed(B_BUTTON))
      {
        overworldState = OverworldState::Saved;
        saveDestination = SaveDestination::World;
        gameState = GameState::Save;
      }
      break;
    }

    case OverworldState::Lair:
    case OverworldState::Enemy:
    case OverworldState::Pawn:
    {
      if (overworldState == OverworldState::Pawn)
        wildPawnBattle = true;
        else wildPawnBattle = false;
      setupEnemyTeam();
      overworldState = OverworldState::Encounter;
      break;
    }

    case OverworldState::Herb:
    {
      if ((herb < 9) && (presentEntity))
      {
        herb += 1;
        entityIdentity = Identity::None;
        presentEntity = false;
      }
    if ((arduboy.justPressed(B_BUTTON)) || (arduboy.justPressed(A_BUTTON)))
        overworldState = OverworldState::Walking;
      break;
    }

    case OverworldState::Saved:
    {
      if ((arduboy.justPressed(B_BUTTON)) || (arduboy.justPressed(A_BUTTON)))
        overworldState = OverworldState::Walking;
      break;
    }

    case OverworldState::Inn:
    {
      if ((arduboy.justPressed(B_BUTTON)) || (arduboy.justPressed(A_BUTTON)))
      {
        healAllPawns();
        overworldState = OverworldState::Walking;
      }
      break;
    }

    case OverworldState::Encounter:
    {
      encounterTransitionCounter += 1;
      if (encounterTransitionCounter == 16)
      {
        if (entityIdentity != Identity::Lair)
        {
          entityIdentity = Identity::None;
          presentEntity = false;
        }
        gameState = GameState::BattleSetup;
      }
      break;
    }

    default:
    {
      overworldState = OverworldState::Walking;
      break;
    }
  }

}