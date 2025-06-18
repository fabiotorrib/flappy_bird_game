#pragma once
#include "../flappy_bird_controller.hpp"
#include "../state.hpp"

class Play : public State {
 private:
  std::unique_ptr<FlappyBird> flappy;
  ScreenState status;

 public:
  // Declaração do método enter
  void enter() override;

  // Supondo a nova arquitetura
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
};