/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <stdint.h>
#include <string>

typedef int DisplayMode;
#define DM_WINDOWED     -1
#define DM_FULLSCREEN    0

enum RESOLUTION
{
  RES_INVALID        = -1,
  RES_WINDOW         = 15,
  RES_DESKTOP        = 16,          // Desktop resolution
  RES_CUSTOM         = 16 + 1,      // First additional resolution
};

struct OVERSCAN
{
  int left;
  int top;
  int right;
  int bottom;
public:
  OVERSCAN()
  {
    left = top = right = bottom = 0;
  }
  OVERSCAN(const OVERSCAN& os)
  {
    left = os.left; top = os.top;
    right = os.right; bottom = os.bottom;
  }
  OVERSCAN& operator=(const OVERSCAN&) = default;

  bool operator==(const OVERSCAN& other)
  {
    return left == other.left && right == other.right && top == other.top && bottom == other.bottom;
  }
  bool operator!=(const OVERSCAN& other)
  {
    return left != other.left || right != other.right || top != other.top || bottom != other.bottom;
  }
};

struct EdgeInsets
{
  float left = 0.0f;
  float top = 0.0f;
  float right = 0.0f;
  float bottom = 0.0f;

  EdgeInsets() = default;
  EdgeInsets(float l, float t, float r, float b);
};

//! @brief Provide info of a resolution
struct RESOLUTION_INFO
{
  //!< Screen overscan boundary
  // 显示边界的设置
  OVERSCAN Overscan;

  //!< Edge insets to scale the GUI to prevent the display notch from hiding a part of the GUI
  // GUI 缩放的边距设置
  EdgeInsets guiInsets;

  //!< Specify if it is a fullscreen resolution, otherwise windowed
  // 指示是否为全屏分辨率
  bool bFullScreen;

  //!< Width GUI resolution (pixels), may differ from the screen value if GUI resolution limit, 3D is set or in HiDPI screens
  // GUI 分辨率的宽度（像素）
  int iWidth;

  //!< Height GUI resolution (pixels), may differ from the screen value if GUI resolution limit, 3D is set or in HiDPI screens
  // GUI 分辨率的高度（像素）
  int iHeight;

  //!< Number of pixels of padding between stereoscopic frames
  int iBlanking;

  //!< Screen width (logical width in pixels)
  // 屏幕宽度（逻辑宽度，像素）
  int iScreenWidth;

  //!< Screen height (logical height in pixels)
  // 屏幕高度（逻辑高度，像素）
  int iScreenHeight;

  //!< The vertical subtitle baseline position, may be changed by Video calibration
  // 垂直字幕基线位置，可能会被视频校准改变
  int iSubtitles;

  //!< Properties of the resolution e.g. interlaced mode
  // 分辨率的属性，例如隔行模式
  uint32_t dwFlags;

  //!< Pixel aspect ratio
  // 像素纵横比
  float fPixelRatio;

  //!< Refresh rate
  // 刷新率
  float fRefreshRate;

  //!< Resolution mode description
  // 分辨率模式描述
  std::string strMode;

  //!< Resolution output description
  // 分辨率输出描述
  std::string strOutput;

  //!< Resolution ID
  // 分辨率 ID
  std::string strId;

public:
  RESOLUTION_INFO(int width = 1280, int height = 720, float aspect = 0, const std::string &mode = "");
  float DisplayRatio() const;
  RESOLUTION_INFO(const RESOLUTION_INFO& res);
  RESOLUTION_INFO& operator=(const RESOLUTION_INFO&) = default;
};

class CResolutionUtils
{
public:
  static RESOLUTION ChooseBestResolution(float fps, int width, int height, bool is3D);
  static bool HasWhitelist();
  static void PrintWhitelist();

  /*!
   * \brief Get the max allowed screen resolution, if fullscreen
   * \param width [OUT] Max width resolution
   * \param height [OUT] Max height resolution
   */
  static void GetMaxAllowedScreenResolution(unsigned int& width, unsigned int& height);

protected:
  static void FindResolutionFromWhitelist(float fps, int width, int height, bool is3D, RESOLUTION &resolution);
  static bool FindResolutionFromOverride(float fps, int width, bool is3D, RESOLUTION &resolution, float& weight, bool fallback);
  static float RefreshWeight(float refresh, float fps);
};
