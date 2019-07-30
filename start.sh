#!/bin/sh
# rm -rf node_modules/
# rm -f yarn.lock
# yarn
cd src/native
rm -rf build
node-gyp configure
# node-gyp rebuild --target=5.0.8 --arch=x64 --dist-url=https://atom.io/download/electron
node-gyp rebuild --target=5.0.8 --arch=x64 --dist-url=https://atom.io/download/atom-shell
cd ../..
# ./node_modules/.bin/electron-rebuild
npm run dev