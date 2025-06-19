#include "defines.hpp"  // Para X_INIT, SCREEN_H
#include "doctest/doctest.h"
#include "game_object.hpp"

// Para testar a classe GameObject, vamos criar uma classe filha concreta
class TestObject : public GameObject {
 public:
  TestObject(float x, float y, float w, float h)
      : GameObject(nullptr, x, y, w, h) {
    update_coords();  // Inicializa as coordenadas no construtor
  }

  // Método auxiliar para atualizar todas as coordenadas derivadas de uma só vez
  void update_coords() {
    this->x_final = this->x + this->width;
    this->y_final = this->y + this->height;
    // Para um objeto de teste genérico, 'by' (boundary y) é o mesmo que 'y'
    this->by = this->y;
  }

  // Sobrescreve set_y para já chamar a atualização
  void set_y(float new_y) {
    GameObject::set_y(new_y);
    update_coords();
  }

  // Métodos virtuais puros que precisam ser implementados
  void update() override {
  }
  void draw() override {
  }
};

TEST_CASE("Testando a Classe GameObject") {
  SUBCASE("Verificação de Colisão (check_bird_collision)") {
    TestObject main_obj(100, 100, 50,
                        50);  // Objeto principal em (100,100) com 50x50

    // Objeto colidindo
    TestObject colliding_obj(110, 110, 50, 50);
    CHECK(main_obj.check_bird_collision(colliding_obj) == true);

    // Objeto não colidindo (à direita)
    TestObject non_colliding_right(200, 100, 50, 50);
    CHECK(main_obj.check_bird_collision(non_colliding_right) == false);

    // Objeto não colidindo (abaixo)
    TestObject non_colliding_down(100, 200, 50, 50);
    CHECK(main_obj.check_bird_collision(non_colliding_down) == false);

    // Objeto apenas tocando na borda
    TestObject touching_obj(150, 100, 50, 50);
    CHECK(main_obj.check_bird_collision(touching_obj) == true);
  }

  SUBCASE(
      "Verificação de Colisão com Limites (check_collision_with_boundaries)") {
    // Para este teste, o objeto precisa passar de X_INIT
    TestObject obj(X_INIT + 1, 50, 20, 20);

    // Testando colisão com o teto (by <= 0)
    obj.set_y(-5);  // set_y agora chama update_coords() automaticamente
    CHECK(obj.check_collision_with_boundaries() == true);

    // Testando colisão com o chão (y_final >= SCREEN_H - 101)
    obj.set_y(SCREEN_H - 110);
    CHECK(obj.check_collision_with_boundaries() == true);

    // Testando objeto em posição segura
    obj.set_y(SCREEN_H / 2);
    CHECK(obj.check_collision_with_boundaries() == false);
  }
}