#include "HybridBarcodeGenerator.hpp"

#include "Code128.hpp"

#include <NitroModules/ArrayBuffer.hpp>

namespace margelo::nitro::barcode {

namespace {

code128::RasterOptions toRasterOptions(const std::optional<BarcodeOptions>& options) {
  code128::RasterOptions raster;
  if (!options.has_value()) {
    return raster;
  }
  const BarcodeOptions& o = options.value();
  if (o.moduleWidth.has_value()) {
    raster.moduleWidth = static_cast<int>(o.moduleWidth.value());
  }
  if (o.height.has_value()) {
    raster.height = static_cast<int>(o.height.value());
  }
  if (o.quietZoneModules.has_value()) {
    raster.quietZoneModules = static_cast<int>(o.quietZoneModules.value());
  }
  if (o.lineColor.has_value()) {
    raster.lineColor = static_cast<uint32_t>(o.lineColor.value());
  }
  if (o.backgroundColor.has_value()) {
    raster.backgroundColor = static_cast<uint32_t>(o.backgroundColor.value());
  }
  return raster;
}

} // namespace

BarcodeBitmap HybridBarcodeGenerator::generateCode128(const std::string& value,
                                                      const std::optional<BarcodeOptions>& options) {
  const code128::RasterResult raster =
      code128::rasterizeCode128(value, toRasterOptions(options));

  std::shared_ptr<ArrayBuffer> buffer = ArrayBuffer::copy(raster.rgba);
  return BarcodeBitmap(static_cast<double>(raster.width), static_cast<double>(raster.height), buffer);
}

} // namespace margelo::nitro::barcode
