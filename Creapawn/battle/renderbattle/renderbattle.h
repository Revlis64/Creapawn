#pragma once

void drawBoardCursor(uint8_t x, uint8_t y)
{
  arduboy.drawBitmap((x * 16) + 64, y * 16, boardCursorBackground, 16, 16, 0);
  arduboy.drawBitmap((x * 16) + 64, y * 16, boardCursorForeground, 16, 16, 1);
}

//Draws the text boxes and names on the left side of the battle screen
void drawNameBoxes()
{
  uint8_t nameBoxOrganizer = 0;
    for (uint8_t nameBoxCounter = 0; nameBoxCounter < 6; ++nameBoxCounter)
    {
      if (nameBoxCounter == 3)
        nameBoxOrganizer = 3;
      
      uint8_t boxBump = (nameBoxCounter == selectedPawn) ? 3 : 0;

      if (pawn[nameBoxCounter].zodiac != Zodiac::None)
      {
        uint8_t textBoxColor = (pawn[nameBoxCounter].energy == 0) ? BLACK : WHITE;

        drawTextBox(0 + boxBump, ((nameBoxOrganizer * 7) + (8 * (nameBoxOrganizer / 3))), 61, 6, textBoxColor);
        tinyfont.print(getName(pawn[nameBoxCounter].species));
        tinyfont.setCursor(51 + boxBump, ((nameBoxOrganizer * 7) + (8 * (nameBoxOrganizer / 3))) + 1);

        bool energyDrawIndex = true;

        switch (battleAction)
        {
          case BattleAction::Target:
          {
            switch (attackTarget)
            {
              case AttackTarget::CloseEnemy:
              case AttackTarget::AnyEnemy:
              {
                energyDrawIndex = ((nameBoxCounter == board[selectedSquareY][selectedSquareX]) && (pawn[board[selectedSquareY][selectedSquareX]].draw == false)) ? false : true;
                break;
              }

              case AttackTarget::ProtectAllies:
              case AttackTarget::CloseEmptyTiles:
              case AttackTarget::ClosePawn:
                break;

              case AttackTarget::HealAllies:
              {
                energyDrawIndex = ((pawn[nameBoxCounter].energy == pawn[nameBoxCounter].maxEnergy) || (pawn[nameBoxCounter].energy == 0)) ? true : pawn[nameBoxCounter].draw;
                break;
              }

              default:
              {
                energyDrawIndex = (pawn[nameBoxCounter].energy > 0) ? pawn[nameBoxCounter].draw : true;
                break;
              }

            }
            break;
          }

          default:
            energyDrawIndex = true;
            break;
        }

        if ((energyDrawIndex == true) && ((nameBoxCounter >= enemyPawnStart) || (!endure)))
        { 
          determineZeroPrint(pawn[nameBoxCounter].energyPrint);
          tinyfont.print(pawn[nameBoxCounter].energyPrint);
        } else if ((endure) && (nameBoxCounter <= playerPawnEnd))
          tinyfont.print("Ti");

        ++nameBoxOrganizer;
      }
  }
}

//draws action boxes on the lower left side of battle screen
void drawActionBoxes(Pawn pawn)
{
tinyfont.setTextColor(BLACK);
  uint8_t specialAttackIndex = static_cast<uint8_t>(pawn.specialAttack);
  for(uint8_t actionBoxCounter = 0; actionBoxCounter < 4; ++actionBoxCounter)
  {

    uint8_t boxBump = (selectedAction == actionBoxCounter) ? 3 : 0;
      
    arduboy.fillRoundRect(16 * actionBoxCounter, 53 - boxBump, 14, 11, 1, WHITE);
    tinyfont.setCursor(9 + (16 * actionBoxCounter), 59 - boxBump);

    switch (actionBoxCounter)
    {
      case 0:
      {
       arduboy.drawBitmap((actionBoxCounter * 16) + 1, 55 - boxBump, move, 8, 8, 0);
       tinyfont.print(pawn.actionCost);
       break;
      }

      case 1:
      {
       arduboy.drawBitmap((actionBoxCounter * 16) + 1, 55 - boxBump, hit, 8, 8, 0);
       tinyfont.print(pawn.actionCost + 1);
       break;
      }

      case 2:
      {
      if ((turn == Turn::Opponent) || ((turn == Turn::Neither) && (battleVictory == false)))
        arduboy.drawBitmap((actionBoxCounter * 16) + 3, 55, boardCross, 8, 8, 0);
        else 
        {
          arduboy.drawBitmap((actionBoxCounter * 16) + 1, 55 - boxBump, specialAttackSprite[specialAttackIndex], 8, 8, 0);
          tinyfont.print(pawn.actionCost + 2);
        }
       break;
      }

      case 3:
      {
       arduboy.drawBitmap((actionBoxCounter * 16) + 1, 55 - boxBump, end, 12, 8, 0);
       break;
      }
    }
  }
}

