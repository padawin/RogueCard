#ifndef __MY_SDL2_SURFACE__
#define __MY_SDL2_SURFACE__

class Surface {
	private:
    SDL_Surface* m_surface;

	public:
    Surface(SDL_Surface* surface) : m_surface(surface) {}
	Surface(const Surface&) = delete;  // non-copyable
    Surface& operator=(const Surface&) = delete;  // non-copy-assignable

    ~Surface() {
		SDL_FreeSurface(m_surface);
	}

    SDL_Surface* getSDLSurface() {
		return m_surface;
	}

};

#endif
