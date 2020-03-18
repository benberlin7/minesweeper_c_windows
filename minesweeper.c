/*MINESWEEPER BY BEN HOFFMANN - benberlin7 via github*/

/*BIBILIOTHEKEN EINBINDEN*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

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
void abfrageCursorTaste(int,int,int,int,int*,char,char,char,int*);
void LegendeZeichnen(int,int);
void SchachbrettZeichnen(int,int,int,int,char);
int *MinenBerechnen(int,int,int,int,int);
int *UmfeldBerechnen(int,int,int*,int,int);
void Aufdecken(int,int,int,int,int*);
void NullAufdecken(int,int,int,int,int*,int,int,int*);
void HighscoreEintragen(int,char*);
void delay(unsigned int);
void SiegesAnimation(int,int,int,int);

/*GLOBALE VARIABLEN DEFINIEREN*/

int x,y;

/*START*/

int main(void)
{
	system("cls");
	char Eingabe,tmp,Kontrollansicht=0,level=2;
	int i,z;
	int Spielbrett=8,schwierigkeit=4;
	srand(time(NULL));
	//int MinenArray[][]; 
	int *MinenArrayPointer;
	int *VergleichsArrayPointer;
	int VergleichsArray[MAX][MAX];
	
	int bgcolor=0, fgcolor=4;
	CONSOLE_CURSOR_INFO ci = {10,FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &ci);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgcolor*16+fgcolor);
	
	do
	{
	x=15,y=3; //Cursorstartposition
	Eingabe=0;
	system("cls");
	gotoxy(2,2);
	printf("\t%sMinessweeper",KCYN);
	printf("\n\tMenue");
	printf("\n\n\t%s[s] Starten",KYEL);
	printf("\n\n\t%s[e] Einstellungen",KYEL);
//	printf("\n\n\t%s[h] Highscoreliste",KYEL);
	printf("\n\n\t%s[ESC] Beenden",KYEL);
	Eingabe=getch();
	if(Eingabe=='e')
	{
	do {
	system("cls");
	gotoxy(2,2);
	printf("\t%sMinessweeper",KCYN);
	printf("\n\tEinstellungen");
	printf("\n\n\t%s[f] Spielfeldgroesse aendern (Aktuell %2dx%2d)",KYEL,Spielbrett,Spielbrett);
	printf("\n\n\t%s[l] Schwierigkeitslevel aendern ",KYEL);
		switch(level)
		{
			case 0:printf("(Aktuell sehr leicht)");schwierigkeit=10;break;
			case 1:printf("(Aktuell leicht)");schwierigkeit=5;break;
			case 2:printf("(Aktuell normal)");schwierigkeit=4;break;
			case 3:printf("(Aktuell schwer)");schwierigkeit=3;break;
			case 4:printf("(Aktuell sehr schwer)");schwierigkeit=2;break;
		}
	printf("\n\n\t%s[k] Entwickler-Kontrollansicht zeigen (Aktuell %2d)",KYEL,Kontrollansicht);
	printf("\n\n\t%s[z] Zurueck",KYEL);
	Eingabe=getch();
	if(Eingabe=='f')
		{
		printf("\n\n\tNeuer Wert : ");
		Eingabe=eingabeZahl(2);
		if(Eingabe>2 && Eingabe<64) 
			{
			Spielbrett=Eingabe;
			} else printf("Bitte zw. 2 und 64 waehlen");
		}
	if(Eingabe=='l')
		{
		printf("\n\n\tNeuer Wert (0 sehr leicht bis 4 sehr schwer) : ");
		Eingabe=eingabeZahl(1);
		if(Eingabe>=0 && Eingabe<=4) 
			{
			level=Eingabe;
			} else printf("Bitte zw. 0 und 4 waehlen");
		}
	if(Eingabe=='k')
		{
		printf("\n\n\tNeuer Wert : ");
		Eingabe=eingabeZahl(2);
		if(Eingabe>=0 && Eingabe<=1) 
			{
				Kontrollansicht=Eingabe;
			} else printf("Bitte zw. 1(an) und 0(aus) waehlen");
		}
	} while(Eingabe!='z');
	}
	if(Eingabe=='s')
	{
	system("cls");
	MinenArrayPointer=MinenBerechnen(x,y,Spielbrett,Spielbrett,schwierigkeit);
	MinenArrayPointer=UmfeldBerechnen(x,y,MinenArrayPointer,Spielbrett,Spielbrett);
	LegendeZeichnen(1,2);
	SchachbrettZeichnen(x,y,x+Spielbrett,y+Spielbrett,0);
	//Cursorposition am Anfang anzeigen
		gotoxy(1,0);
		printf("%s%c%d%s(%2d,%2d)",KCYN,x+50,8-(y-3),KGRA,x,y);
	//AnzahlMinen ermitteln und Vergleichsarray erstellen
	char AnzahlMinen=0,AnzahlFrei=0;
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
	gotoxy(x,y);
	abfrageCursorTaste(x,y,Spielbrett,Spielbrett,MinenArrayPointer,Kontrollansicht,AnzahlMinen,AnzahlFrei,VergleichsArrayPointer);
	}
	
	//Ende Programm
	} while(Eingabe!=27);
	gotoxy(1,11);
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
void SchachbrettZeichnen(int startx,int starty,int endex,int endey,char farbwahl)
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
			//innere Elemente
			for(z=0;z<endex-startx;z++)
			{
				gotoxy(startx+i,starty+z);
				printf("%c",176);
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

int *MinenBerechnen(int startx,int starty, int SpielbrettLaenge,int SpielbrettHoehe,int Schwierigkeit)
{
	static int MinenArray[MAX][MAX];
	int ix,iy,tmp=0;
	for(ix=0;ix<SpielbrettLaenge;ix++)
	{
		for(iy=0;iy<SpielbrettHoehe;iy++)
		{
			tmp=rand() % Schwierigkeit;
			if(tmp==1) 
			{
				MinenArray[iy][ix]=-1; 
				gotoxy(startx+ix,starty+iy);
			}
			else MinenArray[iy][ix]=0;
		}
	}
	int *MinenPointer=&MinenArray[0][0];
	return MinenPointer;
}

int *UmfeldBerechnen(int startx,int starty,int *MinenArrayPointer,int SpielbrettLaenge,int SpielbrettHoehe)
{
		char tmp;
		int ix,iy,ivglx,ivgly;
		//Erweitertes Array erstellen
		for(iy=0;iy<SpielbrettHoehe;iy++) 
		{
			for(ix=0;ix<SpielbrettLaenge;ix++) 
			{
				if(*(MinenArrayPointer+iy*MAX+ix)!=-1) //generelle Abbruchbedingung
				{
					if(ix>=0 && iy>=0 && iy<SpielbrettHoehe && ix<SpielbrettLaenge)
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

void HighscoreEintragen(int highscore,char *user)
{
//	FILE *out;
//	char temp;
//	if((out=fopen("c:\\it9source\\minesweeper\\highscore.txt","a"))==NULL)
//	{
//		printf("Highscore Liste konnte nicht geöffnet werden");
//	}
//	else
//	{
//		fputs(highscore,out);
//		fputs(user,out);
//		fputs("\n",out);			
//	}
//	fclose(out);
//	return 0;
}

void abfrageCursorTaste(int startx,int starty,int SpielbrettLaenge,int SpielbrettHoehe,int *MinenArrayPointer,char Kontrollansicht,char AnzahlMinen, char AnzahlFrei,int *VergleichsArrayPointer)
{
	int temp,ix,iy,wert,zeit;
	char entdeckt=0;

	
	//Kontrollansicht
	if(Kontrollansicht)
	{
		gotoxy(0,starty+SpielbrettHoehe+5);
		for(ix=0;ix<SpielbrettLaenge;ix++) 
		{
			printf("\n");
			for(iy=0;iy<SpielbrettHoehe;iy++) 
			{
				printf("%s%2d,%2d%s[%2d]",KGRA,iy+startx,ix+starty,KYEL,*(MinenArrayPointer+ix*MAX+iy));
			}
		}
		gotoxy(x,y);
	}
	while(temp!=27)
	{
		if(kbhit())
		{
			temp=getch();
			if(temp==224)
			{
				temp=getch();
				switch(temp)
				{
					case 80:if(y<starty+SpielbrettHoehe-1){y++;gotoxy(1,0);printf("%s%c%d%s(%2d,%2d)",KCYN,x+50,SpielbrettHoehe-(y-starty),KGRA,x,y);gotoxy(x,y);};break;
					case 75:if(x>startx){x--;gotoxy(1,0);printf("%s%c%d%s(%2d,%2d)",KCYN,x+50,SpielbrettHoehe-(y-starty),KGRA,x,y);gotoxy(x,y);};break;
					case 77:if(x<startx+SpielbrettLaenge-1){x++;gotoxy(1,0);printf("%s%c%d%s(%2d,%2d)",KCYN,x+50,SpielbrettHoehe-(y-starty),KGRA,x,y);gotoxy(x,y);};break;
					case 72:if(y>starty){y--;gotoxy(1,0);printf("%s%c%d%s(%2d,%2d)",KCYN,x+50,SpielbrettHoehe-(y-starty),KGRA,x,y);gotoxy(x,y);};break;
				}
			}
			else 
			{
				switch(temp)
				{
					case 119: //W
							wert=*(MinenArrayPointer+(y-starty)*MAX+(x-startx))+48;
							if (wert==47) {printf("%s%c",KRED,207);Aufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer);}
							if (wert>51) {printf("%s%c",KMAG,wert);*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;}
							if (wert==51) {printf("%s%c",KYEL,wert);*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;}
							if (wert==50) {printf("%s%c",KGRN,wert);*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;}
							if (wert==49) {printf("%s%c",KGRA,wert);*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;}
							if (wert==48) 
							{
								printf("%s ",KGRA);
								putch(8);
								*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;
								NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,x,y,VergleichsArrayPointer);
							}
							*(VergleichsArrayPointer+(y-starty)*MAX+(x-startx))=1;
							//Array wieder mit 0 füllen und Vergleichsarray überprüfen
									for(iy=0,entdeckt=0;iy<SpielbrettHoehe;iy++)
									{
										for(ix=0;ix<SpielbrettLaenge;ix++)
										{
											if(*(VergleichsArrayPointer+(ix)*MAX+(iy))==1) entdeckt++;
											if(*(MinenArrayPointer+(ix)*MAX+(iy))==-2) *(MinenArrayPointer+(ix)*MAX+(iy))=0;			
										}
									};
							if(entdeckt==AnzahlFrei) SiegesAnimation(startx,starty,SpielbrettLaenge,SpielbrettHoehe);
						break;			
					case 97://A
						{
							printf("%s%c%s",KRED,232,KWHT);
							putch(8);
							break;
						} 
					case 115:printf("%s%c%s",KRED,207,KWHT);putch(8);break; //S
					case 100:printf("%s%c%s",KYEL,254,KWHT);putch(8);break; //D
					case 32:putch(' ');putch(8);break; //ESC
				}
				//Kontrollansicht VglArray
				if(Kontrollansicht)
				{
				gotoxy(0,starty+SpielbrettHoehe+SpielbrettHoehe+6);
				for(ix=0;ix<SpielbrettLaenge;ix++) 
				{
				printf("\n");
				for(iy=0;iy<SpielbrettHoehe;iy++) 
				{
					printf("%s%2d,%2d%s[%2d]",KGRA,iy+startx,ix+starty,KYEL,*(VergleichsArrayPointer+ix*MAX+iy));
				}
			}
		}
		gotoxy(x,y);
			}
		}
	}
}

void Aufdecken(int startx,int starty,int SpielbrettLaenge,int SpielbrettHoehe,int *MinenArrayPointer)
{
	int ix,iy;
	char Text[15]={ "V E R L O R E N" };
	for(ix=0;ix<SpielbrettLaenge;ix++)
	{
		for(iy=0;iy<SpielbrettHoehe;iy++)
		{
				gotoxy(startx+ix,starty+iy);
				if(*(MinenArrayPointer+iy*MAX+ix)==-1) printf("%s%c",KRED,207);
				else printf("%s%d",KGRA,*(MinenArrayPointer+iy*MAX+ix));
				delay(10);
		}
	}
	for(ix=0;ix<15;ix++)
	{
		gotoxy(startx-1+ix,SpielbrettHoehe+4);
		printf("%s%c",KRED,Text[ix]);
		delay(50);
	}
	gotoxy(startx,starty);
}

void NullAufdecken(int startx,int starty,int SpielbrettLaenge,int SpielbrettHoehe,int *MinenArrayPointer,int tmpx,int tmpy,int *VergleichsArrayPointer)
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
					if(tmpx-startx+ivglx>=0 && tmpy-starty+ivgly>=0 && tmpy-starty+ivgly<SpielbrettHoehe && tmpx-startx+ivglx<SpielbrettLaenge)
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
							if(x1==0) {x1=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x2==0) {x2=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x3==0) {x3=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x4==0) {x4=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x5==0) {x5=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x6==0) {x6=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x7==0) {x7=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
							if(x8==0) {x8=1;*(MinenArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=-2;*(VergleichsArrayPointer+(tmpy-starty+ivgly)*MAX+(tmpx-startx+ivglx))=1;NullAufdecken(startx,starty,SpielbrettLaenge,SpielbrettHoehe,MinenArrayPointer,tmpx+ivglx,tmpy+ivgly,VergleichsArrayPointer);};
						}
					}
					}
				}						
			}
		gotoxy(x,y);
}

void SiegesAnimation(startx,starty,SpielbrettLaenge,SpielbrettHoehe)
{
	char i,iy,f=0,text[42]={ "G E W O N N E N ! HERZLICHEN GLUECKWUNSCH" };
	for(i=0;i<42;i++,f++)
	{ 
	if(f>8) f=0;
	SchachbrettZeichnen(startx,starty,startx+SpielbrettLaenge,starty+SpielbrettHoehe,f);
	gotoxy(startx-1+i,SpielbrettHoehe+4);
	printf("%s%c",KGRN,text[i]);
	delay(100);
	}
	gotoxy(startx,starty);
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}