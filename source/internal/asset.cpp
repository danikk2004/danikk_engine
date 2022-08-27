#include <danikk_engine/internal/asset.h>
#include <danikk_framework/memory.h>

using namespace danikk_framework;

namespace danikk_engine
{
	namespace internal
	{
		Asset::Asset() : container(createNullRef<AssetContainer>()){}

		Asset::Asset(AssetContainer& container)
		: container(container)
		{
			container.ref_count++;
		}

		Asset::Asset(AssetContainer&& container)
		: container(container){}

		Asset& Asset::operator=(Asset& other)
		{
			this->container = other.container;
			return *this;
		}

		Asset& Asset::operator=(Asset&& other)
		{
			this->container = other.container;
			return *this;
		}

		Asset::~Asset()
		{
			if(!isNullRef(container))
			{
				container.ref_count--;

				if(container.ref_count == 0)
				{
					asset_free_funcs[container.type](container);
				}
			}
		}

		const char* asset_type_strings[3]
		{
			"texture",
			"shader",
			"model",
		};

		ostream& operator<<(ostream& cout, AssetContainer& container)
		{
			cout << "type: " << asset_type_strings[container.type] << " ref_count: " << container.ref_count;
			return cout;
		}
	}
}
