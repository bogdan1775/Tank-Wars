#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
         Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // functii adaugate de mine
        void DesenareTancuri();
        void DesenareTeren();
        void DesenareTraiectorie(float x_tanc, float y_tanc, float rotatie_tanc, float rotatie_tun, int id_tanc, float deltaTimeSeconds);
        void DesenareProiectil(float deltaTimeSeconds);
        void Verificare_Coliziune_Teren();
        void AlunecareTeren(float deltaTime);
        void DeplasareTanc(float x_tanc, float y_tanc, int id_tanc);
        void DesenareBaraViata(float x_tanc, float y_tanc, int viata);
        void Verificare_Coliziune_Tanc(float x_tanc, float y_tanc,int id);

        // structura pentru proiectil
        struct Proiectil {
            bool ok_lansare;
            float x_proiectil, y_proiectil,rotatie_tun;
            float vy;
        };

     protected:
        glm::mat3 modelMatrix;
        int numar_puncte;
        float magnitudine;
        float g;
        std::vector<Proiectil>proiectile;
        float raza_cerc;

        // pentru tanc1
        float x1_tanc;
        float y1_tanc;
        float rotatie_tanc1;
        float rotatie_tun1;
        int viata1;


        // pentru teren
        std::vector<float>teren_x;
        std::vector<float>teren_y;


        // desenare tanc2
        float x2_tanc;
        float y2_tanc;
        float rotatie_tanc2;
        float rotatie_tun2;
        int viata2;

    };
}   // namespace m1
