#pragma once

//draws a text box
void drawTextBox(uint8_t x, uint8_t y, uint8_t width, uint8_t length, bool color)
{
  arduboy.fillRoundRect(x, y, width, length, 1, color);
  if (color == WHITE)
    color = BLACK;
    else color = WHITE;
  tinyfont.setTextColor(color);
  tinyfont.setCursor( x + 1, y + 1);
}

//Gets name of the pawn, depending on species
const __FlashStringHelper *getName(Species species)
{
  switch(species)
  {
    case Species::Voidismal:
      return F("VOIDISMAL");

    case Species::Audiouse:
      return F("AUDIOUSE");

    case Species::Boltnetic:
      return F("BOLTNETIC");

    case Species::Dribby:
      return F("DRIBBY");

    case Species::Luminat:
      return F("LUMINAT");

    case Species::Micrunt:
      return F("MICRUNT");

    case Species::Odrion:
      return F("ODRION");

    case Species::Outlectric:
      return F("OUTLECTRIC");

    case Species::Slugamma:
      return F("SLUGAMMA");

    case Species::Spymera:
      return F("SPYMERA");

    case Species::Xenaucer:
      return F("XENAUCER");

    case Species::Beethrone:
      return F("BEETHRONE");

    case Species::Bubblue:
      return F("BUBBLUE");

    case Species::Bunnerina:
      return F("BUNNERINA");

    case Species::Champanzon:
      return F("CHAMPANZON");

    case Species::Chloroar:
      return F("CHLOROAR");

    case Species::Cribbit:
      return F("CRIBBIT");

    case Species::Dashound:
      return F("DASHOUND");

    case Species::Mayham:
      return F("MAYHAM");

    case Species::Necrawler:
      return F("NECRAWLER");

    case Species::Terruption:
      return F("TERRUPTION");

    case Species::Chivampera:
      return F("CHIVAMPERA");

    case Species::Dualdra:
      return F("DUALDRA");

    case Species::Faefluff:
      return F("FAEFLUFF");

    case Species::Grifelios:
      return F("GRIFELIOS");

    case Species::Mauroah:
      return F("MAUROAH");

    case Species::Pegshire:
      return F("PEGSHIRE");

    case Species::Polterror:
      return F("POLTERROR");

    case Species::Ravuack:
      return F("RAVUACK");

    case Species::Scardra:
      return F("SCARDRA");

    case Species::Squeamask:
      return F("SQUEAMASK");

    case Species::Trikurn:
      return F("TRIKURN");

    default:
      return F("ERROR");
  }
}

const __FlashStringHelper *getZodiac(Zodiac zodiac)
{
  switch(zodiac)
  {
    case Zodiac::Capricorn:
      return F("CAPRICORN");

    case Zodiac::Aquarius:
      return F("AQUARIUS");
      
    case Zodiac::Pisces:
      return F("PISCES");
      
    case Zodiac::Aries:
      return F("ARIES");

    case Zodiac::Taurus:
      return F("TAURUS");
      
    case Zodiac::Gemini:
      return F("GEMINI");
      
    case Zodiac::Cancer:
      return F("CANCER");

    case Zodiac::Leo:
      return F("LEO");
      
    case Zodiac::Virgo:
      return F("VIRGO");
      
    case Zodiac::Libra:
      return F("LIBRA");

    case Zodiac::Scorpio:
      return F("SCORPIO");
      
    case Zodiac::Sagittarius:
      return F("SAGITTARI.");

    case Zodiac::None:
      return F("NONE");
    
    default:
      return F("ERROR");
      
  }
}

const __FlashStringHelper *getType(Type type)
{
  switch(type)
  {
    case Type::Null:
      return F("NULL");

    case Type::Synth:
      return F("SYNTH");

    case Type::Nature:
      return F("NATURE");

    case Type::Mystic:
      return F("MYSTIC");

    case Type::Omni:
      return F("OMNI");

    default:
      return F("ERROR");
  }
}

void determineZeroPrint(uint8_t index)
{
  if (index < 10)
    tinyfont.print(F("0"));
}