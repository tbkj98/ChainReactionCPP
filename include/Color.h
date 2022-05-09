#pragma once

#include <iostream>
#include <vector>

class Color
{
private:
    std::string name;
    size_t code;

    // Overloading the operator to directly print the object over console
    void print(std::ostream& out);
    friend std::ostream& operator<<(std::ostream& out, Color& color);
public:
    Color();
    Color(const Color& color);
    Color(std::string name, size_t code);

    bool operator == (Color const& color);

    size_t getCode();
    std::string getName();
};

const std::vector<Color> colors = {
    Color("Red", 31),
    Color("Green", 32),
    Color("Yellow", 33),
    Color("Blue", 34),
    Color("Magenta", 35),
    Color("Cyan", 36),
    Color("White", 37)
};
