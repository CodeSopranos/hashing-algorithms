set build_prefix=build-win

mkdir %build_prefix%-release
PUSHD %build_prefix%-release

cmake -G "Visual Studio 15 2017" -A x64 ..
cmake --build .

POPD