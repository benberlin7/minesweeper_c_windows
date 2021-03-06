/*MINESWEEPER BY BEN HOFFMANN, ITW BERLIN 2020*/

/*BIBILIOTHEKEN EINBINDEN*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "myfunctions.c"

/*KONSTANTEN DEFINIEREN*/

#define KGRA  "\x1b[90m"
#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define MAX 64

/*FUNKTIONEN DEKLARIEREN*/

void gotoxy(int,int);
float abfrageCursorTaste(int,int,int,int*,char,int,int,int*,int,char);
void LegendeZeichnen(int,int);
void SchachbrettZeichnen(int,int,int,int,char,char);
int *MinenBerechnen(int,int,int,int);
int *UmfeldBerechnen(int,int,int*,int);
void Aufdecken(int,int,int,int*);
void NullAufdecken(int,int,int,int*,int,int,int*);
void HighscoreEintragen(float,char*,char);
void SiegesAnimation(int,int,int);
int HighscoreErmitteln(char);

/*GLOBALE VARIABLEN DEFINIEREN*/

int x,y;

/*START*/

int main(void)
{
//	system("cls");
//	itwIntro(0,11);
//	delay(1000);
//	system("cls");
//	introEichhoernchen (0,7);
//	delay(1000);
	
	char Eingabe,tmp,Kontrollansicht=0,level=2,ErsteNull=1;
	int i,z;
	int Spielbrett=8,schwierigkeit=6,highscore=0;
	int *MinenArrayPointer;
	int *VergleichsArrayPointer;
	int VergleichsArray[MAX][MAX];
	char userName[25] = { "user" };
	char *userNamePtr;
	float score;
	
	srand(time(NULL));
	highscore=HighscoreErmitteln(0);
	
	do
	{
	x=15,y=3; //Cursorstartposition
	Eingabe=0;
	system("cls");
	//Men� zeichnen
	MinesweeperMenu(0,10); //Hintergrundgrafik generieren
	gotoxy(0,12);
	printf("\n\n\t\t\t%sM I N E S W E E P E R",KYEL);
	printf("\n\n\t\t\t%s[s] starten als %s",KRED,userName);
	printf("\n\t\t\t[e] einstellungen (%dx%d,",Spielbrett,Spielbrett);
			switch(level)
		{
			case 0:printf("Aktuell sehr leicht)");schwierigkeit=10;break; //10% Minen
			case 1:printf("Aktuell leicht)");schwierigkeit=8;break; //12,5%
			case 2:printf("Aktuell normal)");schwierigkeit=6;break; //17%
			case 3:printf("Aktuell schwer)");schwierigkeit=4;break; //25% 
			case 4:printf("Aktuell sehr schwer)");schwierigkeit=3;break; //33%
		}
	printf("\n\t\t\t[h] highscores");
	printf("\n\t\t\t[ESC] beenden");
	Eingabe=getch();
	if(Eingabe=='e') //Einstellungen
	{
		do {
		system("cls");
		MinesweeperMenu(0,10);
		gotoxy(0,12);
		printf("\n\t\t%sE I N S T E L L U N G E N",KYEL);
		printf("\n\n\t\t%s[u] Namen aendern (Aktuell %s)",KRED,userName);
		printf("\n\t\t%s[f] Spielfeldgroesse aendern (Aktuell %2dx%2d)",KRED,Spielbrett,Spielbrett);
		printf("\n\t\t%s[l] Schwierigkeitslevel aendern ",KRED);
			switch(level)
			{
				case 0:printf("(Aktuell sehr leicht)");schwierigkeit=10;break; //10% Minen
				case 1:printf("(Aktuell leicht)");schwierigkeit=8;break; //12,5%
				case 2:printf("(Aktuell normal)");schwierigkeit=6;break; //17%
				case 3:printf("(Aktuell schwer)");schwierigkeit=4;break; //25% 
				case 4:printf("(Aktuell sehr schwer)");schwierigkeit=3;break; //33%
			}
		printf("\n\t\t%s[n] Erste Null automatisch aufdecken (Aktuell ",KRED,ErsteNull);
			switch(ErsteNull)
			{
				case 0:printf("aus)");break;
				case 1:printf("ein)");break;
			}
		printf("\n\t\t%s[k] Entwickleransicht zeigen (Aktuell ",KRED,Kontrollansicht);
			switch(Kontrollansicht)
			{
				case 0:printf("aus)");break;
				case 1:printf("ein)");break;
			}
		printf("\n\t\t%s[z] Zurueck",KRED);
		Eingabe=getch();
		if(Eingabe=='u')
			{
				for(i=0;userName[i]!='\0';i++)userName[i]='\0';
				printf("\n\n\t\t\t\t%sNeuer Name : ",KYEL);
				userNamePtr=eingabeText(24);
				for(i=0;userNamePtr[i]!='\0';i++)userName[i]=userNamePtr[i];
			}
		if(Eingabe=='f')
			{
			printf("\n\n\t\t\t\t%sNeuer Wert : ",KYEL);
			Eingabe=eingabeZahl(2);
			if(Eingabe>2 && Eingabe<=64) 
				{
				Spielbrett=Eingabe;
				} else {printf(" Bitte zw. 2 und 64 waehlen");getch();}
			}
		if(Eingabe=='l')
			{
			printf("\n\n\t\t%sNeuer Wert (0 sehr leicht bis 4 sehr schwer) : ",KYEL);
			Eingabe=eingabeZahl(1);
			if(Eingabe>=0 && Eingabe<=4) 
				{
				level=Eingabe;
				} else {printf(" Bitte zw. 0 und 4 waehlen");getch();}
			}
		if(Eingabe=='k')
			{
			printf("\n\n\t\t\t%sHinweis - ist dieser Modus aktiv wird Ihre Punktzahl nicht gewertet\n\t\t\tNeuer Wert : ",KYEL);
			Eingabe=eingabeZahl(1);
			if(Eingabe>=0 && Eingabe<=1) 
				{
					Kontrollansicht=Eingabe;
				} else {printf(" Bitte zw. 1(an) und 0(aus) waehlen");getch();}
			}
		if(Eingabe=='n')
			{
			printf("\n\n\t\t\t\t%sNeuer Wert : ",KYEL);
			Eingabe=eingabeZahl(1);
			if(Eingabe>=0 && Eingabe<=1) 
				{
					ErsteNull=Eingabe;
				} else {printf(" Bitte zw. 1(an) und 0(aus) waehlen");getch();}
			}		
	} while(Eingabe!='z' && Eingabe!=13);
	}
	
	if(Eingabe=='h') //Highscore
	{
		highscore = HighscoreErmitteln(1);
	}
	
	if(Eingabe=='s') //Programm start
	{
	system("cls");
	//Minenarray erstellen und das Umfeld berechnen
	MinenArrayPointer=MinenBerechnen(x,y,Spielbrett,schwierigkeit);
	MinenArrayPointer=UmfeldBerechnen(x,y,MinenArrayPointer,Spielbrett);
	//Vergleichsarray erstellen zur fehlerfreien �berpr�fung der Siegbedingung
		int AnzahlMinen=0,AnzahlFrei=0;
		for(i=0;i<Spielbrett;i++)
		{
			for(z=0;z<Spielbrett;z++)
			{
				if(*(MinenArrayPointer+(i)*MAX+(z))==-1) 
				{
					AnzahlMinen++;
					VergleichsArray[z][i]=*(MinenArrayPointer+(i)*MAX+(z));
				}
				else 
				{	
					AnzahlFrei++;
					VergleichsArray[z][i]=0;
				}
			}
		}
		VergleichsArrayPointer=&VergleichsArray[0][0];
	//Grafische Elemente generieren
	gotoxy(0,0);
	MinesweeperMenu(0,10);
	LegendeZeichnen(1,2);
	SchachbrettZeichnen(x,y,x+Spielbrett,y+Spielbrett,0,0);
	//Cursorposition in der Legende anzeigen
	gotoxy(1,0);
	printf("%s%c%d%s(%2d,%2d)",KCYN,x+50,8-(y-3),KGRA,x,y);
	//Cursor zum Start bewegen und dynamische Abfrage starten
	gotoxy(x,y);
	score=abfrageCursorTaste(x,y,Spielbrett,MinenArrayPointer,Kontrollansicht,AnzahlMinen,AnzahlFrei,VergleichsArrayPointer,highscore,ErsteNull);
	//Ggfs. Punktzahl eintragen
	if(score>0) 
	{
		userNamePtr=&userName[0];
		HighscoreEintragen(score,userNamePtr,Kontrollansicht);
	}
	}
	
	//Ende Programm
	} while(Eingabe!=27);
	gotoxy(1,30);
	return 0;
}

