#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"

#include "line.hpp"
#include "window.hpp"

#include <colex.hpp>

using namespace colex;
using namespace draw;

TEST_CASE("hello world") {
  window::init(window::Spec{.width = 2000, .height = 1000, .name = "Sound"});

  Line line({{0, 0}, {1000, 1000}, {2000, 1000}});

  std::vector<float> vertices(line.vertex_size() * line.vertices_count());
  std::vector<unsigned int> indices(line.indices_count());

  line.build(0);

  std::cout << "vertices: " << std::endl;
  iter(vertices) | for_each([](auto x) { std::cout << x << std::endl; });

  std::cout << "indices: " << std::endl;
  iter(indices) | for_each([](auto x) { std::cout << x << std::endl; });

  while (window::advance()) {}

  window::destroy();
}
