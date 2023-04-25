#pragma once

uint8_t board[4][4];

void setupPawns()
{
  const uint8_t player = 0;
  const uint8_t foe = 1;
  //clears board
  for (uint8_t x = 0; x < 4; ++x)
    for (uint8_t y = 0; y < 4; ++y)
      board[y][x] = 6;

  for (uint8_t index = 0; index < 6; ++index)
  {
    pawn[index].draw = false;
    pawn[index].damage = 0;
    if (pawn[index].zodiac != Zodiac::None)
    {
     pawn[index].draw = true;
     uint8_t side = index / 3;
     switch (side)
     {
        case player:
        {
          if (pawn[index].species == Species::Trikurn)
            pawn[index].specialAttack = getSpecialAttack(pawn[index]);
          pawn[index].direction = Direction::Right;
          board[0][0] = board[1][0];
          board[1][0] = board[2][0];
          board[2][0] = index;
          break;
        }

        case foe:
        {
          pawn[index].direction = Direction::Left;
          board[index - 2][3] = index;
          break;
        }
     }

    }
  }
}
  //for(uint8_t index = 0; index < 6; ++index)
    //pawn[index].draw = true;

//guarentees that a foe pawn of the generated number is created
 //uint8_t enemyTeamSize = random(0, 3);

//Configures the player's pawns
 /*for (int8_t pawnIndex = 0; pawnIndex < 3; ++pawnIndex)
 {

    generatePawn(pawn[pawnIndex], 249, 16);

    pawn[pawnIndex].draw = true;

    pawn[pawnIndex].damage = 0;

    //pawn[pawnIndex].energy = 0;
      
    if (pawn[pawnIndex].zodiac != Zodiac::None)
    {
      createStats(pawn[pawnIndex]);

      pawn[pawnIndex].direction = Direction::Right;

      board[0][0] = board[1][0];
      board[1][0] = board[2][0];
      board[2][0] = pawnIndex;
    }*/
//Creates Foe Pawns
/*
for (uint8_t pawnIndex = 0; pawnIndex < 3; ++pawnIndex)
{
  uint8_t const enemyPawnStart = 3;

  pawn[pawnIndex + enemyPawnStart].zodiac = Zodiac::None;

  if (pawnIndex <= enemyTeamSize)
    generateNewPawn(pawn[pawnIndex + enemyPawnStart]);

  pawn[pawnIndex + enemyPawnStart].draw = true;

  pawn[pawnIndex + enemyPawnStart].damage = 0;

  pawn[pawnIndex + enemyPawnStart].energy = 0;

  if (pawn[pawnIndex + enemyPawnStart].zodiac != Zodiac::None)
  {
    createStats(pawn[pawnIndex + enemyPawnStart]);

    pawn[pawnIndex + enemyPawnStart].direction = Direction::Left;

    //pawn[pawnIndex + enemyPawnStart].actionCost = (pawn[pawnIndex + enemyPawnStart].actionCost + 1) / 2;

    pawn[pawnIndex + enemyPawnStart].specialAttack = SpecialAttack::Hit;


  }
}

}*/