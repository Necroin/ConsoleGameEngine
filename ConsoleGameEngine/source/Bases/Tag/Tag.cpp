#include "Tag.h"

namespace CGE {
	tag_t get_class_tag() {
		static tag_t value = 0;
		return value++;
	}
};