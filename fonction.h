#ifndef DEF_FONCTION
#define DEF_FONCTION

#include "struct.h"

void saveImage(const char* filename);
void screenshot();
void Blit_Matrix_Effet(General *var, SDL_Surface *ecran);
void save_unlock(General *var);
void Blit_BarreEffet(General *var, Menu *menu, SDL_Surface *ecran);
void Blit_Pluie(General *var, Anim *anim, SDL_Surface *ecran);
void PlayWav(Mix_Chunk *wav, int *joue);
void Paused(Menu *menu, General *var, Sons *mus, Niveau *lvl, Anim *anim, SDL_Surface *ecran);
void PlayedSong_Init(Sons *mus);
void Sons_Init(Sons *mus);
void cheat(General *var, Niveau *lvl);
void stop_cpu(General *var, Perso *perso, Niveau *lvl);
void check_who_win(General *var, Perso *perso, Niveau *lvl, Anim *anim, SDL_Surface *ecran, Menu *menu, int X, int Y, Sons *mus);
void vision_sys(int i, Sentinelle *senti);
void check_if_see(Sentinelle *senti, Perso *perso, int Xmin, int Xmax, int origine_X, int origine_Y);
void blit_sentinelle(Sentinelle *senti, SDL_Surface *ecran, General *var);
void follow_the_line(General *var, Perso *perso, int Xmin , int Xmax, int UporDown);
void check_malus(General *var, Perso *perso, Anim *anim, SDL_Surface *ecran);
void Replace_position(Niveau *lvl, Perso *perso);
void perso_anim(Perso *perso, SDL_Surface *ecran, General *var);
void intro_anim(Perso *perso, General *var, Niveau *lvl1, Anim *anim, SDL_Surface *ecran, Sons *mus);
void Perso_Init(Perso *perso, int X, int Y);
void Anim_Init(Anim *anim);
void General_Init(General *var);
void Init_baton(Sentinelle *senti, int A, int B);
void Init_boule(Sentinelle *senti);
void Init_vision(Sentinelle *senti, int A, int B);
void Init_background(Niveau *lvl, int X, int Y);
void Senti_Activation_Init(Niveau *lvl);
void Niveau1_init(Niveau *lvl1);
void Niveau2_init(Niveau *lvl2);
void Niveau3_init(Niveau *lvl);
void Niveau4_init(Niveau *lvl);
void Niveau5_init(Niveau *lvl);
void Niveau6_init(Niveau *lvl);
void Niveau7_init(Niveau *lvl);
void Niveau8_init(Niveau *lvl);
void Niveau9_init(Niveau *lvl);
void Fin_Init(Niveau *lvl);
void Niveau11_init(Niveau *lvl);

#endif

