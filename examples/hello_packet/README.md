# Hello packet example app

## Running the app

### Compile
```
make
```

### Load program to Kernel
``` bash
sudo bpftool prog load hello_packet_func.bpf.o /sys/fs/bpf/hello_packet  
```

### Make sure that the program is loaded in /sys/fs/bpf
``` bash
sudo ls /sys/fs/bpf  
hello_packet
```

### Inspect loaded program (and get its ID)
``` bash
sudo bpftool prog list
53: xdp  name hello  tag d35b94b4c0c10efb  gpl
        loaded_at 2023-08-25T14:43:39+0300  uid 0
        xlated 96B  not jited  memlock 4096B  map_ids 35,36
        btf_id 24

```
Program ID is 53. `ID is always unique`, but there can be  multiple instances of program with same tag or name.  

``` bash
sudo bpftool prog show id 53 --pretty
{
    "id": 53,
    "type": "xdp",
    "name": "hello",
    "tag": "d35b94b4c0c10efb",
    "gpl_compatible": true,
    "loaded_at": 1692963819,
    "uid": 0,
    "bytes_xlated": 96,
    "jited": false,
    "bytes_memlock": 4096,
    "map_ids": [35,36
    ],
    "btf_id": 24
}
```

### Attach program to event
``` bash
sudo bpftool net attach xdp id 53 dev wlan0
```

Check the network attached programs:
``` bash
sudo bpftool net list

xdp:
wlan0(3) generic id 53

```

``` bash
ip link

3: wlan0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 xdpgeneric qdisc pfifo_fast state UP mode DORMANT group default qlen 1000
    link/ether b8:27:eb:44:26:c9 brd ff:ff:ff:ff:ff:ff
    prog/xdp id 53
```

To detach use:
``` bash
sudo bpftool net detach xdp  dev wlan0
```

### Observe kernel logs
``` bash
sudo cat /sys/kernel/debug/tracing/trace_pipe

kworker/u9:2-581     [000] d.s.1  3752.112209: bpf_trace_printk: Hello World 1577
```

bpftool can do the same:
``` bash
bpftool prog tracelog
```

### Observe program segments
Global variables are stored in BSS segment:
``` bash
$ sudo bpftool map list
35: array  name hello_pa.bss  flags 0x400
        key 4B  value 4B  max_entries 1  memlock 4096B
        btf_id 24
36: array  name hello_pa.rodata  flags 0x80
        key 4B  value 15B  max_entries 1  memlock 4096B
        btf_id 24  frozen
```

Print BSS segment of the program:
(Be aware that `counter` name is shown only -g used during compilation)
``` bash
$ sudo bpftool map dump name hello_pa.bss
[{
        "value": {
            ".bss": [{
                    "counter": 6851
                }
            ]
        }
    }
]

```

The rodata segment stores read only program data:
``` bash
$ sudo bpftool map dump name hello_pa.rodata
[{
        "value": {
            ".rodata": [{
                    "hello.____fmt": "Hello World %d"
                }
            ]
        }
    }
]

```