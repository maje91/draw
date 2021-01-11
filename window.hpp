#pragma once

#include <string>

namespace draw::window {

struct Spec {
  int width;
  int height;
  std::string name;
};

void init(const Spec &spec);
void destroy();

bool advance();

unsigned int height();
unsigned int width();

}