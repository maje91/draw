#include "render.hpp"

#include "shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace draw::render {

Shape::Shape(std::vector<float> vertices, std::vector<unsigned int> indices) : m_vertices(std::move(vertices)), m_indices(std::move(indices)) {
  auto vertex_shader = shader::compile_vertex("../vertex.glsl");
  auto fragment_shader = shader::compile_fragment("../fragment.glsl");
  m_program = shader::link(vertex_shader, fragment_shader);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (4 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  width_location = glGetUniformLocation(m_program, "width");
  A_location = glGetUniformLocation(m_program, "A");
  b_location = glGetUniformLocation(m_program, "b");
}

void Shape::draw() {
  glUseProgram(m_program);
  glUniform1f(width_location, 0.005f);
  glUniformMatrix2fv(A_location, 1, GL_FALSE, glm::value_ptr(glm::mat2(2.0, 0.0, 0.0, 1.0)));
  glUniform2fv(b_location, 1, glm::value_ptr(glm::vec2(0.0, 0.0)));
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

}

