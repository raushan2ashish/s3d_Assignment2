#pragma once
#include "SoftwareRenderingScene.h"

class LightCastersScene : public SoftwareRenderingScene
{
public:
    void OnLoad() final;
    void OnUnload() final;
    void OnUpdate(float dt) final;

private:
    int CurrentTask = 1;
    void HandleInput();
    void Render1_SpiralSphere();
    void Render2_DiffuseCube();
    void Render3_SpotlightModel();
    //void Render4();
    //void Render5();
    
};
