#ifndef HG_SWIFT_BASE_STD_REGEX
#define HG_SWIFT_BASE_STD_REGEX

#include <engine/include.hpp>

namespace Base {

	namespace std {
		class String;

		class Regex {
			Base::void compile();
			Base::bool check(String seq);
		};
	}
}

#endif //HG_SWIFT_*
