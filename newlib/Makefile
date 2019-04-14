TOPDIR = $(shell pwd)
ARCH = x86
BIT = 32

NEWLIB_PREFX=$(HOME)/Projects/os/sysroot/usr

ifeq ($(ARCH),x86)
ifeq ($(BIT),32)
	TARGET=i386-eduos-elf32
endif
ifeq ($(BIT),64)
	TARGET=x86_64-eduos-elf64
endif
endif

NEWLIB = $(TOPDIR)/$(ARCH)/$(TARGET)
RM = rm -rf
CD = cd
MKDIR = mkdir
TMP = $(TOPDIR)/tmp
OPT = --disable-shared \
	--disable-libstdcxx \
	--disable-multilib \
	--disable-newlib-multithread \
	--disable-newlib-reent-small \
	CC_FOR_TARGET=$(CC_FOR_TARGET) \
    CXX_FOR_TARGET=$(CXX_FOR_TARGET) \
    GCC_FOR_TARGET=$(GCC_FOR_TARGET) \
    AR_FOR_TARGET=$(AR_FOR_TARGET) \
    AS_FOR_TARGET=$(AS_FOR_TARGET) \
    LD_FOR_TARGET=$(LD_FOR_TARGET) \
    NM_FOR_TARGET=$(NM_FOR_TARGET) \
	OBJDUMP_FOR_TARGET=$(OBJDUMP_FOR_TARGET) \
    OBJCOPY_FOR_TARGET=$(OBJCOPY_FOR_TARGET) \
    RANLIB_FOR_TARGET=$(RANLIB_FOR_TARGET) \
    STRIP_FOR_TARGET=$(STRIP_FOR_TARGET) \
    READELF_FOR_TARGET=$(READELF_FOR_TARGET)

# Prettify output
V = 0
ifeq ($V,0)
	Q = @
	P = > /dev/null
endif

default: $(ARCH)
	$Q$(MAKE) ARCH=$(ARCH) BIT=$(BIT) TARGET=$(TARGET) CFLAGS+="-ffreestanding -Wall -I../../include -I../../arch/$(ARCH)/include" LDFLAGS+="" -C examples depend
	$Q$(MAKE) ARCH=$(ARCH) BIT=$(BIT) TARGET=$(TARGET) CFLAGS+="-ffreestanding -Wall -I../../include -I../../arch/$(ARCH)/include" LDFLAGS+="" -C examples

$(ARCH):
	@echo $(TARGET)
	$Q$(RM) $(TMP)
	$Q$(MKDIR) $(TMP)
	$Q$(CD) $(TMP); $(TOPDIR)/src/configure --target=$(TARGET) --prefix=$(TOPDIR)/$(ARCH) $(OPT)  && $(MAKE) && $(MAKE) install

clean:
	@echo Cleaning newlib
	$Q$(MAKE) -C examples clean
	$Q$(RM) $(TMP)

veryclean:
	@echo Propper cleaning newlib
	$Q$(MAKE) -C examples veryclean
	$Q$(RM) $(TOPDIR)/$(ARCH)
