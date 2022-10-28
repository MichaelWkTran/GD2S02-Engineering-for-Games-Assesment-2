// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CSound.h
// Description: CSound initialization file
// Authors: Michael Wai Kit Tran

#pragma once
#include "CUpdatedObject.h"
#include <SFML/Audio.hpp>
#include <string>
#include <map>

class CSound : public CUpdatedObject
{
public:
	static const char* const soundDirective;
	static std::map<std::string /*Sound Directory*/, sf::SoundBuffer*> soundBuffers;
	
	// CSound variables
	sf::Sound sound;
	bool deleteWhenFinished;
	
	//CSound methods
	CSound(const char* const _soundDirectory, bool _startOnConstructor = true, bool _deleteWhenFinished = true);
	void SetVolume(float _volume);
	virtual void Update() override;
};

