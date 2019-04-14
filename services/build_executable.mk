objc := $(patsubst %.c,%.o,$(LOCAL_SRC_FILES))
objs := $(patsubst %.cpp,%.o,$(objc))

CFLAGS := -m32 -Wall -ffreestanding
LDFLAGS := -T link.ld

%.o: %.c
	@echo [CC] $@
	$Q$(GCC_FOR_TARGET) -c $(CFLAGS) $(LOCAL_C_FLAGS) -o $@ $<

%.o: %.cpp
	@echo [CXX] $@
	$Q$(CXX_FOR_TARGET) -c $(CFLAGS) $(LOCAL_CXX_FLAGS) -o $@ $<

$(OUTDIR)/$(LOCAL_MODULE_NAME): $(objs)
	@echo [LD] $(objs)
	$Q$(CXX_FOR_TARGET) -T link.ld $(LDFLAGS) $(CFLAGS) -lsupc++ $(objs) -o $@
	$Q$(OBJCOPY_FOR_TARGET) $(KEEP_DEBUG) $@ $@.sym
	$Q$(OBJCOPY_FOR_TARGET) $(STRIP_DEBUG) $@
	$Qchmod a-x $@.sym


default: $(OUTDIR)/$(LOCAL_MODULE_NAME)
	@echo $(objs)