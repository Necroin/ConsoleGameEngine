#pragma once
#ifndef _TAG_H_
#define _TAG_H_

namespace CGE {
	using tag_t = size_t;

	tag_t get_class_tag();

	template<class _Type>
	size_t get_class_tag() {
		static tag_t value = get_class_tag();
		return value;
	}
};
#endif