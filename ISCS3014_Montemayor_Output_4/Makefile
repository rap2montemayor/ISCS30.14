# Note: Windows only
CXX      := g++
BINDIR   := bin
BUILD    := build
OUT      := out
SRCDIRS  := src libs/Poly/src/
INCLUDES := -I libs/Poly/include -I libs/SFML-2.5.1/include

FLAGS    := -std=c++17 -O3 -Wall -DSFML_STATIC -static -static-libgcc -static-libstdc++
LDFLAGS  := -L libs/SFML-2.5.1/extlibs -L libs/SFML-2.5.1/lib-s
LIBS     := -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
LIBS     += -lfreetype -lopengl32 -lwinmm -lgdi32

# Replaces forward slashes because Windows.
SRCDIRS := $(foreach DIR,$(SRCDIRS),$(subst /,\,$(DIR)))

# Gets .cpp files for each directory listed in SRC_DIRS
SRCS := $(foreach DIR,$(SRCDIRS),$(shell where /r $(DIR) *.cpp))

# Replaces backslashes because Windows.
SRCS := $(foreach FILE,$(SRCS),$(subst \,/,$(FILE)))

# Get relative paths
SRCS := $(foreach FILE,$(SRCS),$(subst $(CURDIR)/,,$(FILE)))

# Object files will be in the build folder, which will mirror the directory
# structure of the root folder.
OBJS := $(foreach FILE,$(SRCS),$(BUILD)/$(subst cpp,obj,$(FILE)))

make: $(OBJS)
	@echo [%TIME%] Compiling program
	$(CXX) $(OBJS) -o $(BINDIR)/$(OUT).exe $(FLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS)  
	@if exist $(BINDIR)\$(OUT).exe (echo [%TIME%] Done compiling)

# $@ = target, $< = first prerequisite file
$(BUILD)/%.obj: %.cpp
	@echo [%TIME%] Compiling source file $<
	@if not exist $(subst /,\,$(dir $@)) (mkdir $(subst /,\,$(dir $@)))
	$(CXX) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo [%TIME%] Created $@

clean:
	@if exist $(subst /,\,$(BUILD))	(echo -n Will delete: && rd $(subst /,\,$(BUILD)) /S) 
