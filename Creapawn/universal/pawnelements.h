#pragma once

enum class SpecialAttack : uint8_t 
{
  Sacrifice,
  Shockwave,
  Swap,
  Blast,
  Strike,
  Endure,
  HealAll,
  Hit,
};

enum class Species : uint8_t
{
  Voidismal,

  Audiouse,
  Boltnetic,
  Dribby,
  Luminat,
  Micrunt,
  Odrion,
  Outlectric,
  Slugamma,
  Spymera,
  Xenaucer,

  Beethrone,
  Bubblue,
  Bunnerina,
  Champanzon,
  Chloroar,
  Cribbit,
  Dashound,
  Mayham,
  Necrawler,
  Terruption,

  Chivampera,
  Dualdra,
  Faefluff,
  Grifelios,
  Mauroah,
  Pegshire,
  Polterror,
  Ravuack,
  Scardra,
  Squeamask,

  Trikurn,
};

//specific stats, which is dependent on the pawn's species
const uint8_t speciesStats[32][3]
{
  // Energy, Power, Action Cost
  //NULL
  /*VOIDISMAL*/{0, 0, 0},
  
  //SYNTH
  /*AUDIOUSE*/{2, 0, 2},
  /*BOLTNETIC*/{1, 2, 1},
  /*DRIBBY*/{2, 1, 1},
  /*LUMINAT*/{3, 0, 1},
  /*MICRUNT*/{1, 0, 3},
  /*ODRION*/{1, 3, 0},
  /*OUTLECTRIC*/{0, 1, 3},
  /*SLUGAMMA*/{3, 1, 0},
  /*SPYMERA*/{0, 2, 2},
  /*XENAUCER*/{0, 3, 1},

  //NATURE
  /*BEETHRONE*/{0, 2, 2},
  /*BUBBLUE*/{2, 2, 0,},
  /*BUNNERINA*/{1, 0, 3},
  /*CHAMPANZON*/{1, 2, 1},
  /*CHLOROAR*/{1, 1, 2},
  /*CRIBBIT*/{3, 1, 0},
  /*DASHOUND*/{2, 1, 1},
  /*MAYHAM*/{1, 3, 0},
  /*NECRAWLER*/{0, 1, 3},
  /*TERRUPTION*/{0, 3, 1},

  //MYSTIC
  /*CHIVAMPERA*/{2, 0, 2},
  /*DUALDRA*/{1, 1, 2},
  /*FAEFLUFF*/{2, 0, 2},
  /*GRIFELIOS*/{2, 2, 0},
  /*MAUROAH*/{3, 1, 0},
  /*PEGSHIRE*/{1, 1, 2},
  /*POLTERROR*/{1, 3, 0},
  /*RAVUACK*/{0, 1, 3},
  /*SCARDRA*/{0, 3, 1},
  /*SQUEAMASK*/{3, 0, 1},

  //OMNI
    /*TRIKURN*/{3, 3, 3},
};



enum class Type : uint8_t 
{
  Null,
  Synth,
  Nature,
  Mystic,
  Omni,
};

//retrieves a type, depending the the pawn's species
Type  obtainType(Species species)
{
  switch (species)
  {
    
    case Species::Audiouse:
    case Species::Boltnetic:
    case Species::Dribby:
    case Species::Luminat:
    case Species::Micrunt:
    case Species::Odrion:
    case Species::Outlectric:
    case Species::Slugamma:
    case Species::Spymera:
    case Species::Xenaucer:
      return Type::Synth;

    case Species::Beethrone:
    case Species::Bubblue:
    case Species::Bunnerina:
    case Species::Champanzon:
    case Species::Chloroar:
    case Species::Cribbit:
    case Species::Dashound:
    case Species::Mayham:
    case Species::Necrawler:
    case Species::Terruption:
      return Type::Nature;

    case Species::Chivampera:
    case Species::Dualdra:
    case Species::Faefluff:
    case Species::Grifelios:
    case Species::Mauroah:
    case Species::Pegshire:
    case Species::Polterror:
    case Species::Ravuack:
    case Species::Scardra:
    case Species::Squeamask:
      return Type::Mystic;

    case Species::Trikurn:
      return Type::Omni;

    case Species::Voidismal:
    default:
      return Type::Null;
   }
}



