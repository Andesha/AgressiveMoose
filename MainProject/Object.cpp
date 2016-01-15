#include "stdafx.h"

Object::Object(){
    this->objectName = new char[25];

}

Object::~Object() {
	delete objectName;
}


void Object::init(){
    for (int i = 0; i < this->components.size(); i++){
        components[i]->initialize();
    }
}


void Object::draw(){
    for (int i = 0; i < this->components.size(); i++){
        components[i]->draw();
    }
}