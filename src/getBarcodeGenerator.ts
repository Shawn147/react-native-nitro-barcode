import { NitroModules } from 'react-native-nitro-modules';

import type { BarcodeGenerator } from './specs/BarcodeGenerator.nitro';

let cached: BarcodeGenerator | undefined;

export function getBarcodeGenerator(): BarcodeGenerator {
  if (cached == null) {
    cached = NitroModules.createHybridObject<BarcodeGenerator>('BarcodeGenerator');
  }
  return cached;
}
