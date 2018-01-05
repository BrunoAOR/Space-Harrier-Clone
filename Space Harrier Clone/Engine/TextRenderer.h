#ifndef H_TEXT_RENDERER
#define H_TEXT_RENDERER

#include "Renderer.h"
#include <map>
#include "Font.h"


class TextRenderer :
	public Renderer
{
public:
	TextRenderer();
	~TextRenderer();

	// Inherited via Renderer
	virtual void render() override;

	bool loadFont(const Font& font);
	int getCharacterSpacing() const;
	void setCharacterSpacing(int charSpacing);
	int getLineSpacing() const;
	void setLineSpacing(int lineSpacing);
	std::string getText() const;
	void setText(const std::string& text);

protected:
	bool rebuildTexture();
	SDL_Rect m_clipRect;
	bool m_shouldReloadTexture;

private:
	bool getBlankTexture();
	void freeFontTexture();
	bool validateFont(const Font& font, int width, int height) const;

	Font m_font;
	SDL_Texture* m_fontTexture = nullptr;
	std::string m_text;
	int m_characterSpacing;
	int m_lineSpacing;
};


#endif // !H_TEXT_RENDERER
