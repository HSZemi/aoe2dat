/*
    geniedat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2013  Armin Preiml
    Copyright (C) 2011 - 2018  Mikko "Tapsa" P

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GENIE_UNITCOMMAND_H
#define GENIE_UNITCOMMAND_H
#include "genie/file/ISerializable.h"

namespace genie
{

class Task : public ISerializable
{
public:
  Task();
  virtual ~Task();
  virtual void setGameVersion(GameVersion gv);

  int16_t TaskType = 1;
  int16_t ID = -1;
  int8_t IsDefault = false;
  int16_t ActionType = 0;
  int16_t ClassID = -1;
  int16_t UnitID = -1;
  int16_t TerrainID = -1;
  int16_t ResourceIn = -1;
  int16_t ResourceMultiplier = -1;
  int16_t ResourceOut = -1;
  int16_t UnusedResource = -1;
  float WorkValue1 = 0;
  float WorkValue2 = 0;
  float WorkRange = 0;
  int8_t AutoSearchTargets = 0;
  float SearchWaitTime = 0;
  int8_t EnableTargeting = 0;
  int8_t CombatLevelFlag = false;
  int16_t GatherType = 0;
  int16_t WorkFlag2 = 0;
  int8_t TargetDiplomacy = 0;
  int8_t CarryCheck = false;
  int8_t PickForConstruction = false;
  int16_t MovingGraphicID = -1;
  int16_t ProceedingGraphicID = -1;
  int16_t WorkingGraphicID = -1;
  int16_t CarryingGraphicID = -1;
  int16_t ResourceGatheringSoundID = -1;
  int16_t ResourceDepositSoundID = -1;
  uint32_t WwiseResourceGatheringSoundID = 0;
  uint32_t WwiseResourceDepositSoundID = 0;

private:
  virtual void serializeObject(void);
};

}

#endif // GENIE_UNITCOMMAND_H
