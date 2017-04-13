#/usr/bin/env sh

# This is a wrapper script to enable quick benchmarking of various build
# configurations. This script uses the `benchmark` executable built in the
# `tests/` directory.

set -e

# Update these variables for your own system.
cpd_dir="$HOME/Repos/cpd"
fgt_dir="$HOME/Repos/fgt"
cpd_cmake="cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/local -DWITH_JSONCPP=ON -DWITH_TESTS=ON"
fgt_cmake="cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/local"

# Data files and output directory.
#
# `grealpath` is provided on OSX by `brew install coreutils`.
method=$1
fixed=$(grealpath $2)
moving=$(grealpath $3)
niter=$4
outdir=$(grealpath $5)

# Setup
mkdir -p $outdir
cd $cpd_dir
rm -rf build && mkdir build && cd build

# First benchmark: cpd without fgt
eval $cpd_cmake -DWITH_FGT=OFF
ninja
tests/benchmark $method $fixed $moving $niter $outdir/no-fgt.txt

# Second benchmark: cpd with fgt (no openmp)
cd $fgt_dir
rm -rf build && mkdir build && cd build
eval $fgt_cmake -DWITH_OPENMP=OFF
ninja install
cd $cpd_dir/build
eval $cpd_cmake -DWITH_FGT=ON
ninja
tests/benchmark $method $fixed $moving $niter $outdir/fgt.txt
