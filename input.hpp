#pragma once

#include <variant>

namespace draw::input {

enum class ButtonAction {
  Press,
  Release
};

enum class ButtonState {
  Pressed,
  Released
};

class Button {
 public:
  Button() : m_state(ButtonState::Released) {}
  explicit Button(ButtonState state) : m_state(state) {}

  bool is_pressed() const {
    return m_state == ButtonState::Pressed;
  }

 private:
  ButtonState m_state;
};

struct Mouse {
  Button left;
  Button right;
  double x;
  double y;
};

namespace mouse {

struct Left { ButtonAction action; };
struct Right { ButtonAction action; };
struct Scroll { double offset; };
struct Move { double x; double y; };

using Event = std::variant<Left, Right, Scroll, Move>;

}
}