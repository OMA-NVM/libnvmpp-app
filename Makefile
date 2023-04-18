UK_ROOT ?= $(PWD)/../../unikraft
UK_LIBS ?= $(PWD)/../../libs
LIBS := $(UK_LIBS)/lib-tinyalloc:$(UK_LIBS)/lib-allocnv

all:
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS)

$(MAKECMDGOALS):
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS) $(MAKECMDGOALS)

all-in-one: all
	@find build -mindepth 2 -name '*.o'|grep -v kconfig|grep -v '.ld.o' |sort > objectfiles
	@msp430-elf-gcc \
	-nostdlib  \
	-nostdinc \
	-mmcu=msp430fr5994 \
	-L ../../unikraft/plat/msp430fr5994/include \
	-T build/libmsp430fr5994plat/link.lds \
	-T ../../unikraft/plat/msp430fr5994/msp430fr5994.ld \
	$$(cat objectfiles) \
	-lmul_f5 \
	-lgcc \
	-o build/all-in-one.dbg
	@printf '  %-7s %s\n' 'SCSTRIP'  'all-in-one.dbg' &&  ../../unikraft/support/scripts/sect-strip.py  build/all-in-one.dbg -o build/all-in-one && msp430-elf-strip -s build/all-in-one
	@printf '  %-7s %s\n' 'OBJCOPY'  'all-in-one.hex' &&  msp430-elf-objcopy -O ihex --keep-section .bss build/all-in-one build/all-in-one.hex

flash: all-in-one
	@/usr/local/bin/msp430flasher -q -n msp430fr5994 -w build/all-in-one.hex -v build/all-in-one.hex -z [VCC,RESET]
