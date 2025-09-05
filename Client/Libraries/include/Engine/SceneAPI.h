#pragma once

class Shader;
class Texture;
class Sprite;

class SceneAPI
{
	static shared_ptr<Sprite> CreateSprite(shared_ptr<Shader> shader, shared_ptr<Texture> texture, const vector<string>& uniforms);
};

