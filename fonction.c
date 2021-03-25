#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psppower.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <png.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include "struct.h"
#include "menu.h"
#include "fonction.h"

#define MENU 1
#define JEU 2

void saveImage(const char* filename)
{
	u32* vram32;
	u16* vram16;
	int bufferwidth;
	int pixelformat;
	int unknown;
	int i, x, y;
	png_structp png_ptr;
	png_infop info_ptr;
	FILE* fp;
	u8* line;

        fp = fopen(filename, "wb");
        if (!fp) return;
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr) return;
        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
                png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
                fclose(fp);
                return;
        }
        png_init_io(png_ptr, fp);
        png_set_IHDR(png_ptr, info_ptr, 480, 272,
                8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
        png_write_info(png_ptr, info_ptr);
        line = (u8*) malloc(480 * 3);
        sceDisplayWaitVblankStart();  
        sceDisplayGetFrameBuf((void**)&vram32, &bufferwidth, &pixelformat, &unknown);
        vram16 = (u16*) vram32;
        for (y = 0; y < 272; y++) {
                for (i = 0, x = 0; x < 480; x++) {
                        u32 color = 0;
                        u8 r = 0, g = 0, b = 0;
                        switch (pixelformat) {
                                case PSP_DISPLAY_PIXEL_FORMAT_565:
                                        color = vram16[x + y * bufferwidth];
                                        r = (color & 0x1f) << 3;
                                        g = ((color >> 5) & 0x3f) << 2 ;
                                        b = ((color >> 11) & 0x1f) << 3 ;
                                        break;
                                case PSP_DISPLAY_PIXEL_FORMAT_5551:
                                        color = vram16[x + y * bufferwidth];
                                        r = (color & 0x1f) << 3;
                                        g = ((color >> 5) & 0x1f) << 3 ;
                                        b = ((color >> 10) & 0x1f) << 3 ;
                                        break;
                                case PSP_DISPLAY_PIXEL_FORMAT_4444:
                                        color = vram16[x + y * bufferwidth];
                                        r = (color & 0xf) << 4;
                                        g = ((color >> 4) & 0xf) << 4 ;
                                        b = ((color >> 8) & 0xf) << 4 ;
                                        break;
                                case PSP_DISPLAY_PIXEL_FORMAT_8888:
                                        color = vram32[x + y * bufferwidth];
                                        r = color & 0xff;
                                        g = (color >> 8) & 0xff;
                                        b = (color >> 16) & 0xff;
                                        break;
                        }
                        line[i++] = r;
                        line[i++] = g;
                        line[i++] = b;
                }
                png_write_row(png_ptr, line);
        }
        free(line);
        png_write_end(png_ptr, info_ptr);
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(fp);
}

void screenshot()
{
char savescreenshot[100] = "";
int i = 0;
FILE *testing_file;
DIR *folder;

	if ((folder = opendir("ms0:/PICTURE/Awaker/"))==NULL)
	{
	mkdir("ms0:/PICTURE/Awaker/",0775);
	closedir(folder);
	}
	else closedir(folder);

	for(i=0;i<1000;i++)
	{
	sprintf(savescreenshot,"ms0:/PICTURE/Awaker/%d.png",i);
		if ((testing_file = fopen(savescreenshot, "r+"))==NULL)
		{
		saveImage(savescreenshot);
		fclose(testing_file);
		break;
		}
		else fclose(testing_file);
	}
}

void Blit_Matrix_Effet(General *var, SDL_Surface *ecran)
{
var->affich_pluie = 0;
	for(var->i=0;var->i<=95;var->i++)
	{
	var->matrix[var->i].y+=2;
		if (var->matrix[var->i].y >=268) (var->matrix[var->i].y = -5);
	var->matrix[var->i].pos.y = var->matrix[var->i].y;
	SDL_BlitSurface(var->img_lvl, &var->matrix[var->i].dim, ecran , &var->matrix[var->i].pos);
	}
	var->matrix[0].y++; var->matrix[4].y++; var->matrix[8].y++; var->matrix[14].y++;
	var->matrix[19].y++; var->matrix[22].y++; var->matrix[27].y++; var->matrix[30].y++;
	var->matrix[35].y++; var->matrix[39].y++; var->matrix[42].y++; var->matrix[46].y++;
	var->matrix[50].y++; var->matrix[55].y++; var->matrix[58].y++; var->matrix[64].y++;
	var->matrix[69].y++; var->matrix[73].y++; var->matrix[79].y++; var->matrix[83].y++;
	var->matrix[89].y++; var->matrix[92].y++; var->matrix[94].y++;
	var->matrix[11].y++; var->matrix[25].y++; var->matrix[61].y++;
}

void save_unlock(General *var)
{
	var->file = fopen("data/dat.dat","w+");
	fprintf(var->file, "%d", var->unlock);
	fclose(var->file);
}

void Blit_BarreEffet(General *var, Menu *menu, SDL_Surface *ecran)
{
	if(var->barre[0].y >=240) (var->switch_barre[0] = 0);
	else if(var->barre[0].y <=-5) (var->switch_barre[0] = 1);
	if(var->barre[1].y >=255) (var->switch_barre[1] = 0);
	else if(var->barre[1].y <=-5) (var->switch_barre[1] = 1);
	if(var->barre[2].y >=270) (var->switch_barre[2] = 0);
	else if(var->barre[2].y <=-5) (var->switch_barre[2] = 1);

	if(var->switch_barre[0] == 1) (var->barre[0].y++);
	else if(var->switch_barre[0] == 0) (var->barre[0].y--);
	if(var->switch_barre[1] == 1) (var->barre[1].y++);
	else if(var->switch_barre[1] == 0) (var->barre[1].y--);
	if(var->switch_barre[2] == 1) (var->barre[2].y+=2);
	else if(var->switch_barre[2] == 0) (var->barre[2].y-=2);

	var->barre[0].pos.x = var->barre[0].x; var->barre[1].pos.x = var->barre[1].x;
	var->barre[0].pos.y = var->barre[0].y; var->barre[1].pos.y = var->barre[1].y;
	var->barre[2].pos.x = var->barre[2].x;
	var->barre[2].pos.y = var->barre[2].y;
	SDL_BlitSurface(var->img_lvl, &var->barre[0].dim, ecran , &var->barre[0].pos);
	SDL_BlitSurface(var->img_lvl, &var->barre[1].dim, ecran , &var->barre[1].pos);
	SDL_BlitSurface(var->img_lvl, &var->barre[2].dim, ecran , &var->barre[2].pos);
	printf("pouet\n");
}

