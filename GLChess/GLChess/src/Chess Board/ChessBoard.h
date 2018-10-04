#pragma once
#include <glm/glm.hpp>

glm::vec2** AssignBoardCoords();
glm::vec2 GetMovement(int x, int y);
glm::vec2 GetTileCentre(double x, double y);

extern glm::vec2** Board;