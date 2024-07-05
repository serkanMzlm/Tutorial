## MAVLink Haberleşmesi

#### Build
1. Yol:
```
cmake -B build 
cd build
make
```

2. Yol:
```
cmake -B build -D[pkg_path]
cmake --build [pkg_path]
```

```bash
cmake -B build -H. -DCMAKE_PREFIX_PATH=../mavlink/install
```

```bash
./mavlink_control -d /dev/ttyACM0
./mavlink_control -u 127.0.0.1 -a
```