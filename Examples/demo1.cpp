#include <Material.hpp>
#include <Mesh.hpp>
#include <GameApp.hpp>
#include <ECS.hpp>
#include <Camera.hpp>
#include <Light.hpp>
#include <Renderable.hpp>

#include <GLFW/glfw3.h>

class PBRData : public Component
{
public:
	float Metallic = 0;
	float Roughness = 0;
	float Specular = 0;
	float pad;
};

class Demo1 : public GameApp
{
public:
	void Start() override
	{
		m_Shader = ShaderUtil::Compile("D:/program/FishEngine-ECS/shader/vs.bin", "D:/program/FishEngine-ECS/shader/fs.bin");
		
		{
			EntityID goID = m_Scene->CreateGameObject();
			m_Scene->GameObjectAddComponent<Camera>(goID);
		}
		{
			EntityID goID = m_Scene->CreateGameObject();
			m_Scene->GameObjectAddComponent<Light>(goID);
		}
		
		for (int y = 0; y < 11; ++y)
		{
			for (int x = 0; x < 11; ++x)
			{
				EntityID goID = m_Scene->CreateGameObject();
				//PBRData* rotator = m_Scene->GameObjectAddComponent<PBRData>(goID);
				//rotator->x = x;
				//rotator->y = y;
				auto go = m_Scene->GetGameObjectByID(goID);
				auto& pos = go->GetTransform()->position;
				pos.x = -7.5f + x * 1.5f;
				pos.y = -7.5f + y * 1.5f;
				Renderable* rend = m_Scene->GameObjectAddComponent<Renderable>(goID);
				rend->mesh = Mesh::Sphere;

				Material* mat = new Material();
				mat->m_Shader = m_Shader;
				mat->pbrparams[0] = x * 0.1f;
				mat->pbrparams[1] = y * 0.1f;
				rend->material = mat;
			}
		}

		m_Scene->Start();
	}

	void Update() override
	{
		float lightDir[] = { 1, 1, 1, 0 };
		m_Scene->Update();
	}
	
private:
	Shader* m_Shader = nullptr;
};


int main(void)
{
	Demo1 demo;
	demo.Run();
	return 0;
}
