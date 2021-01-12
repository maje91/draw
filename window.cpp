#include "window.hpp"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace draw::window {

static std::optional<std::function<void(const input::Mouse &mouse, input::mouse::Event event)>> m_handle_mouse_event;
static input::Mouse m_mouse;
static GLFWwindow *m_window;
static unsigned int m_width;
static unsigned int m_height;

static input::ButtonAction button_action_from_glfw(int action) {
  switch (action) {
  case GLFW_PRESS: return input::ButtonAction::Press;
  case GLFW_RELEASE: return input::ButtonAction::Release;
  default:
    throw std::runtime_error(
      "button_action_from_glfw: Invalid GLFW action code");
  }
}

static void mouse_callback(GLFWwindow *window, double x, double y) {
  (void) window;

  if (m_handle_mouse_event.has_value()) {
    m_handle_mouse_event.value()(m_mouse, input::mouse::Move{.x = x, .y = y});
    m_mouse.x = x;
    m_mouse.y = y;
  }
}

static void scroll_callback(
  GLFWwindow *window, double x_offset, double y_offset) {
  (void) window;
  (void) x_offset;

  if (m_handle_mouse_event.has_value()) {
    m_handle_mouse_event.value()(
      m_mouse, input::mouse::Scroll{.offset = y_offset});
  }
}

static void mouse_button_callback(
  GLFWwindow *window, int button, int action, int mods) {
  (void) window;
  (void) mods;

  input::ButtonAction button_action = button_action_from_glfw(action);

  if (m_handle_mouse_event.has_value()) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT: {
      m_handle_mouse_event.value()(
        m_mouse, input::mouse::Left{.action = button_action});
      m_mouse.left = input::Button(input::ButtonState::Pressed);
      break;
    }

    case GLFW_MOUSE_BUTTON_RIGHT: {
      m_handle_mouse_event.value()(m_mouse, input::mouse::Right{.action = button_action});
      m_mouse.right = input::Button(input::ButtonState::Released);
      break;
    }

    default:
      throw std::runtime_error("mouse_button_callback: Invalid GLFW button code");
    }
  }
}

static void framebuffer_size_callback(
  GLFWwindow *window, int width, int height) {
  (void) window;

  m_width = width;
  m_height = height;
  glViewport(0, 0, width, height);
}

void init(const Spec &spec) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(
    spec.width, spec.height, spec.name.c_str(), nullptr, nullptr);
  m_width = spec.width;
  m_height = spec.height;

  if (m_window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(m_window);
  glfwSetCursorPosCallback(m_window, mouse_callback);
  glfwSetScrollCallback(m_window, scroll_callback);
  glfwSetMouseButtonCallback(m_window, mouse_button_callback);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }
}

void set_event_handler(const std::function<void(const input::Mouse &, input::mouse::Event)> &on_mouse_event) {
  m_handle_mouse_event = on_mouse_event;
}

bool advance() {
  glfwSwapBuffers(m_window);
  glfwPollEvents();

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  return !glfwWindowShouldClose(m_window);
}

void destroy() { glfwTerminate(); }

unsigned int width() { return m_width; }

unsigned int height() { return m_height; }

}  // namespace draw::window
