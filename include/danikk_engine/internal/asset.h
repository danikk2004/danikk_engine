#pragma once

#include <danikk_engine/danikk_engine.h>

namespace danikk_engine
{
	namespace internal
	{
		struct TextureData
		{
			uint handle;
			uint16 width;
			uint16 height;
		};

		struct ShaderData
		{
			uint handle;
		};

		struct FontData;//Имплементация в <internal/font.h>

		struct AssetContainer;

		typedef void (*asset_free_func_t)(AssetContainer&);

		struct AssetType
		{
			const char* name;
			asset_free_func_t free_func;
		};

		struct asset_type
		{
			static constexpr size_t texture = 0;
			static constexpr size_t shader = 1;
			static constexpr size_t font = 2;
			static constexpr size_t model = 3;
		};

		extern AssetType asset_types[4];

		void initAssetTypes();

		struct AssetContainer
		{
			AssetType* type;
			size_t ref_count;
			String name;

			union
			{
				TextureData texture_data;
				ShaderData shader_data;
				FontData* font_ptr;
				Model* model_ptr;
			};

			AssetContainer(size_t type, const String& name);

			friend std::ostream& operator<<(std::ostream& cout, AssetContainer& container);
		};

		struct Asset
		{
			friend class AssetContainer;
			AssetContainer* container;

			Asset();

			Asset(AssetContainer* container);

			Asset& operator=(Asset& other);

			Asset& operator=(Asset&& other);

			bool isNull();

			~Asset();
		};
	}
}
