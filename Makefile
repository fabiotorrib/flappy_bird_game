# ---------------- CONFIGURAÇÃO -----------------------------------------
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Iinclude -MMD -MP

LDLIBS    := -lallegro_main -lallegro                \
             -lallegro_image -lallegro_font -lallegro_ttf \
             -lallegro_primitives -lallegro_audio -lallegro_acodec

TARGET := flappy.exe
SRCDIR := src
OBJDIR := obj

# ------------- FONTES & OBJETOS (recursivo, só com wildcard) -----------
# GNU make ≥4.3 entende ** para recursão; caso use 4.2 veja nota ao fim
SRC := $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard $(SRCDIR)/*.cpp)

# Converte  src/foo/bar.cpp → obj/foo/bar.o
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

# ---------------- REGRAS PRINCIPAIS ------------------------------------
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@ $(LDLIBS)

# Compila .cpp → .o (cria subdir se preciso)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@