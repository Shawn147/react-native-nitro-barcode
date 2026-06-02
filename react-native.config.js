module.exports = {
  dependency: {
    platforms: {
      ios: {},
      android: {
        sourceDir: 'android',
        packageImportPath:
          'import com.margelo.nitro.barcode.NitroBarcodePackage;',
        packageInstance: 'new NitroBarcodePackage()',
      },
    },
  },
};
