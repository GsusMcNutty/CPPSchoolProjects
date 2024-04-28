//
// Item.cpp
// Created by Kyle
// 10/14/2023.
//

#include "Item.h"
void Item::SetName(std::string name) {
    this->name = name;
}

void Item::SetFrequency(int frequency) {
    this->frequency = frequency;
}

std::string Item::GetName() {
    return this->name;
}

int Item::GetFrequency() {
    return this->frequency;
}