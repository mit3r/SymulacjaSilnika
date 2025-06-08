#pragma once
#include <glm/glm.hpp>

struct Vertex {
  glm::vec4 position;  // Współrzędne w przestrzeni modelu
  glm::vec4 normal;    // Wektor normalny
  glm::vec4 texCoord;  // Współrzędne tekstury
};