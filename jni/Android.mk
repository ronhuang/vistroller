#==============================================================================
#            Copyright (c) 2010 QUALCOMM Incorporated.
#            All Rights Reserved.
#            Qualcomm Confidential and Proprietary
#==============================================================================


# An Android.mk file must begin with the definition of the LOCAL_PATH
# variable. It is used to locate source files in the development tree. Here
# the macro function 'my-dir', provided by the build system, is used to return
# the path of the current directory.

LOCAL_PATH := $(call my-dir)

# The CLEAR_VARS variable is provided by the build system and points to a
# special GNU Makefile that will clear many LOCAL_XXX variables for you
# (e.g. LOCAL_MODULE, LOCAL_SRC_FILES, LOCAL_STATIC_LIBRARIES, etc...),
# with the exception of LOCAL_PATH. This is needed because all build
# control files are parsed in a single GNU Make execution context where
# all variables are global.

include $(CLEAR_VARS)

# The LOCAL_MODULE variable must be defined to identify each module you
# describe in your Android.mk. The name must be *unique* and not contain
# any spaces. Note that the build system will automatically add proper
# prefix and suffix to the corresponding generated file. In other words,
# a shared library module named 'foo' will generate 'libfoo.so'.

LOCAL_MODULE := vistroller

# The TARGET_PLATFORM defines the targetted Android Platform API level

TARGET_PLATFORM := android-5

# An optional list of paths, relative to the NDK *root* directory,
# which will be appended to the include search path when compiling
# all sources (C, C++ and Assembly). These are placed before any
# corresponding inclusion flag in LOCAL_CFLAGS / LOCAL_CPPFLAGS.

LOCAL_C_INCLUDES := $(QCAR_SDK_ROOT)/build/include

# This sample always uses OpenGL ES 2.0.
OPENGLES_LIB  := -lGLESv1_CM
OPENGLES_DEF  := -DUSE_OPENGL_ES_1_1

# An optional set of compiler flags that will be passed when building
# C ***AND*** C++ source files.
#
# NOTE: flag "-Wno-write-strings" removes warning about deprecated conversion
#       from string constant to ‘char*’

LOCAL_CFLAGS := -Wno-write-strings $(OPENGLES_DEF)

# The list of additional linker flags to be used when building your
# module. This is useful to pass the name of specific system libraries
# with the "-l" prefix.

# The following resolves cygwin paths problem caused by the ndk-r5
QCAR_LOCAL_PATH := $(QCAR_SDK_ROOT)/build/lib/$(TARGET_ARCH_ABI)

LOCAL_LDLIBS := \
    -L$(QCAR_LOCAL_PATH) \
    -llog -lQCAR \
	$(OPENGLES_LIB)


# The LOCAL_SRC_FILES variables must contain a list of C and/or C++ source
# files that will be built and assembled into a module. Note that you should
# not list header and included files here, because the build system will
# compute dependencies automatically for you; just list the source files
# that will be passed directly to a compiler, and you should be good.

LOCAL_SRC_FILES := Vistroller.cpp SampleUtils.cpp Texture.cpp

# By default, ARM target binaries will be generated in 'thumb' mode, where
# each instruction are 16-bit wide. You can define this variable to 'arm'
# if you want to force the generation of the module's object files in
# 'arm' (32-bit instructions) mode

LOCAL_ARM_MODE := arm

# The BUILD_SHARED_LIBRARY is a variable provided by the build system that
# points to a GNU Makefile script that is in charge of collecting all the
# information you defined in LOCAL_XXX variables since the latest
# 'include $(CLEAR_VARS)' and determine what to build, and how to do it
# exactly. There is also BUILD_STATIC_LIBRARY to generate a static library.

include $(BUILD_SHARED_LIBRARY)