void Blit_Pluie(General *var, Anim *anim, SDL_Surface *ecran)
{
	if((var->pad.Buttons & PSP_CTRL_RTRIGGER) && (var->appuis == 0))
	{
		if(var->affich_pluie == 1) (var->affich_pluie = 0);
		else if(var->affich_pluie == 0) (var->affich_pluie = 1);
	}

	if(var->affich_pluie == 1)
	{
		for(var->i=0;var->i<=46;var->i++)
		{
		var->pluie[var->i].y++;
			if (var->pluie[var->i].y >=272) (var->pluie[var->i].y = -6);
		var->pluie[var->i].pos.y = var->pluie[var->i].y;
		SDL_BlitSurface(anim->img, &var->pluie[var->i].dim, ecran , &var->pluie[var->i].pos);
		}
	var->pluie[5].y++;
	var->pluie[16].y++;
	var->pluie[21].y++;
	var->pluie[35].y++;
	var->pluie[42].y++;;
	var->pluie[28].y++;
	var->pluie[1].y++;
	var->pluie[12].y++;
	var->pluie[25].y++;
	var->pluie[45].y++;
	var->pluie[30].y++;
	var->pluie[10].y++;
	var->pluie[40].y++;
	}
}

void PlayWav(Mix_Chunk *wav, int *joue)
{
	if((*joue)==0)
	{
	Mix_PlayChannel(-1,wav,0);
	(*joue) = 1;
	}
}

void Paused(Menu *menu, General *var, Sons *mus, Niveau *lvl, Anim *anim, SDL_Surface *ecran)
{
	if((var->pad.Buttons & PSP_CTRL_START) && (var->appuis == 0) && (lvl->perdu != 1) && (lvl->start == 1))
	{
		if(lvl->pause==0)
		{
		Mix_PauseMusic();
		lvl->pause=1;
		PlayWav(mus->pause, &mus->joue[7]);
		}
		else if(lvl->pause==1)
		{
		Mix_ResumeMusic();
		lvl->pause=0;
		mus->joue[7] = 0;
		}
	}

	if (lvl->pause == 1)
	{
	SDL_BlitSurface(anim->img, &anim->pause.dim,ecran,&anim->pause.pos);
		if((var->pad.Buttons & PSP_CTRL_SELECT) && (var->appuis == 0))
		{
		Mix_ResumeMusic();
		var->fenetre = MENU;
		var->niveau = 1;
		}
	}
}

void PlayedSong_Init(Sons *mus)
{
	mus->joue[0] = 0;mus->joue[1] = 0;mus->joue[2] = 0;mus->joue[3] = 0;mus->joue[4] = 0;
	mus->joue[5] = 0;mus->joue[6] = 0;mus->joue[7] = 0;mus->joue[8] = 0;mus->joue[9] = 0;
	mus->joue[10] = 0;
}
void Sons_Init(Sons *mus)
{
	mus->music = Mix_LoadMUS("data/music/music.ogg");
	mus->awaker = Mix_LoadWAV("data/music/awaker.wav");
	mus->gameover = Mix_LoadWAV("data/music/gameover.wav");
	mus->un = Mix_LoadWAV("data/music/1.wav");
	mus->deux = Mix_LoadWAV("data/music/2.wav");
	mus->trois = Mix_LoadWAV("data/music/3.wav");
	mus->start = Mix_LoadWAV("data/music/start.wav");
	mus->earlystart = Mix_LoadWAV("data/music/earlystart.wav");
	printf("OK\n\n");
	mus->pause = Mix_LoadWAV("data/music/pause.wav");
	mus->win = Mix_LoadWAV("data/music/levelwin.wav");
	PlayedSong_Init(mus);
}

void cheat(General *var, Niveau *lvl)
{
	if((var->pad.Buttons & PSP_CTRL_TRIANGLE) && (var->appuis == 0)) (lvl->perdu = -1);
}

void stop_cpu(General *var, Perso *perso, Niveau *lvl)
{
	if(perso->cpu.x == 0)
	{
		if(var->difficulte == 0) (perso->cpu.intelligent_arret = (0) + ((float) rand() / RAND_MAX * (1 - (0) + 1)));
		else if(var->difficulte == 1) (perso->cpu.intelligent_arret = (-3) + ((float) rand() / RAND_MAX * (1 - (-3) + 1)));
	}
	if(perso->cpu.intelligent_arret <=0) (perso->cpu.intelligent_arret = 0);

	if(((lvl->senti1.active >= 1) && (perso->cpu.x >= lvl->senti1.vision.x - 15) && (perso->cpu.x <= lvl->senti1.vision.x + lvl->senti1.vision.dim.w-30)) || ((lvl->senti2.active >= 1) && (perso->cpu.x >= lvl->senti2.vision.x - 15) && (perso->cpu.x <= lvl->senti2.vision.x + lvl->senti2.vision.dim.w-30)) || ((lvl->senti3.active >= 1) && (perso->cpu.x >= lvl->senti3.vision.x - 15) && (perso->cpu.x <= lvl->senti3.vision.x + lvl->senti3.vision.dim.w-30)) || ((lvl->senti4.active >= 1) && (perso->cpu.x >= lvl->senti4.vision.x - 15) && (perso->cpu.x <= lvl->senti4.vision.x + lvl->senti4.vision.dim.w-30)) || ((lvl->senti5.active >= 1) && (perso->cpu.x >= lvl->senti5.vision.x - 15) && (perso->cpu.x <= lvl->senti5.vision.x + lvl->senti5.vision.dim.w-30)))
	{
	perso->cpu.en_mvt = perso->cpu.intelligent_arret;
	}
	else (perso->cpu.en_mvt = 1);

}

