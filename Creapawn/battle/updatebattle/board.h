#pragma once

//Checks if the target(s), whether empty tiles or pawns, is close to the selected pawn.
bool checkProximity(uint8_t x, uint8_t y, uint8_t targetX, uint8_t targetY)
{
      if (((((y - targetY) == 1) && (x == targetX))
      || (((y - targetY) == -1) && (x == targetX))
      || (((x - targetX) == 1) && (y == targetY))
      || (((x - targetX) == -1) && (y == targetY))))
        return true;
        else return false;
}


//Used to determine potential damage to targeted pawn without inflicting actual damage.
void determineEnergyPrint(Pawn & pawn, Pawn & targetedPawn)
{
  targetedPawn.energyPrint = targetedPawn.energy;
  uint8_t damage = calculateDamage(pawn, targetedPawn);
  targetedPawn.energyPrint -= ((targetedPawn.energyPrint - damage) < 0) ? targetedPawn.energyPrint : damage;
}


//Subtracts both the pawn's accrued damage, along with the pawn's until, until the accrued damage is equal to zero.
void reduceEnergyAndDamage(uint8_t x, uint8_t y, bool & pawnsWithoutDamage, Pawn & pawn)
{
  if (board[y][x] == invalidTile)
    board[y][x] = blankTile;
  if (board[y][x] < blankTile)
    {
      if (enduredPawn == board[y][x])
        pawn.damage = 0;

      if (pawn.damage == 0)
      {
        if (pawn.energy > 0)
          pawn.draw = true;
          else pawn.draw = false;
      }

      if (pawn.damage > 0)
      {
        pawnsWithoutDamage = false;
        pawn.damage -= 1;
        pawn.energy -= 1;
        pawn.draw = (pawn.draw) ? false : true;
      }
        pawn.energyPrint = pawn.energy;
    }
    if ((x == 3) && (y == 3) && (pawnsWithoutDamage))
      battleAction = BattleAction::PawnAndAction;
}


//Determines what is exactly being targeted, based off of the move selected and how it's drawn on the board.
void determineBoardTarget(uint8_t x, uint8_t y, uint8_t & tileIndex, Pawn & affectedPawn)
{

  uint8_t target = board[selectedSquareY][selectedSquareX];

  switch (attackTarget)
  {
    case AttackTarget::CloseEmptyTiles:
    {
      bool results = checkProximity(selectedPawnX, selectedPawnY, x, y);
      switch (results)
      {
        case true:
        {
          if ((tileIndex > enemyPawnEnd) && (arduboy.everyXFrames(5)))
            tileIndex = (tileIndex == blankTile) ? validTile : blankTile;
          break;
        }

        case false:
        {
          if (tileIndex > enemyPawnEnd)
            tileIndex = invalidTile;
          break;
        }
      }
      break;
    }

    case AttackTarget::CloseEnemy:
    {
      uint8_t results = checkProximity(selectedPawnX, selectedPawnY, x, y);
      switch (results)
      {
        case true:
        {
          if ((tileIndex < blankTile) && (board[y][x] > playerPawnEnd)) 
          {
            if (target == tileIndex)
              determineEnergyPrint(pawn[selectedPawn], affectedPawn);

            if (arduboy.everyXFrames(5))
              affectedPawn.draw = (affectedPawn.draw) ? false : true;
          }
            else if (tileIndex > enemyPawnEnd)
              tileIndex = invalidTile;
          break;
        }

        case false:
        {
          if ((tileIndex < blankTile) && (tileIndex > playerPawnEnd))
            affectedPawn.draw = true;
            else if (tileIndex > enemyPawnEnd)
              tileIndex = invalidTile;
          break;
        }
      }
      break;
    }

      case AttackTarget::AllEnemies:
      case AttackTarget::AnyEnemy:
      {
        if ((tileIndex < blankTile) && (tileIndex > playerPawnEnd))
        {
          if (((target == tileIndex) && (attackTarget == AttackTarget::AnyEnemy)) || (attackTarget == AttackTarget::AllEnemies))
            determineEnergyPrint(pawn[selectedPawn], affectedPawn);
          if (arduboy.everyXFrames(5))
            affectedPawn.draw = (affectedPawn.draw) ? false : true;
        } else if (tileIndex < blankTile)
          affectedPawn.draw = true;
            else if ((tileIndex > enemyPawnEnd) && (attackTarget == AttackTarget::AnyEnemy))
              tileIndex = invalidTile;
        break;
      }

      case AttackTarget::AllAllies:
      {
        if ((tileIndex < enemyPawnStart) && (affectedPawn.energy < affectedPawn.maxEnergy))
        {
          affectedPawn.energyPrint = ((affectedPawn.energy + (affectedPawn.maxEnergy / 2)) > affectedPawn.maxEnergy) ? affectedPawn.maxEnergy : affectedPawn.energy + (affectedPawn.maxEnergy / 2);
          if (arduboy.everyXFrames(5))
            affectedPawn.draw = (affectedPawn.draw) ? false : true;
        } else if (tileIndex < blankTile)
          affectedPawn.draw = true;
        break;
      }

      case AttackTarget::Self:
      {
        if (tileIndex == selectedPawn)
        {
          if (arduboy.everyXFrames(5))
            affectedPawn.draw = (affectedPawn.draw) ? false : true;
        } else if (tileIndex < blankTile)
          affectedPawn.draw = true;
        break;
      }
      
      case AttackTarget::ClosePawn:
      {
        uint8_t results = checkProximity(selectedPawnX, selectedPawnY, x, y);
        switch (results)
        {
          case true:
          {
            if ((tileIndex < blankTile) && (arduboy.everyXFrames(5)))
              affectedPawn.draw = (affectedPawn.draw) ? false : true;
              else if (tileIndex > enemyPawnEnd)
                tileIndex = invalidTile;
            break;
          }

          case false:
          {
            if (tileIndex < blankTile)
              affectedPawn.draw = true;
              else if (tileIndex > enemyPawnEnd)
                board[y][x] = invalidTile;
            break;
          }
        }
        break;
      }

      default:
        break;
          
  }
}


