#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"

#include "line.hpp"
#include "colex.hpp"

using namespace colex;

TEST_CASE("hello world") {
  draw::Line line({{0, 0}, {1000, 1000}, {2000, 1000}});

  std::vector<float> vertices(line.vertex_size() * line.vertices_count());
  std::vector<unsigned int> indices(line.indices_count());

  line.build(vertices.data(), indices.data());

  std::cout << "vertices: " << std::endl;
  iter(vertices) | for_each([](auto x) { std::cout << x << std::endl; });

  std::cout << "indices: " << std::endl;
  iter(indices) | for_each([](auto x) { std::cout << x << std::endl; });
}