void LegendeZeichnen(int startx,int starty)
{
	int i;
	for(i=0;i<12;i++)
	{
		gotoxy(startx+9,i);
		printf("%s%c",KGRA,221);
	}
	gotoxy(startx,starty);
	printf("%s[W]\nSuchen\n\n [A]\nMarkieren\n\n [ESC]\nZum Menue",KGRA);
}
void SchachbrettZeichnen(int startx,int starty,int endex,int endey,char farbwahl,char modus)
{
	int i,z;
	printf("%s",KWHT);
	//Farbwahl
	char farbe[9];
	if (farbwahl<0 || farbwahl>8) farbwahl=0;
	switch(farbwahl)
	{
		case 0: strcpy(farbe,"\x1B[37m");break;
		case 1: strcpy(farbe,"\x1B[31m");break;
		case 2: strcpy(farbe,"\x1B[0m");break;
		case 3: strcpy(farbe,"\x1B[32m");break;
		case 4: strcpy(farbe,"\x1B[33m");break;
		case 5: strcpy(farbe,"\x1B[34m");break;
		case 6: strcpy(farbe,"\x1B[35m");break;
		case 7: strcpy(farbe,"\x1B[36m");break;
		case 8: strcpy(farbe,"\x1b[90m");break;
	}
	//Rahmen zeichnen	
	printf("%s",farbe);
	for (i=0;i<=endey-starty;i++) 
	{
		if(i<endey-starty)
			{ //vertikal
			gotoxy(endex,starty+i);
			printf("%c",186);
			gotoxy(startx-1,starty+i);
			printf("%c",186);
			//Legende
			if(i<endex-startx)
			{
				gotoxy(startx+i,starty-2);
				printf("%c",65+i);
			}
			if(modus==0)
			{
				//innere Elemente
				for(z=0;z<endex-startx;z++)
				{
					gotoxy(startx+i,starty+z);
					printf("%c",176);
				}
			}
			}
		if(i<endex-startx)
			{ //horizontal
			gotoxy(startx+i,starty-1);
			printf("%c",205);
			gotoxy(startx+i,endey);
			printf("%c",205);
			//Legende
			if(i<endex-startx)
			{
				gotoxy(startx-3,starty+i);
				printf("%2d",endey-starty-i);
			}			
			}
	}
//eckenelemente
	gotoxy(startx-1,starty-1);
	printf("%c",201);
	gotoxy(startx-1,endey);
	printf("%c",200);
	gotoxy(endex,starty-1);
	printf("%c",187);
	gotoxy(endex,endey);
	printf("%c",188);
}