void check_who_win(General *var, Perso *perso, Niveau *lvl, Anim *anim, SDL_Surface *ecran, Menu *menu, int X, int Y, Sons *mus)
{
	if(lvl->perdu == 0)
	{
		if(perso->joueur.x >= 437) (lvl->perdu = -1);
		else if (perso->cpu.x >= 437) (lvl->perdu = 1);
	}
	else if(lvl->perdu == -1)
	{
	PlayWav(mus->win, &mus->joue[8]);
	SDL_BlitSurface(anim->img,&anim->lvl_win.dim,ecran,&anim->lvl_win.pos);
		if((var->pad.Buttons & PSP_CTRL_CROSS) && (var->appuis == 0))
		{
		Anim_Init(anim);
		Perso_Init(perso,X,Y);
		var->niveau++;
		PlayedSong_Init(mus);
		}
	}
	else if(lvl->perdu == 1)
	{
	PlayWav(mus->gameover, &mus->joue[1]);
	SDL_BlitSurface(anim->img,&anim->gameover.dim,ecran,&anim->gameover.pos);
		if((var->pad.Buttons & PSP_CTRL_START) && (var->appuis == 0))
		{
		Menu_Init(menu);
		Perso_Init(perso,0,173);
		General_Init(var);
		Anim_Init(anim);
		var->fenetre = MENU;
		PlayedSong_Init(mus);
		}
	}
}

void vision_sys(int i, Sentinelle *senti)
{
	if (senti->counter >= 0) (senti->counter++);
	else if(senti->counter < 0) (senti->counter=0);

	if((senti->counter >= 5+i) && (senti->counter < 10+i)) (senti->active=1);
	else if((senti->counter >= 10+i) && (senti->counter < 15+i)) (senti->active=2);
	else if((senti->counter >= 15+i) && (senti->counter < 20+i)) (senti->active=1);
	else if((senti->counter >= 20+i) && (senti->counter < 25+i)) (senti->active=2);
	else if((senti->counter >= 25+i) && (senti->counter < 30+i)) (senti->active=1);
	else if((senti->counter >= 30+i) && (senti->counter < 35+i)) (senti->active=2);
	else if((senti->counter >= 35+i) && (senti->counter < 40+i)) (senti->active=1);
	else if((senti->counter >= 40+i) && (senti->counter < 45+i)) (senti->active=2);
	else if((senti->counter >= 45+i) && (senti->counter < 50+i)) (senti->active=1);
	else if((senti->counter >= 50+i) && (senti->counter < 55+i)) (senti->active=2);
	else if((senti->counter >= 55+i) && (senti->counter < 60+i)) (senti->active=1);
	else if((senti->counter >= 60+i) && (senti->counter < 65+i)) (senti->active=2);
	else if((senti->counter >= 65+i) && (senti->counter < 70+i)) (senti->active=1);
	else if((senti->counter >= 70+i) && (senti->counter < 75+i)) (senti->active=2);
	else if((senti->counter >= 75+i) && (senti->counter < 80+i)) (senti->active=1);
	else if((senti->counter >= 80+i) && (senti->counter < 85+i)) (senti->active=2);
	else if((senti->counter >= 85+i) && (senti->counter < 90+i)) (senti->active=1);
	else if((senti->counter >= 90+i) &&  (senti->counter < 175+i)) (senti->active = 3);
	else if(senti->counter >= 175+i) (senti->active = 0);
	if(senti->counter >= 250+i) (senti->counter = -20);
}

void check_if_see(Sentinelle *senti, Perso *perso, int Xmin, int Xmax, int origine_X, int origine_Y)
{
	if(senti->active==3)
	{
		if((perso->cpu.en_mvt == 1) && (perso->cpu.x >= Xmin) && (perso->cpu.x <= Xmax))
		{
		perso->cpu.x = origine_X;
		perso->cpu.y = origine_Y-1;
		}
		if((perso->joueur.en_mvt == 1) && (perso->joueur.x >= Xmin) && (perso->joueur.x <= Xmax))
		{
		perso->joueur.x = origine_X;
		perso->joueur.y = origine_Y;
		}
	}
}

void blit_sentinelle(Sentinelle *senti, SDL_Surface *ecran, General *var)
{
	SDL_BlitSurface(var->img_lvl,&senti->baton.dim,ecran,&senti->baton.pos);
	if(senti->active!=3) SDL_BlitSurface(var->img_lvl,&senti->boules.dim,ecran,&senti->boules.pos);

	if(senti->active==0) (senti->boules.dim.x = 512);
	else if(senti->active==1) (senti->boules.dim.x = 563);
	else if(senti->active==2) (senti->boules.dim.x = 614);
	else if(senti->active==3) (SDL_BlitSurface(var->img_lvl,&senti->vision.dim,ecran,&senti->vision.pos));
}

void follow_the_line(General *var, Perso *perso, int Xmin , int Xmax, int UporDown)
{
	if(perso->mallus == 0)
	{
		if((var->pad.Buttons & PSP_CTRL_RIGHT) || (var->pad.Lx > 190))
		{
			if((perso->joueur.pos.x >= Xmin) && (perso->joueur.pos.x >= Xmin) && (perso->joueur.pos.x < Xmax))
			{
			perso->joueur.y += UporDown;
			}
		}
		if((var->difficulte == 1) && (UporDown == 1) && (perso->joueur.pos.x >= Xmin) && (perso->joueur.pos.x < Xmax) && (!var->pad.Buttons) && (var->pad.Lx < 190))
		{
		perso->joueur.y+=1;
		perso->joueur.x+=1;
		perso->joueur.en_mvt = 1;
		}
		if(((var->difficulte == 1) && (UporDown != 1) && (perso->joueur.pos.x >= Xmin) && (perso->joueur.pos.x < Xmax)) || ((!var->pad.Buttons) && (var->difficulte ==0)))
		{
		perso->joueur.en_mvt = 0;
		}
	}
	if((perso->cpu.pos.x >= Xmin) && (perso->cpu.pos.x < Xmax) && (perso->cpu.en_mvt == 1))
	{
	perso->cpu.y += UporDown;
	}
}

