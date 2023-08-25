# ebpf-guide

## Links

[Code examples](https://github.com/lizrice/learning-ebpf)

## Example apps
[Hello packet app - Loading app to kernel and attaching to net dev](/examples/hello_packet/README.md)  

## Installation

### Installing libbpf
``` bash
sudo apt-get install libelf-dev
git clone --depth 1 https://github.com/libbpf/libbpf
cd libbpf/src
sudo make install
```

### installing bpftool
[bpftool official guide](https://github.com/libbpf/bpftool)

### Installing CLang 11
``` bash
sudo apt install clang-11 --install-suggests
```

### Installing LLVM tools
Tools: llvm-objdump  
``` bash
sudo apt install llvm
```


## Dev Tools

### llvm-objdump output example
`pi@raspberrypi:~ $ llvm-objdump -S hello_packet_func.bpf.o`

``` bash
hello_packet_func.bpf.o:        file format ELF64-BPF

Disassembly of section xdp:
hello:
; int hello(struct xdp_md *ctx) {
       0:       18 06 00 00 00 00 00 00 00 00 00 00 00 00 00 00         r6 = 0 ll
; bpf_printk("Hello World %d", counter);
       2:       61 63 00 00 00 00 00 00         r3 = *(u32 *)(r6 + 0)
       3:       18 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00         r1 = 0 ll
       5:       b7 02 00 00 0f 00 00 00         r2 = 15
       6:       85 00 00 00 06 00 00 00         call 6
; counter++;
       7:       61 61 00 00 00 00 00 00         r1 = *(u32 *)(r6 + 0)
       8:       07 01 00 00 01 00 00 00         r1 += 1
       9:       63 16 00 00 00 00 00 00         *(u32 *)(r6 + 0) = r1
; return XDP_PASS;
      10:       b7 00 00 00 02 00 00 00         r0 = 2
      11:       95 00 00 00 00 00 00 00         exit
```