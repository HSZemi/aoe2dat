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

#ifndef GENIE_GRAPHICATTACKSOUND_H
#define GENIE_GRAPHICATTACKSOUND_H
#include "genie/file/ISerializable.h"

namespace genie
{

class GraphicAngleSound : public ISerializable
{
public:
  GraphicAngleSound();
  virtual ~GraphicAngleSound();
  virtual void setGameVersion(GameVersion gv);

  //TODO: Array
  int16_t FrameNum = -1;
  int16_t SoundID = -1;
  uint32_t WwiseSoundID = 0;

  int16_t FrameNum2 = -1;
  int16_t SoundID2 = -1;
  uint32_t WwiseSoundID2 = 0;

  int16_t FrameNum3 = -1;
  int16_t SoundID3 = -1;
  uint32_t WwiseSoundID3 = 0;

private:
  virtual void serializeObject(void);
};

}

#endif // GENIE_GRAPHICATTACKSOUND_H
