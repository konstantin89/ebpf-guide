# ebpf-guide

## Links

[Code examples](https://github.com/lizrice/learning-ebpf)

## Tools

### Installing libbpf
``` bash
sudo apt-get install libelf-dev
git clone --depth 1 https://github.com/libbpf/libbpf
cd libbpf/src
sudo make install
```

### Installing CLang 11
``` bash
sudo apt install clang-11 --install-suggests
```