#pragma once

#include <variant>

namespace draw::input {

/**
 * Events that may happen to a button
 */
enum class ButtonEvent {
  /**
   * The button is pressed
   */
  Press,

  /**
   * The button is released
   */
  Release
};

/**
 * States a button can be in
 */
enum class ButtonState {
  /**
   * The button is pressed
   */
  Pressed,

  /**
   * The button is released
   */
  Released
};

/**
 * Represents the state of a button
 */
class Button {
 public:
  /**
   * Constructs a released button
   */
  Button();

  /**
   * Constructs a button in a given `state`
   */
  explicit Button(ButtonState state);

  /**
   * Returns whether the button is pressed or not
   */
  [[nodiscard]] bool is_pressed() const;

 private:
  ButtonState m_state;
};

/**
 * Represents a computer mouse
 */
struct Mouse {
  /**
   * State of the left mouse button
   */
  Button left;

  /**
   * State of the right mouse button
   */
  Button right;

  /**
   * x-posistion of the cursor in the window
   */
  double x;

  /**
   * y-position of the cursor in the window
   */
  double y;
};

namespace mouse {

/**
 * Left mouse button event variant
 */
struct Left {
  ButtonEvent event;
};

/**
 * Right mouse button event variant
 */
struct Right {
  ButtonEvent event;
};

/**
 * Mouse scrollwheel event variant
 */
struct Scroll {
  /**
   * How much was scrolled. Scrolling up is positive
   */
  double offset;
};

/**
 * Mouse move event variant
 */
struct Move {
  /**
   * The new x-position of the cursor
   */
  double x;

  /**
   * The new y-position of the cursor
   */
  double y;
};

/**
 * Represents any mouse-related event
 */
using Event = std::variant<Left, Right, Scroll, Move>;

}  // namespace mouse
}  // namespace draw::input