/**
 * @file flappy_bird_controller.hpp
 * @brief Declaracao da classe FlappyBird (controlador principal).
 * @details Coordena objetos, pontuacao, sons, HUD e logica de estados
 *          do jogo. Comentarios seguem padrao Doxygen sem acentos.
 */
#pragma once

#include <memory>
#include "assets.hpp"
#include "bird.hpp"
#include "defines.hpp"
#include "game_object.hpp"
#include "init.hpp"
#include "pipe.hpp"
#include "player.hpp"

/**
 * @class FlappyBird
 * @brief Controlador principal do jogo: orquestra objetos, HUD, pontuação e fluxo de estados.
 */
class FlappyBird {
 private:
  std::unique_ptr<Image> bird1;          //!< sprite 1 do passaro
  std::unique_ptr<Image> bird2;          //!< sprite 2 do passaro
  std::unique_ptr<Image> bird3;          //!< sprite 3 do passaro
  std::unique_ptr<Image> pipe;           //!< sprite do cano
  std::unique_ptr<Image> ground;         //!< sprite do solo
  std::unique_ptr<Image> ground2;        //!< sprite do solo (loop)
  std::unique_ptr<Sound> pointSound;     //!< som de pontuacao
  std::unique_ptr<Sound> gameOverSound;  //!< som de game over

  Bird flappy_obj;       //!< instancia controlavel do passaro
  PipeList pipelist;     //!< lista de canos ativos

  /* variaveis de estado e pontuacao */
  int state   = 0;       //!< 0 = intro, 1 = aguardando, 2 = jogando
  float time  = 0;
  float velocity = PIPE_SPEED;
  float velocity_backup = 0;
  int score   = 0;

  /* animacao de solo */
  float positionF_x  = 0;
  float positionF2_x = SCREEN_W;

  int change_vel      = 2;      //!< frequencia de aumento de velocidade
  int difficulty_game = difficulty;

  Player* currentPlayer = nullptr; //!< ponteiro para jogador atual

 public:
  /**
   * @brief Construtor padrao.
   * @details Carrega assets, inicializa objetos e listas.
   */
  FlappyBird();

  /* ---------------------------- metodos principais ----------------------- */
  /** @brief Desenha cena completa conforme estado. */
  void draw();

  /** @brief Atualiza logica principal (estado, objetos, pipes). */
  void update();

  /** @brief Reseta jogo para configuracao inicial. */
  void reset();

  /**
   * @brief Define jogador atual (para leaderboard).
   * @param player referencia ao objeto Player.
   */
  void set_current_player(Player& player);

  /** @brief Salva pontuacao no leaderboard externo. */
  void saveCurrentPlayerScore();

  /**
   * @brief Verifica colisao entre passaro, limites ou canos.
   * @return true se colisao final detectada.
   */
  bool check_collisions();

  /* ------------------------------- acoes ---------------------------------- */
  /** @brief Comanda pulo do passaro (estado 2). */
  void jump();

  /** @brief Transita do estado 1 para 2 e aplica primeiro pulo. */
  void starter();

  /** @brief Adiciona / remove canos conforme necessidade. */
  void control_pipes();

  /** @brief Desenha texto inicial "PRESS SPACE TO PLAY". */
  void draw_intial_text();

  /** @brief Atualiza pontuacao quando passaro passa canos. */
  void update_score();

  /** @brief Aumenta velocidade conforme pontuacao. */
  void change_velocity();

  /** @brief Desenha HUD de pontuacao. */
  void draw_HUD();

  /**
   * @brief Desenha solo em loop para criar efeito de movimento.
   * @param velocity velocidade horizontal a aplicar.
   */
  void draw_animated_ground(float velocity);

  /** @brief Pausa fisica e anima passaro colidido. */
  void breaker();

  /** @brief Retoma jogo apos pausa. */
  void unbreaker();

  /* ------------------------------ auxiliares ----------------------------- */
  /** @brief Retorna estado atual (0,1,2). */
  int get_state();

  /** @brief Atualiza score no objeto Player. */
  void set_playerscore();

  /* getters */
  const Bird& get_bird()  const { return flappy_obj; }
  const PipeList& get_pipes() const { return pipelist; }
};
