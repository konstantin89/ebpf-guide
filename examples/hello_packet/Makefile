TARGETS = hello_packet_func
CLANG=clang-11
all: $(TARGETS)
.PHONY: all

$(TARGETS): %: %.bpf.o 

%.bpf.o: %.bpf.c
	$(CLANG)                                 \
	    -target bpf                          \
		-I /usr/include/arm-linux-gnueabihf/ \
		-g                                   \
	    -O2 -o $@ -c $<

clean: 
	- rm *.bpf.o
#	- rm -f /sys/fs/bpf/hello 
#	- rm -f /sys/fs/bpf/hello-func