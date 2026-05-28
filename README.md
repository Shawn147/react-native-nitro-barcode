# react-native-nitro-barcode

Native CODE128 barcode rasterization for React Native, implemented in C++ via [Nitro Modules](https://nitro.margelo.com).

## Features

- CODE128 set B encoding (same symbology as `react-native-barcode-svg` / JsBarcode)
- Rasterizes to RGBA8888 on a background thread (C++)
- Zero SVG / JS barcode layout work at runtime
- Typed Nitro Hybrid Object API

## Install

```sh
npm install react-native-nitro-barcode react-native-nitro-modules @shopify/react-native-skia
```

or:

```sh
yarn add react-native-nitro-barcode react-native-nitro-modules @shopify/react-native-skia
```

Then install iOS pods:

```sh
cd ios && pod install
```

`react-native-nitro-modules` and `@shopify/react-native-skia` are peer dependencies and must be installed in the host app.

## Usage

```ts
import {
  getBarcodeGenerator,
  NitroBarcodeImage,
} from 'react-native-nitro-barcode';

const gen = getBarcodeGenerator();
const bitmap = gen.generateCode128('1234567890', {
  moduleWidth: 2,
  height: 60,
  lineColor: 0xff000000,
  backgroundColor: 0xffffffff,
});
// bitmap: { width, height, data: ArrayBuffer }

<NitroBarcodeImage
  value={loyaltyId}
  options={{ moduleWidth: 2, height: 60, lineColor: 0xff000000 }}
/>
```

## Regenerate Nitro bindings

After editing `src/specs/*.nitro.ts`, regenerate the Nitro bindings:

```sh
npx nitrogen
npm run build
```
