# FlyUFMG
## Remake do Flappy Bird original

- Todas funcionalidades do Flappy Bird inclusas
- Contém cenários dinâmicos com diferentes climas
- Níveis de dificuldade implantados
- Salva e gerencia seu ranking de pontuações
- Possui um design refeito, mas preservando parte do jogo original

## Visão Geral da Solução

O jogo foi construído utilizando a linguagem C++ (padrão C++17) e a biblioteca gráfica Allegro 5 para manipulação de janelas, renderização, entrada de usuário (teclado e mouse) e áudio.

### Estrutura do Programa

O fluxo do programa é controlado por uma classe principal (`AllegroController`) que gerencia o loop de jogo e a transição entre os diferentes estados. Cada estado representa uma tela ou um modo de jogo específico, como:

*   **Menu Principal:** A tela inicial, onde o jogador pode escolher iniciar um novo jogo, carregar um jogo salvo, ver o placar de líderes, acessar as configurações ou sair.
*   **Estado de Jogo (Play):** Onde a jogabilidade principal acontece. Controla o movimento do pássaro, a geração de canos, a detecção de colisões e a pontuação.
*   **Menu de Dificuldade:** Permite ao jogador escolher entre diferentes níveis de dificuldade (fácil, normal, difícil).
*   **Menu de Configurações:** Oferece opções para ajustar as configurações do jogo, como a música de fundo.
*   **Carregar Jogo / Salvar Jogo:** Permite que o progresso do jogador seja salvo e posteriormente carregado.
*   **Placar de Líderes (Leaderboard):** Exibe as melhores pontuações alcançadas.

## Principais Dificuldades Encontradas

O desenvolvimento do projeto apresentou desafios interessantes como:

- **Produção de Sprites:** Produzir sprites que se encaixassem esteticamente nas animações e nos 3 climas criados.
- **Sincronização de Animações:** Preserva a fluidez e em sincronizar as animações do clima de neve e chuva na tela de forma que os sprites sempre estejam na tela.
- **Sincronização dos Frames** Garantir que todas as máquinas estejam atualizando a tela na mesma taxa de atualização, para evitar diferentes velocidades nos jogos para clocks de máquinas diferentes.
- **Primeiros Passos** Implementar e modelar a máquina de estados que armazena a lógica de diferentes telas do jogo.
- **Jogo** Modelar a dinâmica de jogo, com diferentes movimentações, objetos, colisões, etc.

## Implementações Extras

Além da mecânica básica do Flappy Bird, várias funcionalidades extras foram adicionadas para enriquecer a experiência do jogador:

*   **Múltiplos Níveis de Dificuldade:** O jogador pode escolher entre os modos Fácil, Normal e Difícil, alterando a velocidade do jogo e a complexidade dos obstáculos.
*   **Trilha Sonora e Efeitos Sonoros:** Foram adicionadas músicas de fundo e efeitos sonoros para colisões e pontuação, com opções para silenciá-los no menu de configurações.
*   **Temas Visuais:** O jogo conta com diferentes temas visuais (dia, neve, chuva) que alteram o plano de fundo e adicionam efeitos visuais, como partículas de neve ou gotas de chuva.
- **Gerenciamento de Recursos:** Classes utilitárias (`Image`, `Music`, `Sound`, `TextFont`) que encapsulam o carregamento, uso e liberação de assets, garantindo eficiência e otimização.

## Classes Notáveis

Nosso projeto é estruturado em torno de diversas classes que gerenciam diferentes aspectos do jogo:

| Classe | Descrição |
| ------ | ----------- |
| `AllegroController` | Orquestrador principal; gerencia display, eventos e transições entre estados de jogo. |
| `State` | Interface base para todos os estados (telas) do jogo. |
| `FlappyBird` | Controlador principal da lógica do jogo ativo (pontuação, eventos, interação pássaro/canos). |
| `Bird` | O personagem jogável; cuida de sua física, animação e colisões. |
| `Pipe`, `PipePair`, `PipeList` | Implementam o sistema de obstáculos: canos individuais, pares de canos e o gerenciamento da lista de canos. |
| `GameObject` | Classe base abstrata para objetos do jogo com posição, sprite e hitbox. |
| `Player` | Modela um jogador, com nome e pontuação, e funcionalidades para o ranking. |
| `Motion` | Gerencia os efeitos de parallax e as animações do cenário, incluindo os diferentes climas. |
| `Image`, `Music`, `Sound`, `TextFont` | Classes utilitárias para carregar e manipular recursos gráficos e de áudio. |
| `DifficultyMenu` | Estado do jogo para seleção e gerenciamento da dificuldade. |
| `LeaderboardMenu` | Estado do jogo para exibição do ranking de pontuações. |
| `LoadName` | Estado do jogo para inserção ou carregamento do nome do jogador. |
| `MainMenu` | O estado inicial e principal do jogo, com opções de navegação. |
| `Play` | O estado de jogo ativo, onde a jogabilidade principal acontece. |
| `SettingsMenu` | Estado do jogo para ajustar configurações como música e clima. |

## Estrutura do Projeto

- `src/`: Código-fonte principal (`.cpp`).
- `include/`: Arquivos de cabeçalho (`.hpp`).
- `assets/`: Armazena todas as mídias (sprites, fontes, sons).
- `tests/`: Casos de teste unitários (com Doctest).
- `docs/`: Documentação automática (via Doxygen).

## Instalação

FlyUFMG requer a biblioteca Allegro 5 para rodar.

Para compilar e executar o projeto, certifique-se de ter o `g++`(com suporte a C++17), `make` e a biblioteca `Allegro 5` devidamente instalados.

**Comando para compilar:**
```bash
make
```

**Comando para executar:**
```bash
./flappy.exe
```

**Executando os testes:**
O projeto utiliza a biblioteca `doctest` para os testes unitários. Para compilá-los e executá-los:
```bash
make test
```

**Gerando a documentação:**
A documentação é gerada com Doxygen.
```bash
make doc
```
Após a execução, a documentação estará disponível em dois formatos:
-   **HTML:** Abra o arquivo `docs/html/index.html` no seu navegador para uma versão interativa. Para a sua melhor experiência, você pode usar um servidor http local. Se tiver o Node.js instalado, pode executar o comando abaixo.

```bash
npx http-server docs/html -p 8000
```
-   **PDF:** O documento `refman.pdf` será gerado no diretório `docs/latex/`.
