#pragma once

#pragma region TEST
class Shader;
class Texture;
class Sprite;
#pragma endregion

class Game
{
public:
	Game();
	~Game();

public:
	void Init();
	void Launch();
	void Update();

private:
	SDL_Event _event;
	bool _running = true;

#pragma region TEST
private:

	// Resources
	shared_ptr<Shader> _shader;
	shared_ptr<Texture> _texture;

	// Component
	shared_ptr<Sprite> _sprite;

	//..

#pragma endregion
};

extern unique_ptr<Game> GAME;