int *MinenBerechnen(int startx,int starty, int Spielbrett,int Schwierigkeit)
{
	//Breite & H�he k�nnen noch nicht im Array verw. werden (dynamic memory)
	static int MinenArray[MAX][MAX];
	int ix,iy,tmp=0;
	//Minenarray komplett leeren um zuf�llige Fehler in den Randbereichen zu unterbinden
	for(ix=0;ix<MAX;ix++)
	{
		for(iy=0;iy<MAX;iy++)
		{
			MinenArray[iy][ix]=0; 
		}
	}
//	int* MinenPointer;
	for(ix=0;ix<Spielbrett;ix++)
	{
		for(iy=0;iy<Spielbrett;iy++)
		{
			tmp=rand() % Schwierigkeit;
			if(tmp==1) 
			{
				MinenArray[iy][ix]=-1; 
				gotoxy(startx+ix,starty+iy);
//				printf("%s%c",KRED,207);
			}
			else MinenArray[iy][ix]=0;
		}
	}
	int *MinenPointer=&MinenArray[0][0];
	return MinenPointer;
}

int *UmfeldBerechnen(int startx,int starty,int *MinenArrayPointer,int Spielbrett)
{
		char tmp;
		int ix,iy,ivglx,ivgly;
		//Erweitertes Array erstellen
		for(iy=0;iy<Spielbrett;iy++) 
		{
			for(ix=0;ix<Spielbrett;ix++) 
			{
				if(*(MinenArrayPointer+iy*MAX+ix)!=-1) //generelle Abbruchbedingung
				{
					if(ix>=0 && iy>=0 && iy<Spielbrett && ix<Spielbrett)
						{	
							gotoxy(startx+ix,starty+iy);
							for(ivgly=-1,tmp=0;ivgly<2;ivgly++) //Abgleich mit umliegenden Feldern
							{
								for(ivglx=-1;ivglx<2;ivglx++)
								{
									if(*(MinenArrayPointer+(iy+ivgly)*MAX+(ix+ivglx))==-1)tmp++;		
								}						
							}
							*(MinenArrayPointer+iy*MAX+ix)=tmp;
						}
				}
			}
		}
		
		return MinenArrayPointer;
}

