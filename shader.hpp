#pragma once

#include <string>

namespace draw::shader {

unsigned int compile_vertex(const std::string &source);
unsigned int compile_fragment(const std::string &source);

unsigned int link(unsigned int vertex_shader, unsigned int fragment_shader);

}  // namespace draw::shader