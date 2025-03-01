#pragma once

#include <danikk_framework/dynamic_array.h>
#include <danikk_framework/array.h>
#include <danikk_engine/danikk_engine.h>

namespace danikk_engine
{
	using danikk_framework::DynamicArray;

	typedef danikk_framework::Array<int16,4> KeyBindKeys;
	typedef void (*key_bind_event_t)();

	class KeyBindArray
	{
		struct KeyBind
		{
			KeyBindKeys keys;
			key_bind_event_t event;

			KeyBind(const KeyBindKeys& keys, key_bind_event_t event);
		};
		DynamicArray<KeyBind> data;

	public:
		KeyBindArray() = default;

		KeyBind* getKeyBind(const KeyBindKeys& keys);

		void bind(const KeyBindKeys& keys, key_bind_event_t event);

		void unbind(const KeyBindKeys& keys);

		void checkBindingPress();
	};
}
