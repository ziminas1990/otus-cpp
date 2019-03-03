# Homewordk-03 description

# How to build on Ubuntu
Easy.
```bash
cmake path/to/sources
cmake --build .
cmake --build . --target test
cmake --build . --target package
```

# How to build on Ubuntu (with autotests)
First, you should build gtest:
```bash
git clone https://github.com/google/googletest.git
mkdir googletest-build
cd googletest-build
cmake ../googletest/ -DCMAKE_INSTALL_PREFIX=${GTEST_INSTALL_DIR}
cmake --build . -- -j5
cmake --build . --target install
make install
```

To build ip-filter with autotests you should run:
```bash
cmake path/to/sources -Dwith-tests=ON -DGTEST_ROOT=${GTEST_INSTALL_DIR}
cmake --build .
cmake --build . --target test
cmake --build . --target package
```
