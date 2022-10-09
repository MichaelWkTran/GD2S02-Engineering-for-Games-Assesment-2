#pragma once
#include "CUpdatedObject.h"
#include "SFML/Audio.hpp"
#include <map>

class CSound : public CUpdatedObject
{
public:
	static const char* const soundDirective;
	static std::map<const char* /*Sound Directory*/, sf::SoundBuffer> soundBuffers;

	// CSound variables
	sf::Sound sound;
	bool deleteWhenFinished;

	// CSound methods
	CSound(const char* const _soundDirectory, bool _startOnConstructor = true, bool _deleteWhenFinished = true);
	virtual void Update() override;
};

