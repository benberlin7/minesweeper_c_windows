void RahmenZeichnen(int,int,int,int,int);
char* eingabeText(int);
void gotoxy(int,int);

//gotoxy
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//itwIntro (Eigene)
void itwIntro (int bgfarbe, int fgfarbe)
{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);
char introItw[2250]={ "...............................................................................\n...............................................................................\n.......-:+:-...................................................................\n.....-*=###==+-................................................................\n....:=########*-...............................................................\n....*##########:...........:*-.................................................\n....:=########=-..........-##:.................................................\n.....-*=####=+-..........-=@#:.................................................\n........----............-=@@#:.................................................\n......................-+@@@@#:.................................................\n..................-+=#@@@@@@@@###############*-..+#############*.....-=########\n..........-:++.....---*@@@@@#:----:=@@@@@@@*:-....-:=@@@@@@@=:--......-:*@@@@=:\n...-:+*=#@@@@=-.......*@@@@@#:......-=@@@@#-.........-#@@@@=............-#@#-..\n..+=**#@@@@@@=-.......*@@@@@#:.......-=@@@@=..........:#@@@@*...........*@#-...\n.......*@@@@@=-.......*@@@@@#:........-#@@@@*..........:@@@@@+.........+@#:....\n.......+@@@@@=-.......*@@@@@#:.........:@@@@@+........-#@@@@@#:.......+@@+.....\n.......+@@@@@=-.......*@@@@@#:..........+@@@@#:......-=@=*@@@@#-.....:#@*......\n.......+@@@@@=-.......*@@@@@#:...........*@@@@#-....-=@*.-=@@@@#....-#@*.......\n.......+@@@@@=-.......*@@@@@#:...........-=@@@@=....=@=-..-#@@@@=...=@=-.......\n.......+@@@@@=-.......*@@@@@#:............-#@@@@*..=@=-....-@@@@@*.*@#-........\n.......+@@@@@=-.......*@@@@@#:.............:@@@@@+=@=.......:@@@@@=@#:.........\n.......+@@@@@=-.......+@@@@@@:..............:@@@@@@=.........+@@@@@@+..........\n.......+@@@@@#-.......:#@@@@@#+-..-+#=-......+@@@@=-..........*@@@@*...........\n.....-:#@@@@@@=-.......+@@@@@@@@@@@@=-.......-=@@=-............=@@=-...........\n..:*==============*-.....:*#@@@#=*:...........-==-..............#=-............\n...............................................................................\n..............................................................................." };
int i;
for(i=0;introItw[i]!='\0';i++) 
{
if(introItw[i]=='.') {fgfarbe=7;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);} else {fgfarbe=10;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);};	
printf("%c",introItw[i]);
delay(1);
}
}

//intro Eichhörnchen (Eigene)
void introEichhoernchen (int bgfarbe, int fgfarbe)
{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);
char introItw[1800]={ "...............................................................................\n.....B.E.N....H.O.F.F.M.A.N.N..................................................\n..................................................................:-...........\n.....2.0.2.0.....................................................-***..........\n................................................................-+*==:.........\n..............................................................-:++===*-........\n............................................................-++++**=*==*.......\n................................................-:+****=*=**+++++*++::+==-.....\n..............................................-++*******==*********:++:==*.....\n.............................................:+++********=****++++++++:+++-....\n............................................-:+++++********==***+++++*++++.....\n............................................::::+++++***++++**=***==******-....\n............................................:++:++++++++++**++#=====#*+==+.....\n............................................:+++++++:+++*****+=##==:...........\n..............--::-------:-:***=**++*+-.....:+++++++++**=*****:-...............\n.......-:+++*+++*****+******=========####=*--+++++++****=*****-................\n.....:+***++++************=====###############=***++++*=====*+-................\n...:+*****************========###########@#@####=*****======-....--............\n....--:++*************+++*********=====####=#=#=***++:--*===*+++:--:-..........\n.........................---...................................................\n...............................................................................\n...............................................................................\n" };
int i;
for(i=0;introItw[i]!='\0';i++) 
{
if(introItw[i]=='.') {fgfarbe=7;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);} else {fgfarbe=9;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);};
printf("%c",introItw[i]);
delay(1);
}
}

//Minesweeper Menu (Eigene)
void MinesweeperMenu (int bgfarbe, int fgfarbe)
{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);
char introItw[2980]={ "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@::::+@@@@*::::::::::::::::::::::*@@@@+::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@::::+@@@@*::::::::::::::::::::::*@@@@+::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@=::::::::::::::::::::::::::::::::=@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@=::::::::::::::::::::::::::::::::=@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@****+::::----------::::::::::::::::::+****@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@:::::::::-........-:::::::::::::::::::::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@:::::::::-........-:::::::::::::::::::::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@:::::::::-........-:::::::::::::::::::::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@:::::::::-........-:::::::::::::::::::::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@=::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::=@@@@@@@@\n@@@@@@@@@=::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::=@@@@@@@@\n@@@@@@@@@#=========::::::::::::::::::::::::::::::::::::::::::=========#@@@@@@@@\n@@@@@@@@@@@@@@@@@@@::::::::::::::::::::::::::::::::::::::::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@::::::::::::::::::::::::::::::::::::::::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@::::::::::::::::::::::::::::::::::::::::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@::::::::::::::::::::::::::::::::::::::::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@=::::::::::::::::::::::::::::::::=@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@=::::::::::::::::::::::::::::::::=@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@*+++*====+::::::::::::::::::::::+====*+++*@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@::::+@@@@*::::::::::::::::::::::*@@@@+::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@::::*@@@@*::::::::::::::::::::::*@@@@*::::@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::::=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#====#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" };
int i;
for(i=0;introItw[i]!='\0';i++) 
{
if(introItw[i]=='@') {introItw[i]='.';fgfarbe=8;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);} else {fgfarbe=3;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);};
if(introItw[i]==':') {fgfarbe=9;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgfarbe*16+fgfarbe);};
printf("%c",introItw[i]);
}
}

