#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/internal/asset.h>

namespace danikk_engine
{
    class Shader : private internal::Asset
    {
    private:
    	size_t handle();
    public:
        Shader() = default;

        Shader(Shader& other);

        Shader(Shader&& other);

        Shader(internal::AssetContainer& container);

        void operator=(Shader&& other);

        void use();
    };
}
