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

#define MENU 1
#define JEU 2

void Niveau11(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
Blit_Matrix_Effet(var, ecran);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
blit_sentinelle(&lvl->senti3, ecran, var);
perso_anim(perso, ecran, var);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(30, &lvl->senti1);
	vision_sys(100, &lvl->senti2);
	vision_sys(250, &lvl->senti3);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, 22, 153, -15, 173);
	check_if_see(&lvl->senti2, perso, 154, 295, -15, 173);
	check_if_see(&lvl->senti3, perso, 344, 450, -15, 173);

	follow_the_line(var, perso, -20 , 16, 0);
	follow_the_line(var, perso, 16 , 41, -1);
	follow_the_line(var, perso, 41 , 73, 0);
	follow_the_line(var, perso, 73 , 89, 1);
	follow_the_line(var, perso, 89 , 158, -1);
	follow_the_line(var, perso, 158 , 187, 0);
	follow_the_line(var, perso, 187 , 224, 1);
	follow_the_line(var, perso, 224 , 294, 0);
	follow_the_line(var, perso, 294 , 309, -1);
	follow_the_line(var, perso, 309 , 332, 1);
	follow_the_line(var, perso, 332 , 410, -1);
	follow_the_line(var, perso, 410 , 480, 0);
	}

	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 95, mus);
	Paused(menu, var, mus, lvl, anim, ecran);
	cheat(var, lvl);
}

void Fin(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Sons *mus)
{
	if(var->difficulte==0) (Init_background(lvl, 0, 9*272));
	else if(var->difficulte==1) (Init_background(lvl, 0, 10*272));
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if(lvl->start == 1)
	{
		if((var->pad.Buttons & PSP_CTRL_START) && (var->appuis == 0))
		{
		var->fenetre = MENU;
		var->niveau= 1;
			if(var->unlock == 0)
			{
			var->unlock = 1;
			save_unlock(var);
			}
		}
	}

}

void Niveau9(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
blit_sentinelle(&lvl->senti3, ecran, var);
blit_sentinelle(&lvl->senti4, ecran, var);
blit_sentinelle(&lvl->senti5, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(0, &lvl->senti1);
	vision_sys(400, &lvl->senti2);
	vision_sys(300, &lvl->senti3);
	vision_sys(500, &lvl->senti4);
	vision_sys(600, &lvl->senti5);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, -10, 107, -15, 29);
	check_if_see(&lvl->senti2, perso, 47, 176, -15, 29);
	check_if_see(&lvl->senti3, perso, 125, 264, -15, 29);
	check_if_see(&lvl->senti4, perso, 212, 322, -15, 29);
	check_if_see(&lvl->senti5, perso, 290, 393, -15, 29);

	follow_the_line(var, perso, -20 , 21, 0);
	follow_the_line(var, perso, 21 , 36, 1);
	follow_the_line(var, perso, 36 , 51, 0);
	follow_the_line(var, perso, 51 , 63, -1);
	follow_the_line(var, perso, 63 , 118, 0);
	follow_the_line(var, perso, 118 , 132, 1);
	follow_the_line(var, perso, 132 , 188, 0);
	follow_the_line(var, perso, 188 , 207, -1);
	follow_the_line(var, perso, 207 , 249, 0);
	follow_the_line(var, perso, 249 , 410, 1);
	follow_the_line(var, perso, 410 , 480, 0);
	}
	Paused(menu, var, mus, lvl, anim, ecran);
		if ((var->unlock == 1) && (lvl->perdu == -1))
		{
		PlayWav(mus->win, &mus->joue[8]);
		SDL_BlitSurface(anim->img,&anim->lvl_win.dim,ecran,&anim->lvl_win.pos);
			if((var->pad.Buttons & PSP_CTRL_CROSS) && (var->appuis == 0))
			{
			Anim_Init(anim);
			Perso_Init(perso,-15,173);
			var->niveau = 11;
			PlayedSong_Init(mus);
			}
		}
		else (check_who_win(var, perso, lvl, anim, ecran, menu, -15, 29, mus));
	cheat(var, lvl);
}

void Niveau8(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
blit_sentinelle(&lvl->senti3, ecran, var);
blit_sentinelle(&lvl->senti4, ecran, var);
blit_sentinelle(&lvl->senti5, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(0, &lvl->senti1);
	vision_sys(400, &lvl->senti2);
	vision_sys(300, &lvl->senti3);
	vision_sys(500, &lvl->senti4);
	vision_sys(600, &lvl->senti5);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, -10, 110, -15, 111);
	check_if_see(&lvl->senti2, perso, 77, 165, -15, 111);
	check_if_see(&lvl->senti3, perso, 135, 270, -15, 111);
	check_if_see(&lvl->senti4, perso, 224, 365, -15, 111);
	check_if_see(&lvl->senti5, perso, 345, 450, -15, 111);

	follow_the_line(var, perso, -20 , 23, 0);
	follow_the_line(var, perso, 23 , 39, 1);
	follow_the_line(var, perso, 39 , 65, 0);
	follow_the_line(var, perso, 65 , 101, -1);
	follow_the_line(var, perso, 101 , 128, 0);
	follow_the_line(var, perso, 128 , 178, 1);
	follow_the_line(var, perso, 178 , 202, 0);
	follow_the_line(var, perso, 202 , 223, -1);
	follow_the_line(var, perso, 223 , 244, 0);
	follow_the_line(var, perso, 244 , 294, 1);
	follow_the_line(var, perso, 294 , 319, 0);
	follow_the_line(var, perso, 319 , 374, -1);
	follow_the_line(var, perso, 374 , 394, 0);
	follow_the_line(var, perso, 394 , 408, -1);
	follow_the_line(var, perso, 408 , 480, 0);
	}

	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 29, mus);
	Paused(menu, var, mus, lvl, anim, ecran);
	cheat(var, lvl);
}

