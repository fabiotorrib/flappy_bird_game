# ---------------- CONFIGURAÇÃO -----------------------------------------
CXX       := g++

# Allegro packages for pkg-config
ALLEGRO_PKGS := allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 \
                allegro_primitives-5 allegro_audio-5 allegro_acodec-5

# Compiler flags
CXXFLAGS  := -std=c++17 -Wall -Wextra -Iinclude -Iinclude/states -MMD -MP \
             $(shell pkg-config --cflags $(ALLEGRO_PKGS))

# Detect host OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)          # macOS
    LDLIBS := -lallegro_main $(shell pkg-config --libs $(ALLEGRO_PKGS))
else                              # Linux, *BSD, etc.
    LDLIBS := $(shell pkg-config --libs $(ALLEGRO_PKGS))
endif

TARGET := flappy.exe 
SRCDIR := src
OBJDIR := obj

# ------------- FONTES & OBJETOS (recursivo, só com wildcard) -----------
SRC := $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard $(SRCDIR)/*.cpp)

OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

# ---------------- REGRAS PRINCIPAIS ------------------------------------
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@ $(LDLIBS)  

# Compila .cpp → .o (cria subdir se preciso)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)        
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
    
# Comando para limpar os arquivos gerados
clean:
	rm -f $(TARGET)             
	rm -rf $(OBJDIR)            

# Inclui os arquivos de dependência gerados pelo -MMD
-include $(DEP)