enum class Zodiac : uint8_t 
{
  None,
  Capricorn,
  Aquarius,
  Pisces,
  Aries,
  Taurus,
  Gemini,
  Cancer,
  Leo,
  Virgo,
  Libra,
  Scorpio,
  Sagittarius,
};

//Specific stats, which are dependent on the pawn's zodiac
const uint8_t zodiacStats[13][3]
{
  // Energy, Power, Action Cost
  /*If no pawn is present*/{0, 0, 0},
  /*CAPRICORN*/{1, 0, 3},
  /*AQUARIUS*/{2, 1, 1},
  /*PISCES*/{1, 1, 2},
  /*ARIES*/{1, 3, 0},
  /*TAURUS*/{0, 3, 1},
  /*GEMINI*/{1, 2, 1},
  /*CANCER*/{2, 2, 0},
  /*LEO*/{0, 2, 2},
  /*VIRGO*/{0, 1, 3},
  /*LIBRA*/{3, 0, 1},
  /*SCORPIO*/{3, 1, 0},
  /*SAGITTARIUS*/{2, 0, 2},
};



struct Pawn 
{
  Species species;
  Type type;
  Zodiac zodiac;
  SpecialAttack specialAttack;
  Direction direction;
  uint8_t level;
  uint8_t energy;
  uint8_t energyPrint;
  uint8_t maxEnergy;
  int8_t damage;
  uint8_t actionCost;
  uint8_t power;
  uint8_t experience;
  bool draw;

};

Pawn pawn[6];

uint8_t team[3];



//Determines pawn's zodiac
Zodiac getZodiac(uint8_t zodiacNumber)
{
  //uint8_t zodiacNumber = random(1, 13);
  Zodiac zodiac = static_cast<Zodiac>(zodiacNumber);

  return zodiac;
}

/*Zodiac getZodiac(uint8_t pawnByteIndex)
{
  uint8_t zodiacNumber = (11110000 & pawnByteIndex) >> 4;
  Zodiac zodiac = static_cast<Zodiac>(zodiacNumber);

  return zodiac;
}*/

//Creates pawn's species
Species getSpecies(uint8_t speciesNumber)
{
  //uint8_t speciesNumber = random(0, 32);
  Species species = static_cast<Species>(speciesNumber);

  return species;
}

//determines pawn's species
/*Species getSpecies(uint8_t pawnByteIndex)
{
  uint8_t speciesNumber = pawnByteIndex >> 3;
  Species species = static_cast<Species>(speciesNumber);

  return species;
}*/

void generatePawn(Pawn & pawn, uint8_t speciesNumber, uint8_t zodiacNumber, uint8_t level)
{
  pawn.zodiac = getZodiac(zodiacNumber);
  pawn.species = getSpecies(speciesNumber);

  pawn.level = level;

  if ((pawn.level == 9) || ((pawn.level == 8) && (pawn.experience == 15)))
  {
    pawn.level = 9;
    pawn.experience = 15;
  }
}

/*void generatePawn(Pawn & pawn, uint8_t pawnByteIndex, uint8_t pawnByteIndexTwo)
{
  pawn.zodiac = getZodiac(pawnByteIndexTwo);
  pawn.species = getSpecies(pawnByteIndex);

  pawn.level = (7 & pawnByteIndex) + 1;

  pawn.experience = (15 & pawnByteIndexTwo);

  if ((pawn.level == 8) && (pawn.experience == 15))
    pawn.level += 1;
}*/

