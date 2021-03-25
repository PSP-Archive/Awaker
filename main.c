#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psppower.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include "struct.h"
#include "fonction.h"
#include "menu.h"
#include "jeu.h"

#define MENU 1
#define JEU 2
#define printf pspDebugScreenPrintf

PSP_MODULE_INFO("Awaker", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

int continuer = 1;

int exit_callback(int arg1, int arg2, void *common);
int CallbackThread(SceSize args, void *argp);
int SetupCallbacks(void);

int main()
{
	pspDebugScreenInit();
	SetupCallbacks();
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	scePowerSetClockFrequency(333, 333, 166);

	SDL_Surface *ecran = SDL_SetVideoMode(480, 272, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	printf("Thanks to play Awaker.\n\n\n\n\nPlease wait while loading...\n\nLoading gfx ...");

	srand(time(NULL));
	Menu menu;
	Menu_Init(&menu); menu.img = IMG_Load("data/gfx/menu.png");

	General var; var.img_lvl = IMG_Load("data/gfx/lvl.png");
	General_Init(&var); var.file = fopen("data/dat.dat","r");
	fgets(var.unlock_txt, 2, var.file); var.unlock = atoi(var.unlock_txt); fclose(var.file);
	Anim anim;
	Anim_Init(&anim); anim.img = IMG_Load("data/gfx/anim.png");

	Perso perso;
	Perso_Init(&perso,0,173); perso.img = IMG_Load("./data/gfx/joueur.png");
	printf("OK\n\nLoading music...");
	Niveau lvl1, lvl2, lvl3, lvl4, lvl5, lvl6, lvl7, lvl8, lvl9, fin, lvl11;
	Niveau1_init(&lvl1);	Niveau2_init(&lvl2);	Niveau3_init(&lvl3);	Niveau4_init(&lvl4);
	Niveau5_init(&lvl5);	Niveau6_init(&lvl6);	Niveau7_init(&lvl7);	Niveau8_init(&lvl8);
	Niveau9_init(&lvl9);	Fin_Init(&fin);	Niveau11_init(&lvl11);

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	Sons mus; Sons_Init(&mus);

	PlayWav(mus.awaker, &mus.joue[0]);
	Mix_PlayMusic(mus.music, -1);

	while(continuer == 1)
	{
	sceCtrlReadBufferPositive(&var.pad, 1);
		if (var.fenetre == MENU)
		{
		Anim_Init(&anim);
		PlayedSong_Init(&mus);
		Menu_Sys(&menu, &var, ecran, &lvl1, &lvl2, &lvl3, &lvl4, &lvl5, &lvl6, &lvl7, &lvl8, &lvl9);
		Perso_Init(&perso,-15,173);
		}
		else if (var.fenetre == JEU)
		{
			if(var.niveau==1) (Niveau1(&lvl1, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==2) (Niveau2(&lvl2, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==3) (Niveau3(&lvl3, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==4) (Niveau4(&lvl4, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==5) (Niveau5(&lvl5, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==6) (Niveau6(&lvl6, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==7) (Niveau7(&lvl7, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==8) (Niveau8(&lvl8, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==9) (Niveau9(&lvl9, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau==10) (Fin(&fin, &var, ecran, &anim, &perso, &mus));
			else if(var.niveau==11) (Niveau11(&lvl11, &var, ecran, &anim, &perso, &menu, &mus));
			else if(var.niveau>=12) (Fin(&fin, &var, ecran, &anim, &perso, &mus));
		}
		if(var.niveau != 11) (Blit_Pluie(&var, &anim, ecran));

		if((var.pad.Buttons & PSP_CTRL_LTRIGGER) && (var.appuis ==0)) (screenshot());
		if(var.pad.Buttons) (var.appuis = 1);
		else if(!var.pad.Buttons) (var.appuis = 0);
	SDL_Flip(ecran);
	}

	Mix_FreeMusic(mus.music);
	Mix_CloseAudio();
	SDL_FreeSurface(menu.img);
	SDL_FreeSurface(var.img_lvl);
	SDL_FreeSurface(anim.img);

sceKernelSleepThread();
return 0;
}

int exit_callback(int arg1, int arg2, void *common)
{
	continuer = 0;
	sceKernelExitGame();
	return 0;
}

int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);
	if(thid >= 0)
	{
	sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}


