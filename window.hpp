#pragma once

#include "input.hpp"

#include <string>
#include <functional>

namespace draw::window {

/**
 * The things that must be specified to initialize the window
 */
struct Spec {
  int width;
  int height;
  std::string name;
};

/**
 * Initializes the window. Important that this is called
 * before preparing any shapes as it also sets up OpenGL.
 * Typically, it should be the first line of a program.
 */
void init(const Spec &spec);

/**
 * Destroys the window
 */
void destroy();

/**
 * Sets a callback for mouse events. `mouse` is the current state of the mouse and `event` is a new thing that has happened.
 * The state automatically is updated with the new event after this function has run.
 */
void set_event_handler(const std::function<void(const input::Mouse &mouse, input::mouse::Event event)> &on_mouse_event);

/**
 * Advances the window and OpenGL to the next frame. Returns false if the window should close
 */
bool advance();

/**
 * Returns the height of the window
 */
unsigned int height();

/**
 * Returns the widt of the window
 */
unsigned int width();

}  // namespace draw::window