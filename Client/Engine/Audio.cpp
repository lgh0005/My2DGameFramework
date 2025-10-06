#include "pch.h"
#include "Audio.h"

Audio::Audio(const string& name, const string& filePath, AudioType type, AudioGroups group)
	: Super(name), _audioPath(filePath), _type(type), _group(group)
{
	FMOD::System* coreSystem = AUDIO.GetCoreSystem();
	FMOD_RESULT res = coreSystem->createStream(_audioPath.c_str(), FMOD_2D, 0, &_sound);
	if (res != FMOD_OK) cout << FMOD_ErrorString(res) << endl;
	_sound->setMode(FMOD_2D);
}