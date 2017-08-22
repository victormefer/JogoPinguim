#Compilador + flags
#CXX 		= MinGW32-g++
CXX 		= g++
SDL 		= -lSDL2
SDL_main	= -lSDL2main
SDL_image 	= -lSDL2_image
SDL_mixer 	= -lSDL2_mixer
SDL_ttf 	= -lSDL2_ttf


#Diretórios
SRCDIR		= src
BUILDDIR 	= build
EXE 		= main
SDL_DIR 	= C:\SDL

#Arquivos
SRCEXT 	= cpp
#HFILES	= $(wildcard $(SRCDIR)/*.h)
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Header dependencies
# DEP = $(OBJECTS:%.o=%.d)


#Flags para linking
CXXFLAGS 	= -Wall -std=c++11 -w -g
LIB 		= $(SDL_main) $(SDL) $(SDL_image) $(SDL_mixer) $(SDL_ttf)

INC = -I$(SDL_DIR)\include -L$(SDL_DIR)\lib

# -include $(DEP)


all: main

main: $(OBJECTS)
	@echo " Linking..."
	$(CXX) $(OBJECTS) -o $(EXE).exe $(INC) -lmingw32 $(LIB) $(CXXFLAGS)

#Geração dos objetos '.o' a partir dos arquivos fonte '.cpp'
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) -lmingw32 $(INC) $(CXXFLAGS) $(LIB) -c -o $@ $<

# Limpa a compilação anterior
clean:
	@echo " Cleaning...";
	rm -r $(OBJECTS)


.PHONY: clean

# Checa a versão do compilador, para depuração mais eficiente
version:
	$(CPLUS) --version