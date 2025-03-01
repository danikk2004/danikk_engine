#pragma once

#include <danikk_engine/shader.h>
#include <danikk_engine/model.h>
#include <danikk_engine/texture.h>
#include <danikk_framework/memory_buffer.h>
#include <danikk_framework/path_buffer.h>

#include <danikk_framework/cataloged_dictionary.h>

namespace danikk_engine
{
	namespace internal
	{
		void initDataManager();

		bool loadDataToBuffer(const String& asset_type, const String& name, const String& extension);

	    extern MemoryBuffer asset_load_buffer;
	    extern String localpath_buffer;
	    extern danikk_framework::CatalogedDictionary<AssetContainer*, danikk_framework::pathSlash> assets;
	}
}
