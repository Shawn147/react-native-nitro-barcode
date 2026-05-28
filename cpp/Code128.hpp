#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace margelo::nitro::barcode::code128 {

struct RasterOptions {
  int moduleWidth = 2;
  int height = 60;
  int quietZoneModules = 10;
  uint32_t lineColor = 0xFF000000;
  uint32_t backgroundColor = 0xFFFFFFFF;
};

struct RasterResult {
  int width = 0;
  int height = 0;
  std::vector<uint8_t> rgba;
};

/** Encode text as CODE128 set B and rasterize to RGBA8888. */
RasterResult rasterizeCode128(const std::string& value, const RasterOptions& options);

} // namespace margelo::nitro::barcode::code128
