import {
  AlphaType,
  Canvas,
  ColorType,
  Image,
  Skia,
} from '@shopify/react-native-skia';
import React, { useMemo } from 'react';
import { StyleProp, View, ViewStyle } from 'react-native';

import { getBarcodeGenerator } from './getBarcodeGenerator';
import type { BarcodeOptions } from './specs/BarcodeGenerator.nitro';

export type NitroBarcodeImageProps = {
  value: string;
  options?: BarcodeOptions;
  style?: StyleProp<ViewStyle>;
};

/**
 * Renders a CODE128 barcode using the native Nitro C++ rasterizer and Skia.
 */
export function NitroBarcodeImage({
  value,
  options,
  style,
}: NitroBarcodeImageProps) {
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
    return Skia.Image.MakeImage(
      {
        width: bitmap.width,
        height: bitmap.height,
        alphaType: AlphaType.Premul,
        colorType: ColorType.RGBA_8888,
      },
      Skia.Data.fromBytes(bytes),
      bitmap.width * 4,
    );
  }, [bitmap]);

  if (!skiaImage || !bitmap) {
    return <View style={style} />;
  }

  return (
    <View style={style}>
      <Canvas style={{ width: bitmap.width, height: bitmap.height }}>
        <Image
          image={skiaImage}
          x={0}
          y={0}
          width={bitmap.width}
          height={bitmap.height}
          fit="fill"
        />
      </Canvas>
    </View>
  );
}
