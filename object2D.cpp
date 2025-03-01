#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

// creez corpul tancului
Mesh* object2D::CreateCorpTanc(
    const std::string& name,
    glm::vec3 color1,
    glm::vec3 color2)
{

    std::vector<VertexFormat> vertices
    {
        // trapezul de jos
        VertexFormat(glm::vec3(-1, 0,  0), color1),
        VertexFormat(glm::vec3(1, 0,  0), color1),
        VertexFormat(glm::vec3(-1.15f, 0.3f,  0), color1),
        VertexFormat(glm::vec3(1.15f, 0.3f,  0), color1),

        //trapezul de sus
        VertexFormat(glm::vec3(-1.5, 0.3f,  0), color2),
        VertexFormat(glm::vec3(1.5, 0.3f,  0), color2),
        VertexFormat(glm::vec3(-1.35f, 1.0f,  0), color2),
        VertexFormat(glm::vec3(1.35f, 1.0f,  0), color2),


    };

    Mesh* corptanc = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 2, 3,
        0, 1, 3,
        4, 6, 7,
        4, 5, 7,


    };

    corptanc->InitFromData(vertices, indices);
    return corptanc;
}

// creez discul pentru tanc
Mesh* object2D::CreateDisc(
    const std::string& name,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(glm::vec3(0, 1.0f, 0), color));
    for (int i = 0;i < 31;i++) {
        float theta = M_PI / 30 * i;
        float x = 0.65 * cos(theta);
        float y = 0.65 * sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y + 1.0f, 0),color));
    }

    Mesh* disc = new Mesh(name);
    std::vector<unsigned int> indices;
    for (int i = 0;i <= 31;i++)
        indices.push_back(i);

    disc->SetDrawMode(GL_TRIANGLE_FAN);
    disc->InitFromData(vertices, indices);
    return disc;
}

// creez tunul pentru tanc
Mesh* object2D::CreateTun(
    const std::string& name,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-0.07, 1.55, 0), color),
        VertexFormat(glm::vec3(0.07, 1.55, 0), color),
        VertexFormat(glm::vec3(-0.07, 2.6, 0), color),
        VertexFormat(glm::vec3(0.07, 2.6, 0), color),


    };

    Mesh* tun = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 2, 3,
        0, 1, 3,
        4, 6, 7,
        4, 5, 7,


    };


    tun->InitFromData(vertices, indices);
    return tun;
}

// creez proiectilul
Mesh* object2D::CreateProiectil(
    const std::string& name,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));
    for (int i = 0;i < 31;i++) {
        float theta = 2*M_PI / 30 * i;
        float x = 0.55 * cos(theta);
        float y = 0.55 * sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    Mesh* proiectil = new Mesh(name);
    std::vector<unsigned int> indicesDisk;
    for (int i = 0;i <= 31;i++)
        indicesDisk.push_back(i);

    proiectil->SetDrawMode(GL_TRIANGLE_FAN);
    proiectil->InitFromData(vertices, indicesDisk);
    return proiectil;
}


// creez dreptunghiul pentru bara de viata pentru tanc
Mesh* object2D::CreateDreptunghiViata(
    const std::string& name,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices
    {
         VertexFormat(glm::vec3(-1.4f, 2.85f, 0), color),
         VertexFormat(glm::vec3(1.4f, 2.85f, 0), color),
         VertexFormat(glm::vec3(-1.4f, 3.3f, 0), color),
         VertexFormat(glm::vec3(1.4f, 3.3f, 0), color),
    };

    Mesh* dreptunghiViata = new Mesh(name);
    std::vector<unsigned int> indices{
        0,2,3,1,0,
    };
    dreptunghiViata->SetDrawMode(GL_LINE_STRIP);
    dreptunghiViata->InitFromData(vertices, indices);
    return dreptunghiViata;
}