#pragma once
#ifndef _TEXT_H_
#define _TEXT_H_
#include "../UIObject/UIObject.h"

namespace CGE::UI {
	/**
	Text(Renderer& renderer, const std::string text, int color, UIObject* parent = nullptr);
	Text(Renderer& renderer, const std::string text, int color, int x, int y);
	*/
	class Text : public UIObject
	{
	private:
		std::string _text;
		int _color;
	public:
		Text(Renderer& renderer, const std::string text, int color, UIObject* parent = nullptr);
		Text(Renderer& renderer, const std::string text, int color, int x, int y);
	public:
		const std::string& text() const;
		void set_text(std::string text);
		virtual void render() override;
	};
}
#endif
