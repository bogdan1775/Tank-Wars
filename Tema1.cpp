#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}



void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    magnitudine = 70;
    g=9.8;
    raza_cerc = 70;

    // initiere valori pentru tanc2
    x2_tanc = 950;
    y2_tanc = 0;
    rotatie_tanc2 = 0;
    rotatie_tun2 = 0;
    viata2 = 7;

    // initiere valori pentru tanc1
    x1_tanc = 150;
    y1_tanc = 0;
    rotatie_tanc1 = 0;
    rotatie_tun1 = 0;
    viata1 = 7;

    // pentru tanc1
    Mesh* corptanc = object2D::CreateCorpTanc("corptanc", glm::vec3(139.0/255, 69.0/255, 19.0/255), glm::vec3(205.0 / 255, 133.0 / 255, 63.0 / 255));
    AddMeshToList(corptanc);
    Mesh* disc = object2D::CreateDisc("disc", glm::vec3(205.0 / 255, 133.0 / 255, 63.0 / 255));
    AddMeshToList(disc);
    Mesh* tun = object2D::CreateTun("tun", glm::vec3(0, 0, 0));
    AddMeshToList(tun);

    // pentru tanc2
    Mesh* corptanc2 = object2D::CreateCorpTanc("corptanc2", glm::vec3(139.0 / 255, 69.0 / 255, 19.0 / 255), glm::vec3(107.0 / 255, 142.0 / 255, 35.0 / 255));
    AddMeshToList(corptanc2);
    Mesh* disc2 = object2D::CreateDisc("disc2", glm::vec3(107.0 / 255, 142.0 / 255, 35.0 / 255));
    AddMeshToList(disc2);
    Mesh* tun2 = object2D::CreateTun("tun2", glm::vec3(0, 0, 0));
    AddMeshToList(tun2);

    Mesh* proiectil = object2D::CreateProiectil("proiectil", glm::vec3(0,0,0));
    AddMeshToList(proiectil);

    Mesh* dreptunghiViata = object2D::CreateDreptunghiViata("dreptunghiViata", glm::vec3(1, 1, 1));
    AddMeshToList(dreptunghiViata);

    meshes["teren"] = new Mesh("generated teren");
    meshes["baraViata"] = new Mesh("generated baraViata");
    meshes["traiectorie"] = new Mesh("generated traiectorie");
    meshes["traiectorie2"] = new Mesh("generated traiectorie2");


    // retinere teren
    numar_puncte = 500;
    float x_min = 0, x_max = 1280;
    float delta = (x_max - x_min) / numar_puncte;
    float x = 0,height;
    for (int i = 0;i < numar_puncte+1;i++) {
        x = i * delta;
        // cu asta arata terenul putin mai diferit
        //float height = 190 + 80.0 * sin(x * 0.003) + 60.0 * sin(0.015 * x) + 5 * sin(0.05 * x);
        // cu asta e mai accentuata diferenta de inaltime
        float height = 190 + 80.0 * sin(x * 0.005) + 60.0 * sin(0.02 * x) + 20 * sin(0.03 * x);
        //float height = 190 + 80.0 * sin(x * 0.003) + 60.0 * sin(0.015 * x) + 20 * sin(0.02 * x);
        teren_x.push_back(x);
        teren_y.push_back(height);
    }
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(135.0f/255, 206.0f/255, 250.0f/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

// Functie desenare bara viata tanc
void Tema1::DesenareBaraViata(float x_tanc, float y_tanc, int viata) {

    std::vector<VertexFormat> vertices;
    // de la poz1 se deseneaza pe lungime
    float poz1 = -1.4f;
    vertices.push_back(VertexFormat(glm::vec3(poz1, 2.85f, 0), glm::vec3(1, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(poz1, 3.3f, 0), glm::vec3(1, 1, 1)));
    for (int i = 1;i <=viata;i++) {
        vertices.push_back(VertexFormat(glm::vec3(poz1+i*0.4f, 2.85f, 0), glm::vec3(1, 1, 1)));
        vertices.push_back(VertexFormat(glm::vec3(poz1 + i*0.4f, 3.3f, 0), glm::vec3(1, 1, 1)));
    }

    std::vector<unsigned int> indices;
    for (int i = 0;i < viata*2+2;i++)
        indices.push_back(i);

    //meshes["baraViata"] = new Mesh("generated baraViata");
    meshes["baraViata"]->InitFromData(vertices, indices);
    meshes["baraViata"]->SetDrawMode(GL_TRIANGLE_STRIP);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x_tanc, y_tanc);
    modelMatrix *= transform2D::Scale(20, 20);
    RenderMesh2D(meshes["baraViata"], shaders["VertexColor"], modelMatrix);
    

}

// Functie desenare tancuri
void Tema1::DesenareTancuri() {
    // desenare tanc1
    if (viata1 > 0 && x1_tanc>-20 && x1_tanc<1300) {
        // trapeze
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x1_tanc, y1_tanc);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Rotate(rotatie_tanc1);
        RenderMesh2D(meshes["corptanc"], shaders["VertexColor"], modelMatrix);

        // disc
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x1_tanc, y1_tanc);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Rotate(rotatie_tanc1);
        RenderMesh2D(meshes["disc"], shaders["VertexColor"], modelMatrix);

        // tun
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x1_tanc, y1_tanc);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Rotate(rotatie_tanc1);
        modelMatrix *= transform2D::Translate(0, 1.3f);
        modelMatrix *= transform2D::Rotate(rotatie_tun1 - rotatie_tanc1);
        modelMatrix *= transform2D::Translate(0, -1.3f);
        RenderMesh2D(meshes["tun"], shaders["VertexColor"], modelMatrix);

        // bara_viata
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x1_tanc, y1_tanc);
        modelMatrix *= transform2D::Scale(20, 20);
        RenderMesh2D(meshes["dreptunghiViata"], shaders["VertexColor"], modelMatrix);
        DesenareBaraViata(x1_tanc, y1_tanc, viata1);
    }

    // desenare tanc2
    if (viata2 > 0 && x2_tanc > -20 && x2_tanc < 1300) {
        // trapeze
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x2_tanc, y2_tanc);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Rotate(rotatie_tanc2);
        RenderMesh2D(meshes["corptanc2"], shaders["VertexColor"], modelMatrix);

        // disc
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x2_tanc, y2_tanc);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Rotate(rotatie_tanc2);
        RenderMesh2D(meshes["disc2"], shaders["VertexColor"], modelMatrix);

        // tun
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x2_tanc, y2_tanc);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Rotate(rotatie_tanc2);
        modelMatrix *= transform2D::Translate(0, 1.3f);
        modelMatrix *= transform2D::Rotate(rotatie_tun2 - rotatie_tanc2);
        modelMatrix *= transform2D::Translate(0, -1.3f);
        RenderMesh2D(meshes["tun2"], shaders["VertexColor"], modelMatrix);

        // bara_viata
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x2_tanc, y2_tanc);
        modelMatrix *= transform2D::Scale(20, 20);
        RenderMesh2D(meshes["dreptunghiViata"], shaders["VertexColor"], modelMatrix);
        DesenareBaraViata(x2_tanc, y2_tanc, viata2);
    }
}

