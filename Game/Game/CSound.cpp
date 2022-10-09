// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CSound.cpp
// Description: CSound declaration file
// Authors: Michael Wai Kit Tran

#include "CSound.h"
#include <string>

const char* const CSound::soundDirective = "Assets/Sounds/";
std::map<const char*, sf::SoundBuffer*> CSound::soundBuffers;

CSound::CSound(const char* const _soundDirectory, bool _startOnConstructor, bool _deleteWhenFinished)
{
	deleteWhenFinished = _deleteWhenFinished;

	// get the full sound directory
	std::string fullSoundDirectory = std::string(soundDirective) + _soundDirectory;
	
	// if the requested sound buffer exists, otherwise create a new one and load the sound
	auto bufferIterator = soundBuffers.find(fullSoundDirectory.c_str());
	if (bufferIterator == soundBuffers.end())
	{
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;
		soundBuffer->loadFromFile(fullSoundDirectory);

		soundBuffers.emplace(fullSoundDirectory.c_str(), soundBuffer);
	}
	
	// set the sound buffer to the stored sf::Sound
	sound.setBuffer(*soundBuffers.at(fullSoundDirectory.c_str()));

	// play the sound when it is created
	if (_startOnConstructor) sound.play();
}

void CSound::Update()
{
	// delete the sound object when it has finihed playing and deleteWhenFinished is true
	if (deleteWhenFinished && sound.getStatus() == sf::Sound::Stopped) DeleteObject();
}