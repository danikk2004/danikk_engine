#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/internal/texture_data.h>
#include <danikk_engine/internal/shader_data.h>

namespace danikk_engine
{
	namespace internal
	{
		struct AssetContainer;

		class Asset
		{
		protected:
			friend class AssetContainer;
			AssetContainer& container;

			Asset();

			Asset(AssetContainer& container);

			Asset(AssetContainer&& container);

			Asset& operator=(Asset& other);

			Asset& operator=(Asset&& other);

			~Asset();
		};

		enum
		{
			texture_enum,
			shader_enum,
			model_enum,
		};

		typedef void (*asset_free_func_t)(AssetContainer&);

		extern asset_free_func_t asset_free_funcs[];//Определение в data_manager.cpp

		extern const char* asset_type_strings[];

		struct AssetContainer
		{
			uint32 type;
			uint32 ref_count;

			union
			{
				TextureData texture_data;
				ShaderData shader_data;
			};

			friend ostream& operator<<(ostream& cout, AssetContainer& container);
		};
	}
}
