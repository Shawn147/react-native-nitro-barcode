#pragma once

#include "HybridBarcodeGeneratorSpec.hpp"

namespace margelo::nitro::barcode {

class HybridBarcodeGenerator final : public HybridBarcodeGeneratorSpec {
public:
  HybridBarcodeGenerator() : HybridObject(TAG) {}

  BarcodeBitmap generateCode128(const std::string& value,
                                const std::optional<BarcodeOptions>& options) override;
};

} // namespace margelo::nitro::barcode
