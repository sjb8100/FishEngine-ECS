#pragma once
#include <FishEngine/ECS.hpp>
#include <bgfx/bgfx.h>

class Material;
class Mesh;
class Camera;


class Skin : public NonCopyable
{
	//COMPONENT(Skin);
public:
	std::vector<Matrix4x4> inverseBindMatrices;
	ECS::GameObject* root = nullptr;
	std::vector<ECS::GameObject*> joints;
	std::string name;
};


class Renderable : public ECS::Component
{
	COMPONENT(Renderable);
	
//	void SetMaterial();
//	void SetMaterial(int index);
	
	void OnDrawGizmosSelected() const override;

public:
	//Material* material = nullptr;
	bool m_Enabled = true;
	std::vector<Material*> m_Materials;
	Mesh* mesh = nullptr;
	Skin* skin = nullptr;
};


class Skybox : public ECS::Component
{
	COMPONENT(Skybox);
public:
	Material * m_skyboxMaterial = nullptr;
};


enum class DrawCallType
{
	Opaque,
	Transparent,
	Overlay,
};


struct DrawCall
{
//	int renderQueue = 0;
	DrawCallType type = DrawCallType::Opaque;
	int viewID = 0;
	int subMeshId = -1;
	Mesh* mesh = nullptr;
	Material* material = nullptr;
	Camera*	camera = nullptr;
//	uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_CULL_CCW;
	uint64_t state = 0;
	Matrix4x4 modelMatrix;
};
