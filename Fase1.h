void fase1(Window win,Magia fireball[4][2],ALLEGRO_FONT *font5,int explox[4][2],int exploy[4][2],Pessoa *p,Sprite s)
{
	char** matriz;
	int mapsize,xtile[TAM],ytile[TAM],xcorte[TAM],ycorte[TAM], njogadores = 4;
	FILE *mapa,*errext;
	ALLEGRO_BITMAP *map, *frente;
	int i,j,k,cont = 0,*tlep,*cor;
	bool redraw = false, sair = false, *puxa, *temneon;

	puxa = (bool *) malloc(sizeof(bool) * njogadores);
	temneon = (bool *) malloc(sizeof(bool) * njogadores);
	tlep = (int *) malloc(sizeof(int) * njogadores);
	cor = (int *) malloc(sizeof(int) * njogadores);

	for(i=0; i<njogadores; ++i) {
		p[i].x = 100 + 50*i;
		p[i].y = 200;
		puxa[i] = false;
		temneon[i] = true;
		tlep[i] = 0;
		cor[i] = i+1;
	}

	errext = fopen("err.txt","w");

	mapa = fopen("Fases/F1/mapa.txt","r");
    if(!mapa) {
    	fprintf(errext,"Erro ao abrir mapa.txt.");
    	fclose(errext);
    	exit(1);
    }

    fscanf(mapa,"%i\n",&mapsize);
    for(i=0;i<mapsize+1;i++)
        fscanf(mapa,"%i %i %i %i\n",&xtile[i],&ytile[i],&xcorte[i],&ycorte[i]);

    map = cria_mapa(win,mapa,mapsize,xtile,ytile,xcorte,ycorte,s);
    frente = cria_frente(win,mapa,mapsize,xcorte,ycorte,xtile,ytile,s); // Obs: Confundi dentro da fun�ao, entao to passando invertido aqui. EH PROPOSITAL!

	matriz = le_matriz(fopen("Fases/F1/matriz.txt","r"));

	al_flush_event_queue(win.event_queue);
	while (!sair) /* Pra sair, botoes como Esc, o X ali em cima direita,... transformam a variavel sair de false pra true, dai sai do while. */
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(win.event_queue, &ev);
        //al_draw_textf(font5,VERDE_LIMAO,20,450,0,"%d",fireball[i][j].explosao);
        //al_draw_textf(font,VERDE_LIMAO,20,470,0,"Coord x: %d      Coord y: %d     %c",cx[0],cy[0],matriz[cx[0]][cy[0]]);
        //al_draw_textf(font,VERDE_LIMAO,20,490,0,"Direcao = %d",fireball[0][0].d);
		//al_flip_display(); // Essa fun�ao faz o buffer automatico do Allegro trocar de lugar com a screen.

        /* Trata eventos. */
	   	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // Detecta se clicaram no X.
			graphdeinit(win);
			exit(1);
		} else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { // Detecta se apertaram alguma tecla.
			keyboard_down(ev.keyboard.keycode,puxa,tlep,fireball,p);
        } else if(ev.type == ALLEGRO_EVENT_KEY_UP) { // Detecta se soltaram alguma tecla.
			keyboard_up(ev.keyboard.keycode,puxa,&sair,p);
        } else if (al_is_event_queue_empty(win.event_queue)) { // Nao ocorreu nenhum evento.
            /* Imprime */
			redraw = false; // Fica true quando Timer acaba
			al_clear_to_color(PRETO);
			al_draw_bitmap(map,0,0,0);

			cont++;
			for(i=0; i<njogadores; i++) // Faz parar de correr quando a energia acaba.
				if(p[i].energia <= 0)
					p[i].correr = 1;

			flash(p,tlep,matriz);

			usa_magias(matriz,fireball,p);

			for(k=0;k<njogadores;k++) {
				for(j=0;j<2;j++) {
					if(fireball[k][j].ativa == true) {
						al_draw_bitmap(s.fireballs[fireball[k][j].d],fireball[k][j].x,fireball[k][j].y,0);
					}
					if(fireball[k][j].explosao == true) { // Enquanto explox = 288 e exploy = 224, ele nao immprime a explosao.
									// Entao o esquema eh zerar eles e dai o programa come�a a contagem e a impressao.
						explox[k][j] = exploy[i][j] = 0;
						fireball[k][j].explosao = false;
						//contalinhaexplo = 0;
					}
					if(explox[k][j] < 280 && exploy[k][j] < 220) { // Imprime a explosao.
						al_draw_bitmap_region(s.explosion,explox[k][j],exploy[k][j],32,32,fireball[k][j].x,fireball[k][j].y,0);
						explox[k][j] += 32;
						if(explox[k][j] >= 288) {
							exploy[k][j] += 32;
							if(exploy[k][j] < 224)
								explox[k][j] = 0;
						}
					}
				}
			}

			tira_neon(puxa,temneon,p);

			for(i=0;i<4;i++) // Pra nao contar como se estivesse sempre tentando puxar.
				puxa[i] = false;

            imprime_4_chars_for(cont,matriz,cor,temneon,njogadores,p,s);

            IA(p);

            if(cont == CONT)
          		cont = 0;
          	for(i=0; i<njogadores; ++i)
          		if(p[i].energia < 100)
					p[i].energia++;

            desconta_energia(p,njogadores);

            al_draw_bitmap(frente,0,0,0);

            al_draw_text(font5,VERDE_LIMAO,20,600,0,"Player 1:               Player 2:             Player 3:               Player 4:");
            al_draw_text(font5,VERMELHO,20,620,0,   "Vida    :               Vida    :             Vida    :               Vida    :");
            al_draw_text(font5,AZUL,20,640,0,       "Energia :               Energia :             Energia :               Energia :");
            for(i=0; i<njogadores; ++i)
            	for(j=0; j< (p[i].energia/5);j++ )
            		al_draw_text(font5,AMARELO,100+200*i+4*j,640,0,"| ");
            //al_draw_textf(font5,VERDE_LIMAO,20,450,0,"%d",fireball[i][j].explosao);
			al_flip_display();
		}
	}
}
