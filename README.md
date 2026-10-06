# Math3D

A lightweight, header-only C++ mathematics library for computer graphics inspired by [OpenGL Mathematics (GLM)](https://github.com/g-truc/glm).

## Installation

### CMake using FetchContent

Add the following to your `CMakeLists.txt` file to automatically download and link _Math3D_ as a dependency:

```cmake
include(FetchContent)

fetchcontent_declare(
  math3d
  GIT_REPOSITORY https://github.com/marcelagallegos/math3d
  GIT_TAG fe790f3ddb271d4933033df6654c91e6c9d307da
)

fetchcontent_makeavailable(math3d)

target_link_libraries(<target> PRIVATE math3d::math3d)
```
