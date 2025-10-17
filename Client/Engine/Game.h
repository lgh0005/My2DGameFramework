#pragma once

class Game
{
public:
	Game() = default;
	~Game();

public:
	void Init();
	void Launch(const string& FirstSceneName);
	void Quit();

private:
	void Update();
	void LateUpdate();

private:
	SDL_Event _event;
	bool _running = true;
};

extern unique_ptr<Game> GAME;