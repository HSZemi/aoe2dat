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

#ifndef GENIE_SOUND_H
#define GENIE_SOUND_H
#include "genie/file/ISerializable.h"

#include <vector>
#include "SoundItem.h"

namespace genie
{

class Sound : public ISerializable
{
public:
  Sound();
  virtual ~Sound();
  virtual void setGameVersion(GameVersion gv);

  int16_t ID = -1;
  int16_t PlayDelay = 0;
  int32_t CacheTime = 300000; // 5 minutes
  int16_t TotalProbability = 100;
  std::vector<SoundItem> Items;

private:
  virtual void serializeObject(void);
};

}

#endif // GENIE_SOUND_H