// Functie desenare teren
void Tema1::DesenareTeren() {
    vector<VertexFormat>vertices;
    for (int i = 0;i < numar_puncte+1;i++) {
        vertices.push_back(VertexFormat(glm::vec3(teren_x[i], teren_y[i], 0), glm::vec3(1, 1, 0)));
        vertices.push_back(VertexFormat(glm::vec3(teren_x[i], 0, 0), glm::vec3(1, 1, 0)));
    }
    vector<unsigned int> indices;
    for (int i = 0;i < 2*numar_puncte+2;i++)
        indices.push_back(i);

    //meshes["teren"] = new Mesh("generated teren");
    meshes["teren"]->InitFromData(vertices, indices);
    meshes["teren"]->SetDrawMode(GL_TRIANGLE_STRIP);
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["teren"], shaders["VertexColor"], modelMatrix);
}

// Functie desenare traiectorie proiectil
void Tema1::DesenareTraiectorie(float x_tanc, float y_tanc, float rotatie_tanc, float rotatie_tun, int id_tanc,float deltaTimeSeconds)
{
   
    float vtx = cos(rotatie_tun+M_PI_2) * magnitudine;
    float vty = sin(rotatie_tun+ M_PI_2) * magnitudine;

    float x, y;
    vector<VertexFormat>vertices;
    vector<unsigned int> indices;
    float delta_y;
    delta_y = 26;

    x = x_tanc - delta_y * sin(rotatie_tanc);
    y = y_tanc + delta_y * cos(rotatie_tanc);  
    int i = 0;
   
    while (y>-5) {
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), glm::vec3(1, 1, 1)));
        indices.push_back(i);
        x = x + vtx * deltaTimeSeconds * 1;
        y = y + vty * deltaTimeSeconds * 1;
        vty = vty - g * deltaTimeSeconds * 1;
        i++;
    }

    if (id_tanc == 1) {
        //meshes["traiectorie"] = new Mesh("generated traiectorie");
        meshes["traiectorie"]->InitFromData(vertices, indices);
        meshes["traiectorie"]->SetDrawMode(GL_LINE_STRIP);
        modelMatrix = glm::mat3(1);
        glLineWidth(3.0f);
        RenderMesh2D(meshes["traiectorie"], shaders["VertexColor"], modelMatrix);
    }
    else {
        //meshes["traiectorie2"] = new Mesh("generated traiectorie2");
        meshes["traiectorie2"]->InitFromData(vertices, indices);
        meshes["traiectorie2"]->SetDrawMode(GL_LINE_STRIP);
        modelMatrix = glm::mat3(1);
        glLineWidth(3.0f);
        RenderMesh2D(meshes["traiectorie2"], shaders["VertexColor"], modelMatrix);
    }
}

