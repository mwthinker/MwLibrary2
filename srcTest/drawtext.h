#ifndef DRAWTEXT_H
#define DRAWTEXT_H

#include "testshaderdata.h"

#include <mw/text.h>

#include <memory>

class DrawText;
using DrawTextPtr = std::shared_ptr<DrawText>;

class DrawText : public TestShaderData {
public:
	DrawText(const std::shared_ptr<TestShader>& testShader, const mw::Text text_, float lowX, float lowY);

	void update(std::string text, float lowX, float lowY);

	void draw();

private:
	mw::Text text_;
};

#endif // DRAWTEXT_H