void Niveau7(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
blit_sentinelle(&lvl->senti3, ecran, var);
blit_sentinelle(&lvl->senti4, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(50, &lvl->senti1);
	vision_sys(175, &lvl->senti2);
	vision_sys(250, &lvl->senti3);
	vision_sys(375, &lvl->senti4);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, -10, 110, -15, 155);
	check_if_see(&lvl->senti2, perso, 98, 198, -15, 155);
	check_if_see(&lvl->senti3, perso, 205, 303, -15, 155);
	check_if_see(&lvl->senti4, perso, 266, 397, -15, 155);

	follow_the_line(var, perso, -20 , 21, 0);
	follow_the_line(var, perso, 21 , 74, 1);
	follow_the_line(var, perso, 74 , 245, -1);
	follow_the_line(var, perso, 245 , 268, 0);
	follow_the_line(var, perso, 268 , 294, 1);
	follow_the_line(var, perso, 294 , 311, 0);
	follow_the_line(var, perso, 311 , 334, 1);
	follow_the_line(var, perso, 334 , 353, 0);
	follow_the_line(var, perso, 353 , 369, 1);
	follow_the_line(var, perso, 369 , 390, 0);
	follow_the_line(var, perso, 390 , 424, 1);
	follow_the_line(var, perso, 424 , 480, 0);
	}

	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 111, mus);
	Paused(menu, var, mus, lvl, anim, ecran);
	cheat(var, lvl);
}

void Niveau6(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
blit_sentinelle(&lvl->senti3, ecran, var);
blit_sentinelle(&lvl->senti4, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(100, &lvl->senti1);
	vision_sys(200, &lvl->senti2);
	vision_sys(270, &lvl->senti3);
	vision_sys(350, &lvl->senti4);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, -10, 118, -15, 119);
	check_if_see(&lvl->senti2, perso, 109, 233, -15, 119);
	check_if_see(&lvl->senti3, perso, 177, 320, -15, 119);
	check_if_see(&lvl->senti4, perso, 323, 442, -15, 119);

	follow_the_line(var, perso, -20 , 45, 0);
	follow_the_line(var, perso, 45 , 56, -1);
	follow_the_line(var, perso, 56 , 92, 1);
	follow_the_line(var, perso, 92 , 120, -1);
	follow_the_line(var, perso, 120 , 193, 0);
	follow_the_line(var, perso, 193 , 204, -1);
	follow_the_line(var, perso, 204 , 284, 1);
	follow_the_line(var, perso, 284 , 344, -1);
	follow_the_line(var, perso, 344 , 358, 1);
	follow_the_line(var, perso, 358 , 377, -1);
	follow_the_line(var, perso, 377 , 480, 0);
	}

	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 155, mus);
	Paused(menu, var, mus, lvl, anim, ecran);
	cheat(var, lvl);
}

void Niveau5(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
blit_sentinelle(&lvl->senti3, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(50, &lvl->senti1);
	vision_sys(150, &lvl->senti2);
	vision_sys(230, &lvl->senti3);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, -10, 111, -15, 95);
	check_if_see(&lvl->senti2, perso, 158, 277, -15, 95);
	check_if_see(&lvl->senti3, perso, 271, 378, -15, 95);

	follow_the_line(var, perso, -20 , 19, 0);
	follow_the_line(var, perso, 19 , 41, 1);
	follow_the_line(var, perso, 41 , 73, -1);
	follow_the_line(var, perso, 73 , 133, 1);
	follow_the_line(var, perso, 133 , 163, -1);
	follow_the_line(var, perso, 163 , 193, 0);
	follow_the_line(var, perso, 193 , 299, -1);
	follow_the_line(var, perso, 299 , 402, 1);
	follow_the_line(var, perso, 402 , 424, -1);
	follow_the_line(var, perso, 424 , 480, 0);
	}

	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 119, mus);
	Paused(menu, var, mus, lvl, anim, ecran);
	cheat(var, lvl);
}

