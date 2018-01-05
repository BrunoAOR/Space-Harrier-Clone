#ifndef H_CLIPPABLE_TEXT_RENDERER
#define H_CLIPPABLE_TEXT_RENDERER

#include "../Engine/TextRenderer.h"


class ClippableTextRenderer :
	public TextRenderer
{
public:
	virtual void render() override;
	void setRenderRange(int xLeftWorld, int xRightWorld, int YBottomWorld, int yTopWorld);

private:
	void customRender();

	int m_xLeft;
	int m_xRight;
	int m_yBottom;
	int m_yTop;
};


#endif // !H_CLIPPABLE_TEXT_RENDERER
