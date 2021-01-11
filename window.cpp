#include "window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdexcept>

namespace draw::window {

static GLFWwindow *m_window;
static unsigned int m_width;
static unsigned int m_height;

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

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }
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
