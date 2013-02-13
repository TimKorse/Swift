#ifndef HG_SWIFT_BASE_STD_STRING
#define HG_SWIFT_BASE_STD_STRING

#include <engine/include.hpp>

namespace Base {

	namespace std {
		class Regex;

		class String {
			String replace(Regex match, String value, Base::bool all);
			String find(Regex match);
		};
	}
}

#endif //HG_SWIFT_*
