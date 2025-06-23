# ---------------- CONFIGURAÇÃO -----------------------------------------
CXX_LINUX         := g++
CXX_WINDOWS       := x86_64-w64-mingw32-g++

# Flags padrão
CXXFLAGS_COMMON   := -std=c++17 -Wall -Wextra -Iinclude -MMD -MP

# --- Configuração específica da plataforma ---
ifeq ($(OS),Windows_NT)
    # Build nativo no Windows (se necessário)
    TARGET          := flappy.exe
    CXX             := $(CXX_WINDOWS)
    CXXFLAGS        := $(CXXFLAGS_COMMON)
    LDLIBS          := -L/path/to/allegro/lib -lallegro_monolith-static -lopengl32 -lgdi32 -luser32 -lkernel32 -lpsapi -lwinmm -lstdc++fs -luuid -lshlwapi -lopenal -lfreeglut -ldumb -lvorbis -lvorbisfile -ltheora -lflac -logg
    RM              := del /Q
    RMDIR           := rd /S /Q
else
    # Lógica para build no Linux ou Cross-compilation a partir do Linux
    ifeq ($(MAKECMDGOALS),windows)
        # Cross-compilation para Windows a partir do Linux
        TARGET      := flappy.exe
        CXX         := $(CXX_WINDOWS)
        CXXFLAGS    := $(CXXFLAGS_COMMON) -I./allegro-build/include
        # Link estático para que o .exe seja portátil
        LDLIBS      := -L./allegro-build/lib -static -lallegro_monolith-static -lopengl32 -lgdi32 -luser32 -lkernel32 -lpsapi -lwinmm -lstdc++fs -luuid -lshlwapi
        MAKECMDGOALS := all # Força o alvo 'all'
    else
        # Build padrão para Linux
        TARGET      := flappy.bin # Renomeado para não conflitar
        CXX         := $(CXX_LINUX)
        CXXFLAGS    := $(CXXFLAGS_COMMON)
        LDLIBS      := -lallegro_main -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_audio -lallegro_acodec
    endif
    RM              := rm -f
    RMDIR           := rm -rf
endif


# --- CONFIGURAÇÃO DO JOGO PRINCIPAL ---
SRCDIR    := src
OBJDIR    := obj
SRC       := $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard $(SRCDIR)/*.cpp)
OBJ       := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEP       := $(OBJ:.o=.d)

# --- CONFIGURAÇÃO DOS TESTES (Apenas para Linux) ---
TEST_TARGET   := test_runner.exe
TEST_SRCDIR   := tests
TEST_OBJDIR   := obj_test
TEST_SRC := $(wildcard $(TEST_SRCDIR)/*.cpp)
GAME_SRC_FOR_TESTS := $(filter-out $(SRCDIR)/main.cpp, $(SRC))
TEST_GAME_OBJ := $(patsubst $(SRCDIR)/%.cpp,$(TEST_OBJDIR)/%.o,$(GAME_SRC_FOR_TESTS))
TEST_TEST_OBJ := $(patsubst $(TEST_SRCDIR)/%.cpp,$(TEST_OBJDIR)/%.o,$(TEST_SRC))
ALL_TEST_OBJ  := $(TEST_GAME_OBJ) $(TEST_TEST_OBJ)


# ---------------- REGRAS PRINCIPAIS ------------------------------------
.PHONY: all clean test doc clean-doc linux windows

# 'make' ou 'make all' ou 'make linux' irá compilar para Linux
all: linux
linux: $(TARGET)
windows: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@ $(LDLIBS)

test: $(TEST_TARGET)
	@echo "--- Rodando os testes ---"
	./$(TEST_TARGET)
	@echo "-------------------------"

# ---------------- REGRAS DE COMPILAÇÃO ---------------------------------
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regras de teste (apenas Linux)
$(TEST_TARGET): $(ALL_TEST_OBJ)
	$(CXX_LINUX) $^ -o $@ $(LDLIBS)

$(TEST_OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXXFLAGS_COMMON) -c $< -o $@

$(TEST_OBJDIR)/%.o: $(TEST_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXXFLAGS_COMMON) -c $< -o $@

# ---------------- LIMPEZA ----------------------------------------------
clean:
	$(RM) flappy.bin flappy.exe test_runner.exe
	$(RMDIR) $(OBJDIR) $(TEST_OBJDIR)

-include $(DEP)

# ---------------- DOCUMENTAÇÃO (Doxygen) ----------------
doc: clean-doc
	doxygen Doxyfile
	$(MAKE) -C docs/latex

clean-doc:
	$(RMDIR) docs/html docs/latex