void HighscoreEintragen(float score,char *user,char kontrolle)
{
	FILE *out;
	char temp;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	if((out=fopen("highscore.txt","a"))==NULL)
	{
		printf("Highscore Liste konnte nicht ge�ffnet werden");
	}
	else
	{
		if(kontrolle==1) ;//fprintf(out,"> %6.0f [DEV] %s (%d-%02d-%02d) ",score,user,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
		else fprintf(out,"> %6.0f | %s (%d-%02d-%02d)(%02d:%02d)",score,user,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,tm.tm_hour,tm.tm_min);	
	}
	fclose(out);
}

int HighscoreErmitteln(char modus)
{
	if(modus==1)system("cls");
	if(modus==1)MinesweeperMenu(0,10);
	FILE *in;
	char temp,i=0,z=0;
	int tempscore[8],zwischen=0,multiplikator=1,highscore=0;
	
	if((in=fopen("highscore.txt","r"))==NULL)
	{
		printf("Highscore Liste konnte nicht ge�ffnet werden");
	}
	else
	{
		gotoxy(0,9);
		if(modus==1)printf("\t\t\t\t%sHighscoreliste%s\n",KYEL,KRED);
		while((temp=fgetc(in))!=EOF)
		{
			if(temp=='>') {if(modus==1)printf("\n\t\t\t");for(z=0;tempscore[z]!='\0';z++) tempscore[z]=0;}
			if(temp>=48 && temp<=57) {tempscore[i]=temp-48;i++;}
			if(temp=='|') 
			{
				while(i>0){zwischen+=(tempscore[i-1]*multiplikator);multiplikator*=10;i--;} 
				if(zwischen>=highscore) highscore=zwischen ;
			}
			if(temp==')') {while(i<0){tempscore[i]='\0';i--;};zwischen=0;multiplikator=1;i=0;}
			if(modus==1)fputc(temp,stdout);
			}
			if(modus==1)printf("\n\n\t\t\t\t%s[Highscore %d]",KYEL,highscore);
		}
		fclose(in);
		if(modus==1)getch();
		return highscore;
}

