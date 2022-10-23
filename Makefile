PROJECT_NAME = Cosmic

CXX := clang++
CXX_DEBUG := -g
CXX_FLAGS := -O2 -Wall -Wextra -pedantic -std=c++20
CXX_LIBS := -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama -lXcursor #-lcosmic

SRC := src/
BIN := bin/
OBJS := objs/

CXX_INCLUDES := $(SRC)includes/
CXX_FILES := $(wildcard $(SRC)*.cpp)
CXX_OBJS := $(patsubst $(SRC)%.cpp, $(OBJS)%.o, $(CXX_FILES))
#----------------------------------------------------------------------------------
DEPENDENCIES_SRC := dependencies/
DEPENDENCIES_OBJS := objs/dependencies/

DEPENDENCIES_GLAD := $(DEPENDENCIES_SRC)glad/
DEPENDENCIES_GLAD_CC := $(wildcard $(DEPENDENCIES_GLAD)*.c)
DEPENDENCIES_GLAD_OBJ := $(patsubst $(DEPENDENCIES_GLAD)%.c, $(DEPENDENCIES_OBJS)%.o, $(DEPENDENCIES_GLAD_CC))

DEPENDENCIES_IMGUI := $(DEPENDENCIES_SRC)imgui/cpp/
DEPENDENCIES_IMGUI_CXX := $(wildcard $(DEPENDENCIES_SRC)imgui/cpp/*.cpp)
DEPENDENCIES_IMGUI_OBJS := $(patsubst $(DEPENDENCIES_SRC)imgui/cpp/%.cpp, $(DEPENDENCIES_OBJS)%.o, $(DEPENDENCIES_IMGUI_CXX))

CXX_DEPENDENCIES_FLAGS := -c -O3 -w -std=c++20
DEPENDENCIES_INCLUDES := -I $(DEPENDENCIES_SRC)/ -I $(DEPENDENCIES_SRC)glad/ -I $(DEPENDENCIES_SRC)imgui/
#----------------------------------------------------------------------------------
COSMIC_SRC := $(SRC)cosmic/
COSMIC_LIB := $(COSMIC_SRC)lib/
COSMIC_SRC_OBJS := $(OBJS)cosmic/
COSMIC_CXX := $(wildcard $(COSMIC_SRC)*.cpp)
COSMIC_OBJS := $(patsubst $(COSMIC_SRC)%.cpp, $(COSMIC_SRC_OBJS)$(COSMIC_OBJS)%.o, $(COSMIC_CXX))
COSMIC_INCLUDES := $(COSMIC_SRC)includes/
CXX_COSMIC_FLAGS := -c -O3 -Wall -Wextra -pedantic -std=c++20
#----------------------------------------------------------------------------------
all: clear all-deps $(OBJS)main.o $(CXX_OBJS) link run

clear:
	@clear
run: 
	@echo '\033[0m' ""
	@$(BIN)$(PROJECT_NAME).out
clean:
	-rm -f $(OBJS)*.o
	-rm -f $(BIN)*
clean-cosmic:
	-rm -f $(COSMIC_SRC_OBJS)*.o
	-rm -f $(COSMIC_LIB)*.a
clean-deps:
	-rm -f $(DEPENDENCIES_OBJS)*.o
clean-all: clear clean clean-cosmic clean-deps
all-deps: deps cosmic
#----------------------------------------------------------------------------------
$(OBJS)main.o: $(SRC)main.cpp
	@echo '\033[1;32m' "\nCompiling main\n"
	@$(CXX) $(CXX_DEBUG) -c $< $(DEPENDENCIES_INCLUDES) -I $(COSMIC_INCLUDES) -I $(CXX_INCLUDES) $(CXX_COSMIC_FLAGS) -o $(OBJS)main.o


$(OBJS)%.o: $(SRC)%.cpp $(CXX_INCLUDES)%.hpp
	@echo '\033[1;32m' "\nCompiling $*\n"
	@$(CXX) $(CXX_DEBUG) $< $(DEPENDENCIES_INCLUDES) -I $(COSMIC_INCLUDES) -I $(CXX_INCLUDES) -c -o $(OBJS)$*.o

link:
	@$(CXX) $(CXX_DEBUG) $(OBJS)*.o $(COSMIC_SRC_OBJS)*.o $(DEPENDENCIES_OBJS)*.o -L $(COSMIC_LIB) $(CXX_FLAGS) $(CXX_LIBS) -I $(CXX_INCLUDES) $(DEPENDENCIES_INCLUDES) -I $(COSMIC_INCLUDES) -o $(BIN)$(PROJECT_NAME).out

#----------------------------------------------------------------------------------
$(COSMIC_SRC_OBJS)%.o: $(COSMIC_SRC)%.cpp $(COSMIC_INCLUDES)%.hpp
	@echo '\033[1;32m' "\nCompiling $*\n"
	@$(CXX) $(CXX_DEBUG) $< -I $(COSMIC_INCLUDES) $(DEPENDENCIES_INCLUDES) $(CXX_COSMIC_FLAGS) -o $(COSMIC_SRC_OBJS)$*.o

cosmic: clear $(COSMIC_OBJS)
#	@ar rvs $(COSMIC_LIB)libcosmic.a $(COSMIC_SRC_OBJS)*.o $(DEPENDENCIES_OBJS)*.o
#----------------------------------------------------------------------------------
$(DEPENDENCIES_OBJS)%.o: $(DEPENDENCIES_GLAD)%.c
	@echo '\033[1;32m' "\nCompiling $*\n"
	@$(CXX) $< $(DEPENDENCIES_INCLUDES) -o $(DEPENDENCIES_OBJS)$*.o $(CXX_DEPENDENCIES_FLAGS)

$(DEPENDENCIES_OBJS)%.o: $(DEPENDENCIES_IMGUI)%.cpp
	@echo '\033[1;32m' "\nCompiling $*\n"
	@$(CXX) $< $(DEPENDENCIES_INCLUDES) -o $(DEPENDENCIES_OBJS)$*.o $(CXX_DEPENDENCIES_FLAGS)

deps: clear $(DEPENDENCIES_GLAD_OBJ) $(DEPENDENCIES_IMGUI_OBJS)
