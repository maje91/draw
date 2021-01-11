#include "shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

static std::string read_file(const std::string &path) {
  std::ifstream file;

  file.open(path);

  std::stringstream stream;
  stream << file.rdbuf();

  return stream.str();
}

static void compile_shader(unsigned int shader, const std::string &file_path) {
  auto source = read_file(file_path);
  auto raw = source.c_str();

  glShaderSource(shader, 1, &raw, nullptr);
  glCompileShader(shader);

  int success;
  char info_log[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, info_log);
    std::cout << shader << std::endl;
    std::cout << info_log << std::endl;

    throw std::runtime_error("Failed to compile shader");
  }
}

namespace draw::shader {

unsigned int compile_vertex(const std::string &file_path) {
  unsigned int shader = glCreateShader(GL_VERTEX_SHADER);
  compile_shader(shader, file_path);

  return shader;
}

unsigned int compile_fragment(const std::string &file_path) {
  unsigned int shader = glCreateShader(GL_FRAGMENT_SHADER);
  compile_shader(shader, file_path);

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

}
