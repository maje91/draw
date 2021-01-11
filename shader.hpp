#pragma once

#include <string>

namespace draw::shader {

unsigned int compile_vertex(const std::string &file_path);
unsigned int compile_fragment(const std::string &file_path);

unsigned int link(unsigned int vertex_shader, unsigned int fragment_shader);

}  // namespace draw::shader