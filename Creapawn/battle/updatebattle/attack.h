#pragma once

//determines and returns the attacking power of the attacking pawn towards the defending pawn based off of their opposing stats.
uint8_t calculateDamage(Pawn attackingPawn, Pawn defendingPawn)
{

  enum class Effectiveness : uint8_t
  {
    NotEffective,
    Effective,
    VeryEffective,
  };

  Effectiveness typeEffectivenessTable[5][5]
          //Defender
  {       //Null                        Synth                         Nature                        Mystic                        Omni
//Attacker
/*Null*/  {Effectiveness::Effective,    Effectiveness::NotEffective,  Effectiveness::NotEffective,  Effectiveness::NotEffective,  Effectiveness::Effective},
/*Synth*/ {Effectiveness::NotEffective, Effectiveness::Effective,     Effectiveness::VeryEffective, Effectiveness::NotEffective,  Effectiveness::VeryEffective},
/*Nature*/{Effectiveness::NotEffective, Effectiveness::NotEffective,  Effectiveness::Effective,     Effectiveness::VeryEffective, Effectiveness::VeryEffective},
/*Mystic*/{Effectiveness::NotEffective, Effectiveness::VeryEffective, Effectiveness::NotEffective,  Effectiveness::Effective,     Effectiveness::VeryEffective},
/*Omni*/  {Effectiveness::Effective,    Effectiveness::VeryEffective, Effectiveness::VeryEffective, Effectiveness::VeryEffective, Effectiveness::Effective}
  };
  
  uint8_t attackerType = static_cast<uint8_t>(attackingPawn.type);
  uint8_t defenderType = static_cast<uint8_t>(defendingPawn.type);

  Effectiveness typeEffectiveness = typeEffectivenessTable[attackerType][defenderType];
  uint8_t typeDamageMultiplier;
  uint8_t typeDamageDivider;

  switch (typeEffectiveness)
  {
    case Effectiveness::NotEffective:
    {
      typeDamageMultiplier = 1;
      typeDamageDivider = 2;
      break;
    }

    default:
    {
      typeDamageMultiplier = 1;
      typeDamageDivider = 1;
      break;
    }

    case Effectiveness::VeryEffective:
    {
      typeDamageMultiplier = 2;
      typeDamageDivider = 1;
      break;
    }
  }

  uint8_t damage = (attackingPawn.power * typeDamageMultiplier) / typeDamageDivider;

  if (((gameState == GameState::Battle) && (selectedAction == 2)) || (gameState == GameState::Box) || (gameState == GameState::Catch))
  {
    switch (attackingPawn.specialAttack)
    {
      //does damage equal to the defending pawn's energy, regardless of differing types of the attacking and defending pawn.
      case SpecialAttack::Sacrifice:
      {
        damage = defendingPawn.energy - 1;
        break;
      }

      //doubles the damage.
      case SpecialAttack::Strike:
      {
        damage = damage * 2;
        break;
      }

      //Divides the damage by 3;
      case SpecialAttack::Shockwave:
      {
        damage = damage / 3;
        break;
      }

      default:
        break;
    }
  }
  
  return ++damage;
}


//Executes the attack of the attacking pawn.
void deployAttack(SpecialAttack specialAttack)
{
  uint8_t specialAttackCost = (specialAttack == SpecialAttack::Hit) ? 1 : 2;
  uint8_t attackersActionPoints = static_cast<uint8_t>(turn);
  
  actionPoints[attackersActionPoints] -= (pawn[selectedPawn].actionCost + specialAttackCost);

  uint8_t damage = calculateDamage(pawn[selectedPawn], pawn[board[selectedSquareY][selectedSquareX]]);

  switch (specialAttack)
  {
    
    //damages the targeted pawn for estimated damage.
    case SpecialAttack::Blast:
    case SpecialAttack::Strike:
    case SpecialAttack::Hit:
    {
      if ((pawn[board[selectedSquareY][selectedSquareX]].energy - damage) <= 0)
        pawn[board[selectedSquareY][selectedSquareX]].damage = pawn[board[selectedSquareY][selectedSquareX]].energy;
      else pawn[board[selectedSquareY][selectedSquareX]].damage = damage;
      battleAction = BattleAction::Damage;
      break;  
    }
      
    //Makes the attacking pawn invulnerable to attack.
    case SpecialAttack::Endure:
    {
      enduredPawn = selectedPawn;
      battleAction = BattleAction::PawnAndAction;
      break;
    }

    //Swaps the positions of the targeted and attacking pawn.
    //Any pawn can be targeted with this move within range, other than the attack pawn itself.
    case SpecialAttack::Swap:
    {
      directionHolder = pawn[selectedPawn].direction;
      pawn[selectedPawn].direction = pawn[board[selectedSquareY][selectedSquareX]].direction;
      pawn[board[selectedSquareY][selectedSquareX]].direction = directionHolder;   

      uint8_t pawnHolder = board[selectedSquareY][selectedSquareX];
      board[selectedSquareY][selectedSquareX] = board[selectedPawnY][selectedPawnX];
      board[selectedPawnY][selectedPawnX] = pawnHolder;
      battleAction = BattleAction::PawnAndAction;
      break;
    }      

    //Hits all of the opposing pawns for the established damage.
    case SpecialAttack::Shockwave:
    {
      for (uint8_t enemyPawnIndex = 3; enemyPawnIndex < 6; ++enemyPawnIndex)
      {
        damage = calculateDamage(pawn[selectedPawn], pawn[enemyPawnIndex]);

        if ((pawn[enemyPawnIndex].energy - damage) <= 0)
          pawn[enemyPawnIndex].damage = pawn[enemyPawnIndex].energy;
        else pawn[enemyPawnIndex].damage = damage;
      }
      battleAction = BattleAction::Damage;
      break;
    }    
    
    //Damages both the attacking pawn and opposing pawn for their remaining energy.
    case SpecialAttack::Sacrifice:
    {
    pawn[board[selectedSquareY][selectedSquareX]].damage = pawn[board[selectedSquareY][selectedSquareX]].energy;
    pawn[selectedPawn].damage = pawn[selectedPawn].energy;
    for (uint8_t pawnPreselect = 0; pawnPreselect < 3; ++pawnPreselect)
      if ((pawn[pawnPreselect].zodiac != Zodiac::None) && (pawn[pawnPreselect].energy > 0) && (pawnPreselect != selectedPawn))
      {
        selectedPawn = pawnPreselect;
        break;
      }
      battleAction = BattleAction::Damage;
      break;
    }
    
    //Heals all of the player's pawn for half their max energy plus one.
    case SpecialAttack::HealAll:
    {
      for (uint8_t pawnIndex = 0; pawnIndex < 3; ++pawnIndex)
        if (pawn[pawnIndex].energy > 0) 
          pawn[pawnIndex].energy = ((pawn[pawnIndex].energy + (pawn[pawnIndex].maxEnergy / 2)) > pawn[pawnIndex].maxEnergy) ? pawn[pawnIndex].maxEnergy : (pawn[pawnIndex].energy + (pawn[pawnIndex].maxEnergy / 2)); 
      battleAction = BattleAction::PawnAndAction;
      break;
    }

    default:
      break;    
     
  }
}