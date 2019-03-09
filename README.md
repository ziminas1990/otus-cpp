# Homework-04 description
print_ip implementation, powered by SFINAE

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

# Usefull links
  - [bmegli/doxygen-with-travis-ci.md](https://gist.github.com/bmegli/e22ba525dda0b197b2d4440d08f43ae2) - article, that helped me to run and publish doxygen files via travis-ci
