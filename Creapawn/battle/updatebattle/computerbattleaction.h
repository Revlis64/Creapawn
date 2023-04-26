#pragma once


struct Context
{
  uint8_t potentialPriority = 0;
  ComputerAction potentialComputerAction = ComputerAction::None;
  uint8_t potentialSelectedSquareX = 0;
  uint8_t potentialSelectedSquareY = 0;
};

bool analyseFirstColumn(uint8_t y)
{
  uint8_t pawnIndex = board[y][1];
  uint8_t secondPawnIndex = board[y][2];

  if ((pawnIndex < enemyPawnStart) && (secondPawnIndex == blankTile))
    return true;
  
  return false;
}

uint8_t findPlayerPawn()
{
  if (pawn[previouslySelectedPawn].energy > 0)
    return previouslySelectedPawn;
   else for (uint8_t pawnPreselect = 0; pawnPreselect < 3; ++pawnPreselect)
  {
    if ((pawn[pawnPreselect].zodiac != Zodiac::None) && (pawn[pawnPreselect].energy > 0))
    {
      return pawnPreselect;
    }
  }
  return invalidPawnIndex;
}



void analyseBottomLeft(uint8_t x, uint8_t y, Context & context)
{
  uint8_t prePotentialPriority = (board[y][3] == blankTile) ? 1 : 0;

  if (board[y][x] <= playerPawnEnd)
    prePotentialPriority += 2;

  if (((board[y][x] <= playerPawnEnd) || (analyseFirstColumn(y))) && (context.potentialPriority < prePotentialPriority))
  {
    context.potentialPriority = prePotentialPriority;
    context.potentialComputerAction = ComputerAction::Move;
    context.potentialSelectedSquareX = x + 1;
    context.potentialSelectedSquareY = y;
  }
}



void analyseMidLeft(uint8_t x, uint8_t y, Context & context)
{
  uint8_t priorPotentialPriority = context.potentialPriority;
  uint8_t tileIndex = board[y][x];

  switch (tileIndex)
  {
    case 0:
    case 1:
    case 2:
    {
      uint8_t prePotentialPriority = 2;

      if (board[y][3] == blankTile)
        prePotentialPriority = 3;

      if ((context.potentialPriority < prePotentialPriority) && (tileIndex != enduredPawn))
      {
        context.potentialPriority = prePotentialPriority;
        context.potentialComputerAction = ComputerAction::Attack;
      }
      break;
    }

    case blankTile:
    {
      if (context.potentialPriority < 2)
      {
        context.potentialPriority = 2;
        context.potentialComputerAction = ComputerAction::Move;
      }
      break;
    }

    default:
      break;
  }

  if (context.potentialPriority > priorPotentialPriority)
  {
    context.potentialSelectedSquareX = x;
    context.potentialSelectedSquareY = y;
  }
}



void analyseTopLeft(uint8_t x, uint8_t y, Context & context)
{
  uint8_t prePotentialPriority = (board[y][3] == blankTile) ? 2 : 0;

  if ((board[y][x] <= playerPawnEnd) && ((x + 1) == 3))
    prePotentialPriority += 2;
    else if (board[y][x] <= playerPawnEnd)
      prePotentialPriority += 1;

  if (((board[y][x] <= playerPawnEnd) || (analyseFirstColumn(y))) && (context.potentialPriority < prePotentialPriority))
  {
    context.potentialPriority = prePotentialPriority;
    context.potentialComputerAction = ComputerAction::Move;
    context.potentialSelectedSquareX = x + 1;
    context.potentialSelectedSquareY = y;
  }
}



void analyseAbove(uint8_t x, uint8_t y, Context & context)
{
  uint8_t pawnIndex = board[y][x];

  switch (pawnIndex)
  {
    case 0:
    case 1:
    case 2:
    {
      if ((context.potentialPriority < 4) && (pawnIndex != enduredPawn))
      {
        context.potentialPriority = 4;
        context.potentialComputerAction = ComputerAction::Attack;
        context.potentialSelectedSquareX = x;
        context.potentialSelectedSquareY = y;
      }
      break;
    }

    case 3:
    case 4:
    case 5:
    {
      if (context.potentialSelectedSquareY == (y))
      {
        context.potentialPriority = 0;
        context.potentialComputerAction = ComputerAction::None;
        context.potentialSelectedSquareX = x; 
        context.potentialSelectedSquareY = y + 1;
      }
      break;
    }

    default:
     break;
  }
}