float abfrageCursorTaste(int startx,int starty,int Spielbrett,int *MinenArrayPointer,char Kontrollansicht,int AnzahlMinen, int AnzahlFrei,int *VergleichsArrayPointer,int highscore,char ErsteNull)
{
	clock_t start, ende;
	float time;
	int temp,ix,iy,wert,zeit,entdeckt=0,tmpix,tmpiy,z;
	char sieg=0,niederlage=0,ErsteNullAufgedeckt=0;
	float score;
	
	start = clock();

	//Kontrollansicht

	{
		gotoxy(startx,starty+Spielbrett+12);
		for(ix=0;ix<Spielbrett;ix++) 
		{
			printf("\n");
			for(iy=0;iy<Spielbrett;iy++) 
			{
					if(Kontrollansicht) 
					{

						printf("%s%2d,%2d%s[%2d]",KGRA,iy+startx,ix+starty,KYEL,*(MinenArrayPointer+ix*MAX+iy));
					}
					if((*(MinenArrayPointer+ix*MAX+iy)==0) && !ErsteNullAufgedeckt) 
					{
						ErsteNullAufgedeckt=1;
						tmpix=ix;
						tmpiy=iy;
					};
			}
		}
		if(ErsteNull) NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpix+startx,tmpiy+starty,VergleichsArrayPointer);
		//Array wieder mit 0 f�llen und Vergleichsarray �berpr�fen (entdeckte Felder z�hlen)
				for(iy=0,entdeckt=0;iy<Spielbrett;iy++)
					{
						for(ix=0;ix<Spielbrett;ix++)
						{
							if(*(VergleichsArrayPointer+(ix)*MAX+(iy))==1) entdeckt++;
							if(*(MinenArrayPointer+(ix)*MAX+(iy))==-2) *(MinenArrayPointer+(ix)*MAX+(iy))=0;			
						}
					};
		gotoxy(1,0);printf("%s%c%d%s(noch %d)",KCYN,x+50,Spielbrett-(y-starty),KGRA,AnzahlFrei-entdeckt);
		gotoxy(x,y);
	}
	while(temp!=27 && sieg!=1 && niederlage!=1)
	{
		if(kbhit())
		{
			temp=getch();
			if(temp==224)
			{
				temp=getch();
				switch(temp)
				{
					case 80:if(y<starty+Spielbrett-1){y++;gotoxy(1,0);printf("%s%c%d%s(noch %3d)",KCYN,x+50,Spielbrett-(y-starty),KGRA,AnzahlFrei-entdeckt);gotoxy(x,y);};break;
					case 75:if(x>startx){x--;gotoxy(1,0);printf("%s%c%d%s(noch %3d)",KCYN,x+50,Spielbrett-(y-starty),KGRA,AnzahlFrei-entdeckt);gotoxy(x,y);};break;
					case 77:if(x<startx+Spielbrett-1){x++;gotoxy(1,0);printf("%s%c%d%s(noch %3d)",KCYN,x+50,Spielbrett-(y-starty),KGRA,AnzahlFrei-entdeckt);gotoxy(x,y);};break;
					case 72:if(y>starty){y--;gotoxy(1,0);printf("%s%c%d%s(noch %3d)",KCYN,x+50,Spielbrett-(y-starty),KGRA,AnzahlFrei-entdeckt);gotoxy(x,y);};break;
				}
			}
			else 
			{
				switch(temp)
				{
					case 119: //W
							wert=*(MinenArrayPointer+(y-starty)*MAX+(x-startx))+48;
							if (wert==47) {printf("%s%c",KRED,207);Aufdecken(startx,starty,Spielbrett,MinenArrayPointer);getch();niederlage=1;score=0;}
							if (wert>51) {printf("%s%c",KMAG,wert);*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;}
							if (wert==51) {printf("%s%c",KYEL,wert);*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;}
							if (wert==50) {printf("%s%c",KGRN,wert);*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;}
							if (wert==49) {printf("%s%c",KGRA,wert);*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;}
							if (wert==48) 
							{
								printf("%s ",KGRA);
								putch(8);
								*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;
								NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,x,y,VergleichsArrayPointer);
							}
							*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;
							//Array wieder mit 0 f�llen und Vergleichsarray �berpr�fen (entdeckte Felder z�hlen)
									for(iy=0,entdeckt=0;iy<Spielbrett;iy++)
									{
										for(ix=0;ix<Spielbrett;ix++)
										{
											if(*(VergleichsArrayPointer+(ix)*MAX+(iy))==1) entdeckt++;
											if(*(MinenArrayPointer+(ix)*MAX+(iy))==-2) *(MinenArrayPointer+(ix)*MAX+(iy))=0;			
										}
									};
							if(Kontrollansicht)
								{
									gotoxy(startx+Spielbrett+4,starty);
									ende = clock();
									time = ((float)(ende - start) / CLOCKS_PER_SEC * 1000) / 1000;
									printf("%sFRE:%d MIN:%d TIM:%.2f",KYEL,AnzahlFrei,AnzahlMinen,time);
									gotoxy(startx+Spielbrett+4,starty+1);
									printf("%sENT:%d WIN:%d LOS:%d",KYEL,entdeckt,sieg,niederlage);
									gotoxy(x,y);
								}
							if(entdeckt==AnzahlFrei && !niederlage) 
								{
									ende = clock();
									SiegesAnimation(startx,starty,Spielbrett);
									time = ((float)(ende - start) / CLOCKS_PER_SEC * 1000) / 1000;
									score = round((1/((time+10)/(AnzahlMinen)))*1000+(AnzahlFrei/1.5));
									RahmenZeichnen(startx-2,Spielbrett+6,startx+30,Spielbrett+11,4);
									gotoxy(startx-1,Spielbrett+6);
									printf("%s\tAnzahl freie Felder : %d \n\t\tAnzahl Minen: %d \n\t\tZeit: %.2f Sekunden\n\t\tScore : %.0f",KYEL,AnzahlFrei,AnzahlMinen,time,score);
									if(score>highscore && !Kontrollansicht) printf("\n\t\t%s NEUE HIGHSCORE!",KMAG); else printf("\n\t\tAktuelle Highscore : %d", highscore);
									getch();
									sieg=1;
								}

						break;			
					case 97://A
						{
							printf("%s%c%s",KRED,232,KWHT);
							putch(8);
							break;
						} 
					case 32:putch(' ');putch(8);break; //ESC
				}
				//Kontrollansicht VglArray
				if(Kontrollansicht)
				{
					gotoxy(0,starty+Spielbrett+Spielbrett+13);
					for(ix=0;ix<Spielbrett;ix++) 
					{
					printf("\n");
					for(iy=0;iy<Spielbrett;iy++) 
					{
						printf("%s%2d,%2d%s[%2d]",KGRA,iy+startx,ix+starty,KYEL,*(VergleichsArrayPointer+ix*MAX+iy));
					}
					}
				}		
				gotoxy(x,y);
			}
		}
	} if(temp==27 && !sieg) score=0;
	return score;
}

