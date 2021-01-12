#include "shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>

static void compile_shader(unsigned int shader, const std::string &source) {
  auto raw = source.c_str();

  glShaderSource(shader, 1, &raw, nullptr);
  glCompileShader(shader);

  int success;
  char info_log[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, info_log);
    std::cout << source << std::endl;
    std::cout << info_log << std::endl;

    throw std::runtime_error("Failed to compile shader");
  }
}

namespace draw::shader {

unsigned int compile_vertex(const std::string &source) {
  unsigned int shader = glCreateShader(GL_VERTEX_SHADER);
  compile_shader(shader, source);

  return shader;
}

unsigned int compile_fragment(const std::string &source) {
  unsigned int shader = glCreateShader(GL_FRAGMENT_SHADER);
  compile_shader(shader, source);

  return shader;
}

unsigned int link(unsigned int vertex_shader, unsigned int fragment_shader) {
  unsigned int program = glCreateProgram();

  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  int success;
  char info_log[512];

  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(program, 512, nullptr, info_log);
    std::cout << info_log << std::endl;
    throw std::runtime_error("Failed to link shader program");
  }

  return program;
}

}  // namespace draw::shader
