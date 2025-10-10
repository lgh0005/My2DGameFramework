#pragma once
#include "ITexture.h"

class Shader;
class Camera;

struct FlipbookInfo
{
	uint32 rows;
	uint32 cols;
	uint32 animationRow;
	uint32 startFrame;
	uint32 endFrame;
	float fps;
	bool isPlaying;
	bool isLoop;
};

class Flipbook : public ITexture
{
	using Super = ITexture;

public:
	Flipbook(const string& name, const string& filePath, FlipbookInfo& info);
	virtual ~Flipbook() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetFrame(uint32 frame);
	uint32 GetCurrentFrame() const { return _currentFrame; }
	uint32 GetTotalFrames() const { return _flipbookInfo.endFrame - _flipbookInfo.startFrame + 1; }

public:
	void Play();
	void Stop();

private:
	void GetFrameVertices();

private:
	FlipbookInfo _flipbookInfo;
	uint32 _currentFrame;
	float _elapsedTime;
};

