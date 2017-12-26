#ifndef H_SFX
#define H_SFX

struct Mix_Chunk;


struct SFX {
	friend class AudioController;

public:
	SFX() {}

	operator bool() const
	{
		return m_sfx != nullptr;
	}

private:
	SFX(Mix_Chunk* sfx) : m_sfx(sfx) {}
	Mix_Chunk* m_sfx = nullptr;
};


#endif // !H_SFX
