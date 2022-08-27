#include <danikk_engine/shader.h>
#include <glad/glad.h>

namespace danikk_engine
{
	using namespace internal;

    size_t Shader::handle()
    {
    	return container.shader_data.handle;
    }

    Shader::Shader(Shader& other) : Asset(other.container){}

    Shader::Shader(Shader&& other) : Asset(move(other.container)){}

    Shader::Shader(AssetContainer& container) : Asset(container){}

    void Shader::operator=(Shader&& other)
	{
    	new (this) Shader((Shader&&)other);
	}

    void Shader::use()
    {
        glUseProgram(handle());
    }
}
