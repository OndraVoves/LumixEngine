#pragma once


#include "core/array.h"
#include "core/resource.h"


namespace Lux
{
namespace FS
{
	class FileSystem;
	class IFile;
}

class PipelineInstance;
class Renderer;
class ResourceManager;
class Shader;
class Texture;


class Material : public Resource
{
	friend class MaterialManager;
public:
	void apply(Renderer& renderer, PipelineInstance& pipeline);
	void setShader(Shader* shader) { m_shader = shader; }
	void addTexture(Texture* texture) { m_textures.push(texture); }
	Shader* getShader() const { return m_shader; }
	bool isZTest() const { return m_is_z_test; }
	void enableZTest(bool enable) { m_is_z_test = enable; }
	bool isBackfaceCulling() const { return m_is_backface_culling; }
	void enableBackfaceCulling(bool enable) { m_is_backface_culling = enable; }
	int getTextureCount() const { return m_textures.size(); }
	Texture* getTexture(int i) { return m_textures[i]; }
	void setTexture(int i, Texture* texture) { m_textures[i] = texture; }

private:
	Material(const Path& path, ResourceManager& resource_manager)
		: Resource(path, resource_manager)
		, m_shader()
		, m_textures()
		, m_is_z_test(true)
		, m_is_backface_culling(true)
	{ }

	~Material()
	{ }

	virtual void doUnload(void) override;
	virtual FS::ReadCallback getReadCallback() override;

	void loaded(FS::IFile* file, bool success, FS::FileSystem& fs);

private:
	struct Uniform
	{
		enum Type
		{
			INT,
			FLOAT,
			MATRIX
		};
		static const int MAX_NAME_LENGTH = 30;
		char m_name[MAX_NAME_LENGTH + 1];
		Type m_type;
		union
		{
			int32_t m_int;
			float m_float;
			float m_matrix[16];
		};
	};

private:
	void deserializeUniforms(class ISerializer& serializer);

private:
	Shader*	m_shader;
	Array<Texture*> m_textures;
	Array<Uniform> m_uniforms;
	bool m_is_z_test;
	bool m_is_backface_culling;
};

} // ~namespace Lux