void Niveau4(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
blit_sentinelle(&lvl->senti3, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(15, &lvl->senti1);
	vision_sys(130, &lvl->senti2);
	vision_sys(30, &lvl->senti3);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, 58, 158, -15, 194);
	check_if_see(&lvl->senti2, perso, 160, 286, -15, 194);
	check_if_see(&lvl->senti3, perso, 274, 400, -15, 194);

	follow_the_line(var, perso, -20 , 8, 0);
	follow_the_line(var, perso, 8 , 26, -1);
	follow_the_line(var, perso, 26 , 38, 1);
	follow_the_line(var, perso, 38 , 192, -1);
	follow_the_line(var, perso, 192 , 222, 1);
	follow_the_line(var, perso, 222 , 240, -1);
	follow_the_line(var, perso, 240 , 266, 1);
	follow_the_line(var, perso, 266 , 290, 0);
	follow_the_line(var, perso, 290 , 336, 1);
	follow_the_line(var, perso, 336 , 378, 0);
	follow_the_line(var, perso, 378 , 398, 1);
	follow_the_line(var, perso, 398 , 480, 0);
	}

	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 95, mus);
	Paused(menu, var, mus, lvl, anim, ecran);
	cheat(var, lvl);
}

void Niveau3(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(15, &lvl->senti1);
	vision_sys(120, &lvl->senti2);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, 48, 192, -15, 117);
	check_if_see(&lvl->senti2, perso, 242, 343, -15, 117);

	follow_the_line(var, perso, -20 , 16, 0);
	follow_the_line(var, perso, 16 , 38, -1);
	follow_the_line(var, perso, 38 , 97, 1);
	follow_the_line(var, perso, 97 , 118, -1);
	follow_the_line(var, perso, 118 , 141, 1);
	follow_the_line(var, perso, 141 , 215, -1);
	follow_the_line(var, perso, 215 , 229, 1);
	follow_the_line(var, perso, 229 , 241, -1);
	follow_the_line(var, perso, 241 , 306, 0);
	follow_the_line(var, perso, 306 , 428, 1);
	follow_the_line(var, perso, 428 , 480, 0);
	}

	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 194, mus);

	Paused(menu, var, mus, lvl, anim, ecran);

	cheat(var, lvl);
}

void Niveau2(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
blit_sentinelle(&lvl->senti2, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	vision_sys(15, &lvl->senti1);
	vision_sys(120, &lvl->senti2);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, 36, 145, -10, 71);
	check_if_see(&lvl->senti2, perso, 245, 363, -10, 71);

	follow_the_line(var, perso, -20 , 84, 1);
	follow_the_line(var, perso, 84 , 110, -1);
	follow_the_line(var, perso, 110 , 171, 1);
	follow_the_line(var, perso, 171 , 204, -1);
	follow_the_line(var, perso, 204 , 232, 0);
	follow_the_line(var, perso, 232 , 252, -1);
	follow_the_line(var, perso, 252 , 268, 0);
	follow_the_line(var, perso, 268 , 284, -1);
	follow_the_line(var, perso, 284 , 324, 0);
	follow_the_line(var, perso, 324 , 376, -1);
	follow_the_line(var, perso, 376 , 400, 1);
	follow_the_line(var, perso, 400 , 480, 0);
	}

	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 117, mus);

	Paused(menu, var, mus, lvl, anim, ecran);

	cheat(var, lvl);
}

void Niveau1(Niveau *lvl, General *var, SDL_Surface *ecran, Anim *anim, Perso *perso, Menu *menu, Sons *mus)
{
Replace_position(lvl, perso);
SDL_BlitSurface(var->img_lvl,&lvl->bg.dim,ecran,&lvl->bg.pos);
blit_sentinelle(&lvl->senti1, ecran, var);
perso_anim(perso, ecran, var);
Blit_BarreEffet(var, menu, ecran);
intro_anim(perso, var, lvl, anim, ecran, mus);

	if((lvl->start == 1) && (lvl->perdu == 0) && (lvl->pause == 0))
	{
	check_malus(var, perso, anim, ecran);

	stop_cpu(var, perso, lvl);
		if(perso->cpu.en_mvt == 1) (perso->cpu.x++);

	check_if_see(&lvl->senti1, perso, 155, 295, 0, 173);

	vision_sys(20, &lvl->senti1);

	follow_the_line(var, perso, -20 , 16, 0);
	follow_the_line(var, perso, 16 , 41, -1);
	follow_the_line(var, perso, 41 , 73, 0);
	follow_the_line(var, perso, 73 , 89, 1);
	follow_the_line(var, perso, 89 , 158, -1);
	follow_the_line(var, perso, 158 , 187, 0);
	follow_the_line(var, perso, 187 , 224, 1);
	follow_the_line(var, perso, 224 , 294, 0);
	follow_the_line(var, perso, 294 , 309, -1);
	follow_the_line(var, perso, 309 , 332, 1);
	follow_the_line(var, perso, 332 , 410, -1);
	follow_the_line(var, perso, 410 , 480, 0);
	}
	check_who_win(var, perso, lvl, anim, ecran, menu, -15, 71, mus);

	Paused(menu, var, mus, lvl, anim, ecran);

	cheat(var, lvl);
}
