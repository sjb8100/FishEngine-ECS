#pragma once

#include "Object.hpp"
#include <vector>
#include <bgfx/bgfx.h>
#include <map>
#include <string>
#include "Math.hpp"

struct MaterialProperties
{
	std::map<std::string, Vector4> vec4s;
	std::map<std::string, bgfx::TextureHandle> textures;
};

class Shader;

class Material : public Object
{
public:
	
	void SetShader(Shader* shader);
	Shader* GetShader() const { return m_Shader; }
	
	void SetVector(const std::string& name, const Vector4& value);
	void SetTexture(const std::string& name, bgfx::TextureHandle value);
	void BindUniforms() const;
	
	static Material* Clone(Material* mat)
	{
		Material* m = new Material();
		m->m_Shader = mat->m_Shader;
		m->m_UniformInfos = mat->m_UniformInfos;
		m->m_MaterialProperties = mat->m_MaterialProperties;
		return m;
	}
	
	static void StaticInit();
	inline static Material* Default;
	inline static Material* Texture;
	
protected:
	Shader* m_Shader = nullptr;
	std::map<std::string, std::pair<bgfx::UniformHandle, bgfx::UniformInfo>> m_UniformInfos;
	MaterialProperties m_MaterialProperties;
};
