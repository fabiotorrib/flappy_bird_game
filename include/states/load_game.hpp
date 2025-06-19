#pragma once
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"
#include "../../include/assets.hpp"
#include <memory>

enum insertNameSituations
{
    noName,
    existName,
    noexistName,
    noError,
    successInsert
};

class LoadName : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  LoadName();
  std::string playerNameString = "";
  int buttonPositionSelected = 2;
  int errorSituation = noError;
  std::vector<Button> menuButtons = {
      {"Back", 0}, {"Insert", 0}, {"NameCamp", 1}};
  
 private:
    std::unique_ptr<Image> buttonBackSelect;
    std::unique_ptr<Image> buttonBackDeselect;
    std::unique_ptr<Image> buttonInsertSelect;
    std::unique_ptr<Image> buttonInsertDeselect;
    std::unique_ptr<Image> nameCampSelect;
    std::unique_ptr<Image> nameCampDeselect;
    std::unique_ptr<TextFont> nameFont;
    std::unique_ptr<TextFont> errorFont;   

};