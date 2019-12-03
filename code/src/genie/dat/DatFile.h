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

#ifndef GENIE_DATFILE_H
#define GENIE_DATFILE_H

#include <string>
#include <iostream>

#include "genie/Types.h"
#include "genie/file/IFile.h"
#include "genie/file/Compressor.h"
#include "TerrainRestriction.h"
#include "PlayerColour.h"
#include "Sound.h"
#include "Graphic.h"
#include "TerrainBlock.h"
#include "Terrain.h"
#include "Techage.h"
#include "UnitHeader.h"
#include "Civ.h"
#include "Research.h"
#include "TerrainBorder.h"
#include "UnitLine.h"
#include "TechTree.h"
#include "RandomMap.h"

namespace boost { namespace iostreams { struct zlib_params; } }

namespace genie
{

class DatFile : public IFile
{
public:
  //----------------------------------------------------------------------------
  /// Standard constructor
  //
  DatFile();

  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~DatFile();

  //----------------------------------------------------------------------------
  virtual void setGameVersion(GameVersion gv);

  //----------------------------------------------------------------------------
  /// Uncompress dat file.
  //
  void extractRaw(const char *inFile, const char *outFile);

  //----------------------------------------------------------------------------
  /// Debug information will be printed to stdout if activated.
  ///
  /// @param verbose true to activate
  //
  void setVerboseMode(bool verbose);

  // File data
  static const unsigned short FILE_VERSION_SIZE = 8;
  std::string FileVersion;

  std::vector<int32_t> FloatPtrTerrainTables;
  std::vector<int32_t> TerrainPassGraphicPointers;
  std::vector<TerrainRestriction> TerrainRestrictions;

  std::vector<PlayerColour> PlayerColours;

  std::vector<Sound> Sounds;

  std::vector<int32_t> GraphicPointers;
  std::vector<Graphic> Graphics;

  genie::TerrainBlock TerrainBlock;
  genie::RandomMaps RandomMaps;

  std::vector<Effect> Effects;

  std::vector<UnitHeader> UnitHeaders;

  std::vector<Civ> Civs;

  std::vector<Tech> Techs;

  /// Only present in gv >= SWGB
  std::vector<UnitLine> UnitLines;

  genie::TechTree TechTree;

  /// History totals
  int32_t TimeSlice;
  int32_t UnitKillRate;
  int32_t UnitKillTotal;
  int32_t UnitHitPointRate;
  int32_t UnitHitPointTotal;
  int32_t RazingKillRate;
  int32_t RazingKillTotal;

  uint16_t TerrainsUsed1;

  //SWGB Unknowns:
  int32_t SUnknown2;
  int32_t SUnknown3;
  int32_t SUnknown4;
  int32_t SUnknown5;

  int8_t SUnknown7;
  int8_t SUnknown8;

private:
  // if true print debug messages
  bool verbose_ = false;

  std::string file_name_ = "";
  std::fstream *file_ = 0;

  Compressor compressor_;

  DatFile(const DatFile &other);
  DatFile &operator=(const DatFile &other);

  //----------------------------------------------------------------------------
  /// Clears all data.
  //
  virtual void unload(void);

  virtual void serializeObject(void);
};

}

#endif // GENIE_DATFILE_H
