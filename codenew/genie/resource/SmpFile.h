/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2018  Mikko "Tapsa" P

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

#ifndef GENIE_SMPFILE_H
#define GENIE_SMPFILE_H

#include <istream>
#include <vector>

#include "genie/file/IFile.h"
#include "genie/util/Logger.h"
#include "PalFile.h"
#include "SmpFrame.h"

namespace genie
{

//------------------------------------------------------------------------------
/// A smp file stores one or several images encoded using simple commands.
/// The image is stored as 8 bits per pixel, that means only the index of a
/// color in a palette is saved.
//
class SmpFile : public IFile
{

public:
  //----------------------------------------------------------------------------
  /// Constructor
  //
  SmpFile();

  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~SmpFile();

  //----------------------------------------------------------------------------
  /// Frees all content of a smp file.
  //
  void unload(void);

  //----------------------------------------------------------------------------
  /// Check whether the files content is loaded or not.
  //
  bool isLoaded(void) const;

  //----------------------------------------------------------------------------
  /// Return number of frames stored in the file. Available after load.
  ///
  /// @return number of frames
  //
  uint32_t getFrameCount(void);
  void setFrameCount(uint32_t);

  //----------------------------------------------------------------------------
  /// Returns the smp frame at given frame index.
  ///
  /// @param frame frame index
  /// @return SmpFrame
  //
  SmpFramePtr getFrame(uint32_t frame=0);
  void setFrame(uint32_t, SmpFramePtr);

  std::string signature;
  std::string comment;
  uint32_t version;
  uint32_t num_animations;
  uint32_t num_frames_per_animation;
  uint32_t checksum;
  uint32_t size;
  uint32_t resource_id;

private:
  static Logger &log;

  bool loaded_ = false;

  uint32_t num_frames_ = 0;

  std::vector<uint32_t> frame_offsets_;
  typedef std::vector<SmpFramePtr> FrameVector;
  FrameVector frames_;

  // Used to calculate offsets when saving the SMP.
  uint32_t smp_offset_;

  //----------------------------------------------------------------------------
  virtual void serializeObject(void);

  //----------------------------------------------------------------------------
  /// Loads the file and its frames.
  //
  void loadFile(void);
  void saveFile(void);

  //----------------------------------------------------------------------------
  void serializeHeader(void);
};

typedef std::shared_ptr<SmpFile> SmpFilePtr;

}

#endif // GENIE_SMPFILE_H
