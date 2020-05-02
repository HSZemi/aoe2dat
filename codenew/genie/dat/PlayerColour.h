/*
    geniedat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2013  Armin Preiml
    Copyright (C) 2011 - 2017  Mikko "Tapsa" P

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

#ifndef GENIE_PLAYERCOLOUR_H
#define GENIE_PLAYERCOLOUR_H
#include "genie/file/ISerializable.h"

namespace genie
{

class PlayerColour : public ISerializable
{
public:
  PlayerColour();
  virtual ~PlayerColour();
  virtual void setGameVersion(GameVersion gv);

  int32_t ID = -1;
  int32_t MinimapColour = 0;

// AoE 2 variables

  int32_t PlayerColorBase = 0;
  int32_t UnitOutlineColor = 0;
  int32_t UnitSelectionColor1 = 0;
  int32_t UnitSelectionColor2 = 0;
  int32_t MinimapColor2 = 0;
  int32_t MinimapColor3 = 0;

  /// Reference to PlayerColour, often itself
  int32_t StatisticsText = -1;

// AoE 1 variables

  static const unsigned short NAME_SIZE = 30;
  std::string Name = "";

  /// Intended to replace filename, but never actually made so.
  int16_t ResourceID = 0;

  /// 0 transform, 1 transform player color, 2 shadow, 3 translucent
  uint8_t Type = 1;

private:
  virtual void serializeObject(void);
};

}

#endif // GENIE_PLAYERCOLOUR_H
