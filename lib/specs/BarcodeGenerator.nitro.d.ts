import type { HybridObject } from 'react-native-nitro-modules';
export interface BarcodeOptions {
    /**
     * Width of one barcode module in pixels (default: 2).
     */
    moduleWidth?: number;
    /**
     * Bar height in pixels, excluding quiet zone (default: 60).
     */
    height?: number;
    /**
     * Quiet zone width in modules on left and right (default: 10).
     */
    quietZoneModules?: number;
    /**
     * Foreground color as 0xAARRGGBB (default: 0xFF000000).
     */
    lineColor?: number;
    /**
     * Background color as 0xAARRGGBB (default: 0xFFFFFFFF).
     */
    backgroundColor?: number;
}
/**
 * RGBA8888 bitmap generated on the native thread.
 */
export interface BarcodeBitmap {
    width: number;
    height: number;
    data: ArrayBuffer;
}
export interface BarcodeGenerator extends HybridObject<{
    ios: 'c++';
    android: 'c++';
}> {
    /**
     * Encode `value` as CODE128 (set B) and rasterize to an RGBA bitmap.
     */
    generateCode128(value: string, options?: BarcodeOptions): BarcodeBitmap;
}