void renderBoard()
{
  for (uint8_t boardX = 0; boardX < 4; ++boardX)
    for (uint8_t boardY = 0; boardY < 4; ++boardY)
    {

      arduboy.fillRect((boardX * 16) + 64, boardY * 16, 16, 16, (boardX + boardY) % 2);

      uint8_t tileIndex = board[boardY][boardX];

       switch (tileIndex)
       {
         case 0:
         case 1:
         case 2:
         case 3:
         case 4:
         case 5:
         {
           if (pawn[tileIndex].draw)
             drawPawn(pawn[tileIndex].species, (boardX * 16) + 64, boardY * 16, tileIndex / 3, pawn[tileIndex].direction);
           break;
         }

         case 7:
         {
           arduboy.drawBitmap((boardX * 16) + 68, (boardY * 16) + 4, boardCross, 8, 8, (boardX + boardY + 1) % 2);
           break;
         }

         case 8:
         {
           arduboy.drawBitmap((boardX * 16) + 68, (boardY * 16) + 4, boardCircle, 8, 8, (boardX + boardY + 1) % 2);
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
              drawBoardCursor(selectedPawnX, selectedPawnY);
              break;
            }

            case BattleAction::Target:
            {
              switch (attackTarget)
              {
                case AttackTarget::ProtectAllies:
                {
                  if (board[boardY][boardX] < 3)
                    drawBoardCursor(boardX, boardY);
                  break;
                }
                case AttackTarget::AllEnemies:
                {
                  if ((board[boardY][boardX] > 2) && (board[boardY][boardX] < 6))
                    drawBoardCursor(boardX, boardY);
                  break;
                }
                case AttackTarget::HealAllies:
                {
                  if ((board[boardY][boardX] < 3) && (pawn[board[boardY][boardX]].energy < pawn[board[boardY][boardX]].maxEnergy))
                    drawBoardCursor(boardX, boardY);
                  break;
                }
                default:
                {
                  drawBoardCursor(selectedSquareX, selectedSquareY);
                  break;
                }
              }
            break;
            }

          default:
            break;
         }
        }

        default:
          break;
       }
    }
}

void printBattleResults()
{
  switch (battleVictory)
  {
    case true:
    {
      drawTextBox(45, 28, 38, 8, 0);
      drawTextBox(46, 29, 36, 6, 1);
      tinyfont.print("VICTORY");
      break;
    }
    case false:
    {
      drawTextBox(48, 28, 33, 8, 0);
      drawTextBox(49, 29, 31, 6, 1);
      tinyfont.print("DEFEAT");
      break;
    }
  }
}

void drawCenterMenu()
{
  if ((computerActionTaken == false) && (skipCounter > 0))
  {
    drawTextBox(20, 22, 21, 6, 1);
    tinyfont.print("SKIP");
  } else arduboy.drawBitmap(28, 23, downTriangle, 8, 8, 1);
}

void renderBattle()
{
  drawNameBoxes();
  drawActionBoxes(pawn[selectedPawn]);

  for (uint8_t actionPointsIndex = 0; actionPointsIndex < 2; ++actionPointsIndex)
  {
    drawTextBox(0 + (actionPointsIndex * 45), 21 + actionPointsIndex, 16, 6, 1);
    tinyfont.print("AP");
    tinyfont.print(actionPoints[actionPointsIndex]);
  }
  if ((turn == Turn::Opponent) || ((turn == Turn::Neither) && (battleVictory == false)))
    drawCenterMenu();
    else arduboy.drawBitmap(28, 23, upTriangle, 8, 8, 1);

  renderBoard();
  if (turn == Turn::Neither)
    printBattleResults();

}
