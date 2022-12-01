CXX := g++

DETECTED_OS := 
ifeq ($(OS), Windows_NT)
	DETECTED_OS := Windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		DETECTED_OS := Linux
	endif
endif

#----------------------------------------------------------------------------------

# Main
CXX_FLAGS := -g -O2 -Wall -Wextra -pedantic -std=c++20

ALL_INCLUDES += -I src/includes
ALL_INCLUDES += -I src/cosmic/includes
ALL_INCLUDES += -I dependencies
ALL_INCLUDES += -I dependencies/glfw/include
ALL_INCLUDES += -I dependencies/glad
ALL_INCLUDES += -I dependencies/glm
ALL_INCLUDES += -I dependencies/imgui
ALL_INCLUDES += -I dependencies/stb

CXX_LINUX_LIBS := -lGL dependencies/glfw/src/libglfw3.a -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama -lXcursor
CXX_WINDOWS_LIBS := dependencies/glfw/src/libglfw3.a -lopengl32 -lgdi32 -luser32 -lkernel32

SRC := src
BIN := bin
OBJS_DIR := objs

CXX_FILES := $(wildcard $(SRC)/*.cpp)
CXX_OBJS := $(patsubst $(SRC)/%.cpp, $(OBJS_DIR)/%.o, $(CXX_FILES))

#----------------------------------------------------------------------------------

#Dependencies

DEPS_SRC := dependencies/
DEPS_OBJS_DIR := $(OBJS_DIR)/dependencies

# Glad
DEPS_GLAD := $(DEPS_SRC)/glad
DEPS_GLAD_CC := $(wildcard $(DEPS_GLAD)/*.c)
DEPS_GLAD_OBJ := $(patsubst $(DEPS_GLAD)/%.c, $(DEPS_OBJS_DIR)/%.o, $(DEPS_GLAD_CC))

# Imgui
DEPS_IMGUI := $(DEPS_SRC)/imgui/cpp
DEPS_IMGUI_CXX := $(wildcard $(DEPS_IMGUI)/*.cpp)
DEPS_IMGUI_OBJS := $(patsubst $(DEPS_IMGUI)/%.cpp, $(DEPS_OBJS_DIR)/%.o, $(DEPS_IMGUI_CXX))

CXX_DEPS_FLAGS := -g -c -O3 -w -std=c++20

#----------------------------------------------------------------------------------

#Cosmic engine

COSMIC_SRC := $(SRC)/cosmic
COSMIC_LIB := $(COSMIC_SRC)/lib
COSMIC_OBJS_DIR := $(OBJS_DIR)/cosmic

COSMIC_CXX := $(wildcard $(COSMIC_SRC)/*.cpp)
COSMIC_OBJS := $(patsubst $(COSMIC_SRC)/%.cpp, $(COSMIC_OBJS_DIR)/%.o, $(COSMIC_CXX))

COSMIC_INCLUDES := $(COSMIC_SRC)/includes
CXX_COSMIC_FLAGS := -g -c -O3 -Wall -Wextra -pedantic -std=c++20

#----------------------------------------------------------------------------------

.PHONY: all clear clean run

all: clear \
	dirs \
	build \
	link \
	run 

dirs:
	@mkdir -p bin/ objs/ $(COSMIC_OBJS_DIR)/ objs/dependencies/

build: glfw deps cosmic main

glfw:
ifeq ($(wildcard dependencies/glfw/.*),)
	git clone https://github.com/glfw/glfw.git dependencies/glfw
	cmake -S dependencies/glfw/ -B dependencies/glfw/ -G"Unix Makefiles"
	make -C dependencies/glfw
endif

clear:
	@clear
run: 
	@$(BIN)/a.out
clean:
	@-rm -f $(OBJS_DIR)/*.o $(BIN)/*.o
clean-cosmic:
	@-rm -f $(COSMIC_OBJS_DIR)/*.o
clean-deps:
	@-rm -f $(DEPS_OBJS_DIR)/*.o
clean-glfw:
	@-rm -rf $(DEPS_SRC)/glfw/
clean-all:
	@-rm -rf objs/ bin/

#----------------------------------------------------------------------------------

# Compile main files

$(OBJS_DIR)/%.o: $(SRC)/%.cpp $(SRC)/includes/%.hpp 
	@echo "COMPILING MAIN::$*"
	@$(CXX) -c $< -o $(OBJS_DIR)/$*.o $(ALL_INCLUDES)

$(OBJS_DIR)/%.o: $(SRC)/%.cpp
	@echo "COMPILING MAIN::$*"
	@$(CXX) -c $< -o $(OBJS_DIR)/$*.o $(ALL_INCLUDES)

link:
ifeq ($(DETECTED_OS),Windows)
	@$(CXX) $(OBJS_DIR)/*.o $(COSMIC_OBJS_DIR)/*.o $(DEPS_OBJS_DIR)/*.o -o $(BIN)/a.out $(CXX_FLAGS) $(CXX_WINDOWS_LIBS) $(ALL_INCLUDES)
else ifeq ($(DETECTED_OS),Linux)
	@$(CXX) $(OBJS_DIR)/*.o $(COSMIC_OBJS_DIR)/*.o $(DEPS_OBJS_DIR)/*.o -o $(BIN)/a.out $(CXX_FLAGS) $(CXX_LINUX_LIBS) $(ALL_INCLUDES)
endif

main: $(OBJS_DIR) $(CXX_OBJS)

#----------------------------------------------------------------------------------

# Compile Cosmic files

$(COSMIC_OBJS_DIR)/%.o: $(COSMIC_SRC)/%.cpp $(COSMIC_INCLUDES)/%.hpp
	@echo "COMPILING COSMIC::$*"
	@$(CXX) $< $(ALL_INCLUDES) $(CXX_COSMIC_FLAGS) -o $(COSMIC_OBJS_DIR)/$*.o

$(COSMIC_OBJS_DIR)/%.o: $(COSMIC_SRC)/%.cpp
	@echo "COMPILING COSMIC::$*"
	@$(CXX) $< $(ALL_INCLUDES) $(CXX_COSMIC_FLAGS) -o $(COSMIC_OBJS_DIR)/$*.o


cosmic: $(COSMIC_OBJS)

#----------------------------------------------------------------------------------

# Compile dependencies

# Glad
$(DEPS_OBJS_DIR)/%.o: $(DEPS_GLAD)/%.c
	@echo "COMPILING DEPENDENCIES::$*"
	@$(CXX) $< $(ALL_INCLUDES) -o $(DEPS_OBJS_DIR)/$*.o $(CXX_DEPS_FLAGS)

# Imgui
$(DEPS_OBJS_DIR)/%.o: $(DEPS_IMGUI)/%.cpp
	@echo "COMPILING DEPENDENCIES::$*"
	@$(CXX) $< $(ALL_INCLUDES) -o $(DEPS_OBJS_DIR)/$*.o $(CXX_DEPS_FLAGS)

deps: $(DEPS_GLAD_OBJ) $(DEPS_IMGUI_OBJS)