void check_malus(General *var, Perso *perso, Anim *anim, SDL_Surface *ecran)
{
	if(perso->mallus==1)
	{
	SDL_BlitSurface(anim->img, &anim->comptage.dim,ecran,&anim->comptage.pos);
	anim->comptage.dim.y = 131;
	anim->comptage.dim.x = 3*345;
	perso->mallus_time1++;
		if (perso->mallus_time1 >= 100)
		{
		perso->mallus = 0;
		perso->mallus_time1 = 0;
		}
	}
	if(((var->pad.Buttons & PSP_CTRL_RIGHT) || (var->pad.Lx >=190)) && (perso->mallus == 0))
	{
	perso->joueur.x++;
	perso->joueur.en_mvt = 1;
	}
}

void Replace_position(Niveau *lvl, Perso *perso)
{

	if(perso->joueur.x > 452) (perso->joueur.x = 452);
	if(perso->cpu.x > 452) (perso->cpu.x = 452);

	perso->joueur.pos.x = perso->joueur.x;
	perso->joueur.pos.y = perso->joueur.y;
	perso->cpu.pos.x = perso->cpu.x;
	perso->cpu.pos.y = perso->cpu.y;

	lvl->senti1.baton.pos.x = lvl->senti1.baton.x;
	lvl->senti1.baton.pos.y = lvl->senti1.baton.y;
	lvl->senti1.vision.pos.x = lvl->senti1.vision.x;
	lvl->senti1.vision.pos.y = lvl->senti1.vision.y;
	lvl->senti1.boules.pos.x = lvl->senti1.boules.x;
	lvl->senti1.boules.pos.y = lvl->senti1.boules.y;
	lvl->senti1.vision.pos.x = lvl->senti1.vision.x;
	lvl->senti1.vision.pos.y = lvl->senti1.vision.y;

	lvl->senti2.baton.pos.x = lvl->senti2.baton.x;
	lvl->senti2.baton.pos.y = lvl->senti2.baton.y;
	lvl->senti2.vision.pos.x = lvl->senti2.vision.x;
	lvl->senti2.vision.pos.y = lvl->senti2.vision.y;
	lvl->senti2.boules.pos.x = lvl->senti2.boules.x;
	lvl->senti2.boules.pos.y = lvl->senti2.boules.y;
	lvl->senti2.vision.pos.x = lvl->senti2.vision.x;
	lvl->senti2.vision.pos.y = lvl->senti2.vision.y;

	lvl->senti3.baton.pos.x = lvl->senti3.baton.x;
	lvl->senti3.baton.pos.y = lvl->senti3.baton.y;
	lvl->senti3.vision.pos.x = lvl->senti3.vision.x;
	lvl->senti3.vision.pos.y = lvl->senti3.vision.y;
	lvl->senti3.boules.pos.x = lvl->senti3.boules.x;
	lvl->senti3.boules.pos.y = lvl->senti3.boules.y;
	lvl->senti3.vision.pos.x = lvl->senti3.vision.x;
	lvl->senti3.vision.pos.y = lvl->senti3.vision.y;

	lvl->senti4.baton.pos.x = lvl->senti4.baton.x;
	lvl->senti4.baton.pos.y = lvl->senti4.baton.y;
	lvl->senti4.vision.pos.x = lvl->senti4.vision.x;
	lvl->senti4.vision.pos.y = lvl->senti4.vision.y;
	lvl->senti4.boules.pos.x = lvl->senti4.boules.x;
	lvl->senti4.boules.pos.y = lvl->senti4.boules.y;
	lvl->senti4.vision.pos.x = lvl->senti4.vision.x;
	lvl->senti4.vision.pos.y = lvl->senti4.vision.y;

	lvl->senti5.baton.pos.x = lvl->senti5.baton.x;
	lvl->senti5.baton.pos.y = lvl->senti5.baton.y;
	lvl->senti5.vision.pos.x = lvl->senti5.vision.x;
	lvl->senti5.vision.pos.y = lvl->senti5.vision.y;
	lvl->senti5.boules.pos.x = lvl->senti5.boules.x;
	lvl->senti5.boules.pos.y = lvl->senti5.boules.y;
	lvl->senti5.vision.pos.x = lvl->senti5.vision.x;
	lvl->senti5.vision.pos.y = lvl->senti5.vision.y;
}

void perso_anim(Perso *perso, SDL_Surface *ecran, General *var)
{

	if(var->niveau <=9) (perso->cpu.dim.y = 50 * var->niveau);
	else if(var->niveau <=11) (perso->cpu.dim.y = 100);
SDL_BlitSurface(perso->img, &perso->cpu.dim, ecran, &perso->cpu.pos);
SDL_BlitSurface(perso->img, &perso->joueur.dim, ecran, &perso->joueur.pos);
perso->anim++;
	if(perso->anim > 15) (perso->anim=0);
perso->cpu.dim.x = perso->anim * 51;
perso->joueur.dim.x = perso->anim * 51;
}

void intro_anim(Perso *perso, General *var, Niveau *lvl1, Anim *anim, SDL_Surface *ecran, Sons *mus)
{
	if(lvl1->start == 0)
	{
		if (anim->active_comptage == 0)
		{
			if(anim->bande[14].dim.h <=0)
			{
			anim->i = 0;
				if(var->niveau !=10) (anim->active_comptage = 1);
				else if(var->niveau==10) (lvl1->start = 1);
			}
			if (anim->i >= 22)
			{
			anim->comptage.dim.x = 2*345;
			}
			for(anim->i=0;anim->i<=23;anim->i++)
			{
			SDL_BlitSurface(anim->img,&anim->bande[anim->i].dim,ecran,&anim->bande[anim->i].pos);
				if ((anim->active_bande == anim->i) && (anim->bande[anim->i].dim.h > 0)) anim->bande[anim->i].dim.h-=2;
				if(anim->bande[anim->i].dim.h <=0) (anim->active_bande = anim->i+1);
			}
		}
		else if (anim->active_comptage == 1)
		{
		SDL_BlitSurface(anim->img, &anim->comptage.dim,ecran,&anim->comptage.pos);
		anim->i++;
			if(anim->i>=280) lvl1->start = 1;
			if(perso->mallus == 0)
			{
				if(anim->i<70)
				{
				anim->comptage.dim.x = 2*345;
				PlayWav(mus->trois, &mus->joue[2]);
				}
				else if((anim->i>=70) && (anim->i<140))
				{
				anim->comptage.dim.x = 345;
				PlayWav(mus->deux, &mus->joue[3]);
				}
				else if((anim->i>=140) && (anim->i<210))
				{
				anim->comptage.dim.x = 0;
				PlayWav(mus->un, &mus->joue[4]);
				}
				else if((anim->i>=210) && (anim->i<280))
				{
				anim->comptage.dim.x = 3*345;
				PlayWav(mus->start, &mus->joue[5]);
				}
			}
			else if (perso->mallus == 1)
			{
			PlayWav(mus->earlystart, &mus->joue[6]);
			anim->comptage.dim.y = 131;
			anim->comptage.dim.x = 3*345;
			}
			if((var->pad.Buttons & PSP_CTRL_RIGHT) && (var->appuis == 0)) (perso->mallus = 1);
		}
		
	}
}

