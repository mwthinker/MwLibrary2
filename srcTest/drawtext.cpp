#include "drawtext.h"

DrawText::DrawText(const std::shared_ptr<TestShader>& testShader, const mw::Text text, float lowX, float lowY)
	: TestShaderData(testShader), text_(text) {	

	update(text.getText(), lowX, lowY);
}

void DrawText::update(std::string text, float lowX, float lowY) {
	text_.setText(text);
	begin();
	addSquareTRIANGLE_STRIP(lowX, lowY, text_);
	end();
}

void DrawText::draw() {
	text_.bindTexture();
	setTexture(true);
	drawTRIANGLE_STRIP();
}
