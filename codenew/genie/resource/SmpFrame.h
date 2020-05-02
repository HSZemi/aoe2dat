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

#ifndef GENIE_SMPFRAME_H
#define GENIE_SMPFRAME_H

#include "genie/file/ISerializable.h"
#include "genie/util/Logger.h"

#include <istream>
#include <vector>
#include <set>
#include <stdint.h>

#include "PalFile.h"

namespace genie
{

struct SmpFrameData
{
  std::vector<uint32_t> pixel_indexes;
  std::vector<uint8_t> alpha_channel;
  std::vector<PlayerColorXY> player_color_mask;
};

//------------------------------------------------------------------------------
/// Class for reading a frame of a SMP file. Once loaded the image can be
/// obtained as a pixel array. A pixel is stored as the index of a color
/// in a palette.
//
class SmpFrame : protected ISerializable
{
public:
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  SmpFrame();

  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~SmpFrame();

  //----------------------------------------------------------------------------
  /// Loads header data. The headers of frames are stored after the header of
  /// the smp file.
  //
  void serializeHeader(void);
  void setLoadParams(std::istream &istr, uint32_t smp_offset_);
  void setSaveParams(std::ostream &ostr, uint32_t &smp_offset_);

  //----------------------------------------------------------------------------
  /// Loads frame data and creates an image. Frame data is located after all
  /// frame headers of the smp file.
  //
  void load(std::istream &istr);
  void save(std::ostream &ostr);

  //----------------------------------------------------------------------------
  /// Get images width.
  //
  uint32_t getWidth(void) const;

  //----------------------------------------------------------------------------
  /// Get images height.
  //
  uint32_t getHeight(void) const;

  bool is32bit(void) const {return false;}

  //----------------------------------------------------------------------------
  /// Get the hotspot of the frame. The Hotspot is the isometric center of
  /// the object presented by this frame.

  int32_t hotspot_x;
  int32_t hotspot_y;
  uint32_t type;
  uint32_t diffuse_palette_xid;
  uint32_t diffuse_palette_num;
  uint32_t num_layers;

  // These should be in an array.
  int32_t layer_hotspot_x;
  int32_t layer_hotspot_y;

  SmpFrameData img_data;

private:
  static Logger &log;

  std::streampos smp_frame_pos_;

  uint32_t layer_type_;
  uint32_t layer_outline_offsets_;
  uint32_t layer_data_offsets_;
  uint32_t layer_flags_;

  uint32_t width_;
  uint32_t height_;
  uint32_t layer_width_ = 0;
  uint32_t layer_height_ = 0;

  std::vector<uint16_t> left_edges_;
  std::vector<uint16_t> right_edges_;
  std::vector<uint32_t> cmd_offsets_;

  virtual void serializeObject(void);

  //----------------------------------------------------------------------------
  /// Reads the edges of the frame. An edge int is the number of pixels in
  /// a row which are transparent. There are two 16 bit unsigned integers for
  /// each side of a row. One starting from left and the other starting from the
  /// right side.
  /// Assuming stream pointer is at beginning of edges array.
  //
  void readEdges(void);

  //----------------------------------------------------------------------------
  /// Reads pixel indexes from file and sets the pixels according to the
  /// colors from the palette.
  /// It is assumed that the stream pointer is at the start of the pixel array.
  ///
  /// @param row row to set pixels at
  /// @param col column to set pixels from
  /// @param count how many pixels should be read
  /// @param player_col if true, pixel will be written to player color image
  //
  void readPixelsToImage(uint32_t row, uint32_t &col, uint32_t count, bool player_col);
};

typedef std::shared_ptr<SmpFrame> SmpFramePtr;

}

#endif // GENIE_SMPFRAME_H