void Perso_Init(Perso *perso, int X, int Y)
{
	perso->vitesse = 1;
	perso->anim = 0;
	perso->mallus = 0;
	perso->mallus_time1 = 0;

	perso->joueur.x = X;
	perso->joueur.y = Y;
	perso->joueur.pos.x = 0;
	perso->joueur.dim.x = 0;
	perso->joueur.dim.y = 0;
	perso->joueur.dim.w = 51;
	perso->joueur.dim.h = 50;
	perso->joueur.en_mvt = 0;

	perso->cpu.x = X;
	perso->cpu.y = Y-5;
	perso->cpu.pos.x = 0;
	perso->cpu.pos.y = 168;
	perso->cpu.dim.x = 0;
	perso->cpu.dim.y = 50;
	perso->cpu.dim.w = 51;
	perso->cpu.dim.h = 50;
	perso->cpu.en_mvt = 1;
	perso->cpu.intelligent_arret = 0;
}

void Anim_Init(Anim *anim)
{
	for(anim->i=0;anim->i<24;anim->i++)
	{
	anim->bande[anim->i].pos.x = 0;
	anim->bande[anim->i].pos.y = anim->i*20;
	anim->bande[anim->i].dim.x = 0;
	anim->bande[anim->i].dim.y = 262;
	anim->bande[anim->i].dim.w = 480;
	anim->bande[anim->i].dim.h = 20;
	}
	anim->gameover.pos.x = 62;
	anim->gameover.pos.y = 71;
	anim->gameover.dim.x = 690;
	anim->gameover.dim.y = 131;
	anim->gameover.dim.w = 345;
	anim->gameover.dim.h = 131;

	anim->lvl_win.pos.x = 62;
	anim->lvl_win.pos.y = 71;
	anim->lvl_win.dim.x = 345;
	anim->lvl_win.dim.y = 131;
	anim->lvl_win.dim.w = 345;
	anim->lvl_win.dim.h = 131;

	anim->comptage.pos.x = 62;
	anim->comptage.pos.y = 71;
	anim->comptage.dim.x = 0;
	anim->comptage.dim.y = 0;
	anim->comptage.dim.w = 345;
	anim->comptage.dim.h = 131;

	anim->pause.pos.x = 62;
	anim->pause.pos.y = 71;
	anim->pause.dim.x = 0;
	anim->pause.dim.y =131;
	anim->pause.dim.w = 345;
	anim->pause.dim.h = 120;

	anim->active_bande = 0;
	anim->active_comptage = 0;
	anim->i = 0;
}