// Functie desenare proiectil
void Tema1::DesenareProiectil(float deltaTimeSeconds)
{
    // parcurg vectorul de proiectile
    for ( auto& proiectil : proiectile) {
        float vx = cos(proiectil.rotatie_tun + M_PI_2) * magnitudine;

        proiectil.x_proiectil = proiectil.x_proiectil + vx * deltaTimeSeconds * 10;
        proiectil.y_proiectil = proiectil.y_proiectil + proiectil.vy * deltaTimeSeconds * 10;

        if (proiectil.y_proiectil < 0)
            proiectil.ok_lansare = false;
        if(proiectil.x_proiectil<0 || proiectil.x_proiectil>1280)
            proiectil.ok_lansare = false;

        proiectil.vy = proiectil.vy - g * deltaTimeSeconds * 10.4;

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(proiectil.x_proiectil, proiectil.y_proiectil);
        modelMatrix *= transform2D::Scale(10, 10);
        RenderMesh2D(meshes["proiectil"], shaders["VertexColor"], modelMatrix);
    }
    
    // sterg din vectorul de proiectile proiectilele de care nu mai am nevoie
    for (auto it = proiectile.begin();it != proiectile.end();) {
        if (it->ok_lansare == false)
            it = proiectile.erase(it);
        else
            ++it;
    }
}

// Functie care verifica coliziunile cu terenul
void Tema1::Verificare_Coliziune_Teren()
{

    float rez = 1.0 * 1280 / numar_puncte;
    float diff_index = 1.0 * raza_cerc / rez;
    diff_index = floor(diff_index);

    for (auto& proiectil : proiectile) {
        float index = 1.0 * proiectil.x_proiectil / rez;
        // indexul unde are loc coliziunea
        int index1;
        index1 = floor(index);
        if (index1 < 0) {
            index1 = 0;

        }
        if (index1 >= numar_puncte) {
            index1 = numar_puncte;
        }
        float diff = proiectil.y_proiectil - teren_y[index1];
        float y_deformare;
        int st = index1 - diff_index + 1;
        int dr = index1 + diff_index + 1;
        if (st < 0)
            st = 0;
        if (dr >= numar_puncte)
            dr = numar_puncte ;

        if (diff < 5 && proiectil.ok_lansare == true) {

            for (int i = st;i <= dr;i++) {
                // aflu inaltimea noua dupa impact
                y_deformare = raza_cerc * raza_cerc - (teren_x[i] - proiectil.x_proiectil) * (teren_x[i] - proiectil.x_proiectil);
                y_deformare = sqrt(y_deformare);
                y_deformare = proiectil.y_proiectil - y_deformare;
           
                if (y_deformare < 0) {
                    teren_y[i] = 0;
                }

                else if (y_deformare < teren_y[i]) {
                    teren_y[i] = y_deformare;
          
                }
            }
            proiectil.ok_lansare = false;
        }
    }
}

// Functie care verifica coliziunile cu tancul
void Tema1::Verificare_Coliziune_Tanc(float x_tanc,float y_tanc,int id)
{
    float x, y, raz;
    for (auto& proiectil : proiectile) {
        x = proiectil.x_proiectil - x_tanc;
        y = proiectil.y_proiectil - y_tanc;
        raz = x*x + y * y;
        if (raz<800 && proiectil.ok_lansare == true) {
            if (id == 1) {
                viata1--;
            }
            else {
                viata2--;
            }
            proiectil.ok_lansare = false;
        }
    }
}

