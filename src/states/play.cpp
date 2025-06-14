#include "play.hpp"
#include "flappy_bird_controller.hpp"
#include "init.hpp"
#include "main_menu.hpp"
#include "state.hpp"
#include "states/states.hpp"  // Adicionado para ter acesso ao 'motion' global

State* Play::loop(FlappyBird* game) {
  static float framerate = 0;
  static bool game_over = false;

  // Processa eventos
  while (al_get_next_event(queue, &ev)) {
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        return new MainMenu();
      }
      if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE && !game_over) {
        game->jump();
      }
      if (ev.keyboard.keycode == ALLEGRO_KEY_R && game_over) {
        // Reinicia o jogo
        game->reset();
        game_over = false;
        framerate = 0;
      }
    }

    if (ev.type == ALLEGRO_EVENT_TIMER) {
      if (!game_over) {
        game->update();
        framerate++;

        // Spawna pipe a cada 90 frames (~1.5 segundos a 60 FPS)
        if (framerate >= 90) {
          game->spawn_pipe();
          framerate = 0;
        }

        // Verifica colisões
        if (game->check_collision_with_boundaries()) {
          game_over = true;
        }

        auto pipes = game->get_pipes();
        for (const auto& p : pipes) {
          if (game->check_bird_collision(p)) {
            game_over = true;
            break;
          }
        }
      }
    }
  }

  // Renderização

  // Chama motion.loop() para desenhar todo o fundo animado e sincronizado.
  motion.loop();

  // Desenha pipes
  auto pipes = game->get_pipes();
  if (pipe_green) {
    float pipe_w = al_get_bitmap_width(pipe_green);  // Largura do cano
    float pipe_h =
        al_get_bitmap_height(pipe_green);  // Altura original da imagem

    for (const auto& p : pipes) {
      // === Cano Superior ===
      float top_pipe_h = p.get_y();
      al_draw_scaled_bitmap(pipe_green, 0, 0, pipe_w,
                            pipe_h,        // Origem (imagem inteira)
                            p.get_x(), 0,  // Destino (canto superior esquerdo)
                            pipe_w, top_pipe_h,  // Tamanho final (esticado)
                            ALLEGRO_FLIP_VERTICAL);

      // === Cano Inferior ===
      float bottom_pipe_y = p.get_y() + GAP_SIZE;
      float bottom_pipe_h = SCREEN_H - bottom_pipe_y;
      al_draw_scaled_bitmap(
          pipe_green, 0, 0, pipe_w, pipe_h,  // Origem (imagem inteira)
          p.get_x(), bottom_pipe_y,  // Destino (canto superior esquerdo)
          pipe_w, bottom_pipe_h,     // Tamanho final (esticado)
          0);
    }
  }

  // Desenha o bird
  if (bird1) {
    // Calcula o centro do pássaro na tela
    float bird_center_x =
        game->get_bird().get_x() + game->get_bird().get_width() / 2;
    float bird_center_y =
        game->get_bird().get_y() + game->get_bird().get_height() / 2;

    // Desenha o bitmap rotacionado em seu ponto central
    al_draw_rotated_bitmap(
        bird1,
        al_get_bitmap_width(bird1) / 2,   // Centro x da imagem original
        al_get_bitmap_height(bird1) / 2,  // Centro y da imagem original
        bird_center_x,                    // Posição x de destino (centro)
        bird_center_y,                    // Posição y de destino (centro)
        game->get_bird().get_rotation(),  // Rotação
        0);
  }

  // Desenha UI de game over
  if (game_over && font) {
    al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_W / 2, SCREEN_H / 2 - 50,
                 ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2,
                 SCREEN_H / 2 + 20, ALLEGRO_ALIGN_CENTER,
                 "Press R to restart or ESC to menu");
  }

  al_flip_display();
  return this;
}

void Play::reset() {
  // Reset do estado se necessário
}