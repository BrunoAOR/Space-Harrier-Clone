#ifndef H_MUSIC
#define H_MUSIC

struct _Mix_Music;
typedef struct _Mix_Music Mix_Music;


struct Music {
	friend class AudioController;

public:
	Music() {}

	operator bool() const
	{
		return m_music != nullptr;
	}

private:
	Music(Mix_Music* music) : m_music(music) {}
	Mix_Music* m_music;
};


#endif // !H_MUSIC
