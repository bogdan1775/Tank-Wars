#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCorpTanc(const std::string& name, glm::vec3 color1, glm::vec3 color2);
    Mesh* CreateDisc(const std::string& name, glm::vec3 color);
    Mesh* CreateTun(const std::string& name, glm::vec3 color);
    Mesh* CreateProiectil(const std::string& name, glm::vec3 color);
    Mesh* CreateDreptunghiViata(const std::string& name, glm::vec3 color);
}
