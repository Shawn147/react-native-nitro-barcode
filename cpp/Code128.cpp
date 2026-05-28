#include "Code128.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

namespace margelo::nitro::barcode::code128 {

namespace {

constexpr int START_B = 104;
constexpr int STOP = 106;
constexpr int MODULO = 103;

// Same symbol patterns as JsBarcode CODE128 (11 modules each; STOP has 13).
constexpr uint64_t BARS[107] = {
    11011001100, 11001101100, 11001100110, 10010011000, 10010001100, 10001001100, 10011001000, 10011000100,
    10001100100, 11001001000, 11001000100, 11000100100, 10110011100, 10011011100, 10011001110, 10111001100,
    10011101100, 10011100110, 11001110010, 11001011100, 11001001110, 11011100100, 11001110100, 11101101110,
    11101001100, 11100101100, 11100100110, 11101100100, 11100110100, 11100110010, 11011011000, 11011000110,
    11000110110, 10100011000, 10001011000, 10001000110, 10110001000, 10001101000, 10001100010, 11010001000,
    11000101000, 11000100010, 10110111000, 10110001110, 10001101110, 10111011000, 10111000110, 10001110110,
    11101110110, 11010001110, 11000101110, 11011101000, 11011100010, 11011101110, 11101011000, 11101000110,
    11100010110, 11101101000, 11101100010, 11100011010, 11101111010, 11001000010, 11110001010, 10100110000,
    10100001100, 10010110000, 10010000110, 10000101100, 10000100110, 10110010000, 10110000100, 10011010000,
    10011000010, 10000110100, 10000110010, 11000010010, 11001010000, 11110111010, 11000010100, 10001111010,
    10100111100, 10010111100, 10010011110, 10111100100, 10011110100, 10011110010, 11110100100, 11110010100,
    11110010010, 11011011110, 11011110110, 11110110110, 10101111000, 10100011110, 10001011110, 10111101000,
    10111100010, 11110101000, 11110100010, 10111011110, 10111101110, 11101011110, 11110101110, 11010000100,
    11010010000, 11010011100, 1100011101011};

std::string patternDigits(int symbolIndex) {
  if (symbolIndex < 0 || symbolIndex >= 107) {
    throw std::runtime_error("Invalid CODE128 symbol index");
  }
  return std::to_string(BARS[symbolIndex]);
}

std::vector<int> encodeCode128B(const std::string& value) {
  if (value.empty()) {
    throw std::runtime_error("Barcode value cannot be empty");
  }

  std::vector<int> symbols;
  symbols.reserve(value.size() + 3);
  symbols.push_back(START_B);

  int checksum = START_B;
  int weight = 1;

  for (unsigned char c : value) {
    if (c < 32 || c > 126) {
      throw std::runtime_error("CODE128 supports printable ASCII only (32-126)");
    }
    const int code = static_cast<int>(c) - 32;
    symbols.push_back(code);
    checksum += code * weight;
    weight++;
  }

  symbols.push_back(checksum % MODULO);
  symbols.push_back(STOP);
  return symbols;
}

std::vector<bool> buildModuleGrid(const std::vector<int>& symbols) {
  std::vector<bool> modules;
  modules.reserve(symbols.size() * 12);

  for (const int symbol : symbols) {
    const std::string pattern = patternDigits(symbol);
    for (char bit : pattern) {
      modules.push_back(bit == '1');
    }
  }
  return modules;
}

inline uint8_t rgbaChannel(uint32_t argb, int shift) {
  return static_cast<uint8_t>((argb >> shift) & 0xFF);
}

void fillPixel(std::vector<uint8_t>& rgba, int width, int x, int y, uint32_t argb) {
  const size_t offset = static_cast<size_t>((y * width + x) * 4);
  rgba[offset] = rgbaChannel(argb, 16);
  rgba[offset + 1] = rgbaChannel(argb, 8);
  rgba[offset + 2] = rgbaChannel(argb, 0);
  rgba[offset + 3] = rgbaChannel(argb, 24);
}

} // namespace

RasterResult rasterizeCode128(const std::string& value, const RasterOptions& options) {
  const int moduleWidth = std::max(1, options.moduleWidth);
  const int barHeight = std::max(1, options.height);
  const int quietModules = std::max(0, options.quietZoneModules);

  const std::vector<int> symbols = encodeCode128B(value);
  const std::vector<bool> grid = buildModuleGrid(symbols);

  const int totalModules = static_cast<int>(grid.size());
  const int pixelModules = totalModules + quietModules * 2;
  const int width = pixelModules * moduleWidth;
  const int height = barHeight + quietModules * 2 * moduleWidth;
  const int quietPx = quietModules * moduleWidth;

  RasterResult result;
  result.width = width;
  result.height = height;
  result.rgba.assign(static_cast<size_t>(width * height * 4), 0);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      fillPixel(result.rgba, width, x, y, options.backgroundColor);
    }
  }

  for (int i = 0; i < totalModules; i++) {
    const bool isBar = grid[static_cast<size_t>(i)];
    if (!isBar) {
      continue;
    }
    const int moduleX = quietPx + i * moduleWidth;
    for (int dx = 0; dx < moduleWidth; dx++) {
      for (int y = quietPx; y < quietPx + barHeight; y++) {
        fillPixel(result.rgba, width, moduleX + dx, y, options.lineColor);
      }
    }
  }

  return result;
}

} // namespace margelo::nitro::barcode::code128
