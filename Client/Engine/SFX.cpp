#include "pch.h"
#include "SFX.h"

SFX::SFX(const string& name, const string& filePath, FMOD_MODE playMode)
	: Super(name, filePath, playMode)
{
	AUDIO.GetCoreSystem()->createSound(filePath.c_str(), FMOD_2D | playMode, nullptr, &_sound);
}

SFX::~SFX()
{
	_channel->stop();
	_channel = nullptr;
}

void SFX::Play(FMOD::ChannelGroup* group)
{
	FMOD::Channel* channel = nullptr;
	AUDIO.GetCoreSystem()->playSound(_sound, group, false, &channel);
	if (group) channel->setChannelGroup(group);
	_channel = channel;
}

void SFX::Stop()
{
	if (_channel) _channel->stop();
	_channel = nullptr;
}

void SFX::Pause()
{
	bool paused = false;
	_channel->getPaused(&paused);
	if (!paused) _channel->setPaused(true);
}

void SFX::Resume()
{
	bool paused = false;
	_channel->getPaused(&paused);
	if (paused) _channel->setPaused(false);
}

bool SFX::IsPlaying() const
{
	if (!_channel) return false;
	bool playing = false;
	_channel->isPlaying(&playing);
	return playing;
}