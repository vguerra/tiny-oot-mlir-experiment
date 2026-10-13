#!/bin/sh

if [ -d "./build" ]; then
    echo "removing build directory"
    rm -r build
fi
mkdir -p build

pushd build

MLIR_DIR=$(brew --prefix llvm) cmake .. -G Ninja
cmake --build . --target FoldAddZeroPass
cmake --build . --target my-opt

popd

ln -sf ./build/compile_commands.json
