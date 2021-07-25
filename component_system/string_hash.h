#pragma once
#include <string_view>

namespace wx2 {

	struct StringCompare 
	{
		using is_transparent = void;
		bool operator()(std::string_view key, std::string_view s) const {
			return key == s;
		}
	};

	struct StringHash 
	{
		using is_transparent = void;
		using transparent_key_equal = StringCompare;

		using HashType = std::hash<std::string_view>;

		size_t operator()(std::string_view s) const { return HashType{}(s); }
		size_t operator()(const std::string& s) const { return HashType{}(s); }
		size_t operator()(const char* s) const { return HashType{}(s); }
	};

}