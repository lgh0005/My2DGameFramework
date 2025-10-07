#include "pch.h"
#include "BGM.h"

BGM::BGM(const string& name, const string& filePath, FMOD_MODE playMode)
	: Super(name, filePath, playMode)
{
	AUDIO.GetCoreSystem()->createStream(filePath.c_str(), FMOD_2D | playMode, nullptr, &_sound);
}

BGM::~BGM()
{
	_channel->stop();
	_channel = nullptr;
}

void BGM::Play(FMOD::ChannelGroup* group)
{
	FMOD::Channel* channel = nullptr;
	AUDIO.GetCoreSystem()->playSound(_sound, nullptr, false, &channel);
	if (group) channel->setChannelGroup(group);
	_channel = channel;
}

void BGM::Stop()
{
	if (_channel) _channel->stop();
	_channel = nullptr;
}

void BGM::Pause()
{
	bool paused = false;
	_channel->getPaused(&paused);
	if (!paused) _channel->setPaused(true);
}

void BGM::Resume()
{
	bool paused = false;
	_channel->getPaused(&paused);
	if (paused) _channel->setPaused(false);
}

bool BGM::IsPlaying() const
{
	if (!_channel) return false;
	bool playing = false;
	_channel->isPlaying(&playing);
	return playing;
}
