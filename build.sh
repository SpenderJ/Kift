#!/usr/bin/env bash

brew install sox
brew tap watsonbox/cmu-sphinx
brew install --HEAD watsonbox/cmu-sphinx/cmu-sphinxbase
brew install --HEAD watsonbox/cmu-sphinx/cmu-pocketsphinx
cd client
npm install
npm run build
rm -irf ../site/*
cp -R build/* ../site/
cd ..
make re
./server
