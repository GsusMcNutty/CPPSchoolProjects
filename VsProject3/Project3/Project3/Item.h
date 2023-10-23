//
// Item.h
// Created by Kyle
// 10/14/2023.
//

#pragma once
#include <string>
class Item {
public:
    void SetName(std::string name);
    std::string GetName();
    void SetFrequency(int frequency);
    int GetFrequency();
private:
    std::string name = " ";
    int frequency = 1;
};


