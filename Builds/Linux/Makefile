# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_8068DBC5=1" -I /usr/include -I /usr/include/freetype2 -I ../Jucer/JuceLibraryCode -I ../../Extern/JUCE -I ../../Extern/VFLib
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_8068DBC5=1" -I /usr/include -I /usr/include/freetype2 -I ../Jucer/JuceLibraryCode -I ../../Extern/JUCE -I ../../Extern/VFLib
  TARGET := LayerEffects
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_8068DBC5=1" -I /usr/include -I /usr/include/freetype2 -I ../Jucer/JuceLibraryCode -I ../../Extern/JUCE -I ../../Extern/VFLib
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_8068DBC5=1" -I /usr/include -I /usr/include/freetype2 -I ../Jucer/JuceLibraryCode -I ../../Extern/JUCE -I ../../Extern/VFLib
  TARGET := LayerEffects
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/vf_core_cae091f1.o \
  $(OBJDIR)/vf_concurrent_61d393e1.o \
  $(OBJDIR)/vf_gui_33d46993.o \
  $(OBJDIR)/vf_unfinished_938ddd89.o \
  $(OBJDIR)/source_704c2604.o \
  $(OBJDIR)/juce_audio_basics_454b9ecb.o \
  $(OBJDIR)/juce_audio_devices_a68a6cc9.o \
  $(OBJDIR)/juce_audio_formats_d50bb669.o \
  $(OBJDIR)/juce_core_f6491dad.o \
  $(OBJDIR)/juce_data_structures_d80ae1a9.o \
  $(OBJDIR)/juce_events_698aeba1.o \
  $(OBJDIR)/juce_graphics_5c9f1285.o \
  $(OBJDIR)/juce_gui_basics_f79baf81.o \
  $(OBJDIR)/juce_gui_extra_d475cd49.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking LayerEffects
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning LayerEffects
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

strip:
	@echo Stripping LayerEffects
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/vf_core_cae091f1.o: ../../Extern/VFLib/modules/vf_core/vf_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_concurrent_61d393e1.o: ../../Extern/VFLib/modules/vf_concurrent/vf_concurrent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_concurrent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_gui_33d46993.o: ../../Extern/VFLib/modules/vf_gui/vf_gui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_gui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_unfinished_938ddd89.o: ../../Extern/VFLib/modules/vf_unfinished/vf_unfinished.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_unfinished.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/source_704c2604.o: ../../Source/source.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling source.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_454b9ecb.o: ../../Extern/JUCE/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a68a6cc9.o: ../../Extern/JUCE/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d50bb669.o: ../../Extern/JUCE/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_f6491dad.o: ../../Extern/JUCE/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_d80ae1a9.o: ../../Extern/JUCE/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_698aeba1.o: ../../Extern/JUCE/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_5c9f1285.o: ../../Extern/JUCE/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_f79baf81.o: ../../Extern/JUCE/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_d475cd49.o: ../../Extern/JUCE/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
