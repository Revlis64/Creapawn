#pragma once

uint8_t findComputerPawn()
{
  for (uint8_t pawnPreselect = 3; pawnPreselect < 6; ++pawnPreselect)
  {
    if ((pawn[pawnPreselect].zodiac != Zodiac::None) && (pawn[pawnPreselect].energy > 0))
    {
      return pawnPreselect;
    }
  }
  return invalidPawnIndex;
}


AttackTarget determineAttackTarget()
{
  switch (selectedAction)
  {
    case 0:
      return AttackTarget::CloseEmptyTiles;
    case 1:
      return AttackTarget::CloseEnemy;
    case 2:
      switch (pawn[selectedPawn].specialAttack)
      {
       case SpecialAttack::Sacrifice:
       case SpecialAttack::Strike:
       case SpecialAttack::Hit:
         return AttackTarget::CloseEnemy;
       case SpecialAttack::Blast:
         return AttackTarget::AnyEnemy;
       case SpecialAttack::HealAll:
         return AttackTarget::AllAllies;
       case SpecialAttack::Shockwave:
         return AttackTarget::AllEnemies;
       case SpecialAttack::Endure:
         return AttackTarget::Self;
       case SpecialAttack::Swap:
         return AttackTarget::ClosePawn;
      }
    default:
      return AttackTarget::None;
  }
}



void movePlayerPawnAndActionCursor()
{

  if(arduboy.justPressed(UP_BUTTON))
  {
    if (selectedPawn > 0)
    {
      for (int8_t pawnSelectionCounter = (selectedPawn - 1); pawnSelectionCounter > -1; --pawnSelectionCounter)
        if(pawn[pawnSelectionCounter].energy > 0)
        {
          selectedPawn = pawnSelectionCounter;
          break;
        }
    }
  }

  if(arduboy.justPressed(DOWN_BUTTON))
  {
    if (selectedPawn < 2)
    {
      for (uint8_t pawnSelectionCounter = (selectedPawn + 1); pawnSelectionCounter < 3; ++pawnSelectionCounter)
        if ((pawn[pawnSelectionCounter].energy > 0) && (pawn[pawnSelectionCounter].zodiac != Zodiac::None))
        {
          selectedPawn = pawnSelectionCounter;
          break;
        }
    }
  }
        
  if(arduboy.justPressed(LEFT_BUTTON) && selectedAction > 0)
    --selectedAction;
  if(arduboy.justPressed(RIGHT_BUTTON) && selectedAction < 3)
    ++selectedAction;

  uint8_t actionCost = pawn[selectedPawn].actionCost;

  if (selectedAction == 1)
    actionCost += 1;
    else if (selectedAction == 2)
      actionCost += 2;

  if ((arduboy.justPressed(A_BUTTON)) && ((actionPoints[0] >= actionCost) || (selectedAction == 3)))
  {
    selectedSquareX = selectedPawnX;
    selectedSquareY = selectedPawnY;
    directionHolder = pawn[selectedPawn].direction;
    battleAction = BattleAction::Target;
    attackTarget = determineAttackTarget();
  }

  if (arduboy.justPressed(B_BUTTON))
    selectedAction = 3;

}



void moveCursor()
{  
  if ((arduboy.justPressed(UP_BUTTON)) && (selectedSquareY > 0))
    --selectedSquareY;
    else if ((arduboy.justPressed(DOWN_BUTTON)) && (selectedSquareY < 3))
      ++selectedSquareY;
      else if ((arduboy.justPressed(LEFT_BUTTON)) && (selectedSquareX > 0))
        --selectedSquareX;
        else if ((arduboy.justPressed(RIGHT_BUTTON)) && (selectedSquareX < 3))
          ++selectedSquareX;
    
      
  Direction directionSelector = (selectedPawnX < selectedSquareX) ? Direction::Right : Direction::Left;
  if ((selectedSquareY == selectedPawnY) && (selectedSquareX != selectedPawnX)) 
    pawn[selectedPawn].direction = directionSelector;
}



