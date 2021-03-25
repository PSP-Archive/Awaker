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

#include "struct.h"
#include "fonction.h"

#define PRINCIPALE 1
#define CHOIX_DIFFICUTLE 2
#define RULES 3
#define CREDITS 4

int continuer;

void Menu_Anim_Difficulte(Menu *menu, SDL_Surface *ecran)
{
SDL_BlitSurface(menu->img, &menu->selection2.dim,ecran, &menu->selection2.pos);
	if(menu->selection2.pos.x > 0)
	{
	menu->selection1.x-=4;
	menu->selection2.x-=4;
	}
	else if (menu->selection2.pos.x <= 0)
	{
	menu->animation = 0;
	menu->fenetre = CHOIX_DIFFICUTLE;
	}
}
void Menu_Anim_DifficulteRewind(Menu *menu, SDL_Surface *ecran)
{
SDL_BlitSurface(menu->img, &menu->selection1.dim,ecran, &menu->selection1.pos);
	if(menu->selection2.pos.x < 481)
	{
	menu->selection1.x+=4;
	menu->selection2.x+=4;
	}
	else if (menu->selection2.pos.x >= 480)
	{
	menu->animation = 0;
	menu->fenetre = PRINCIPALE;
	}
}

void Menu_Anim_Credits(Menu *menu, SDL_Surface *ecran)
{
SDL_BlitSurface(menu->img, &menu->selection3.dim,ecran, &menu->selection3.pos);
	if(menu->selection3.x < 0)
	{
	menu->selection1.x+=4;
	menu->selection3.x+=4;
	}
	else if (menu->selection3.x >= 0)
	{
	menu->animation = 0;
	menu->fenetre = CREDITS;
	}
}
void Menu_Anim_CreditsRewind(Menu *menu, SDL_Surface *ecran)
{
SDL_BlitSurface(menu->img, &menu->selection1.dim,ecran, &menu->selection1.pos);
	if(menu->selection1.pos.x > 0)
	{
	menu->selection1.x-=4;
	menu->selection3.x-=4;
	}
	else if (menu->selection1.pos.x <= 0)
	{
	menu->animation = 0;
	menu->fenetre = PRINCIPALE;
	}
}

