#!/bin/sh

mkdir build/
cd build

git clone https://github.com/sylvainprigent/score.git
cd score
mkdir build/
cd build/
cmake ..
make
cd ../..

git clone https://github.com/sylvainprigent/sdata.git
cd sdata
mkdir build/
cd build/
cmake ..
make
cd ../..

git clone https://github.com/sylvainprigent/simage.git
cd simage
mkdir build/
cd build/
cmake .. -Dscore_DIR=${PWD}/../../score/build/ -Dsdata_DIR=${PWD}/../../sdata/build/
make
cd ../..

git clone https://github.com/sylvainprigent/simageio.git
cd simageio
mkdir build/
cd build/
cmake .. -Dsimageio_BUILD_TOOLS=OFF -Dscore_DIR=${PWD}/../../score/build/ -Dsimage_DIR=${PWD}/../../simage/build/
make
cd ../..

git clone https://github.com/sylvainprigent/sdataio.git
cd sdataio
mkdir build/
cd build/
cmake .. -Dsdataio_BUILD_TOOLS=OFF -Dscore_DIR=${PWD}/../../score/build/ -Dsdata_DIR=${PWD}/../../sdata/build/
make
cd ../..

git clone https://github.com/sylvainprigent/sshape.git
cd sshape
mkdir build/
cd build/
cmake .. -Dsshape_BUILD_TOOLS=OFF -Dscore_DIR=${PWD}/../../score/build/ -Dsimage_DIR=${PWD}/../../simage/build/
make
cd ../..

git clone https://github.com/sylvainprigent/scli.git
cd scli
mkdir build/
cd build/
cmake .. -Dscli_BUILD_TOOLS=OFF -Dscore_DIR=${PWD}/../../score/build/
make
cd ../..

# STracking
cmake .. -Dstracking_BUILD_TOOLS=ON -Dscore_DIR=${PWD}/score/build/ -Dsimage_DIR=${PWD}/simage/build/ -Dsdata_DIR=${PWD}/sdata/build/ -Dsimageio_DIR=${PWD}/simageio/build/ -Dsdataio_DIR=${PWD}/sdataio/build/ -Dsshape_DIR=${PWD}/sshape/build/ -Dscli_DIR=${PWD}/scli/build/
cmake ..
make
