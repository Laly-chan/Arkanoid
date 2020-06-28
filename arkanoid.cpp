#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<fstream>
#include<conio.h>

#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27
#define enter 13
#define spc 32

using namespace std;

class Bloque{
	private:
		int vida, cont, destcomp;
		int block[5][2];
	public:
		Bloque(int,int);
		~Bloque();
		void mostrar();
		void hitbox();
		void destruir();
		void setterxy(int, int, int);
		int getterhp();
		int gettercomp();
		void setterhp(int, int);
};

Bloque::Bloque(int vida_, int cont_){
	vida = vida_;
	cont = cont_;
}

Bloque::~Bloque(){}

void gotoxy(int,int);
void bordes();
void prestecla();
void okuu();

void mostabla();
void postabla();
void deltabla();
void movtabla();
void hitboxtabla();

void pospelota();
void mospelota();
void delpelota();
void dirpelota();

void pospowerup();
void mospowerup();
void delpowerup();

void level1();
void objlvl1();
void level2();
void objlvl2();

void ganar();
void perder();
void game_over();
void menu();

void score();
void savescore();
void loadscore();
void sumarvida();
void pospoint();
void mospoint();
void delpoint();

int lon, xt, tab[9];
char tecla;
int pel[2], x, y, c ;
int pelx, pely = -1;
int xpwr, ypwr, pwr[2], comp, timer;
int lvl, objcomp;
int cbl;
int scr, nwscr;
char hiscr[5] = {'1','0','0'};
int lives, compvid = 0;
int opc = 1;
int xpnt, ypnt, cpnt = 7, tpnt = 0;
string mpnt;

Bloque l1_b3[8] = {Bloque(3,0),Bloque(3,0),Bloque(3,0),Bloque(3,0),Bloque(3,0), Bloque(3,1), Bloque(3,0), Bloque(3,0)};
Bloque l1_b2[8] = {Bloque(2,0),Bloque(2,0),Bloque(2,0),Bloque(2,0),Bloque(2,0), Bloque(2,0), Bloque(2,0), Bloque(2,0)};
Bloque l1_b1[8] = {Bloque(1,0),Bloque(1,1),Bloque(1,0),Bloque(1,0),Bloque(1,0), Bloque(1,0), Bloque(1,0), Bloque(1,0)};

int main(){
	do {
		xt = 35, lon = 7, c = 0, pelx = 1, comp = 0, timer = 0, lvl = 1, objcomp = 1, cbl = 0, scr = 0, lives = 3;
		bordes();
		loadscore();
		tecla = up;
		menu();
		if (opc == 1){
			for (int i = 0; i < lives; i++){
				gotoxy(53+(i*2),13); printf("%c",3);
			}
			gotoxy(53,15); printf("Score: ");
			gotoxy(54,17); cout<<"Hi: "<<hiscr<<"00";
			okuu();
			while (tecla != esc){
				switch (lvl){
					case 1:
						level1(); break;
					case 2:
						level2(); break;
				}
				postabla();
				mostabla();
				deltabla();
				
				pospelota();
				mospelota();
				delpelota();
				
				hitboxtabla();
				
				if (comp == 1 && ypwr < 24){
					if (timer == 2){
						pospowerup();
						mospowerup();
						delpowerup();
						timer = 0;
					}
					timer++;
				}
				
				dirpelota();
				
				prestecla();
				prestecla();
				
				score();
				
				if (cpnt < 7){
					if (tpnt >= 3){
						pospoint();
						mospoint();
						delpoint();
						tpnt = 0;
					}
					tpnt++;
				}
				
				if ((scr >= 100 && compvid == 0) || (scr >= 200 && compvid == 1) || (scr >= 300 && compvid == 2) || (scr >= 500 && compvid == 3 && lives < 6)){
					sumarvida();
				}
				
				if (cbl == 0){
					gotoxy(0,0);
					Sleep(1500);
					ganar();
				}
				if (y == 24){
					gotoxy(0,0);
					Sleep(1000);
					perder();
					if (lives == 0){
						game_over();
						break;
					}
				}
				Sleep(75);
			}
		}
		system("cls");
	} while (opc != 0);
	return 0;
}

