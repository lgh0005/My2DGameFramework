#pragma once

class Game
{
public:
	Game();
	~Game();

public:
	void Init();
	void Launch();
	void Update();
	void Render();

private:
	SDL_Window* _window;
	SDL_GLContext _glContext;
	SDL_Event _event;
	bool _running = true;
	int bufferWidth = 0;
	int bufferHeight = 0;
};

extern unique_ptr<Game> GAME;