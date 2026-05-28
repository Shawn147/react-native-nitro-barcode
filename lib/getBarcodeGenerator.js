import { NitroModules } from 'react-native-nitro-modules';
let cached;
export function getBarcodeGenerator() {
    if (cached == null) {
        cached = NitroModules.createHybridObject('BarcodeGenerator');
    }
    return cached;
}
