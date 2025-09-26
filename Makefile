CXX := g++

CXXFLAGS := -Wall -std=c++23 -Iinclude -Iinclude/pdcurses -Iinclude/text-editor



OBJDIR := build/obj/

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:src/%.cpp=$(OBJDIR)%.o)

ifeq ($(OS), Windows_NT)
	LDFLAGS := -Llib/pdcurses
	LDLIBS := -lpdcurses
	DIR := build/windows
	MKDIR := if not exist "$(DIR)" mkdir "$(DIR)"
	MKBIN := if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"
else
	LDLIBS := -lncurses
	LDFLAGS :=
	DIR := build/unix/
	MKDIR := mkdir -p "$(DIR)"
	MKBIN := mkdir -p "$(OBJDIR)"
endif




build: $(OBJS)
	$(MKDIR)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(DIR)/texteditor

$(OBJDIR)%.o: src/%.cpp
	$(MKBIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@



	
	