//RahmenZeichnen (Eigene)
void RahmenZeichnen(int startx,int starty,int endex,int endey,int farbwahl)
{
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
	int i,z;
	//Rahmen zeichnen	
	printf("%s",farbe);
	for (i=0;i<=endex-startx;i++) 
	{
		if(i<endey-starty)
			{ //vertikal
			gotoxy(endex,starty+i);
			printf("%c",186);
			gotoxy(startx-1,starty+i);
			printf("%c",186);
			//Legende
//			if(i<endex-startx)
//			{
//				gotoxy(startx+i,starty-2);
//				printf("%c",65+i);
//			}
			//innere Elemente
//			for(z=0;z<endex-startx;z++)
//			{
//				gotoxy(startx+i,starty+z);
//				printf("%c",176);
//			}
			}
		if(i<endex-startx)
			{ //horizontal
			gotoxy(startx+i,starty-1);
			printf("%c",205);
			gotoxy(startx+i,endey);
			printf("%c",205);
			//Legende
//			if(i<endex-startx)
//			{
//				gotoxy(startx-3,starty+i);
//				printf("%2d",endey-starty-i);
//			}			
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
//Eingabe Text 9.3.2020


char* eingabeText(int anz)
{
	static char text[255];
	char *charptr;
	int i=0,y;
	
	do
	{
		text[i]=getch();
		
		if(i>=0 && i<anz && !(text[i]==8 || text[i]==13))
		{
			printf("%c",text[i]);
			i++;
		}

		if (text[i]==8 && i>0)
		{
			printf("%c",text[i]);
			printf(" ");
			printf("%c",text[i]);
			text[i]=0;
			i--;
		}
	} while(!(text[i]==13));
	text[i]='\0';
	charptr=&text[0];
	return charptr;
}

//Zahleneingabe Übung 26.2

int eingabeZahl(int stellen)
{
int abbruch=0,ganzzahl=0,i,y,potenz=1;
int zahl[stellen]; //max 9 elemente

for(i=1;i<=stellen;i++)
{
	do
	{
		zahl[i]=getch();
		if (zahl[i]==13) abbruch=1;
	} while (!(zahl[i]<=57 && zahl[i]>=48 || zahl[i]==13));
	if (abbruch) 
	{
		abbruch=stellen;
		stellen=i-1;
		i=abbruch;
	} 
	else 
	{
		printf("%d",zahl[i]-48);
		zahl[i]=zahl[i]-48;
	}
}
if (stellen>1) {
	for(i=1;i<=stellen;i++)
	{
		for(y=i;y<stellen;y++)
		{
			potenz=potenz*10;
		}
		ganzzahl+=zahl[i]*potenz;
		potenz=1;
	}
	//printf("\nGanzzahl : %d\n",ganzzahl);
	} 
else 
	{
	ganzzahl=zahl[1];
	//printf("\nGanzzahl : %d\n",ganzzahl);
	}
return(ganzzahl);
}
//Gleitkommazahl übung 28.2

double eingabeGleitkommaZahl(int vorkomma,int nachkomma)
{
	double gleitkommazahl=0,faktor=1;
	char tmp,komma=0,vorkommaArray[15],nachkommaArray[7];
	int zVorkomma=0,zNachkomma=0;
	if (vorkomma>15)vorkomma=15;
	if (nachkomma>7)nachkomma=7;
	do
	{
		tmp=getch();
		if((tmp<=57 && tmp>=48) && zVorkomma<vorkomma && !komma)
		{
			putch(tmp);
			vorkommaArray[zVorkomma]=tmp;
			zVorkomma++;
		}
		if((tmp==',' || tmp=='.') && !komma)
		{
			putch(tmp);
			komma=1;
		}
		if((tmp<=57 && tmp>=48) && zNachkomma<nachkomma && komma)
		{
			putch(tmp);
			nachkommaArray[zNachkomma]=tmp;
			zNachkomma++;
		}
		if(tmp==8 && (komma || zNachkomma>0 || zVorkomma>0))
		{
			if(!komma && zVorkomma>0) zVorkomma--;
			if(komma && zNachkomma==0) komma=0;
			if(komma && zNachkomma>0) zNachkomma--;
			putch(8);
			putch(' ');
			putch(8);
		}
	}while(tmp!=13);
	//BERECHNUNG DER AUSGABE
		//Vorkomma
	for(zVorkomma--;zVorkomma>=0;zVorkomma--,faktor*=10)	
	gleitkommazahl=gleitkommazahl+(vorkommaArray[zVorkomma]-48)*faktor;
		//Nachkomma
	for(nachkomma=0,faktor=0.1;nachkomma<zNachkomma;nachkomma++,faktor/=10)	
	gleitkommazahl=gleitkommazahl+(nachkommaArray[nachkomma]-48)*faktor;
	return(gleitkommazahl);
}