void analyseBelow(uint8_t x, uint8_t y, Context & context)
{
  uint8_t pawnIndex = board[y][x];

  switch (pawnIndex)
  {
    case 0:
    case 1:
    case 2:
    {
      if ((context.potentialPriority < 4) && (pawnIndex != enduredPawn))
      {
        context.potentialPriority = 4;
        context.potentialComputerAction = ComputerAction::Attack;
        context.potentialSelectedSquareX = x;
        context.potentialSelectedSquareY = y;
      }
      break;
    }

    case 3:
    case 4:
    case 5:
    {
      if (context.potentialSelectedSquareY == y)
      {
        context.potentialPriority = 0;
        context.potentialComputerAction = ComputerAction::None;
        context.potentialSelectedSquareX = x;
        context.potentialSelectedSquareY = y - 1;
      }
      break;
    }

    default:
      break;
  }
}



void determineComputerOffensive(uint8_t x, uint8_t y, Context & context)
{
  uint8_t priorPotentialPriority = context.potentialPriority;
  switch (board[y][x - 1])
  {
    case 0:
    case 1:
    case 2:
    {
      if ((context.potentialPriority < 2) && (board[y][x - 1] != enduredPawn))
      {
        context.potentialPriority = 2;
        context.potentialComputerAction = ComputerAction::Attack;
      }
      break;
    }
    case blankTile:
    {
      if (context.potentialPriority < 5)
      {
        context.potentialPriority = 5;
        context.potentialComputerAction = ComputerAction::Move;
      }
      break;
    }
    default:
      break;
  }

  if (context.potentialPriority > priorPotentialPriority)
  {
    context.potentialSelectedSquareX = 0;
    context.potentialSelectedSquareY = y;
  }
}



void computerPass()
{
  const uint8_t move = 0;
  if (computerActionTaken == false)
    ++skipCounter;

  if ((skipCounter == 15) || (computerActionTaken == true))
  {
    computerActionTaken = false;
    skipCounter = 0;
    selectedPawn = findPlayerPawn();
    selectedAction = move;
    turn = Turn::Player;
    battleAction = BattleAction::PawnAndAction;
    actionPoints[0] = ((actionPoints[0] + 5) > 9) ? 9 : (actionPoints[0] + 5);
    enduredPawn = invalidPawnIndex;
  }
}



void updateComputerBattleAction()
{

  switch (battleAction)
  {
    case BattleAction::PawnAndAction:
    {
      computerAction = ComputerAction::None;
      uint8_t computerPriority = 0;

      for (uint8_t x = 3; x > 0; --x)
        for (uint8_t y = 0; y < 4; ++y)
        {

          Context context;

          if (((board[y][x] < 6) && (board[y][x] > 2)) && ((pawn[board[y][x]].actionCost + 1) <= actionPoints[1]))
          {
            switch (x)
            {
              case 2:
              case 3:
              {
                if (y > 0)
                  analyseTopLeft((x - 1), (y - 1), context);
                analyseMidLeft((x - 1), y, context);
                if (y < 3)
                  analyseBottomLeft((x -1), (y + 1), context);
                if (y > 0)
                  analyseAbove(x, (y - 1), context);
                if (y < 3)
                  analyseBelow(x, (y + 1), context);
                break;
              }
              
              case 1:
              {
                determineComputerOffensive(x, y, context);
              }

              default:
                break;
            }
          }
            if (context.potentialPriority > computerPriority)
            {
              selectedPawn = board[y][x];
              computerAction = context.potentialComputerAction;
              computerPriority = context.potentialPriority;
              selectedSquareX = context.potentialSelectedSquareX;
              selectedSquareY = context.potentialSelectedSquareY;
              selectedPawnX = x;
              selectedPawnY = y;
            }
        }

      if (computerAction == ComputerAction::None)
      {  
        computerPass();
      } else battleAction = BattleAction::Target;
      
      break;
    }

    case BattleAction::Target:
    {
      computerActionTaken = true;
      pawn[selectedPawn].direction = Direction::Left;
      switch (computerAction)
      {
        case ComputerAction::Move:
        {
          board[selectedSquareY][selectedSquareX] = board[selectedPawnY][selectedPawnX];
          board[selectedPawnY][selectedPawnX] = blankTile;
          actionPoints[1] -= pawn[selectedPawn].actionCost;
          battleAction = BattleAction::PawnAndAction;
          break;
        }
        case ComputerAction::Attack:
        {
          deployAttack(SpecialAttack::Hit);
          break;
        }

        default:
          break;

      }
      break;
    }

    default:
      break;
  }
}