#pragma once

void renderCatch()
{
  if (emptyBoxIndex != invalidBoxIndex)
  {
    //drawTextBox(53, 0, 51, 6, WHITE);
    //tinyfont.print(F("KEEP PAWN?"));
    drawTextBox(0, 43, 36, 6, WHITE);
    tinyfont.print(F("(A)KEEP"));
    drawTextBox(0, 50, 36, 6, WHITE);
    tinyfont.print(F("(B)FREE"));
    drawPawnStats(pawn[3], false);
    drawPawn(pawn[3].species, 82, 24, BLACK, Direction::Right);
  }
}