void Aufdecken(int startx,int starty,int Spielbrett,int *MinenArrayPointer)
{
	int ix,iy;
	char Text[15]={ "V E R L O R E N" };
	for(ix=0;ix<Spielbrett;ix++)
	{
		for(iy=0;iy<Spielbrett;iy++)
		{
				gotoxy(startx+ix,starty+iy);
				if(*(MinenArrayPointer+iy*MAX+ix)==-1) printf("%s%c",KRED,207);
				else printf("%s%d",KGRA,*(MinenArrayPointer+iy*MAX+ix));
				delay(5);
		}
	}
	for(ix=0;ix<15;ix++)
	{
		gotoxy(startx-1+ix,Spielbrett+4);
		printf("%s%c",KRED,Text[ix]);
		delay(50);
	}
	gotoxy(startx,starty);
}

void NullAufdecken(int startx,int starty,int Spielbrett,int *MinenArrayPointer,int tmpx,int tmpy,int *VergleichsArrayPointer)
{
		char wert,x1=0,x2=0,x3=0,x4=0,x5=0,x6=0,x7=0,x8=0,aufgedeckt=0;
		int ix,iy,ivglx,ivgly;
			for(ivgly=-1;ivgly<2;ivgly++) //Abgleich mit umliegenden Feldern
			{
				for(ivglx=-1;ivglx<2;ivglx++)
				{
				if(*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))>=0)
					{
					wert=*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))+48;
					if(tmpx-startx+ivglx>=0 && tmpy-starty+ivgly>=0 && tmpy-starty+ivgly<Spielbrett && tmpx-startx+ivglx<Spielbrett)
					{
						gotoxy(tmpx+ivglx,tmpy+ivgly);
						if (wert==47) {printf("%s%c",KRED,207);*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;}
						if (wert>51) {printf("%s%c",KMAG,wert);*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;}
						if (wert==51) {printf("%s%c",KYEL,wert);*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;}
						if (wert==50) {printf("%s%c",KGRN,wert);*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;}
						if (wert==49) {printf("%s%c",KGRA,wert);*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;}
						if (wert==48) 
						{
							
							printf("%s ",KGRA);
							if(x1==0) {x1=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x2==0) {x2=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x3==0) {x3=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x4==0) {x4=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x5==0) {x5=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x6==0) {x6=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x7==0) {x7=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x8==0) {x8=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,Spielbrett,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
						}
					}
					}
				}						
			}
		gotoxy(x,y);
}

void SiegesAnimation(startx,starty,Spielbrett)
{
	char i,iy,f=0,text[42]={ "G E W O N N E N ! HERZLICHEN GLUECKWUNSCH" };
	for(i=0;i<42;i++,f++)
	{ 
	if(f>8) f=0;
	SchachbrettZeichnen(startx,starty,startx+Spielbrett,starty+Spielbrett,f,1);
	gotoxy(startx-1+i,Spielbrett+4);
	printf("%s%c",KGRN,text[i]);
	delay(100);
	}
	gotoxy(startx,starty);
}
