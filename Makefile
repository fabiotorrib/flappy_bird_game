# ---------------- CONFIGURAÇÃO -----------------------------------------
CXX		  := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Iinclude -MMD -MP

LDLIBS	  := -lallegro_main -lallegro                     \
			 -lallegro_image -lallegro_font -lallegro_ttf \
			 -lallegro_primitives -lallegro_audio -lallegro_acodec

# --- CONFIGURAÇÃO DO JOGO PRINCIPAL ---
TARGET    := flappy.exe
SRCDIR    := src
OBJDIR    := obj
SRC       := $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard $(SRCDIR)/*.cpp)
OBJ       := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEP       := $(OBJ:.o=.d)


# --- CONFIGURAÇÃO DOS TESTES ---
TEST_TARGET   := test_runner.exe
TEST_SRCDIR   := tests
TEST_OBJDIR   := obj_test

# Fontes dos testes: todos os .cpp da pasta de testes
TEST_SRC := $(wildcard $(TEST_SRCDIR)/*.cpp)

# Fontes do jogo para os testes: todos os .cpp do jogo, EXCETO o main.cpp
GAME_SRC_FOR_TESTS := $(filter-out $(SRCDIR)/main.cpp, $(SRC))

# Mapeia os fontes para arquivos de objeto na pasta de build dos testes (obj_test)
TEST_GAME_OBJ := $(patsubst $(SRCDIR)/%.cpp,$(TEST_OBJDIR)/%.o,$(GAME_SRC_FOR_TESTS))
TEST_TEST_OBJ := $(patsubst $(TEST_SRCDIR)/%.cpp,$(TEST_OBJDIR)/%.o,$(TEST_SRC))
ALL_TEST_OBJ  := $(TEST_GAME_OBJ) $(TEST_TEST_OBJ)


# ---------------- REGRAS PRINCIPAIS ------------------------------------
# O .PHONY diz ao make que 'all', 'clean' e 'test' não são nomes de arquivos.
.PHONY: all clean test

# 'make' ou 'make all' irá compilar o jogo principal.
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@ $(LDLIBS)

# O novo alvo 'test' compila e EXECUTA os testes.
test: $(TEST_TARGET)
	@echo "--- Rodando os testes ---"
	./$(TEST_TARGET)
	@echo "-------------------------"


# ---------------- REGRAS DE COMPILAÇÃO ---------------------------------

# Regra para compilar o jogo principal (.cpp de 'src' para 'obj')
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para linkar o executável de testes
$(TEST_TARGET): $(ALL_TEST_OBJ)
	$(CXX) $^ -o $@ $(LDLIBS)

# Regras para compilar os fontes para os testes (.cpp de 'src' e 'tests' para 'obj_test')
$(TEST_OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_OBJDIR)/%.o: $(TEST_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# ---------------- LIMPEZA ----------------------------------------------
# O alvo 'clean' agora também remove os arquivos gerados pelos testes.
clean:
	rm -f $(TARGET) $(TEST_TARGET)
	rm -rf $(OBJDIR) $(TEST_OBJDIR)

# Inclui os arquivos de dependência gerados pelo -MMD
-include $(DEP)