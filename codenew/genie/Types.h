/*
    genieutils - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2013  Armin Preiml
    Copyright (C) 2014 - 2019  Mikko "Tapsa" P

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

#ifndef GENIE_TYPES_H
#define GENIE_TYPES_H

namespace genie
{

enum GameVersion
{
  GV_None = 0, //Game version not set
  GV_TEST, // ?
  GV_MIK, // ?
  GV_DAVE, // ?
  GV_MATT, // ?
  GV_AoEB, // 7.04 - 7.11
  GV_AoE, // 7.2
  GV_RoR, // 7.24
  GV_Tapsa, GV_T2, GV_T3, GV_T4, GV_T5, GV_T6, GV_T7, GV_T8,
  GV_AoKE3, // 9.36
  GV_AoKA, // 10.19
  GV_AoKB, // 11.05
  GV_AoK, // 11.5
  GV_TC, // 11.76
  GV_Cysion, GV_C2, GV_C3, GV_C4, GV_CK, GV_C5, GV_C6, GV_C7, GV_C8, GV_C9, GV_C10, GV_C11, GV_C12, GV_C13, GV_C14,
  // 12.0 - 12.74
  GV_SWGB, // 1.0
  GV_CC // 1.1
};

extern GameVersion GV_LatestTap, GV_LatestDE2;

struct XYZF
{
  float x, y, z;
};

}

#endif //GENIE_TYPES_H
