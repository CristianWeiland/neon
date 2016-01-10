#include "keys.h"

/*
void teclas_iniciais()
{
	sprintf(pessoa[0].botao_char[0],"%c",'^');
	sprintf(pessoa[0].botao_char[1],"%c",'|');
	sprintf(pessoa[0].botao_char[2],"%c",'>');
	sprintf(pessoa[0].botao_char[3],"%c",'<');
	sprintf(pessoa[0].botao_char[4],"%c",ALLEGRO_KEY_RCTRL+96);
	sprintf(pessoa[0].botao_char[5],"%c",ALLEGRO_KEY_ALTGR+96);

	sprintf(pessoa[1].botao_char[0],"%c",ALLEGRO_KEY_I+96);
	sprintf(pessoa[1].botao_char[1],"%c",ALLEGRO_KEY_K+96);
	sprintf(pessoa[1].botao_char[2],"%c",ALLEGRO_KEY_L+96);
	sprintf(pessoa[1].botao_char[3],"%c",ALLEGRO_KEY_J+96);
	sprintf(pessoa[1].botao_char[4],"%c",ALLEGRO_KEY_U+96);
	sprintf(pessoa[1].botao_char[5],"%c",ALLEGRO_KEY_O+96);

	sprintf(pessoa[2].botao_char[0],"%c",ALLEGRO_KEY_T+96);
	sprintf(pessoa[2].botao_char[1],"%c",ALLEGRO_KEY_G+96);
	sprintf(pessoa[2].botao_char[2],"%c",ALLEGRO_KEY_H+96);
	sprintf(pessoa[2].botao_char[3],"%c",ALLEGRO_KEY_F+96);
	sprintf(pessoa[2].botao_char[4],"%c",ALLEGRO_KEY_R+96);
	sprintf(pessoa[2].botao_char[5],"%c",ALLEGRO_KEY_Y+96);

	sprintf(pessoa[3].botao_char[0],"%c",ALLEGRO_KEY_W+96);
	sprintf(pessoa[3].botao_char[1],"%c",ALLEGRO_KEY_S+96);
	sprintf(pessoa[3].botao_char[2],"%c",ALLEGRO_KEY_D+96);
	sprintf(pessoa[3].botao_char[3],"%c",ALLEGRO_KEY_A+96);
	sprintf(pessoa[3].botao_char[4],"%c",ALLEGRO_KEY_Q+96);
	sprintf(pessoa[3].botao_char[5],"%c",ALLEGRO_KEY_E+96);

	pessoa[0].botao_char_int[0]=ALLEGRO_KEY_UP;
	pessoa[0].botao_char_int[1]=ALLEGRO_KEY_DOWN;
	pessoa[0].botao_char_int[2]=ALLEGRO_KEY_RIGHT;
	pessoa[0].botao_char_int[3]=ALLEGRO_KEY_LEFT;
	pessoa[0].botao_char_int[4]=ALLEGRO_KEY_RCTRL;
	pessoa[0].botao_char_int[5]=ALLEGRO_KEY_ALTGR;

	pessoa[1].botao_char_int[0]=ALLEGRO_KEY_I;
	pessoa[1].botao_char_int[1]=ALLEGRO_KEY_K;
	pessoa[1].botao_char_int[2]=ALLEGRO_KEY_L;
	pessoa[1].botao_char_int[3]=ALLEGRO_KEY_J;
	pessoa[1].botao_char_int[4]=ALLEGRO_KEY_U;
	pessoa[1].botao_char_int[5]=ALLEGRO_KEY_O;

	pessoa[2].botao_char_int[0]=ALLEGRO_KEY_T;
	pessoa[2].botao_char_int[1]=ALLEGRO_KEY_G;
	pessoa[2].botao_char_int[2]=ALLEGRO_KEY_H;
	pessoa[2].botao_char_int[3]=ALLEGRO_KEY_F;
	pessoa[2].botao_char_int[4]=ALLEGRO_KEY_R;
	pessoa[2].botao_char_int[5]=ALLEGRO_KEY_Y;

	pessoa[3].botao_char_int[0]=ALLEGRO_KEY_W;
	pessoa[3].botao_char_int[1]=ALLEGRO_KEY_S;
	pessoa[3].botao_char_int[2]=ALLEGRO_KEY_D;
	pessoa[3].botao_char_int[3]=ALLEGRO_KEY_A;
	pessoa[3].botao_char_int[4]=ALLEGRO_KEY_Q;
	pessoa[3].botao_char_int[5]=ALLEGRO_KEY_E;
	return;
}
*/

void keyboard_down(int evkeyboardkeycode,bool *puxa,int *tlep,Magia (*fireball)[2], Pessoa *p)
{
	for(int i=0; i<4; ++i) {
		if(p[i].comp==0) {
			if(evkeyboardkeycode == p[i].botao_char_int[0]) {
				p[i].andou_c = 1;
			} else if(evkeyboardkeycode == p[i].botao_char_int[1]) {
				p[i].andou_b = 1;
			} else if(evkeyboardkeycode == p[i].botao_char_int[2]) {
				p[i].andou_d = 1;
			} else if(evkeyboardkeycode == p[i].botao_char_int[3]) {
				p[i].andou_e = 1;
			} else if(evkeyboardkeycode == p[i].botao_char_int[4]) {
				p[i].correr = 2;
			} else if(evkeyboardkeycode == p[i].botao_char_int[5]) {
				puxa[i] = true;
			} else if(evkeyboardkeycode == p[i].botao_char_int[6]) {
				tlep[i] = 1;
			}
		}
	}
	switch(evkeyboardkeycode) {   // Os casos DOWN,LEFT,RIGHT,UP sao as setas, e tem que fazer o teu carinha andar. Tah meio bugado, mas funciona um pouco.
		/* Primeiro Player */
        /* Magias */
        case ALLEGRO_KEY_Z:
        	if(fireball[0][0].ativa == true && p[0].energia >= 50 && fireball[0][1].ativa == false) {
        		fireball[0][1].ativa = true;
        		fireball[0][1].x = p[0].x;
        		fireball[0][1].y = p[0].y;
        		fireball[0][1].dist = 0;
        		p[0].energia -= 50;
        	}
        	else if(p[0].energia >= 50) {
        		fireball[0][0].ativa = true;
        		fireball[0][0].x = p[0].x;
        		fireball[0][0].y = p[0].y;
        		fireball[0][0].dist = 0;
        		p[0].energia -= 50;
        	}
    	default: break;
    }
}


void keyboard_up(int evkeyboardkeycode,bool *puxa,bool *sair, Pessoa *p)
{
	for(int i=0; i<4; ++i) {
		if(p[i].comp == 0) {
			if(evkeyboardkeycode == p[i].botao_char_int[0]) {
				p[i].andou_c = 0;
			} else if(evkeyboardkeycode == p[i].botao_char_int[1]) {
				p[i].andou_b = 0;
			} else if(evkeyboardkeycode == p[i].botao_char_int[2]) {
				p[i].andou_d = 0;
			} else if(evkeyboardkeycode == p[i].botao_char_int[3]) {
				p[i].andou_e = 0;
			} else if(evkeyboardkeycode == p[i].botao_char_int[4]) {
				p[i].correr = 1;
			}
		}
	}
}
