#pragma once

struct Context
{
  uint8_t potentialPriority = 0;
  ComputerAction potentialComputerAction = ComputerAction::None;
  uint8_t potentialSelectedSquareX = 0;
  uint8_t potentialSelectedSquareY = 0;
};

bool checkForAllies(uint8_t nonTargetPawn)
{

  const bool noAllies = 1;
  const bool allies = 0;

  for (uint8_t squareX = 2; squareX < 4; ++squareX)
    for (uint8_t squareY = 0; squareY < 4; ++squareY)
      if ((board[squareY][squareX] >= enemyPawnStart) && (board[squareY][squareX] <= enemyPawnEnd) && (board[squareY][squareX] != nonTargetPawn))
        return allies;

  return noAllies;
}

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



void analyseUpperOrLowerLeft(uint8_t x, uint8_t y, uint8_t nonTarget, bool upMove, Context & context)
{

  const bool noAllies = 1;
  uint8_t prePotentialPriority = 3;

  switch (upMove)
  {
    default:
    {
      if (board[y + 1][x] <= playerPawnEnd)
        prePotentialPriority -= 1;
      break;
    }
    case false:
    { 
      if (board[y - 1][x] <= playerPawnEnd)
        prePotentialPriority -= 1;
      break;
    }
  }

  if (((x < 2) && ((board[y][3] != blankTile) || (checkForAllies(nonTarget) == noAllies))) || (board[y][x] == blankTile))
    prePotentialPriority -= 1;

  if ((checkForAllies(nonTarget) == noAllies) && (upMove))
    prePotentialPriority -= 1;


  if (((board[y][x] <= playerPawnEnd) || (analyseFirstColumn(y))) && (board[y][x + 1] == blankTile) && (context.potentialPriority < prePotentialPriority))
  {
    context.potentialPriority = prePotentialPriority;
    context.potentialComputerAction = ComputerAction::Move;
    context.potentialSelectedSquareX = x + 1;
    context.potentialSelectedSquareY = y;
  }
}



void analyseMidLeft(uint8_t x, uint8_t y, Context & context)
{
  const bool allies = 0;

  uint8_t priorPotentialPriority = context.potentialPriority;
  uint8_t tileIndex = board[y][x];
  uint8_t prePotentialPriority = 2;

  switch (tileIndex)
  {
    case 0:
    case 1:
    case 2:
    {
      
      if ((checkForAllies(board[y][x + 1]) == allies) && (board[y][3] != blankTile))        prePotentialPriority -= 1;

      if ((x == 2) || (board[y][3] == blankTile))
        prePotentialPriority += 1;

      if ((context.potentialPriority < prePotentialPriority) && (!endure))
      {
        context.potentialPriority = prePotentialPriority;
        context.potentialComputerAction = ComputerAction::Attack;
      }
      break;
    }

    case blankTile:
    {
      if ((x < 2) && (checkForAllies(board[y][x + 1]) == allies))       
        prePotentialPriority -= 1;

      if (context.potentialPriority < prePotentialPriority)
      {
        context.potentialPriority = prePotentialPriority;
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


void analyseAboveOrBelow(uint8_t x, uint8_t y, Context & context)
{
  uint8_t pawnIndex = board[y][x];

  switch (pawnIndex)
  {
    case 0:
    case 1:
    case 2:
    {
      if ((context.potentialPriority < 3) && (!endure))
      {
        context.potentialPriority = 3;
        context.potentialComputerAction = ComputerAction::Attack;
        context.potentialSelectedSquareX = x;
        context.potentialSelectedSquareY = y;
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
      if ((context.potentialPriority < 2) && (!endure))
      {
        context.potentialPriority = 2;
        context.potentialComputerAction = ComputerAction::Attack;
      }
      break;
    }
    case blankTile:
    {
      if (context.potentialPriority < 4)
      {
        context.potentialPriority = 4;
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
  const uint8_t player = 0;
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
    replenishActionPoints(player);
    endure = false;
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
                  analyseUpperOrLowerLeft((x - 1), (y - 1), board[y][x], true, context); //UP
                analyseMidLeft((x - 1), y, context);
                if (y < 3)
                  analyseUpperOrLowerLeft((x - 1), (y + 1), board[y][x], false, context); //DOWN
                if (y > 0)
                  analyseAboveOrBelow(x, (y - 1), context); //ABOVE
                if (y < 3)
                  analyseAboveOrBelow(x, (y + 1), context); //BELOW
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