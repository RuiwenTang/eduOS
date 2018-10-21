objc := $(patsubst %.c,%.o,$(LOCAL_SRC_FILES))
objs := $(patsubst %.cpp,%.o,$(objc))

%.o: %.c
	@echo [CC] $@
	$Q$(GCC_FOR_TARGET) -c $(CFLAGS) -o $@ $<

%.o: %.cpp
	@echo [CXX] $@
	$Q$(CXX_FOR_TARGET) -c $(CFLAGS) -o $@ $<

$(LOCAL_MODULE_NAME): $(objs)
	@echo $@
	$Q$(CXX_FOR_TARGET) $(LDFLAGS) $(CFLAGS) $< -o $(OUTDIR)/$(LOCAL_MODULE_NAME)


default: $(LOCAL_MODULE_NAME)
	@echo $(objs)