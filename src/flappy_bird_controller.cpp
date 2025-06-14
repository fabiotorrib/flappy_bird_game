#include "flappy_bird_controller.hpp"

void FlappyBird::update() {
  bird.update();
  for (auto it = pipes.begin(); it != pipes.end();) {
    it->update();
    if (it->is_off_screen()) {
      it = pipes.erase(it);
    } else {
      ++it;
    }
  }
  update_score();
}

void FlappyBird::jump() {
  bird.set_vy(JUMP_FORCE);
}

void FlappyBird::reset() {
  bird.set_x(SCREEN_W / 3);
  bird.set_y(SCREEN_H / 2);
  bird.set_vy(0);
  pipes.clear();
  score = 0;
}

void FlappyBird::setPlayerName(const std::string& name) {
  currentPlayer = std::make_unique<Player>(name);
}

void FlappyBird::saveCurrentPlayerScore() {
  if (!currentPlayer) {
    return;
  }

  const std::string leaderboard_file = "leaderboard.txt";
  auto leaderboard = Player::ReadLeaderboard(leaderboard_file);
  bool player_found = false;

  // O acesso com 'currentPlayer->' também funciona da mesma forma.
  for (auto& p : leaderboard) {
    if (p.GetName() == currentPlayer->GetName()) {
      player_found = true;
      if (score > p.GetScore()) {
        p.SetScore(score);
      }
      break;
    }
  }

  if (!player_found) {
    // E o acesso com '*' para obter o objeto também.
    currentPlayer->SetScore(score);
    leaderboard.push_back(*currentPlayer);
  }

  Player::SortLeaderboard(leaderboard);
  Player::SaveLeaderboard(leaderboard_file, leaderboard);
}

bool FlappyBird::check_bird_collision(const GameObject& other) const {
  bool is_inside_other_horizontal =
      (bird.get_x() + bird.get_width() / 2.0f >= other.get_x()) &&
      (bird.get_x() + bird.get_width() / 2.0f <=
       other.get_x() + other.get_width());
  if (is_inside_other_horizontal &&
      ((bird.get_y() <= other.get_y()) ||
       (bird.get_y() + bird.get_height() >= other.get_y() + GAP_SIZE))) {
    return true;
  }
  return false;
}

bool FlappyBird::check_collision_with_boundaries() const {
  if (bird.get_y() <= 0) {
    return true;
  }
  if (bird.get_y() + bird.get_height() >= SCREEN_H) {
    return true;
  }
  return false;
}

void FlappyBird::spawn_pipe() {
  Pipe p(SCREEN_W, 100 + rand() % (SCREEN_H - MIN_PIPE_H));
  p.set_vx(PIPE_SPEED);
  pipes.push_back(p);
  std::cout << "INFO: Cano gerado na posicao x=" << p.get_x()
            << ", y=" << p.get_y() << std::endl;
}

void FlappyBird::update_score() {
  for (auto& pipe : pipes) {
    if (pipe.check_score(bird.get_x())) {
      score++;
    }
  }
}