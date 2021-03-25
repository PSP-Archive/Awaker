#ifndef DEF_STRUCT
#define DEF_STRUCT

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct
{
	SDL_Rect pos;
	SDL_Rect dim;
	int x;
	int y;
	int en_mvt;
	int intelligent_arret;
}Coordonnees;

typedef struct
{
	Coordonnees joueur;
	Coordonnees cpu;
	SDL_Surface *img;
	int vitesse;
	int anim;
	int mallus;
	int mallus_time1;
}Perso;

typedef struct
{
	Coordonnees background;
	Coordonnees selection1;
	Coordonnees selection2;
	Coordonnees selection3;
	SDL_Surface *img;
	int which_bg;
	int choix;
	int fenetre;
	int animation;
}Menu;

typedef struct
{
	int active;
	int counter;
	int lancer_counter;
	Coordonnees baton;
	Coordonnees boules;
	Coordonnees vision;
}Sentinelle;

typedef struct
{
	Sentinelle senti1;
	Sentinelle senti2;
	Sentinelle senti3;
	Sentinelle senti4;
	Sentinelle senti5;
	Sentinelle senti6;
	Coordonnees bg;
	int start;
	int perdu;
	int pause;
}Niveau;

typedef struct
{
	int difficulte;
	int fenetre;
	int pause;
	int appuis;
	int niveau;
	int i;
	int affich_pluie;
	SDL_Surface *img_lvl;
	Coordonnees pluie[48];
	Coordonnees matrix[96];
	SceCtrlData pad;
	Coordonnees barre[3];
	int switch_barre[3];
	int unlock;
	char unlock_txt[3];
	FILE *file;
}General;

typedef struct
{
	Coordonnees bande[26];
	Coordonnees gameover;
	Coordonnees lvl_win;
	Coordonnees comptage;
	Coordonnees pause;
	int active_comptage;
	int active_bande;
	int i;
	SDL_Surface *img;
}Anim;

typedef struct
{
	Mix_Music *music;
	Mix_Chunk *awaker;
	Mix_Chunk *gameover;
	Mix_Chunk *un;
	Mix_Chunk *deux;
	Mix_Chunk *trois;
	Mix_Chunk *start;
	Mix_Chunk *earlystart;
	Mix_Chunk *pause;
	Mix_Chunk *win;
	int joue[12];
}Sons;

#endif

