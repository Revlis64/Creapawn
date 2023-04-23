#pragma once

enum class TitleScreenState : uint8_t
{
  StillLogo,
  LogoScrollUp,
  Options,
  ConfirmNewGame,
};

TitleScreenState titleScreenState = TitleScreenState::StillLogo;
uint8_t titleScreenCounter = 0;

#include "updatetitlescreen.h"
#include "rendertitlescreen.h"