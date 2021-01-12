#pragma once

#include <variant>

namespace draw::input {

enum class ButtonAction {
  Press,
  Release
};

namespace mouse {

struct Left { ButtonAction action; };
struct Right { ButtonAction action; };
struct Scroll { double offset; };
struct Move { double x; double y; };

using Event = std::variant<Left, Right, Scroll, Move>;

}
}