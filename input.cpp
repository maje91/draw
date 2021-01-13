#include "input.hpp"

namespace draw::input {

Button::Button() : m_state(ButtonState::Released) {}
Button::Button(ButtonState state) : m_state(state) {}

bool Button::is_pressed() const { return m_state == ButtonState::Pressed; }
}
