CXX := g++

# Main
CXX_FLAGS += -g -O2 -Wall -Wextra -pedantic -std=c++20

ALL_INCLUDES += -I src/includes
ALL_INCLUDES += -I src/cosmic/includes
ALL_INCLUDES += -I dependencies
ALL_INCLUDES += -I dependencies/glad
ALL_INCLUDES += -I dependencies/glm
ALL_INCLUDES += -I dependencies/imgui
ALL_INCLUDES += -I dependencies/stb
# ALL_INCLUDES += -L src/cosmic/lib

CXX_LIBS += -lGL -lglfw3 -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama -lXcursor #-lcosmic

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

.PHONY: all clear run

all: clear \
	dirs \
	all-deps \
	all-main \
	link \
	run 

dirs:
ifneq ($(wildcard objs/.*),)
else
	@mkdir bin/ objs/ objs/cosmic/ objs/dependencies/
endif

all-deps: deps cosmic

clear:
	@clear
run: 
	@$(BIN)/a.out
clean:
	@-rm -f $(OBJS_DIR)/*.o $(BIN)/*
clean-cosmic:
	@-rm -f $(COSMIC_OBJS_DIR)/*.o $(COSMIC_LIB)/*.a
clean-deps:
	@-rm -f $(DEPS_OBJS_DIR)/*.o
clean-all:
	@-rm -rf objs/ bin/

#----------------------------------------------------------------------------------

# Compile main files

all-main: $(OBJS_DIR) $(CXX_OBJS)

$(OBJS_DIR)/%.o: $(SRC)/%.cpp $(SRC)/includes/%.hpp
	@echo "\nCompiling $*\n"
	@$(CXX) -c $< -o $(OBJS_DIR)/$*.o $(ALL_INCLUDES)

$(OBJS_DIR)/%.o: $(SRC)/%.cpp
	@echo "\nCompiling $*\n"
	@$(CXX) -c $< -o $(OBJS_DIR)/$*.o $(ALL_INCLUDES)

link:
	@$(CXX) $(OBJS_DIR)/*.o $(COSMIC_OBJS_DIR)/*.o $(DEPS_OBJS_DIR)/*.o -o $(BIN)/a.out $(CXX_FLAGS) $(ALL_INCLUDES) $(CXX_LIBS)

#----------------------------------------------------------------------------------

# Compile Cosmic files

$(COSMIC_OBJS_DIR)/%.o: $(COSMIC_SRC)/%.cpp
	@echo "\nCompiling $*\n"
	@$(CXX) $< $(ALL_INCLUDES) $(CXX_COSMIC_FLAGS) -o objs/cosmic/$*.o


$(COSMIC_OBJS_DIR)/%.o: $(COSMIC_SRC)/%.cpp $(COSMIC_INCLUDES)/%.hpp
	@echo "\nCompiling $*\n"
	@$(CXX) $< $(ALL_INCLUDES) $(CXX_COSMIC_FLAGS) -o objs/cosmic/$*.o

cosmic: $(COSMIC_OBJS)
#@ar rvs $(COSMIC_LIB)/libcosmic.a $(COSMIC_OBJS_DIR)/*.o $(DEPS_OBJS_DIR)/*.o

#----------------------------------------------------------------------------------

# Compile dependencies

# Glad
$(DEPS_OBJS_DIR)/%.o: $(DEPS_GLAD)/%.c
	@echo "\nCompiling $*\n"
	@$(CXX) $< $(ALL_INCLUDES) -o $(DEPS_OBJS_DIR)/$*.o $(CXX_DEPS_FLAGS)

# Imgui
$(DEPS_OBJS_DIR)/%.o: $(DEPS_IMGUI)/%.cpp
	@echo "\nCompiling $*\n"
	@$(CXX) $< $(ALL_INCLUDES) -o $(DEPS_OBJS_DIR)/$*.o $(CXX_DEPS_FLAGS)

deps: $(DEPS_GLAD_OBJ) $(DEPS_IMGUI_OBJS)
