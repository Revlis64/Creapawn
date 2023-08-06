#pragma once

bool confirmPawn(Pawn pawn)
{
  if ((pawn.zodiac != Zodiac::None) && (pawn.energy > 0) && (pawn.level < 9))
    return true;
  return false;
}


//Gathers experience points that will be added to players team's experience points.
uint8_t determineExperienceGain(uint8_t selectedIndex)
{
    uint8_t experience = 1;
    const uint8_t enemyPawnStart = 3;
    for (uint8_t index = 0; index < 3; ++index)
    { Pawn playerPawn = pawn[index];
      Pawn enemyPawn = pawn[index + enemyPawnStart];
      if ((enemyPawn.zodiac != Zodiac::None) && (enemyPawn.energy == 0))
        ++experience;

      if ((index != selectedIndex) && (confirmPawn(playerPawn)) && (experience > 1)) 
      {
        --experience;
      }
    }
    

    
    return experience;
}



bool checkForLevelUp(Pawn & pawn)
{
  uint8_t experienceThreshold = (2 * (pawn.level - 1)) + 1;
  if ((pawn.experience >= experienceThreshold) && (pawn.level < 9))
  {
    pawn.level += 1;
    pawn.experience = (pawn.level == 9) ? 15 : (pawn.experience - experienceThreshold);
    createStats(pawn);
    pawn.energy = pawn.maxEnergy;
    return true;
  }
  return false;
}



void updateVictory()
{
  
  switch (postBattleScreenState)
  {
    case 0:
      if ((arduboy.justPressed(B_BUTTON)) || (arduboy.justPressed(A_BUTTON)))
      {
        for (uint8_t index = 0; index < 3; ++index)
          if (confirmPawn(pawn[index]))
          {
            pawn[index].experience += determineExperienceGain(index);
            levelUpConfirm[index] = checkForLevelUp(pawn[index]);
          }

        postBattleScreenState = 1;
      }
      break;

    case 1:
    {
        if ((arduboy.justPressed(B_BUTTON)) || (arduboy.justPressed(A_BUTTON)))
        {
          for(uint8_t index = 0; index < 3; ++index)
            levelUpConfirm[index] = false;

          if (travelDistance == 3200)
            gameState = GameState::End;
          else if ((wildPawnBattle) && (pawn[3].energy == 0))
            gameState = GameState::Catch;
              else if (entityIdentity == Identity::Lair)
              {
                overworldState = OverworldState::Saved;
                saveDestination = SaveDestination::World;
                gameState = GameState::Save;
              } else gameState = GameState::Overworld;
        }
      break;
    }
  }
}