void selectAndConfirmTarget(SpecialAttack specialAttack)
{

  const uint8_t move = 0;
  const uint8_t hit = 1;
  const uint8_t special = 2;
  const uint8_t end = 3;
  const uint8_t none = 4;

  bool results = false;
  switch (selectedAction)
  {
    case move:
      moveCursor();
      if ((arduboy.justPressed(A_BUTTON)) && ((board[selectedSquareY][selectedSquareX] == validTile) || (board[selectedSquareY][selectedSquareX] == blankTile)))
      {
        actionPoints[0] -= pawn[selectedPawn].actionCost;
        uint8_t boardIndexHolder = board[selectedSquareY][selectedSquareX];
        board[selectedSquareY][selectedSquareX] = selectedPawn;
        board[selectedPawnY][selectedPawnX] = boardIndexHolder;
        battleAction = BattleAction::PawnAndAction;
      }
      if (arduboy.justPressed(B_BUTTON))
      {
        pawn[selectedPawn].direction = directionHolder;
        battleAction = BattleAction::PawnAndAction;
      }
      break;

    case hit:
      moveCursor();
      if ((arduboy.pressed(A_BUTTON)) && (board[selectedSquareY][selectedSquareX] < blankTile) && (board[selectedSquareY][selectedSquareX] > playerPawnEnd) && (checkProximity(selectedPawnX, selectedPawnY, selectedSquareX, selectedSquareY)))
        deployAttack(SpecialAttack::Hit);

      if (arduboy.justPressed(B_BUTTON))
      {
        pawn[selectedPawn].direction = directionHolder;
        battleAction = BattleAction::PawnAndAction;
      }
      break;

    case special:
    {
      switch (specialAttack)
      {
        case SpecialAttack::Sacrifice:
        case SpecialAttack::Strike:
        {
          moveCursor();
          if ((board[selectedSquareY][selectedSquareX] < blankTile) && (board[selectedSquareY][selectedSquareX] > playerPawnEnd))
            results = checkProximity(selectedPawnX, selectedPawnY, selectedSquareX, selectedSquareY);
          break;
        }

        case SpecialAttack::Swap:
        {
          moveCursor();
          if (board[selectedSquareY][selectedSquareX] < blankTile)
            results = checkProximity(selectedPawnX, selectedPawnY, selectedSquareX, selectedSquareY);
          break;
        }

        case SpecialAttack::Blast:
        {
          moveCursor();
          results = ((board[selectedSquareY][selectedSquareX] < blankTile) && (board[selectedSquareY][selectedSquareX] > playerPawnEnd)) ? true : false;
          break;
        }

        case SpecialAttack::Endure:
        case SpecialAttack::Shockwave:
        {
          results = true;
          break;
        }
        
        case SpecialAttack::HealAll:
        {
          if (((pawn[0].energy == pawn[0].maxEnergy) || (pawn[0].energy == 0)) 
          && ((pawn[1].energy == pawn[1].maxEnergy) || (pawn[1].energy == 0))
          && ((pawn[2].energy == pawn[2].maxEnergy) || (pawn[2].energy == 0)))
            battleAction = BattleAction::PawnAndAction;
            else results = true;
          break;
        }
        
        default:
          break;
      }

      if ((arduboy.justPressed(A_BUTTON)) && (results == true))
        deployAttack(specialAttack);

      if (arduboy.justPressed(B_BUTTON))
      {
        pawn[selectedPawn].direction = directionHolder;
        battleAction = BattleAction::PawnAndAction;
      }
      break;
    }

    case end:
    {
      previouslySelectedPawn = selectedPawn;
      selectedPawn = findComputerPawn();
      selectedAction = none;
      turn = Turn::Opponent;
      battleAction = BattleAction::PawnAndAction;
      if (firstTurn == false)
        actionPoints[1] = ((actionPoints[1] + 5) > 9) ? 9 : (actionPoints[1] + 5);
        else firstTurn = false;
      break; 
    } 
  }
}



void updatePlayerBattleAction()
{
  
  switch (battleAction)
  {
    case BattleAction::PawnAndAction:
    {
      movePlayerPawnAndActionCursor();
      break;
    }

    case BattleAction::Target:
    {
      selectAndConfirmTarget(pawn[selectedPawn].specialAttack);
      break;
    }

    default:
      break;
  }
}