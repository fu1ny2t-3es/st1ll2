MODULE := src/lib/tinyexif

MODULE_OBJS := \
	src/lib/tinyexif/tinyexif.o

MODULE_TEST_OBJS =

MODULE_DIRS += \
	src/lib/tinyexif

# Include common rules
include $(srcdir)/common.rules
