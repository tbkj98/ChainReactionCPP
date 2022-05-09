#include "..\include\Color.h"

std::ostream& operator<<(std::ostream& out, Color& color)
{
	color.print(out);
	return out;
}

void Color::print(std::ostream& out)
{
	out << "\x1B[" << code << "m" << name<< "\033[0m\t\t";
}

Color::Color()
{
	name = "White";
	code = 37;
}

Color::Color(const Color& color)
{
	this->name = color.name;
	this->code = color.code;
}

Color::Color(std::string name, size_t code)
{
	this->name = name;
	this->code = code;
}

bool Color::operator==(Color const& color)
{
	return name == color.name && code == color.code;
}

size_t Color::getCode()
{
	return code;
}

std::string Color::getName()
{
	return name;
}
