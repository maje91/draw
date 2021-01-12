#pragma once

#include "input.hpp"

#include <string>
#include <functional>

namespace draw::window {

struct Spec {
  int width;
  int height;
  std::string name;
};

void init(const Spec &spec);
void destroy();
void set_event_handler(const std::function<void(input::mouse::Event)> &on_mouse_event);

bool advance();

unsigned int height();
unsigned int width();

}  // namespace draw::window