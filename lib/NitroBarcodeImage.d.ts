import { StyleProp, ViewStyle } from 'react-native';
import type { BarcodeOptions } from './specs/BarcodeGenerator.nitro';
export type NitroBarcodeImageProps = {
    value: string;
    options?: BarcodeOptions;
    style?: StyleProp<ViewStyle>;
};
/**
 * Renders a CODE128 barcode using the native Nitro C++ rasterizer and Skia.
 */
export declare function NitroBarcodeImage({ value, options, style, }: NitroBarcodeImageProps): import("react/jsx-runtime").JSX.Element;