//Reverts defeated pawns and "X" and "O" tiles into blank tiles.
void determinePawnDraw(uint8_t & tileIndex)
{
  if ((tileIndex > enemyPawnEnd) || (pawn[tileIndex].energy == 0))
    tileIndex = blankTile;
    else pawn[tileIndex].draw = true;
            
  pawn[tileIndex].energyPrint = pawn[tileIndex].energy;
}


//Checks if all of the pawns on one side are defeated.
bool checkPawnCondition(uint8_t pawnStartingIndex)
{

  uint8_t loopEnd = pawnStartingIndex + 3;
  for (uint8_t index = pawnStartingIndex; index < loopEnd; ++index)
  {
    Pawn affectedPawn = pawn[index];
      if ((affectedPawn.zodiac != Zodiac::None) && (affectedPawn.energy > 0))
        return false;
  }

  return true;
}


//Updates board in a specific manner, depending on which turn is active.
void updateBoard()
{
  bool pawnsWithoutDamage = true;

  for (uint8_t boardX = 0; boardX < 4; ++boardX)
    for (uint8_t boardY = 0; boardY < 4; ++boardY)
    {
      uint8_t & tileIndex = board[boardY][boardX];

      if (selectedPawn == tileIndex)
        {
          selectedPawnX = boardX;
          selectedPawnY = boardY;
        }

  const uint8_t playerPawn = 0;
  const uint8_t opponentPawn = 1;

  switch (tileIndex / 3)
  {
    case playerPawn:
    {
      if ((checkPawnCondition(enemyPawnStart)) || (boardX == 3))
        {
          battleResultsCounter = 0;
          turn = Turn::Neither;
          battleVictory = true;
        }
      break;
    }

    case opponentPawn:
    {
      if ((checkPawnCondition(playerPawnStart)) || (boardX == 0))
        {
          selectedAction = 4;
          battleResultsCounter = 0;
          turn = Turn::Neither;
          battleVictory = false;
        }
      break;
    }

    default:
      break;
  }

     switch (turn)
     {

      case Turn::Player:
      {
      switch (battleAction)
      { 
        case BattleAction::PawnAndAction:
        {
          determinePawnDraw(tileIndex);
          break;
        }

        case BattleAction::Target:
        {
          if (tileIndex < blankTile)
            pawn[tileIndex].energyPrint = pawn[tileIndex].energy;
          determineBoardTarget(boardX, boardY, tileIndex, pawn[tileIndex]);

          break;
        }

        case BattleAction::Damage:
        {
          reduceEnergyAndDamage(boardX, boardY, pawnsWithoutDamage, pawn[tileIndex]);
          break;
        }
        break;
      }
      break;
     }

     case Turn::Opponent:
     {
      switch (battleAction)
      {
        default:
        {
          determinePawnDraw(tileIndex);
          break;
        }

        case BattleAction::Damage:
        {
          reduceEnergyAndDamage(boardX, boardY, pawnsWithoutDamage, pawn[tileIndex]);
          break;
        }
      }
      break;
     }
    

     case Turn::Neither:
     {
        determinePawnDraw(tileIndex);
     }
     default:
       break;
     
      }
    }
}