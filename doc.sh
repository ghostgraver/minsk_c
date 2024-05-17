#!/bin/bash
rm -rf build/doc
mkdir -p build/doc
cd doc && doxygen Doxyfile
cd ..
cp doc/doxygen-awesome-css/doxygen-awesome-fragment-copy-button.js build/doc/html/
cp doc/doxygen-awesome-css/doxygen-awesome-interactive-toc.js build/doc/html/
cp -r doc/images build/doc/html/images
# cd build/doc/html && serve

