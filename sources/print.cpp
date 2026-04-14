#include <print.hpp>

void print(const std::string& text, std::ostream& out)
{
  out << text << std::endl; // Добавлен endl
}

void print(const std::string& text, std::ofstream& out)
{
  out << text << std::endl; // Добавлен endl для консистентности
}
