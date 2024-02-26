#include "pch.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}

SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::Init(int totalChannels)
{
	Release();
	for (int i = 0; i < totalChannels; ++i)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundMgr::Release()
{
	// StopAll();
	// StopBgm();

	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();
	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Update(float dt)
{
	for (auto it = playing.begin(); it != playing.end(); )
	{
		sf::Sound* sound = *it;
		if (sound->getStatus() == sf::SoundSource::Stopped)
		{
			waiting.push_back(sound);
			it = playing.erase(it);
		}
		else
		{
			it++;
		}
	}

	// 크로스 페이드
	if (isFading)
	{
		fadeTimer += dt;
		float currBgmVolume = bgmVolume * fadeTimer / fadeDuration;
		float prevBgmVolume = bgmVolume - currBgmVolume;

		if (fadeTimer >= fadeDuration)
		{
			currBgmVolume = bgmVolume;
			prevBgmVolume = 0.f;
			bgm[!frontBgmIndex].stop();

			fadeTimer = 0.f;
			isFading = false;
		}

		bgm[frontBgmIndex].setVolume(currBgmVolume);
		bgm[!frontBgmIndex].setVolume(prevBgmVolume);
	}
}

void SoundMgr::PlayBgm(std::string id, bool crossFade)
{
	if(crossFade)
	{
		isFading = true;
	}
	else
	{
		StopBgm();
	}

	frontBgmIndex = (int)!frontBgmIndex;

	bgm[frontBgmIndex].setBuffer(RES_MGR_SOUND_BUFFER.Get(id));
	bgm[frontBgmIndex].setVolume(bgmVolume);
	bgm[frontBgmIndex].play();
}

void SoundMgr::StopBgm()
{
	for (auto sound : bgm)
	{
		sound.stop();
	}
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(RES_MGR_SOUND_BUFFER.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;
	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}

	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->setVolume(sfxVolume);
	sound->play();
	playing.push_back(sound);
}

void SoundMgr::StopAll()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}
