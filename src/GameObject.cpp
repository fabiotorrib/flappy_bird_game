#include "../include/GameObject.hpp"


bool GameObject::checkcollision(const GameObject& other){
    bool dentro_do_cano = (x + width/2>= other.x) && (x + width/2<= other.x + other.width);
    if(dentro_do_cano && ((y-height/2<=other.y) || (y+height/2>= other.y+GAP_SIZE))){
        return true;
    };
    return false;
}

void GameObject::set_x(float new_x){
    x=new_x;
}

void GameObject::set_y(float new_y){
    y=new_y;
}

float GameObject::get_x(){
    return x;
}

float GameObject::get_y(){
    return y;
}
