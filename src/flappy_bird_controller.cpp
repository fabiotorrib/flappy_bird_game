#include "../include/flappy_bird_controller.hpp"
#include <allegro5/bitmap_draw.h>
#include <iostream>

// funcao de desenhar as coisas
void FlappyBird::draw() {
  al_draw_bitmap(background, 0, 0, 0);
  al_draw_bitmap(clouds, cloud_pos_x, 0, 0);
  al_draw_bitmap(clouds2, cloud_pos2_x, 0, 0);
  if (state == 0) {
    al_draw_bitmap(ground, 0, 0, 0);
    draw_intial_text();
  } else if (state == 1) {
    flappy_obj.draw();
    if (flappy_obj.get_x() >= X_INIT) {
      pipelist.draw();
    }
    draw_animated_ground(velocity);
    draw_HUD();
  }
}

void FlappyBird::update() {
  if (state == 1) {
    flappy_obj.update();
    if (flappy_obj.get_x() >= X_INIT) {
      pipelist.set_start();
      pipelist.set_vx(velocity);
      pipelist.update();
    }
    cloud_pos_x -= cloud_speed;
    cloud_pos2_x -= cloud_speed;

    if (cloud_pos_x <= -SCREEN_W) {
      cloud_pos_x = SCREEN_W;
    }
    if (cloud_pos2_x <= -SCREEN_W) {
      cloud_pos2_x = SCREEN_W;
    }
  }
}

void FlappyBird::reset() {
  state = 0;
  time = 0;
  velocity = PIPE_SPEED;
  velocity_backup = 0;
  score = 0;
  positionF_x = 0;
  positionF2_x = SCREEN_W;
  change_vel = 5;
  cloud_pos_x = 0;
  cloud_pos2_x = SCREEN_W;
  flappy_obj.reset_xy();
  flappy_obj.set_break(false);
  pipelist.reset();
  currentPlayer = nullptr;
}

// PLAYER
void FlappyBird::set_current_player(Player& player) {
  currentPlayer = &player;
}
void FlappyBird::set_playerscore() {
  currentPlayer->SetScore(score);
}

void FlappyBird::saveCurrentPlayerScore() {
  currentPlayer->SaveLeaderboard("Leaderboard.txt", ranking, *currentPlayer);
}

// funcao checa colisoes
bool FlappyBird::check_collisions() {
  if ((flappy_obj.check_collision_with_boundaries() && velocity != 0) ||
      (pipelist.check_collision(flappy_obj))) {
    // colocar audio de morte aqui e alguma pisca na tela
    velocity = 0;
    flappy_obj.set_break(true);
    return true;
  }
  return false;
}

// ACTIONS

void FlappyBird::jump() {
  if (velocity != 0) {
    flappy_obj.jump();
  }
}

void FlappyBird::starter() {
  state = 1;
}

void FlappyBird::control_pipes() {
  pipelist.add_pipe_pair();
  pipelist.delete_pipe_pair();
}

void FlappyBird::draw_intial_text() {
  time += 1.0 / FPS;
  float alpha = 0.5f + 0.5f * sinf(OSCILATION * time);
  ALLEGRO_COLOR cor = al_map_rgba_f(1, 1, 1, alpha);
  al_draw_text(font, cor, SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTRE,
               "PRESS SPACE TO PLAY");
}

void FlappyBird::update_score() {
  pipelist.check_score(flappy_obj.get_x());
  score = pipelist.get_points();
}

void FlappyBird::change_velocity() {
  if (score % change_vel == 0 && score != 0) {
    velocity += 0.25;
    change_vel += 2;
  }
}

void FlappyBird::draw_HUD() {
  al_draw_textf(font, al_map_rgb(255, 255, 255), 60, 30, ALLEGRO_ALIGN_CENTRE,
                "%d", score);
}

void FlappyBird::draw_animated_ground(float velocity) {
  positionF_x -= velocity;
  positionF2_x -= velocity;

  if (positionF_x <= -1280) {
    positionF_x = 0;
  }

  if (positionF2_x <= 0) {
    positionF2_x = 1280;
  }

  al_draw_bitmap(ground, positionF_x, 0, 0);
  al_draw_bitmap(ground2, positionF2_x, 0, 0);
}
void FlappyBird::breaker() {
  velocity_backup = velocity;
  velocity = 0;
  flappy_obj.set_break(true);
}
void FlappyBird::unbreaker() {
  velocity = velocity_backup;
  flappy_obj.set_break(false);
}

// AUXILIARES

int FlappyBird::get_state() {
  return state;
}
