/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include <SDL2/SDL_mixer.h>

#include "../common.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music = NULL;

void initSound(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);

	music = NULL;

	loadSounds();
}

void setSoundVolume(int vol)
{
	Mix_Volume(-1, vol);
}

void setMusicVolume(int vol)
{
	Mix_VolumeMusic(vol);
}

void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void pauseMusic(void)
{
	Mix_PauseMusic();
}

void resumeMusic(void)
{
	Mix_ResumeMusic();
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

void playSoundLoop(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], -1);
}

void stopChannel(int channel)
{
	Mix_HaltChannel(channel);
}

static void loadSounds(void)
{
	sounds[SND_THROW_GIFT] = Mix_LoadWAV("sound/60013__qubodup__whoosh.ogg");
	sounds[SND_CHIMNEY_COMPLETE] = Mix_LoadWAV("sound/481060__matrixxx__cow-bells-02.ogg");
	sounds[SND_GAME_OVER] = Mix_LoadWAV("sound/448204__tyops__cartoon-scary-hit.ogg");
	sounds[SND_SNOWMAN_HEAD] = Mix_LoadWAV("sound/540788__magnuswaker__boing-1.ogg");
	sounds[SND_CARROT] = Mix_LoadWAV("sound/391660__jeckkech__projectile.ogg");
	sounds[SND_SNOWMAN_CATCH] = Mix_LoadWAV("sound/450621__breviceps__step-into-water-puddle-wade.ogg");
	sounds[SND_SANTA_HIT] = Mix_LoadWAV("sound/442755__digestcontent__woosh-punch.ogg");
	sounds[SND_CHIMNEY_ENTER] = Mix_LoadWAV("sound/573153__fleurescence__mouth-pop.ogg");
	sounds[SND_SACK_APPEAR] = Mix_LoadWAV("sound/345837__krzysiunet__object-materializing.ogg");
	sounds[SND_GIFT_SACK] = Mix_LoadWAV("sound/232017__danmitch3ll__squeaky-dog-toy.ogg");
	sounds[SND_COAL_SACK] = Mix_LoadWAV("sound/686661__deltacode__reload-gun.ogg");
	sounds[SND_GIFT_BREAK] = Mix_LoadWAV("sound/432669__dxeyes__crate_break_3.ogg");
	sounds[SND_SANTA_OUCH] = Mix_LoadWAV("sound/648976__atomediadesign__oh-ouch.ogg");
}
