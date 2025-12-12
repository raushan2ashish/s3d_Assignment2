#include "LightCastersScene.h"
#include "Rasterization.h"
#include "ImageUtils.h"
#include "Window.h"
#include "Camera.h"
#include "Time.h"
#include "Mesh.h"
#include "RasterizationScene.h"

//barycentric coloring taken from RasterizationScene.cpp ShaderPositions example
Vector3 FS_Barycentric(const VertexAttributes& atr, const UniformData& data)
{
	
	return { fabsf(atr.p.x), fabsf(atr.p.y), fabsf(atr.p.z) };
}

void LightCastersScene::OnLoad() {}
void LightCastersScene::OnUnload() {}

void LightCastersScene::OnUpdate(float dt)
{
	ClearColor(&gImageCPU, BLACK);
	ClearDepth(&gImageCPU, 1.0f);

	HandleInput();

	if (CurrentTask == 1) Render1_SpiralSphere();
	else if (CurrentTask == 2) Render2_DiffuseCube();
	else if (CurrentTask == 3) Render3_SpotlightModel();
	//else if (CurrentTask == 4) Render4();
	//else if (CurrentTask == 5) Render5();
}


void LightCastersScene::HandleInput()
{

	if (IsKeyPressed(KEY_1))
		CurrentTask = 1;
	else if (IsKeyPressed(KEY_2))
	    CurrentTask = 2;
	//else if (IsKeyPressed(KEY_3))
	//    CurrentTask = 3;
	//else if (IsKeyPressed(KEY_4))
	//    CurrentTask = 4;
	//else if (IsKeyPressed(KEY_5))
	//    CurrentTask = 5;
}

void LightCastersScene::Render1_SpiralSphere()
{
	float t = fmodf(TotalTime(), 3.0f);   
	float s = t / 3.0f;                   
	float radius = 6.0f * (1.0f - s);     
	float angle = 6.28318f * 2.0f * s;    
	Vector3 pos = { radius * cosf(angle), radius * sinf(angle), 0.0f };

	Matrix world = Translate(pos.x, pos.y, 0.0f);
	Matrix view = LookAt({ 0,0,10 }, V3_ZERO, V3_UP);
	Matrix proj = Perspective(90.0f * DEG2RAD, 1.0f, 0.1f, 100.0f);

	UniformData data{ world, world * view * proj, nullptr, {1,1,1}, {0,0,-1} };
	DrawMesh(&gImageCPU, gMeshSphere, data, FS_Barycentric);
}

Vector3 FS_Diffuse(const VertexAttributes& atr, const UniformData& data)
{
	Vector3 N = Normalize(atr.n);              
	Vector3 L = Normalize(data.lightDirection); 
	float ndotl = fmaxf(Dot(N, L), 0.0f);      
	return { ndotl, ndotl, ndotl };            
}

void LightCastersScene::Render2_DiffuseCube()
{
	float tt = TotalTime();

	Matrix world = RotateY(0.0f * tt * DEG2RAD) * Translate(0.0f, 0.0f, 7.0f);
	Matrix view = LookAt({ 0.0f, 0.0f, 10.0f }, V3_ZERO, V3_UP);
	Matrix proj = Perspective(90.0f * DEG2RAD, 1.0f, 0.1f, 100.0f);

	UniformData data;
	data.world = world;
	data.mvp = world * view * proj;
	//data.tex = &fTexHead;
	data.lightColor = { sinf(tt) * 0.5f + 0.5f, sinf(tt + PI * 0.33f) * 0.5f + 0.5f, sinf(tt + PI * 0.66f) * 0.5f + 0.5f };
	data.lightDirection = Normalize(V3_RIGHT + V3_UP + V3_FORWARD);



	DrawMesh(&gImageCPU, gMeshCube, data, FS_Diffuse);
}

void LightCastersScene::Render3_SpotlightModel()
{

}



