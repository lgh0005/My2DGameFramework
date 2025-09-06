#pragma once

#pragma region TEST
class Shader;
class Texture;
class Font;
class Sprite;
class Transform;
class Camera;
class Text;
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
	shared_ptr<Font> _font;

	shared_ptr<Shader> _fontShader;

	// Component
	shared_ptr<Sprite> _sprite1;
	shared_ptr<Text> _sprite2; // For the font rendering component. Will be rendered later through the UI component.

	shared_ptr<Transform> _trans1;
	shared_ptr<Transform> _trans4;

	shared_ptr<Camera> _uiCamera;
	shared_ptr<Transform> _trans2;

	shared_ptr<Camera> _worldCamera;
	shared_ptr<Transform> _trans3;
	
	// GameObject
	shared_ptr<GameObject> _gameObject; 
	shared_ptr<GameObject> _gameObject2;
	shared_ptr<GameObject> _cameraObjectUI;
	shared_ptr<GameObject> _cameraObjectWorld;

#pragma endregion
};

extern unique_ptr<Game> GAME;