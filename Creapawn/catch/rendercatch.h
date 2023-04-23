#pragma once

void renderCatch()
{
  if (emptyBoxIndex != invalidBoxIndex)
  {
    drawTextBox(53, 0, 46, 6, WHITE);
    tinyfont.print(F("ADD PAWN?"));
    drawTextBox(0, 43, 31, 6, WHITE);
    tinyfont.print(F("(A)YES"));
    drawTextBox(0, 50, 31, 6, WHITE);
    tinyfont.print(F("(B)NO"));
    drawPawnStats(pawn[3], false);
    drawPawn(pawn[3].species, 72, 24, BLACK, Direction::Right);
  }
}