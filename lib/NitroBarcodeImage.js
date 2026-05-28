import { jsx as _jsx } from "react/jsx-runtime";
import { AlphaType, Canvas, ColorType, Image, Skia, } from '@shopify/react-native-skia';
import { useMemo } from 'react';
import { View } from 'react-native';
import { getBarcodeGenerator } from './getBarcodeGenerator';
/**
 * Renders a CODE128 barcode using the native Nitro C++ rasterizer and Skia.
 */
export function NitroBarcodeImage({ value, options, style, }) {
    const bitmap = useMemo(() => {
        if (!value) {
            return null;
        }
        return getBarcodeGenerator().generateCode128(value, options);
    }, [value, options]);
    const skiaImage = useMemo(() => {
        if (!bitmap) {
            return null;
        }
        const bytes = new Uint8Array(bitmap.data);
        return Skia.Image.MakeImage({
            width: bitmap.width,
            height: bitmap.height,
            alphaType: AlphaType.Premul,
            colorType: ColorType.RGBA_8888,
        }, Skia.Data.fromBytes(bytes), bitmap.width * 4);
    }, [bitmap]);
    if (!skiaImage || !bitmap) {
        return _jsx(View, { style: style });
    }
    return (_jsx(View, { style: style, children: _jsx(Canvas, { style: { width: bitmap.width, height: bitmap.height }, children: _jsx(Image, { image: skiaImage, x: 0, y: 0, width: bitmap.width, height: bitmap.height, fit: "fill" }) }) }));
}
