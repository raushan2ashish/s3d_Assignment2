#include "LightCastersScene.h"
#include "Rasterization.h"
#include "ImageUtils.h"
#include "Window.h"
#include "Camera.h"
#include "Time.h"
#include "Mesh.h"

//barycentric coloring taken from RasterizationScene.cpp ShaderPositions example
Vector3 FS_Barycentric(const VertexAttributes& atr, const UniformData& data)
{
	
	return { fabsf(atr.p.x), fabsf(atr.p.y), fabsf(atr.p.z) };
}

void LightCastersScene::OnLoad() {}
void LightCastersScene::OnUnload() {}
void LightCastersScene::HandleInput()
{

	if (IsKeyPressed(KEY_1))
		CurrentTask = 1;
	//else if (IsKeyPressed(KEY_2))
	//    CurrentTask = 2;
	//else if (IsKeyPressed(KEY_3))
	//    CurrentTask = 3;
	//else if (IsKeyPressed(KEY_4))
	//    CurrentTask = 4;
	//else if (IsKeyPressed(KEY_5))
	//    CurrentTask = 5;
}
void LightCastersScene::OnUpdate(float dt)
{
	ClearColor(&gImageCPU, BLACK);
	ClearDepth(&gImageCPU, 1.0f);

	HandleInput();

	if (CurrentTask == 1) Render1_SpiralSphere();
	//else if (CurrentTask == 2) Render2();
	//else if (CurrentTask == 3) Render3();
	//else if (CurrentTask == 4) Render4();
	//else if (CurrentTask == 5) Render5();
}

void LightCastersScene::Render1_SpiralSphere()
{
	float t = fmodf(TotalTime(), 3.0f);   // restart every 3 seconds
	float s = t / 3.0f;                   // normalized time 0..1
	float radius = 6.0f * (1.0f - s);     // spiral inward
	float angle = 6.28318f * 2.0f * s;    // two full spins
	Vector3 pos = { radius * cosf(angle), radius * sinf(angle), 0.0f };

	Matrix world = Translate(pos.x, pos.y, 0.0f);
	Matrix view = LookAt({ 0,0,10 }, V3_ZERO, V3_UP);
	Matrix proj = Perspective(90.0f * DEG2RAD, 1.0f, 0.1f, 100.0f);

	UniformData data{ world, world * view * proj, nullptr, {1,1,1}, {0,0,-1} };
	DrawMesh(&gImageCPU, gMeshSphere, data, FS_Barycentric);
}
