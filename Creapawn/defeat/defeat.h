#pragma once

void updateDefeat()
{
    healAllPawns();
    presentEntity = false;
    overworldCounter = 1;
    if (!newGamePlus)
    {
      travelDistance = (travelDistance / 400) * 400;
      if (entityIdentity == Identity::Lair)
        travelDistance -= 400;
      if (travelDistance > 399)
      {
        uint8_t landMarkFinder = ((travelDistance - 400) / 400) % 2;
        presentEntity = true;
        entityIdentity = static_cast <Identity> (landMarkFinder);
        entityY = 8;
        entityX = 15;
      }
    } else travelDistance = 0;
    overworldState = OverworldState::Saved;
    saveDestination = SaveDestination::World;
    gameState = GameState::Save;
}