void Matrix_Init(General *var)
{

	var->matrix[0].y = 0; var->matrix[1].y = 100; var->matrix[2].y = 50; var->matrix[3].y = 250; 
	var->matrix[4].y = 25; var->matrix[5].y = 75; var->matrix[6].y = 150; var->matrix[7].y = 10; 
	var->matrix[8].y = 210; var->matrix[9].y = 35; var->matrix[10].y = 110; var->matrix[11].y = 190; 
	var->matrix[12].y = 59; var->matrix[13].y = 1; var->matrix[14].y = 236; var->matrix[15].y = 9; 
	var->matrix[16].y = 73; var->matrix[17].y = 126; var->matrix[18].y = 111; var->matrix[19].y = 19; 
	var->matrix[20].y = 90; var->matrix[21].y = 199; var->matrix[22].y = 170; var->matrix[23].y = 102; 
	var->matrix[24].y = 209; var->matrix[25].y = 260; var->matrix[26].y = 145;var->matrix[27].y = 112; 
	var->matrix[28].y = 0; var->matrix[29].y = 15; var->matrix[30].y = 245; var->matrix[31].y = 36; 
	var->matrix[32].y = 189; var->matrix[33].y = 201; var->matrix[34].y = 81; var->matrix[35].y = 129; 
	var->matrix[36].y = 68; var->matrix[37].y = 220; var->matrix[38].y = 34; var->matrix[39].y = 9; 
	var->matrix[40].y = 107; var->matrix[41].y = 199; var->matrix[42].y = 260;var->matrix[43].y = 135; 
	var->matrix[44].y = 10; var->matrix[45].y = 246; var->matrix[46].y = 192; var->matrix[47].y = 39; 
	var->matrix[48].y = 58; var->matrix[49].y = 174; var->matrix[50].y = 236; var->matrix[51].y = 142; 
	var->matrix[52].y = 98; var->matrix[53].y = 1; var->matrix[54].y = 9; var->matrix[55].y = 104; 
	var->matrix[56].y = 123; var->matrix[57].y = 214; var->matrix[58].y = 257;var->matrix[59].y = 233; 
	var->matrix[60].y = 115; var->matrix[61].y = 0; var->matrix[62].y = 17; var->matrix[63].y = 50; 
	var->matrix[64].y = 150; var->matrix[65].y = 137; var->matrix[66].y = 197; var->matrix[67].y = 6; 
	var->matrix[68].y = 76; var->matrix[69].y = 200; var->matrix[70].y = 250; var->matrix[71].y = 37; 
	var->matrix[72].y = 86; var->matrix[73].y = 100; var->matrix[74].y = 185; var->matrix[75].y = 214; 
	var->matrix[76].y = 200; var->matrix[77].y = 145; var->matrix[78].y = 245; var->matrix[79].y = 49; 
	var->matrix[80].y = 0; var->matrix[81].y = 28; var->matrix[82].y = 157; var->matrix[83].y = 260; 
	var->matrix[84].y = 124; var->matrix[85].y = 5; var->matrix[86].y = 68; var->matrix[87].y = 0; 
	var->matrix[88].y = 150; var->matrix[89].y = 213; var->matrix[90].y = 13; var->matrix[91].y = 100;
	var->matrix[92].y = 74; var->matrix[93].y = 15; var->matrix[94].y = 241; var->matrix[95].y = 154;

	var->matrix[0].dim.x = 480; var->matrix[1].dim.x = 480; var->matrix[2].dim.x = 487;
	var->matrix[3].dim.x = 480; var->matrix[4].dim.x = 487; var->matrix[5].dim.x = 487;
	var->matrix[6].dim.x = 487; var->matrix[7].dim.x = 480; var->matrix[8].dim.x = 487;
	var->matrix[9].dim.x = 480; var->matrix[10].dim.x = 480; var->matrix[11].dim.x = 480;
	var->matrix[12].dim.x = 487; var->matrix[13].dim.x = 487; var->matrix[14].dim.x = 487;
	var->matrix[15].dim.x = 480; var->matrix[16].dim.x = 480; var->matrix[17].dim.x = 487;
	var->matrix[18].dim.x = 487; var->matrix[19].dim.x = 480; var->matrix[20].dim.x = 487;
	var->matrix[21].dim.x = 480; var->matrix[22].dim.x = 487; var->matrix[23].dim.x = 480;
	var->matrix[24].dim.x = 487; var->matrix[25].dim.x = 487; var->matrix[26].dim.x = 480;
	var->matrix[27].dim.x = 480; var->matrix[28].dim.x = 480; var->matrix[29].dim.x = 480;
	var->matrix[30].dim.x = 487; var->matrix[31].dim.x = 480; var->matrix[32].dim.x = 480;
	var->matrix[33].dim.x = 487; var->matrix[34].dim.x = 487; var->matrix[35].dim.x = 480;
	var->matrix[36].dim.x = 487; var->matrix[37].dim.x = 480; var->matrix[38].dim.x = 487;
	var->matrix[39].dim.x = 487; var->matrix[40].dim.x = 487; var->matrix[41].dim.x = 487;
	var->matrix[42].dim.x = 480; var->matrix[43].dim.x = 487; var->matrix[44].dim.x = 487;
	var->matrix[45].dim.x = 487; var->matrix[46].dim.x = 480; var->matrix[47].dim.x = 480;
	var->matrix[48].dim.x = 487; var->matrix[49].dim.x = 480; var->matrix[50].dim.x = 480;
	var->matrix[51].dim.x = 480; var->matrix[52].dim.x = 487; var->matrix[53].dim.x = 480;
	var->matrix[54].dim.x = 480; var->matrix[55].dim.x = 487; var->matrix[56].dim.x = 487;
	var->matrix[57].dim.x = 487; var->matrix[58].dim.x = 480; var->matrix[59].dim.x = 487;
	var->matrix[60].dim.x = 487; var->matrix[61].dim.x = 480; var->matrix[62].dim.x = 487;
	var->matrix[63].dim.x = 480; var->matrix[64].dim.x = 487; var->matrix[65].dim.x = 480;
	var->matrix[66].dim.x = 480; var->matrix[67].dim.x = 487; var->matrix[68].dim.x = 480;
	var->matrix[69].dim.x = 480; var->matrix[70].dim.x = 480; var->matrix[71].dim.x = 487;
	var->matrix[72].dim.x = 487; var->matrix[73].dim.x = 487; var->matrix[74].dim.x = 487;
	var->matrix[75].dim.x = 480; var->matrix[76].dim.x = 480; var->matrix[77].dim.x = 487;
	var->matrix[78].dim.x = 480; var->matrix[79].dim.x = 487; var->matrix[80].dim.x = 480;
	var->matrix[81].dim.x = 487; var->matrix[82].dim.x = 487; var->matrix[83].dim.x = 480;
	var->matrix[84].dim.x = 487; var->matrix[85].dim.x = 480; var->matrix[86].dim.x = 487;
	var->matrix[87].dim.x = 480; var->matrix[88].dim.x = 487; var->matrix[89].dim.x = 487;
	var->matrix[90].dim.x = 480; var->matrix[91].dim.x = 487; var->matrix[92].dim.x = 487;
	var->matrix[93].dim.x = 487; var->matrix[94].dim.x = 480; var->matrix[95].dim.x = 480;

	for(var->i=0;var->i<=40;var->i++)
	{
	var->matrix[var->i].dim.w = 7;
	var->matrix[var->i].dim.y = 3255; var->matrix[var->i].dim.h = 9;
	var->matrix[var->i].x = var->i * 5;
	var->matrix[var->i].pos.x = var->matrix[var->i].x;
	var->matrix[var->i].pos.y = var->matrix[var->i].y;
	}

	for(var->i=41;var->i<=95;var->i++)
	{
	var->matrix[var->i].dim.w = 7;
	var->matrix[var->i].dim.y = 3255; var->matrix[var->i].dim.h = 9;
	var->matrix[var->i].x = var->i * 5;
	var->matrix[var->i].pos.x = var->matrix[var->i].x;
	var->matrix[var->i].pos.y = var->matrix[var->i].y;
	}

}