void Menu_Sys(Menu *menu, General *var, SDL_Surface *ecran, Niveau *lvl1, Niveau *lvl2, Niveau *lvl3, Niveau *lvl4, Niveau *lvl5, Niveau *lvl6, Niveau *lvl7, Niveau *lvl8, Niveau *lvl9)
{
menu->selection1.pos.x = menu->selection1.x;
menu->selection1.pos.y = menu->selection1.y;
menu->selection2.pos.x = menu->selection2.x;
menu->selection2.pos.y = menu->selection2.y;
menu->selection3.pos.x = menu->selection3.x;
menu->selection3.pos.y = menu->selection3.y;

SDL_BlitSurface(menu->img, &menu->background.dim,ecran, &menu->background.pos);

	if (menu->fenetre == PRINCIPALE)
	{
	SDL_BlitSurface(menu->img, &menu->selection1.dim,ecran, &menu->selection1.pos);
	menu->background.dim.x = 480;
		if (menu->animation==0)
		{
			if((var->pad.Buttons & PSP_CTRL_DOWN) && (var->appuis == 0) && (menu->choix < 4))
			{
			menu->selection1.dim.y += 90;
			menu->choix++;
			}
			else if((var->pad.Buttons & PSP_CTRL_UP) && (var->appuis == 0) && (menu->choix > 1))
			{
			menu->selection1.dim.y -= 90;
			menu->choix--;
			}
			if((var->pad.Buttons & PSP_CTRL_CROSS) && (var->appuis == 0))
			{
				if (menu->choix == 1) (menu->animation=1);
				else if (menu->choix == 2) menu->fenetre = RULES;
				else if (menu->choix == 3) (menu->animation=3);
				else if (menu->choix == 4)
				{
				continuer =0;
				sceKernelExitGame();
				}
			}
		}
		else if (menu->animation==1) Menu_Anim_Difficulte(menu, ecran);
		else if (menu->animation==3) Menu_Anim_Credits(menu, ecran);
	}
	else if (menu->fenetre == CHOIX_DIFFICUTLE)
	{
	SDL_BlitSurface(menu->img, &menu->selection2.dim,ecran, &menu->selection2.pos);

		if (menu->animation==0)
		{
			if (menu->choix == 1) (menu->selection2.dim.y = 632);
			else if (menu->choix == 2) (menu->selection2.dim.y = 632 + 90);
			else if (menu->choix == 3) (menu->selection2.dim.y = 632 + 180);

			if((var->pad.Buttons & PSP_CTRL_DOWN) && (var->appuis == 0) && (menu->choix < 3))
			{
			var->appuis = 1;
			menu->choix++;
			}
			else if((var->pad.Buttons & PSP_CTRL_UP) && (var->appuis == 0) && (menu->choix > 1))
			{
			var->appuis = 1;
			menu->choix--;
			}
			if((var->pad.Buttons & PSP_CTRL_CROSS) && (var->appuis == 0))
			{
				if (menu->choix == 1)
				{
				var->fenetre = 2;
				var->difficulte = 0;
				var->niveau = 1;
				}
				else if (menu->choix == 2)
				{
				var->fenetre = 2;
				var->difficulte = 1;
				var->niveau = 1;
				}
				else if (menu->choix == 3)
				{
				menu->animation=2;
				menu->choix = 1;
				var->niveau = 1;
				}
			Niveau1_init(lvl1);
			Niveau2_init(lvl2);
			Niveau3_init(lvl3);
			Niveau4_init(lvl4);
			Niveau5_init(lvl5);
			Niveau6_init(lvl6);
			Niveau7_init(lvl7);
			Niveau8_init(lvl8);
			Niveau9_init(lvl9);
			}
		}
		else if (menu->animation==2) (Menu_Anim_DifficulteRewind(menu, ecran));
	}
	else if (menu->fenetre == RULES)
	{
	menu->background.dim.x = 0;
	menu->background.dim.y = 0;
		if((var->pad.Buttons & PSP_CTRL_CROSS) && (var->appuis == 0))
		{
		var->appuis = 1;
		menu->fenetre = PRINCIPALE;
		menu->background.dim.x = 480;
		menu->background.dim.y = menu->which_bg*272;
		}
	}
	else if (menu->fenetre == CREDITS)
	{
	SDL_BlitSurface(menu->img, &menu->selection3.dim,ecran, &menu->selection3.pos);

		if (menu->animation == 4) Menu_Anim_CreditsRewind(menu, ecran);

		if((var->pad.Buttons & PSP_CTRL_CROSS) && (var->appuis == 0))
		{
		menu->animation = 4;
		var->appuis = 1;
		}
	}
}

void Menu_Init(Menu *menu)
{

	menu->which_bg = 0 + ((float) rand() / RAND_MAX * (2 - 0 + 1));
	menu->background.pos.x= 0;
	menu->background.pos.y = 0;
	menu->background.dim.x = 480;
	menu->background.dim.y = menu->which_bg*272;
	menu->background.dim.w = 480;
	menu->background.dim.h = 272;

	menu->selection1.x = 0;
	menu->selection1.y = 180;
	menu->selection1.pos.x= menu->selection1.x;
	menu->selection1.pos.y = menu->selection1.y;
	menu->selection1.dim.x = 0;
	menu->selection1.dim.y = 272;
	menu->selection1.dim.w = 480;
	menu->selection1.dim.h = 90;

	menu->selection2.x = 480;
	menu->selection2.y = 180;
	menu->selection2.pos.x= menu->selection2.x;
	menu->selection2.pos.y = menu->selection2.y;
	menu->selection2.dim.x = 0;
	menu->selection2.dim.y = 632;
	menu->selection2.dim.w = 480;
	menu->selection2.dim.h = 90;

	menu->selection3.x = -480;
	menu->selection3.y = 180;
	menu->selection3.pos.x= menu->selection3.x;
	menu->selection3.pos.y = menu->selection3.y;
	menu->selection3.dim.x = 0;
	menu->selection3.dim.y = 902;
	menu->selection3.dim.w = 480;
	menu->selection3.dim.h = 90;

	menu->choix = 1;
	menu->fenetre = 1;
	menu->animation = 0;
}

