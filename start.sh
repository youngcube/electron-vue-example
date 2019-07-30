#!/bin/sh
cd src/native
rm -rf build
node-gyp configure
node-gyp build
cd ../..
npm run dev