void General_Init(General *var)
{
	var->difficulte = 0;
	var->fenetre = 1;
	var->pause = 0;
	var->appuis = 0;
	var->niveau = 0;
	var->affich_pluie = 0;
	var->pluie[0].y = 10; var->pluie[1].y = 272; var->pluie[2].y = 150; var->pluie[3].y = 190;
	var->pluie[4].y = 231; var->pluie[5].y = 90; var->pluie[6].y = 50; var->pluie[7].y = 222;
	var->pluie[8].y = 0; var->pluie[9].y = 105; var->pluie[10].y = 58; var->pluie[11].y = 124;
	var->pluie[12].y = 207; var->pluie[13].y = 10; var->pluie[14].y = 80; var->pluie[15].y = 69;
	var->pluie[16].y = 159; var->pluie[17].y = 41; var->pluie[18].y = 125; var->pluie[19].y = 190;
	var->pluie[20].y = 9; var->pluie[21].y = 110; var->pluie[22].y = 2; var->pluie[23].y = 105;
	var->pluie[24].y = 180; var->pluie[25].y = 53; var->pluie[26].y = 17; var->pluie[27].y = 0;
	var->pluie[28].y = 240; var->pluie[29].y = 170; var->pluie[30].y = 145; var->pluie[31].y = 222;
	var->pluie[32].y = 7; var->pluie[33].y = 58; var->pluie[34].y = 21; var->pluie[35].y = 151;
	var->pluie[36].y = 270; var->pluie[37].y = 8; var->pluie[38].y = 218; var->pluie[39].y = 161;
	var->pluie[40].y = 13;	var->pluie[41].y = 436; var->pluie[42].y = 40; var->pluie[43].y = 211;
	var->pluie[44].y = 206; var->pluie[45].y = 0; var->pluie[46].y = 151;

	for(var->i = 0; var->i<=46;var->i++)
	{
	var->pluie[var->i].dim.x = 480;
	var->pluie[var->i].dim.y = 262;
	var->pluie[var->i].dim.w = 9;
	var->pluie[var->i].dim.h = 9;
	var->pluie[var->i].x = var->i*10;
	var->pluie[var->i].pos.x = var->pluie[var->i].x;
	var->pluie[var->i].pos.y = var->pluie[var->i].y;
	}
	for(var->i = 0; var->i <= 2; var->i++)
	{
	var->barre[var->i].x = 0;
	var->barre[var->i].pos.x = var->barre[var->i].x;
	var->barre[var->i].pos.y = var->barre[var->i].y;
	var->barre[var->i].dim.x = 0;
	}
	var->barre[0].y = -7; var->barre[1].y = 272; var->barre[2].y = 100;
	var->barre[0].dim.y = 3264; var->barre[1].dim.y = 3321; var->barre[2].dim.y = 3358;
	var->barre[0].dim.w = 480; var->barre[1].dim.w = 480; var->barre[2].dim.w = 480;
	var->barre[0].dim.h = 57; var->barre[1].dim.h = 37; var->barre[2].dim.h = 24;
	var->switch_barre[0] = 1; var->switch_barre[1] = 1; var->switch_barre[2] = 1;

	Matrix_Init(var);
}

void Init_baton(Sentinelle *senti, int A, int B)
{
	senti->baton.x = A;
	senti->baton.y = B;
	senti->baton.pos.x = senti->baton.x;
	senti->baton.pos.y = senti->baton.y;
	senti->baton.dim.x = 480;
	senti->baton.dim.y = 216;
	senti->baton.dim.w = 32;
	senti->baton.dim.h = 56;
}

void Init_boule(Sentinelle *senti)
{
	senti->boules.x = senti->baton.pos.x - 9;
	senti->boules.y = senti->baton.pos.y - 15;
	senti->boules.pos.x = senti->baton.x;
	senti->boules.pos.y = senti->baton.y;
	senti->boules.dim.x = 512;
	senti->boules.dim.y = 219;
	senti->boules.dim.w = 52;
	senti->boules.dim.h = 53;
}

void Init_vision(Sentinelle *senti, int A, int B)
{
	senti->vision.x = senti->baton.pos.x - 88;
	senti->vision.y = senti->baton.pos.y - 95;
	senti->vision.pos.x = senti->vision.x;
	senti->vision.pos.y = senti->vision.y;
	senti->vision.dim.x = A;
	senti->vision.dim.y = B;
	senti->vision.dim.w = 210;
	senti->vision.dim.h = 210;
	senti->counter = 0;
	senti->lancer_counter = 0;
}

void Init_background(Niveau *lvl, int X, int Y)
{
	lvl->bg.pos.x = 0;
	lvl->bg.pos.y = 0;
	lvl->bg.dim.x = X;
	lvl->bg.dim.y = Y;
	lvl->bg.dim.w = 480;
	lvl->bg.dim.h = 272;
}

void Senti_Activation_Init(Niveau *lvl)
{
	lvl->senti1.active = 0;
	lvl->senti2.active = 0;
	lvl->senti3.active = 0;
	lvl->senti4.active = 0;
	lvl->senti5.active = 0;
}

void Niveau1_init(Niveau *lvl1)
{
	Senti_Activation_Init(lvl1);

	Init_baton(&lvl1->senti1, 240, 113);

	Init_boule(&lvl1->senti1);

	Init_vision(&lvl1->senti1, 480, 0);

	Init_background(lvl1, 0, 0);
	lvl1->start = 0;
	lvl1->perdu = 0;
	lvl1->pause = 0;
}

void Niveau2_init(Niveau *lvl2)
{
	Senti_Activation_Init(lvl2);

	Init_baton(&lvl2->senti1, 119, 122);
	Init_baton(&lvl2->senti2, 304, 117);

	Init_boule(&lvl2->senti1);
	Init_boule(&lvl2->senti2);

	Init_vision(&lvl2->senti1, 480, 272);
	Init_vision(&lvl2->senti2, 480, 272);

	Init_background(lvl2, 0, 272);
	lvl2->start = 0;
	lvl2->perdu = 0;
	lvl2->pause = 0;
}

void Niveau3_init(Niveau *lvl)
{
	Senti_Activation_Init(lvl);

	Init_baton(&lvl->senti1, 129, 118);
	Init_baton(&lvl->senti2, 317, 67);

	Init_boule(&lvl->senti1);
	Init_boule(&lvl->senti2);

	Init_vision(&lvl->senti1, 480, 2*272);
	Init_vision(&lvl->senti2, 480, 2*272);

	Init_background(lvl, 0, 2*272);
	lvl->start = 0;
	lvl->perdu = 0;
	lvl->pause = 0;
}