//determines pawn's special attack
SpecialAttack getSpecialAttack(Pawn pawn)
{
  SpecialAttack destinedSpecialAttack;
  const SpecialAttack specialAttackTable[3][3]
  {
           //Capricorn                Taurus                 Virgo
           //Aquarius                 Gemini                 Libra
           //Pisces                   Cancer                 Scorpio
           //Aries                    Leo                    Sagittarius
/*Synth*/  {SpecialAttack::Shockwave, SpecialAttack::Swap,   SpecialAttack::Blast},
/*Nature*/ {SpecialAttack::Swap,      SpecialAttack::Strike, SpecialAttack::Endure},
/*Mystic*/ {SpecialAttack::Blast,     SpecialAttack::Endure, SpecialAttack::HealAll}
  };

  switch (pawn.type)
  {

    case Type::Null:
    {
      return SpecialAttack::Sacrifice;
    }

    case Type::Omni:
    {
      //creates random special attack for pawn with omni typing
      uint8_t randomSpecialAttack = random(0, 7);
      return destinedSpecialAttack = static_cast<SpecialAttack>(randomSpecialAttack);
    }

    case Type::Synth: 
    case Type::Nature: 
    case Type::Mystic:
    default:
    {
      uint8_t typeY = static_cast<uint8_t>(pawn.type);
      uint8_t zodiacX = static_cast<uint8_t>(pawn.zodiac);
      --typeY;
      zodiacX = (zodiacX - 1) >> 2;
      return destinedSpecialAttack = specialAttackTable[typeY][zodiacX];
    }
  }

}


//takes pawn's zodiac, level, and species to create unique stats. Also assigns the pawn a type depending on their species
void createStats (Pawn & pawn)
{

  const uint8_t energyStat = 0;
  const uint8_t powerStat = 1;
  const uint8_t actionCostStat = 2;

  uint8_t zodiacNumber = static_cast<uint8_t>(pawn.zodiac);
  uint8_t speciesNumber = static_cast<uint8_t>(pawn.species);

  pawn.type = obtainType(pawn.species);
  pawn.maxEnergy = ((pawn.level * (zodiacStats[zodiacNumber][energyStat] + speciesStats[speciesNumber][energyStat] + 4)) + 15) / 5;
  pawn.power = ((pawn.level * (zodiacStats[zodiacNumber][powerStat] + speciesStats[speciesNumber][powerStat] + 4)) + 15) / 10;
  pawn.actionCost = 7 - ((zodiacStats[zodiacNumber][actionCostStat] + speciesStats[speciesNumber][actionCostStat]) / 2);
  //pawn.energy = pawn.maxEnergy;
  pawn.specialAttack = getSpecialAttack(pawn);
}

void packAndSavePawn(Pawn pawn, uint8_t addressIndex)
{
  const uint16_t eepromAddressStart = 600;
  uint16_t address = eepromAddressStart + (addressIndex * 3);
  uint16_t modifiedLevel = (pawn.level > 8) ? 7 : pawn.level - 1;
  uint16_t pawnBytes = modifiedLevel + ((static_cast <uint16_t> (pawn.species)) << 3) + (pawn.experience << 8) + ((static_cast <uint16_t> (pawn.zodiac)) << 12);

  EEPROM.put(address, pawnBytes);
  EEPROM.update(address + 2, pawn.energy);
}

void unpackPawn(Pawn & pawn, uint8_t addressIndex)
{
  const uint16_t eepromAddressStart = 600;
  uint16_t address = eepromAddressStart + (addressIndex * 3);
  uint16_t pawnBytes;

  EEPROM.get(address, pawnBytes);
  pawn.energy = EEPROM.read(address + 2);

  pawn.level = (pawnBytes & 7) + 1;
  pawn.species = static_cast <Species> ((pawnBytes & 248) >> 3);
  pawn.experience = (pawnBytes & 3840) >> 8;

  if ((pawn.experience == 15) && (pawn.level == 8))
    pawn.level += 1;

  pawn.zodiac = static_cast <Zodiac> ((pawnBytes & 61440) >> 12);

  //createStats(pawn);
}

void healAllPawns()
{
  Pawn healedPawn;
  for (uint8_t index = 0; index < 32; ++index)
  {
    unpackPawn(healedPawn, index);
    createStats(healedPawn);
    if (healedPawn.zodiac != Zodiac::None)
      healedPawn.energy = healedPawn.maxEnergy;
    packAndSavePawn(healedPawn, index);

    if (index < 3)
      pawn[index].energy = pawn[index].maxEnergy;
  }
}