// Functie alunecare teren
void Tema1::AlunecareTeren(float deltaTime)
{
    float epsilon = 80;
    for (int i = 0;i < numar_puncte;i++) {

        float diff =(teren_y[i] - teren_y[i+1]);
        if (diff > 5) {
            teren_y[i] -= epsilon * deltaTime;
            teren_y[i + 1] += epsilon * deltaTime;
            
        }
        else if (diff < -5) {
            teren_y[i] += epsilon *deltaTime;
            teren_y[i + 1] -= epsilon * deltaTime;
            
        }
    }

 
}

// Functie pentru deplasare tanc
void Tema1::DeplasareTanc(float x_tanc,float y_tanc,int id_tanc){
    float rez = 1.0 * 1280 / numar_puncte;
    float index = x_tanc / rez;
    int index1, index2;
    index1 = floor(index);
    index2 = index1 + 1;
    if (index1 < 0) {
        index1 = 0;
        index2 = 2;
    }
    if (index2 >= numar_puncte) {
        index2 = numar_puncte - 1;
        index1 = numar_puncte - 2;
    }

    float t = (x_tanc - teren_x[index1]) * 1.0 / (teren_x[index2] - teren_x[index1]);
    if (id_tanc == 1) {
        y1_tanc = teren_y[index1] + t * (teren_y[index2] - teren_y[index1]);
    }
    else {
        y2_tanc = teren_y[index1] + t * (teren_y[index2] - teren_y[index1]);
    }

    float yV = teren_y[index2] - teren_y[index1];
    float xV = teren_x[index2] - teren_x[index1];
 
    if (id_tanc == 1) {
        rotatie_tanc1 = atan2(yV, xV);
    }
    else {
        rotatie_tanc2 = atan2(yV, xV);
    }
    
}


void Tema1::Update(float deltaTimeSeconds)
{
    //deplasare tancuri
    DeplasareTanc(x1_tanc, y1_tanc, 1);
    DeplasareTanc(x2_tanc, y2_tanc, 2);

    // desenare tancuri
    DesenareTancuri();

    // Desenare Teren
    DesenareTeren();

    // desenare traiectorii
    if(viata1>0 && x1_tanc > -20 && x1_tanc < 1300)
        DesenareTraiectorie(x1_tanc,y1_tanc,rotatie_tanc1,rotatie_tun1,1,deltaTimeSeconds);
    if(viata2>0 && x2_tanc > -20 && x2_tanc < 1300)
        DesenareTraiectorie(x2_tanc, y2_tanc, rotatie_tanc2, rotatie_tun2, 2, deltaTimeSeconds);

    // desenare proiectil si verificare coliziuni
    if (proiectile.size()>0) {
        DesenareProiectil(deltaTimeSeconds);
        Verificare_Coliziune_Tanc(x1_tanc, y1_tanc, 1);
        Verificare_Coliziune_Tanc(x2_tanc, y2_tanc, 2);
        Verificare_Coliziune_Teren();
    }

    // alunecare teren
    AlunecareTeren(deltaTimeSeconds);
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // pentru tanc1
    if (window->KeyHold(GLFW_KEY_D)) {
        x1_tanc += 200*deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        x1_tanc -= 200*deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_W)) {
        rotatie_tun1 += deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        rotatie_tun1 -= deltaTime;
    }

    // pentru tanc2
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        x2_tanc += 200 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_LEFT)) {
        x2_tanc -= 200 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_UP)) {
        rotatie_tun2 += deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_DOWN)) {
        rotatie_tun2 -= deltaTime;
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key==GLFW_KEY_SPACE) {
        float x, y,delta_y=26;
        x = x1_tanc -delta_y * sin(rotatie_tanc1);
        y = y1_tanc +delta_y * cos(rotatie_tanc1);

        float vy = sin(rotatie_tun1 + M_PI_2) * magnitudine;
        Proiectil proiectil = { true,x,y,rotatie_tun1,vy};
        proiectile.push_back(proiectil);
    }

    if (key == GLFW_KEY_ENTER) {
        float x, y, delta_y = 26;
        x = x2_tanc - delta_y * sin(rotatie_tanc2);
        y = y2_tanc + delta_y * cos(rotatie_tanc2);

        float vy = sin(rotatie_tun2 + M_PI_2) * magnitudine;
        Proiectil proiectil = { true,x,y,rotatie_tun2,vy };
        proiectile.push_back(proiectil);
    }
    

    
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