void Niveau4_init(Niveau *lvl)
{
	Senti_Activation_Init(lvl);

	Init_baton(&lvl->senti1, 106, 113);
	Init_baton(&lvl->senti2, 233, 48);
	Init_baton(&lvl->senti3, 353, 105);

	Init_boule(&lvl->senti1);
	Init_boule(&lvl->senti2);
	Init_boule(&lvl->senti3);

	Init_vision(&lvl->senti1, 480, 3*272);
	Init_vision(&lvl->senti2, 480, 3*272);
	Init_vision(&lvl->senti3, 480, 3*272);

	Init_background(lvl, 0, 3*272);
	lvl->start = 0;
	lvl->perdu = 0;
	lvl->pause = 0;
}

void Niveau5_init(Niveau *lvl)
{
	Senti_Activation_Init(lvl);

	Init_baton(&lvl->senti1, 69, 87);
	Init_baton(&lvl->senti2, 225, 84);
	Init_baton(&lvl->senti3, 349, 40);

	Init_boule(&lvl->senti1);
	Init_boule(&lvl->senti2);
	Init_boule(&lvl->senti3);

	Init_vision(&lvl->senti1, 480, 4*272);
	Init_vision(&lvl->senti2, 480, 4*272);
	Init_vision(&lvl->senti3, 480, 4*272);

	Init_background(lvl, 0, 4*272);
	lvl->start = 0;
	lvl->perdu = 0;
	lvl->pause = 0;
}

void Niveau6_init(Niveau *lvl)
{
	Senti_Activation_Init(lvl);

	Init_baton(&lvl->senti1, 63, 94);
	Init_baton(&lvl->senti2, 181, 102);
	Init_baton(&lvl->senti3, 259, 135);
	Init_baton(&lvl->senti4, 385, 102);

	Init_boule(&lvl->senti1);
	Init_boule(&lvl->senti2);
	Init_boule(&lvl->senti3);
	Init_boule(&lvl->senti4);

	Init_vision(&lvl->senti1, 480, 5*272);
	Init_vision(&lvl->senti2, 480, 5*272);
	Init_vision(&lvl->senti3, 480, 5*272);
	Init_vision(&lvl->senti4, 480, 5*272);

	Init_background(lvl, 0, 5*272);
	lvl->start = 0;
	lvl->perdu = 0;
	lvl->pause = 0;
}

void Niveau7_init(Niveau *lvl)
{
	Senti_Activation_Init(lvl);

	Init_baton(&lvl->senti1, 51, 154);
	Init_baton(&lvl->senti2, 146, 130);
	Init_baton(&lvl->senti3, 253, 21);
	Init_baton(&lvl->senti4, 345, 65);

	Init_boule(&lvl->senti1);
	Init_boule(&lvl->senti2);
	Init_boule(&lvl->senti3);
	Init_boule(&lvl->senti4);

	Init_vision(&lvl->senti1, 480, 6*272);
	Init_vision(&lvl->senti2, 480, 6*272);
	Init_vision(&lvl->senti3, 480, 6*272);
	Init_vision(&lvl->senti4, 480, 6*272);

	Init_background(lvl, 0, 6*272);
	lvl->start = 0;
	lvl->perdu = 0;
	lvl->pause = 0;
}

void Niveau8_init(Niveau *lvl)
{
	Senti_Activation_Init(lvl);

	Init_baton(&lvl->senti1, 48, 109);
	Init_baton(&lvl->senti2, 139, 73);
	Init_baton(&lvl->senti3, 212, 123);
	Init_baton(&lvl->senti4, 303, 152);
	Init_baton(&lvl->senti5, 403, 101);

	Init_boule(&lvl->senti1);
	Init_boule(&lvl->senti2);
	Init_boule(&lvl->senti3);
	Init_boule(&lvl->senti4);
	Init_boule(&lvl->senti5);

	Init_vision(&lvl->senti1, 480, 7*272);
	Init_vision(&lvl->senti2, 480, 7*272);
	Init_vision(&lvl->senti3, 480, 7*272);
	Init_vision(&lvl->senti4, 480, 7*272);
	Init_vision(&lvl->senti5, 480, 7*272);

	Init_background(lvl, 0, 7*272);
	lvl->start = 0;
	lvl->perdu = 0;
	lvl->pause = 0;
}

void Niveau9_init(Niveau *lvl)
{
	Senti_Activation_Init(lvl);

	Init_baton(&lvl->senti1, 45, 27);
	Init_baton(&lvl->senti2, 119, 18);
	Init_baton(&lvl->senti3, 205, 22);
	Init_baton(&lvl->senti4, 292, 44);
	Init_baton(&lvl->senti5, 363, 115);

	Init_boule(&lvl->senti1);
	Init_boule(&lvl->senti2);
	Init_boule(&lvl->senti3);
	Init_boule(&lvl->senti4);
	Init_boule(&lvl->senti5);

	Init_vision(&lvl->senti1, 480, 8*272);
	Init_vision(&lvl->senti2, 480, 8*272);
	Init_vision(&lvl->senti3, 480, 8*272);
	Init_vision(&lvl->senti4, 480, 8*272);
	Init_vision(&lvl->senti5, 480, 8*272);

	Init_background(lvl, 0, 8*272);
	lvl->start = 0;
	lvl->perdu = 0;
	lvl->pause = 0;
}

void Fin_Init(Niveau *lvl)
{
	lvl->start = 0;
}

void Niveau11_init(Niveau *lvl)
{
	Senti_Activation_Init(lvl);

	Init_baton(&lvl->senti1, 99, 144);
	Init_baton(&lvl->senti2, 234, 113);
	Init_baton(&lvl->senti3, 391, 72);

	Init_boule(&lvl->senti1);
	Init_boule(&lvl->senti2);
	Init_boule(&lvl->senti3);

	Init_vision(&lvl->senti1, 480, 11*272);
	Init_vision(&lvl->senti2, 480, 11*272);
	Init_vision(&lvl->senti3, 480, 11*272);

	Init_background(lvl, 0, 11*272);
	lvl->start = 0;
	lvl->perdu = 0;
	lvl->pause = 0;
}

