# ---------------- CONFIGURAÇÃO -----------------------------------------
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Iinclude -MMD -MP

LDLIBS    := -lallegro_main -lallegro              \
             -lallegro_image -lallegro_font -lallegro_ttf \
             -lallegro_primitives -lallegro_audio -lallegro_acodec

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