void gotoxy(int x1, int y1){
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X = x1;
	dwPos.Y = y1;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

void bordes(){
	gotoxy(25,0); printf("%c",201);
	for(int i = 26; i < 66; i++){
		if (i != 50){
			gotoxy(i,0); printf("%c",205);
			if (i < 50){
				gotoxy(i,25); printf("%c",205);
			} else {
				gotoxy(i,24); printf("%c",205);
			}
			if (i > 51 && i < 65){
				gotoxy(i,1); printf("%c",205);
				gotoxy(i,12); printf("%c",205);
			}
		}
	}
	for (int i = 1; i < 24; i++){
		gotoxy(25,i); printf("%c",186);
		gotoxy(50,i); printf("%c",186);
		gotoxy(66,i); printf("%c",186);
		if(i > 1 && i < 12){
			gotoxy(51,i); printf("%c",186);
			gotoxy(65,i); printf("%c",186);
		}
	}
	gotoxy(25,24); printf("%c",186);
	gotoxy(25,25); printf("%c",200);
	gotoxy(50,0); printf("%c",203);
	gotoxy(50,24); printf("%c",204);
	gotoxy(50,25); printf("%c",188);
	gotoxy(66,0); printf("%c",187);
	gotoxy(66,24); printf("%c",188);
	gotoxy(51,1); printf("%c",201);
	gotoxy(65,1); printf("%c",187);
	gotoxy(51,12); printf("%c",200);
	gotoxy(65,12); printf("%c",188);
}

void mostabla(){
	for (int i = 1; i < lon-1; i++){
		gotoxy(tab[i],23); printf("%c",223);
	}
}

void postabla(){
	int aux = xt;
	for (int i = 0; i < lon; i++){
		tab[i] = aux;
		aux++;
	}
}

void deltabla(){
	if (tab[0] > 25){
		gotoxy(tab[0],23); printf(" ");
	}
	if (tab[lon-1] < 50){
		gotoxy(tab[lon-1],23); printf(" ");
	}
}

void movtabla(){
	if (tecla == left && xt > 25){
		xt--;
	}
	if (tecla == right && xt+lon <= 50){
		xt++;
	}
}

void prestecla(){
	if(kbhit()){
		tecla = getch();
		movtabla();
		if (tecla == spc){
			c = 1;
		} else {
			if (kbhit()){
				tecla = getch();
				movtabla();
			}
		}
	}
}

void pospelota(){
	if (c == 0){
		x = xt+lon/2;
		y = 22;
	} else {
		x += pelx;
		y += pely;
	}
	pel[0] = x;
	pel[1] = y;
}

void mospelota(){
	gotoxy(pel[0],pel[1]); printf("%c",254);
}

void delpelota(){
	int delx, dely;
	if (c == 0){
		gotoxy(pel[0]-1,22); printf(" ");
		gotoxy(pel[0]+1,22); printf(" ");
	} else {
		delx = pel[0]-pelx;
		dely = pel[1]-pely;
		gotoxy(delx,dely); printf(" ");
	}
}

void dirpelota(){
	if (pel[0] == 49) pelx = -1;
	if (pel[0] == 26) pelx = 1;
	if (pel[1] == 1) pely = 1;
}

void hitboxtabla(){
	if (pel[1] == 22){
		for (int i = 0; i < lon/2; i++){
			if (pel[0] == tab[i]){
				pelx = -1;
				pely = -1;
			}
		}
		for (int i = lon; i > lon/2; i--){
			if (pel[0] == tab[i]){
				pelx = 1;
				pely = -1;
			}
		}
		if (pel[0] == tab[lon/2]) pely = -1;
	}
	if (pwr[1] == 22){
		for (int i = 1; i < lon-1; i++){
			gotoxy(pwr[0],pwr[1]); printf(" ");
			if (pwr[0] == tab[i]){
				ypnt = 23;
				xpnt = (xt+(lon/2))-1;
				cpnt = 0;
				pospoint();
				mospoint();
				if (lon == 9){
					scr += 5;
					mpnt = "500";
				} else {
					scr += 2;
					mpnt = "200";
				}
				lon = 9;
				ypwr = 24;
				pwr[1] = 24;
				delpowerup();
			}
		}
	}
}

void Bloque::hitbox(){
	for (int i = 0; i < 5; i++){
		if (block[i][0] == pel[0]){
			if (block[i][1]-1 == pel[1]){
				vida--;
				pely = -1;
				scr = scr + (1*(vida + 1));
				Bloque::mostrar();
			} else if (block[i][1]+1 == pel[1]){
				vida--;
				pely = 1;
				scr = scr + (1*(vida + 1));
				Bloque::mostrar();
			}
			if (block[0][1] == pel[1]){
				vida--;
				pelx = -1;
				scr = scr + (1*(vida + 1));
				Bloque::mostrar();
			}
			if (block[4][1] == pel[1]){
				vida--;
				pelx = 1;
				scr = scr + (1*(vida + 1));
				Bloque::mostrar();
			}
		}
	}
}

void Bloque::mostrar(){
	for (int i = 1; i < 4; i++){
		gotoxy(block[i][0],block[i][1]);
		switch (vida){
			case 1:
				printf("%c",176); break;
			case 2:
				printf("%c",178); break;
			case 3:
				printf("%c",219); break;
		}
	}
}

void Bloque::setterxy(int xb, int yb, int dest){
	for (int i = 0; i < 5; i++){
		block[i][0] = xb;
		block[i][1] = yb;
		xb++;
	}
	destcomp = dest;
}

int Bloque::getterhp(){return vida;} int Bloque::gettercomp(){return destcomp;}

void Bloque::destruir(){
	if (cont == 1){
		ypwr = block[2][1]; 
		xpwr = block[2][0];
		comp = 1;
	}
	for (int i = 1; i < 4; i++){
		gotoxy(block[i][0],block[i][1]);
		printf(" ");
	} vida--; cbl--; destcomp++;
}

void pospowerup(){
	ypwr++;
	pwr[0] = xpwr;
	pwr[1] = ypwr;
}

void mospowerup(){
	gotoxy(pwr[0],pwr[1]); printf("%c",254);
}

void delpowerup(){
	gotoxy(pwr[0],pwr[1]-1); printf(" ");
	if (pwr[1] == 24){
		gotoxy(pwr[0],pwr[1]); printf(" ");
		comp == 0;
	}
}

void objlvl1(){
	int blx = 25;
	for (int i = 0; i < 8; i++){
		l1_b3[i].setterhp(3,0);
		l1_b3[i].setterxy(blx,4,0);
		blx += 3;
		cbl++;
		l1_b3[i].mostrar();
	}
	blx = 25;
	for (int i = 0; i < 8; i++){
		l1_b2[i].setterhp(2,0);
		l1_b2[i].setterxy(blx,5,0);
		blx += 3;
		cbl++;
		l1_b2[i].mostrar();
	}
	blx = 25;
	for (int i = 0; i < 8; i++){
		l1_b1[i].setterhp(1,0);
		l1_b1[i].setterxy(blx,6,0);
		blx += 3;
		cbl++;
		l1_b1[i].mostrar();
	}
}

void level1(){
	if (objcomp == 1){
		objlvl1();
		objcomp++;
	}
	for (int i = 0; i < 8; i++){
		if (l1_b3[i].getterhp() <= 0 && l1_b3[i].gettercomp() == 0){
			l1_b3[i].destruir();
			l1_b3[i].~Bloque();
		} else if (l1_b3[i].getterhp() > 0){
			l1_b3[i].hitbox();
		}
	}
	for (int i = 0; i < 8; i++){
		if (l1_b2[i].getterhp() <= 0 && l1_b2[i].gettercomp() == 0){
			l1_b2[i].destruir();
			l1_b2[i].~Bloque();
		} else if (l1_b2[i].getterhp() > 0){
			l1_b2[i].hitbox();
		}
	}
	for (int i = 0; i < 8; i++){
		if (l1_b1[i].getterhp() <= 0 && l1_b1[i].gettercomp() == 0){
			l1_b1[i].destruir();
			l1_b1[i].~Bloque();
		} else if (l1_b1[i].getterhp() > 0){
			l1_b1[i].hitbox();
		}
	}
}

void objlvl2(){
	int blx = 25;
	int bly = 4;
	for (int i = 0; i < 8; i++){
		l1_b3[i].setterhp(3,0);
		l1_b3[i].setterxy(blx,bly,0);
		blx += 3;
		if (bly == 4) bly++;
		else bly--;
		cbl++;
		l1_b3[i].mostrar();
	}
	bly = 6;
	blx = 25;
	for (int i = 0; i < 8; i++){
		l1_b2[i].setterhp(2,0);
		l1_b2[i].setterxy(blx,bly,0);
		blx += 3;
		if (bly == 6) bly++;
		else bly--;
		cbl++;
		l1_b2[i].mostrar();
	}
	blx = 25;
	bly = 8;
	for (int i = 0; i < 8; i++){
		l1_b1[i].setterhp(1,0);
		l1_b1[i].setterxy(blx,bly,0);
		blx += 3;
		if (bly == 8) bly++;
		else bly--;
		cbl++;
		l1_b1[i].mostrar();
	}
}

void level2(){
	
	if (objcomp == 1){
		objlvl2();
		objcomp++;
	}
	
	for (int i = 0; i < 8; i++){
		if (l1_b3[i].getterhp() <= 0 && l1_b3[i].gettercomp() == 0){
			l1_b3[i].destruir();
			l1_b3[i].~Bloque();
		} else if (l1_b3[i].getterhp() > 0){
			l1_b3[i].hitbox();
		}
	}
	for (int i = 0; i < 8; i++){
		if (l1_b2[i].getterhp() <= 0 && l1_b2[i].gettercomp() == 0){
			l1_b2[i].destruir();
			l1_b2[i].~Bloque();
		} else if (l1_b2[i].getterhp() > 0){
			l1_b2[i].hitbox();
		}
	}
	for (int i = 0; i < 8; i++){
		if (l1_b1[i].getterhp() <= 0 && l1_b1[i].gettercomp() == 0){
			l1_b1[i].destruir();
			l1_b1[i].~Bloque();
		} else if (l1_b1[i].getterhp() > 0){
			l1_b1[i].hitbox();
		}
	}
}

void Bloque::setterhp(int vida_, int dest){
	vida = vida_;
	destcomp = dest;
}

void ganar(){
	gotoxy(x,y); printf(" ");
	for (int i = 1; i < lon-1; i++){
		gotoxy(tab[i],23); printf(" ");
	}
	gotoxy(33,10); printf("You Win!");
	if (lvl == 1){
		lvl++;
	} else {
		lvl--;
	}
	gotoxy(32,12); printf("Your Score:");
	objcomp = 1;
	
	if (scr < 10){
		gotoxy(34,13); cout<<"00"<<scr<<"00";
	} else if (scr < 100){
		gotoxy(34,13); cout<<"0"<<scr<<"00";
	} else {
		gotoxy(34,13); cout<<scr<<"00";
	}
	
	gotoxy(30,15); cout<<"Press Enter To";
	gotoxy(33,16); cout<<"Continue";
	c = 0;
	xt = 35;
	while(tecla != enter){
		if (kbhit()){
			tecla = getch();
		}
	}
	gotoxy(33,10); printf("        ");
	gotoxy(31,12); printf("            ");
	gotoxy(32,13); printf("            ");
	gotoxy(30,15); printf("              ");
	gotoxy(33,16); printf("        ");
}

void score(){
	if (scr < 10){
		gotoxy(59,15); cout<<"00"<<scr<<"00";
	} else if (scr < 100){
		gotoxy(59,15); cout<<"0"<<scr<<"00";
	} else {
		gotoxy(59,15); cout<<scr<<"00";
	}
}

void perder(){
	for (int i = xt+1; i < (xt+lon)-1; i++){
		gotoxy(i,23); printf(" ");
	}
	gotoxy(x,y); printf(" ");
	lives--;
	c = 0;
	lon = 7;
	xt = 35;
	if (comp == 1){
		gotoxy(pwr[0],pwr[1]); printf(" ");
		ypwr = 24;
		delpowerup();
	}
	gotoxy(53+(lives*2),13); printf(" ");
}

void game_over(){
	gotoxy(33,10); printf("Game Over");
	gotoxy(31,12); printf("Final Score:");
	if (scr < 10){
		gotoxy(34,13); cout<<"00"<<scr<<"00";
	} else if (scr < 100){
		gotoxy(34,13); cout<<"0"<<scr<<"00";
	} else {
		gotoxy(34,13); cout<<scr<<"00";
	}
	for (int i = 0; i < 8; i++){
		l1_b1[i].destruir();
		l1_b2[i].destruir();
		l1_b3[i].destruir();
	}
	
	if (scr > atoi(hiscr)){
		savescore();
		gotoxy(30,15); cout<<"New High Score!";
		gotoxy(30,17); cout<<"Press Enter To";
		gotoxy(33,18); cout<<"Continue";
	} else {
		gotoxy(30,15); cout<<"Press Enter To";
		gotoxy(33,16); cout<<"Continue";
	}
	gotoxy(0,0);
	while (tecla != enter){
		if (kbhit()){
			tecla = getch();
		}
	}
}

void savescore(){
	ofstream archivo;
	
	archivo.open("Save.sav",ios::out);
	
	archivo<<scr;
	
	archivo.close();
}

void loadscore(){
	ifstream archivo;
	
	archivo.open("Save.sav",ios::in);
	
	if (archivo.fail()){
		return;
	}
	
	while (!archivo.eof()){
		archivo.getline(hiscr,5);
	}
	
	archivo.close();
}

void menu(){
	gotoxy(33,12); printf("Start Game");
	gotoxy(33,14); printf("Exit Game");
	gotoxy(31,12); printf("%c",16);
	gotoxy(31,14); printf(" ");
	gotoxy(0,0);
	while (tecla != enter){
		tecla = getch();
		switch(tecla){
			case up:
				opc = 1;
				gotoxy(31,12); printf("%c",16);
				gotoxy(31,14); printf(" ");
				gotoxy(0,0); break;
			case down:
				opc = 0;
				gotoxy(31,14); printf("%c",16);
				gotoxy(31,12); printf(" ");
				gotoxy(0,0); break;
		}
	}
	gotoxy(31,12); printf("            ");
	gotoxy(31,14); printf("           ");
}

void sumarvida(){
	gotoxy(53+(lives*2),13); printf("%c",3);
	lives++;
	compvid++;
	ypnt = 23;
	xpnt = (xt+(lon/2))-1;
	cpnt = 0;
	pospoint();
	mospoint();
	mpnt = "1up";
}

void pospoint(){
	ypnt--;
	cpnt++;
}

void mospoint(){
	gotoxy(xpnt,ypnt); cout<<mpnt;
}

void delpoint(){
	gotoxy(xpnt,ypnt+1); printf("   ");
	if (cpnt == 7){
		gotoxy(xpnt,ypnt); printf("   ");
	}
}

void okuu(){
	gotoxy(53,2); printf("%c",220);
	gotoxy(63,2); printf("%c",220);
	
	gotoxy(53,3); printf("%c",176);
	gotoxy(54,3); printf("%c",223);
	gotoxy(55,3); printf("%c",223);
	gotoxy(56,3); printf("%c",220);
	gotoxy(57,3); printf("%c",220);
	gotoxy(58,3); printf("%c",220);
	gotoxy(59,3); printf("%c",220);
	gotoxy(60,3); printf("%c",220);
	gotoxy(61,3); printf("%c",223);
	gotoxy(62,3); printf("%c",223);
	gotoxy(63,3); printf("%c",176);
	
	gotoxy(53,4); printf("%c",220);
	gotoxy(54,4); printf("%c",219);
	gotoxy(55,4); printf("%c",219);
	gotoxy(56,4); printf("%c",219);
	gotoxy(57,4); printf("%c",219);
	gotoxy(58,4); printf("%c",223);
	gotoxy(59,4); printf("%c",219);
	gotoxy(60,4); printf("%c",219);
	gotoxy(61,4); printf("%c",219);
	gotoxy(62,4); printf("%c",219);
	gotoxy(63,4); printf("%c",220);
	
	gotoxy(53,5); printf("%c",219);
	gotoxy(54,5); printf("%c",219);
	gotoxy(55,5); printf("%c",223);
	gotoxy(56,5); printf("%c",220);
	gotoxy(60,5); printf("%c",220);
	gotoxy(61,5); printf("%c",223);
	gotoxy(62,5); printf("%c",15);
	gotoxy(63,5); printf("%c",219);
	
	gotoxy(53,6); printf("%c",219);
	gotoxy(57,6); printf("%c",220);
	gotoxy(58,6); printf("%c",220);
	gotoxy(59,6); printf("%c",220);
	gotoxy(61,6); printf("%c",220);
	gotoxy(62,6); printf("%c",223);
	gotoxy(63,6); printf("%c",219);
	
	gotoxy(53,7); printf("%c",219);
	gotoxy(54,7); printf("%c",223);
	gotoxy(55,7); printf("%c",220);
	gotoxy(56,7); printf("%c",220);
	gotoxy(57,7); printf("%c",220);
	gotoxy(58,7); printf("%c",219);
	gotoxy(59,7); printf("%c",220);
	gotoxy(60,7); printf("%c",220);
	gotoxy(61,7); printf("%c",219);
	gotoxy(62,7); printf("%c",176);
	gotoxy(63,7); printf("%c",219);
	
	gotoxy(53,8); printf("%c",220);
	gotoxy(54,8); printf("%c",223);
	gotoxy(55,8); printf("%c",220);
	gotoxy(58,8); printf("%c",64);
	gotoxy(60,8); printf("%c",176);
	gotoxy(61,8); printf("%c",220);
	gotoxy(62,8); printf("%c",223);
	gotoxy(63,8); printf("%c",176);
	
	gotoxy(53,9); printf("%c",220);
	gotoxy(54,9); printf("%c",219);
	gotoxy(55,9); printf("%c",223);
	gotoxy(56,9); printf("%c",220);
	gotoxy(57,9); printf("%c",220);
	gotoxy(58,9); printf("%c",220);
	gotoxy(59,9); printf("%c",220);
	gotoxy(60,9); printf("%c",220);
	gotoxy(61,9); printf("%c",223);
	gotoxy(62,9); printf("%c",220);
	gotoxy(63,9); printf("%c",220);
	
	gotoxy(53,10); printf("%c",223);
	gotoxy(54,10); printf("%c",220);
	gotoxy(55,10); printf("%c",219);
	gotoxy(56,10); printf("%c",220);
	gotoxy(57,10); printf("%c",220);
	gotoxy(58,10); printf("%c",220);
	gotoxy(59,10); printf("%c",220);
	gotoxy(60,10); printf("%c",220);
	gotoxy(61,10); printf("%c",219);
	gotoxy(62,10); printf("%c",220);
	
	gotoxy(56,11); printf("%c",219);
	gotoxy(57,11); printf("%c",220);
	gotoxy(58,11); printf("%c",223);
	gotoxy(59,11); printf("%c",220);
	gotoxy(60,11); printf("%c",219);
}
