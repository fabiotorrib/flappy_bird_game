/**
 * @file pipe.hpp
 * @brief Declaration of pipe-related classes (Pipe, PipePair, PipeList).
 * @details These classes implement the obstacle logic: horizontal/vertical
 *          movement, collision detection, score handling and difficulty
 *          management for the Flappy-style game.
 */
#pragma once

#include <allegro5/bitmap.h>
#include <random>
#include <vector>
#include "defines.hpp"
#include "game_object.hpp"
#include "init.hpp"

/* -------------------------------------------------------------------------- */
/*                               Class Pipe                                   */
/* -------------------------------------------------------------------------- */
/**
 * @class Pipe
 * @brief Obstáculo individual que se move horizontalmente e gera pontuação.
 */
class Pipe : public GameObject {
 private:
  float vx = 0;  //!< horizontal velocity (pixels per frame)
  bool scored;   //!< true after the bird has already scored on this pipe

 public:
  /**
   * @brief Construct a pipe object.
   * @param img   Pointer to loaded bitmap.
   * @param x     Initial x position.
   * @param y     Initial y position.
   * @details Initializes GameObject base, sets velocity and score flag.
   */
  Pipe(ALLEGRO_BITMAP* img, float x, float y)
      : GameObject(img, x, y, al_get_bitmap_width(img),
                   al_get_bitmap_height(img)),
        vx(PIPE_SPEED),
        scored(false) {
    set_finals();
  }

  /** @brief Move the pipe horizontally and update bounding box. */
  void update() override;

  /** @brief Draw the pipe sprite at its current position. */
  void draw() override;

  /** @brief Check whether the pipe has left the visible screen. */
  bool is_off_screen() const;

  /**
   * @brief Evaluate score condition for this pipe.
   * @param bird_x x position of the bird.
   * @return true if the bird just passed the pipe for the first time.
   */
  bool check_score(float bird_x);

  /** @brief Set horizontal velocity. */
  void set_vx(float vel);

  /** @brief Force a new y position (used for vertical movement). */
  void set_y(float new_y);

  /** @brief Get current y position. */
  float get_y();
};

/* -------------------------------------------------------------------------- */
/*                              Class PipePair                                */
/* -------------------------------------------------------------------------- */
/**
 * @class PipePair
 * @brief Agrupa dois canos (superior e inferior) podendo ter movimento
 * vertical.
 */
class PipePair {
 public:
  Pipe bottom;            //!< lower pipe
  Pipe top;               //!< upper pipe
  bool movement = false;  //!< true if pair moves vertically
  float signal = 1.0;     //!< direction multiplier for vertical motion

  /**
   * @brief Create a static pair of pipes.
   * @param img Bitmap shared by both pipes.
   * @param x   Initial x coordinate.
   * @param y   Bottom pipe y coordinate.
   */
  PipePair(ALLEGRO_BITMAP* img, float x, float y)
      : bottom(img, x, y),
        top(img, x, y - al_get_bitmap_height(img) - GAP_SIZE) {
  }

  /**
   * @brief Create a pair that can optionally move up/down.
   * @param img        Bitmap shared by both pipes.
   * @param x          Initial x coordinate.
   * @param y          Bottom pipe y coordinate.
   * @param type       Enable vertical movement.
   * @param direction  Initial movement direction (true = upward).
   */
  PipePair(ALLEGRO_BITMAP* img, float x, float y, bool type, bool direction)
      : bottom(img, x, y),
        top(img, x, y - al_get_bitmap_height(img) - GAP_SIZE),
        movement(type) {
    if (direction) {
      signal = -1.0f;
    }
  }
};

/* -------------------------------------------------------------------------- */
/*                              Class PipeList                                */
/* -------------------------------------------------------------------------- */
/**
 * @class PipeList
 * @brief Gerencia vetor de PipePair: spawn, atualização, colisão e score.
 */
class PipeList {
 private:
  ALLEGRO_BITMAP* pipe1 = nullptr;  //!< bitmap reference for new pipes
  std::vector<PipePair> Pipes;      //!< active pipe pairs
  bool start = false;               //!< true after first pipe is spawned
  int points = 0;                   //!< current score
  inline static std::mt19937 gen{std::random_device{}()};
  int difficulty_pipe = 1;  //!< 1 = static, 2 = with movers

 public:
  /**
   * @brief Construct a list manager.
   * @param img Bitmap to use when spawning new pipe pairs.
   */
  PipeList();
  PipeList(ALLEGRO_BITMAP* img);

  /** @brief Draw every pipe pair. */
  void draw();

  /** @brief Set uniform horizontal velocity for all pipes. */
  void set_vx(float vel);

  /** @brief Update positions of all pipes and handle vertical motion. */
  void update();

  /** @brief Spawn a new pair if gap condition is satisfied. */
  void add_pipe_pair();

  /** @brief Remove pipes that left the screen. */
  void delete_pipe_pair();

  /**
   * @brief Check bird collision against any pipe.
   * @param bird Player object (as GameObject).
   * @return true if a collision is detected.
   */
  bool check_collision(GameObject& bird);

  /**
   * @brief Check if any pipe pair increments the score.
   * @param bird_x Bird x coordinate.
   * @return true if score increases.
   */
  bool check_score(float bird_x);

  /**
   * @brief Begin spawning logic (first call after game starts).
   * @return true on first activation, false otherwise.
   */
  bool set_start();

  /** @brief Get current score. */
  int get_points();

  /** @brief Configure difficulty (1 = static, 2 = vertical movers). */
  void set_difficulty(int diff);

  /** @brief Expose internal pipe vector (read-only). */
  const std::vector<PipePair>& get_pipe_pairs() const {
    return Pipes;
  }

  /** @brief Clear list and reset all counters. */
  void reset();
};
