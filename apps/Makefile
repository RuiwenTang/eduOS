TOPDIR = $(shell pwd)
ARCH := 32

CROSSCOMPREFIX := i686-eduos-

CC_FOR_TARGET = $(CROSSCOMPREFIX)gcc
CXX_FOR_TARGET = $(CROSSCOMPREFIX)g++
GCC_FOR_TARGET = $(CROSSCOMPREFIX)gcc
CPP_FOR_TARGET = $(CROSSCOMPREFIX)cpp
AR_FOR_TARGET = $(CROSSCOMPREFIX)ar
AS_FOR_TARGET = $(CROSSCOMPREFIX)as
LD_FOR_TARGET = $(CROSSCOMPREFIX)ld
NM_FOR_TARGET = $(CROSSCOMPREFIX)nm
OBJDUMP_FOR_TARGET = $(CROSSCOMPREFIX)objdump
OBJCOPY_FOR_TARGET = $(CROSSCOMPREFIX)objcopy
RANLIB_FOR_TARGET = $(CROSSCOMPREFIX)ranlib
STRIP_FOR_TARGET = $(CROSSCOMPREFIX)strip
READELF_FOR_TARGET = $(CROSSCOMPREFIX)readelf

TOPDIR := $(shell pwd)
OUTDIR := $(TOPDIR)/out

LDFLAGS := -T link.ld
CFLAGS = -Wall -m32

default: all

Modules= bar filemanager

all:
	@echo make service modules
	@mkdir -p out
	@for module in $(Modules); do \
		make TOPDIR=$(TOPDIR) \
		OUTDIR=$(OUTDIR) \
		ARCH=$(ARCH) \
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
        READELF_FOR_TARGET=$(READELF_FOR_TARGET) \
		-C $$module -f build.mk default; \
	done


clean:
	@echo Cleaning tools
	$(shell rm -rf out)

.PHONY: default
    