**include():** Allows us to include another cmake file in the system.

```
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(src/CMakeLists.txt)
```