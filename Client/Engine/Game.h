#pragma once

#pragma region TEST
class Shader;
class Texture;
class Font;
class Sprite;
class Transform;
class GameObject;
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
	shared_ptr<Shader> _texShader;
	shared_ptr<Texture> _texture;
	/*shared_ptr<Font> _font;*/

	/*shared_ptr<Shader> _fontShader;*/

	// Component
	shared_ptr<Sprite> _sprite1;
	// shared_ptr<Sprite> _sprite2; // For the font rendering component. Will be rendered later through the UI component.
	shared_ptr<Transform> _trans1;
	
	// GameObject
	shared_ptr<GameObject> _gameObject;

#pragma endregion
};

extern unique_ptr<Game> GAME;