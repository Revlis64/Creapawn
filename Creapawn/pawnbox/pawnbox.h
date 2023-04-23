#pragma once

enum class BoxState : uint8_t
{
  CannotDoAction,
  SelectPawn,
  ConfigureTeam,
  UseHerb,
  ConfirmRelease,
  ReleasePawn,
  Options,
  NeedTeam,
  Setup,
};

Pawn unpackedPawn;

BoxState boxState = BoxState::Setup;

uint8_t boxSelectionX = 0;
uint8_t boxSelectionY = 0;
uint8_t boxSelectionScroll = 0;
uint8_t optionSelection = 3;
uint8_t boxIndex = 0;

#include "updatePawnBox.h"
#include "renderPawnBox.h"