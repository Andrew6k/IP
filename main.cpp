#include <iostream>
#include <graphics.h>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <fstream>
#pragma comment(lib, "winmm.lib")
#define  Heigth 900
#define Width 1600

using namespace std;
///Declaram variabile globale, pentru a ne usura codul
int lCareu=(Heigth-40)/8-5;///latura careu (reprezinta latura unui patrat)
int lSide=(Width-Heigth)/2+20;///partile laterale din dreapta si stanga careului
int inceput_buton_meniu=325;///punctul din care incep butoanele la meniu
int culoareSelectata;
int lButon=(Heigth-40)/8;
int culoriValabile[]= { BLUE,RED, GREEN, YELLOW, COLOR(255,140,0), CYAN, BROWN, MAGENTA };
int ok=1;
int nivel;
int nr_cercuri; ///nr tipuri de cercuri pt fiecare nivel
int casute_parcurse[8][8];
struct casuta///memoreaza culoare si daca are cerc
{
    int cerc;
    int culoare;
} casute[8][8];

int cercuri[8];
int frecventa[8];
int parcurs[8];
int bile[3];


void desen_careu(int i, int j, int culoare) ///amandoi
{
    int inceput_careu_x=(Width-Heigth)/2+20;///x=inaltime//
    int inceput_careu_y=20;///y=latime//
    rectangle(inceput_careu_x+j*lCareu+5,inceput_careu_y+i*lCareu+5,
              inceput_careu_x+(j+1)*lCareu-5,inceput_careu_y+(i+1)*lCareu-5);
    if(casute[i][j].cerc==1)///1==cercuri negre
        circle(inceput_careu_x+j*lCareu+52, inceput_careu_y+i*lCareu+53, 30 );
    if(casute[i][j].cerc==2)///2==cercuri albe
    {
        circle(inceput_careu_x+j*lCareu+52, inceput_careu_y+i*lCareu+53, 30 );
        setfillstyle(SOLID_FILL,8);
        floodfill(inceput_careu_x+j*lCareu+53, inceput_careu_y+i*lCareu+54,WHITE);
    }
    setfillstyle(SOLID_FILL,culoare);
    floodfill(inceput_careu_x+j*lCareu+6,inceput_careu_y+i*lCareu+6,WHITE);
}
void desen_buton(int i, int culoare) ///Blaga
{
    int inceput_buton_x=(Width-Heigth)-20;
    int inceput_buton_y=250;
    rectangle(inceput_buton_x,inceput_buton_y+i*lButon+75,
              inceput_buton_x+3*lButon,inceput_buton_y+(i+1)*lButon+45);
    settextstyle(4,0,4);///caracteristici titlu(font,directie,marime)
    setcolor(RED);
    outtextxy(inceput_buton_x+100,inceput_buton_y+100,"PLAY");
    setfillstyle(SOLID_FILL,BLACK);
    floodfill(inceput_buton_x+101,inceput_buton_y+101,RED);
    //floodfill(inceput_buton_x+101,inceput_buton_y+401,RED);
    outtextxy(inceput_buton_x+100,inceput_buton_y+208,"HELP");
    //setfillstyle(SOLID_FILL,BLACK);
    outtextxy(inceput_buton_x+105,inceput_buton_y+309,"EXIT");
    //floodfill(inceput_buton_x+101,inceput_buton_y+101,RED);
}
void desen_tabela() ///amandoi
{
    for(int i=0; i<=7; i++)
        for(int j=0; j<=7; j++)
        {
            desen_careu(i,j,BLACK);
        }
}
void desen_nivele(int culoare_nivel) ///Blaga
{
    /*int inceput_careu_x=(Width-Heigth)/2+20;//x=inaltime//
    int inceput_careu_y=60;//y=latime//
    rectangle(inceput_careu_x+i*lCareu+5,inceput_careu_y+j*lCareu+5,
              inceput_careu_x+(i+1)*lCareu-5,inceput_careu_y+(j+1)*lCareu-5);
    setfillstyle(SOLID_FILL,culoare_nivel);
    floodfill(inceput_careu_x+i*lCareu+6,inceput_careu_y+j*lCareu+6,GREEN);*/
    settextstyle(6,0,3);
    for(int i=0; i<3; i++) ///i pentru coloana
    {
        for(int j=0; j<3; j++) ///j pentru linie
        {
            {
                rectangle(Width/ 2 - 375 + i * 300, 200 + j * 200,
                          Width / 2 - 225 + i * 300, 350 + j * 200);
                if(i==0) ///coloana 0
                {
                    if(j==0)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 1");
                    if(j==1)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 4");
                    if(j==2)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 7");
                }
                if(i==1)
                {
                    if(j==0)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 2");
                    if(j==1)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 5");
                    if(j==2)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 8");
                }
                if(i==2)
                {
                    if(j==0)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 3");
                    if(j==1)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 6");
                    if(j==2)
                        outtextxy(Width/2-375+i*300+30,200+j*200+50,"Nivel 9");
                }
            }
            //outtextxy(Width/2-375+i*300+30,200+j*200+50)
/// latura unui buton este de 150,
/// distanta dintre butoane pe orizontala este 300, iar pe verticala 200
/// RANDOM
            rectangle(Width/2-375+600+250,600,Width/2-225+850,350+400);
            outtextxy(Width/2-375+600+270,650,"Random");

        }
    }
}

void desen_partedrp() ///amandoi
{
    int x_start=Width-lSide+80;
    int y_start=40;
    int lCareu = ::lCareu-20;
    for(int i=0; i<=7; i++)
    {
        rectangle(x_start,y_start+i*lCareu,x_start+lCareu,y_start+(i+1)*lCareu);
        setfillstyle(SOLID_FILL,culoriValabile[i]);
        floodfill(x_start+1,y_start+i*lCareu+1,WHITE);
        ///umple patratelele cu o anumita culoare
    }
}
void desen_partestg() ///amandoi
{
    int x_start=Width-lSide-Heigth-260;
    int y_start=40;
    int lCareu = ::lCareu+20;
    rectangle(x_start,y_start+2*lCareu,x_start+200,y_start+2*lCareu+100);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x_start+1,y_start+2*lCareu+1,WHITE);
    outtextxy(x_start+40,y_start+2*lCareu+40,"CHECK");
}

void select_culoare(int x, int y, int &j) ///amandoi
{
    int lCareu= ::lCareu - 20;
    int i = (y-40)/lCareu;
    if (! ( x < Width - lSide + 80 || x >Width - lSide + 80 + lCareu || (y-40)< 0 || i > 7))
    {
        culoareSelectata=culoriValabile[i];
        j=i;
    }
}

///fill
void sol(int i, int j, int c) ///Cîrjanu
{
    if(i>=0 && i<=7 && j>=0 && j<=7)
        if(casute[i][j].culoare==c && casute_parcurse[i][j]==0)
        {
            casute_parcurse[i][j]=1;
            frecventa[c]++;
            if(casute[i][j].cerc==1 || casute[i][j].cerc==2)
                cercuri[c]++;
            sol(i-1,j,c);
            sol(i,j+1,c);
            sol(i+1,j,c);
            sol(i,j-1,c);
        }
}


int verifica() ///Cîrjanu
{
    /*
    int i,j;
    for(i=0;i<=7;i++)
        {for(j=0;j<=7;j++)
          cout<<casute[i][j].culoare<<" ";
        cout<<endl;}*/
    int afis=1;
    int i,j;
    for(i=0; i<=7; i++)
        for(j=0; j<=7; j++)
            if(parcurs[casute[i][j].culoare]==0)
            {
                sol(i,j,casute[i][j].culoare);
                parcurs[casute[i][j].culoare]=1;
            }
    setcolor(LIGHTGRAY);
    int c;
    for(c=0; c<=7; c++)
        if(frecventa[c]!=8 || cercuri[c]!=nr_cercuri)
        {
            outtextxy((Width-Heigth-lSide)/2-40,50,"GRESIT");
            PlaySound(TEXT("Gresit.wav"),NULL,SND_ASYNC);
            afis=0;
            break;
        }
    /*
    if(afis==0)
        {for(int a=0;a<=7;a++)
           {
               frecventa[a]=cercuri[a]=parcurs[a]=0;
               for(int b=0;b<=7;b++)
                casute_parcurse[a][b]=0;}
         afis=2;
        }
        */

    if(afis==1)
        {outtextxy((Width-Heigth-lSide)/2-40,50,"CORECT");
        PlaySound(TEXT("Corect.wav"),NULL,SND_ASYNC);}
    for(int a=0; a<=7; a++)
    {
        frecventa[a]=cercuri[a]=parcurs[a]=0;
        for(int b=0; b<=7; b++)
            casute_parcurse[a][b]=0;
    }
    delay(2000);
    setfillstyle(SOLID_FILL,BLACK);
    floodfill(1,1,WHITE);
    setcolor(WHITE);
    /*
     int i,j;
     for(i=0;i<=7;i++)
        for(j=0;j<=7;j++)
     {
           frecventa[casute[i][j].culoare]++;
           if(casute[i][j].cerc==1|| casute[i][j].cerc==2)
              cercuri[casute[i][j].culoare]++;
     }
     for(i=0;i<=7;i++)
            if(frecventa[i]!=8)
                {outtextxy((Width-Heigth-lSide)/2-40,50,"GRESIT");
                break;}
      // else cout<<"corect";
      */
}
void select_stg(int x,int y) ///amandoi
{
    if(x>Width-lSide-Heigth-260 && x<Width-lSide-Heigth-260+200 &&
            y>81+2*lCareu && y<180+2*lCareu)
        verifica();
}
void bucla_joc();
void start(); ///functiile sunt mai jos
void selectie_nivel() ///amandoi
{
    PlaySound(TEXT("buton.wav"),NULL,SND_ASYNC);
    cleardevice();
    readimagefile("matrix.jpg",0,0,Width,Heigth);
    setcolor(2);
    settextstyle(4,0,5);
    outtextxy(650,60,"Alege nivelul");
    desen_nivele(0);
    int ok2=1;

    while(ok==0 && ok2==1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(mousex()>(Width/2-375) && mousex()<(Width/2-225) &&
                    mousey()>200 && mousey()<349)
                nivel=1;
            if(mousex()>((Width/2-375)+301) && mousex()<(Width/2-225+300) &&
                    mousey()>200 && mousey()<300) //+50
                nivel=2;
            if(mousex()>((Width/2-375)+601) && mousex()<(Width/2-225+600) &&
                    mousey()>200 && mousey()<349)
                nivel=3;
            if(mousex()>(Width/2-375) && mousex()<(Width/2-225) &&
                    mousey()>200+200 && mousey()<550)
                nivel=4;
            if(mousex()>((Width/2-375)+301) && mousex()<(Width/2-225+300) &&
                    mousey()>200+200 && mousey()<550)
                nivel=5;
            if(mousex()>((Width/2-375)+601) && mousex()<(Width/2-225+600) &&
                    mousey()>200+200 && mousey()<550)
                nivel=6;
            if(mousex()>(Width/2-375) && mousex()<(Width/2-225) &&
                    mousey()>200+400 && mousey()<750)
                nivel=7;
            if(mousex()>((Width/2-375)+301) && mousex()<(Width/2-225+300) &&
                    mousey()>200+400 && mousey()<750)
                nivel=8;
            if(mousex()>((Width/2-375)+601) && mousex()<(Width/2-225+600) &&
                    mousey()>200+400 && mousey()<750)
                nivel=9;
            if(mousex()>(Width/2-375+600+250) && mousex()<(Width/2-375+600+400) &&
                    mousey()>200+400 && mousey()<750)
                nivel=10;
            clearmouseclick(WM_LBUTTONDOWN);
            if(nivel!=0)
                ok2=0;
        }
    }
    cleardevice();
    start();

}
void selectie_help() ///Blaga
{
    setcolor(3);
    cleardevice();
    outtextxy(80,20,"Impartiti careul dat in opt parti continui si egale ca arie, care sa aiba ");
    outtextxy(45,60,"fiecare cate o bulina din fiecare fel,folosind culorile din partea dreapta a ");
    outtextxy(45,100,"ecranului cum observati in imaginea de mai jos.");
    readimagefile("img2.jpg",20, 180, Width-20, Heigth-180);//punem imaginea in Help//
    rectangle((Width-lSide-Heigth)/2-20,Heigth-150,(Width-lSide-Heigth)/2+200,Heigth-100);
    outtextxy((Width-lSide-Heigth)/2+25,Heigth-138,"BACK");
    PlaySound(TEXT("buton.wav"),NULL,SND_ASYNC);
}
void selectie_exit() ///amandoi
{
    exit(0);

}
void bucla_joc()///Cîrjanu
{
    int c;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(mousex()>Width-lSide)
                select_culoare(mousex(),mousey(),c);
            if(mousex()<Width-lSide-Heigth)
                select_stg(mousex(),mousey());
            int j=(mousex()-lSide)/lCareu;
            int i=(mousey()-20)/lCareu;
            if(i>=0&&i<=7&&j>=0&&j<=7&&mousex()-lSide>=20&&mousey()>=20)
            {
                desen_careu(i,j,culoareSelectata);
                casute[i][j].culoare=c;
                //cout<<casute[i][j].culoare<<endl;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

void meniu();

void select_buton_meniu()///amandoi
{
    while(ok==1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(mousex()>(Width-Heigth)-19 && mousex()<(Width-Heigth)-19+3*lCareu)
            {
                if(mousey()>inceput_buton_meniu &&
                        mousey()<inceput_buton_meniu+lButon-30)
                {
                    cleardevice();
                    ok=0;
                    selectie_nivel();
                } ///butonul start a fost apasat
                if(mousey()>inceput_buton_meniu+lButon &&
                        mousey()<inceput_buton_meniu+2*lButon-30)
                {
                    selectie_help();
                }
                if(mousey()>inceput_buton_meniu+2*lButon &&
                        mousey()<inceput_buton_meniu+3*lButon-30)
                {
                    ok=0;
                    selectie_exit();
                }

            }
            if(mousex()>(Width-lSide-Heigth)/2-19 && mousex()<(Width-lSide-Heigth)/2+199 &&
                 mousey()>Heigth-150 && mousey()<Heigth-100)
                 {
                     cleardevice();
                     clearmouseclick(WM_LBUTTONDOWN);
                     meniu();

                 }
            /*select_culoare(mousex(),mousey());
            int j=(mousex()-lSide)/lCareu;
            int i=(mousey()-20)/lCareu;
            if(i>=0&&i<=7&&j>=0&&j<=7&&mousex()-lSide>=20&&mousey()>=20)
            desen_careu(i,j,culoareSelectata);*/
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
void start()///Cîrjanu
{
    int i,j;
    if(nivel<10)
    {
        char s1[1];
        s1[0]=nivel+'0';
        char s2[4];
        strcpy(s2,strcat(s1,".in"));
        //cout<<s2;
        ifstream f(s2);
        f>>nr_cercuri;
        for(i=0; i<=7; i++)
            for(j=0; j<=7; j++)
                f>>casute[i][j].cerc;
    }
    if(nivel==10)
    {
        nr_cercuri=2;
        int c;
        int tip;
        for(c=0;c<=15;c++)
        {
            srand (time(NULL));
            do
              {i=rand ()%8;
              j=rand()%8;
              tip=rand()%2+1;
              }
            while (casute[i][j].cerc!=0 || bile[tip]>=8);
            casute[i][j].cerc=tip;
            bile[tip]++;
        }
    }
    for(i=0; i<=7; i++)
    {
        for(j=0; j<=7; j++)
            cout<<casute[i][j].cerc;
        cout<<endl;
    }
    setcolor(WHITE);
    desen_tabela();
    desen_partedrp();
    desen_partestg();
    ///matrice
    bucla_joc();
}
void meniu()///Blaga
{
    readimagefile("Final.jpg",0,0,Width,Heigth);
    settextstyle(6,0,5.5);//caracteristici titlu(font,directie,marime)
    setcolor(RED);
    outtextxy ((Width-Heigth)-95, 120, "Impartirea careului");  //coordonate titlu
    outtextxy((Width-Heigth)+75,170,"2020");
    for(int i=0; i<=2; i++)
    {
        desen_buton(i,BLACK);//pt a crea butoanele din meniu
    }

    select_buton_meniu();


}
int main()///amandoi
{
    PlaySound(TEXT("muzica.wav"),NULL,SND_ASYNC | SND_LOOP);
    initwindow(Width,Heigth,"Impartirea careului");
    meniu();
    Sleep(100000);
    /*
    for(i=0;i<=7;i++)
        {   for(j=0;j<=7;j++)
            cout<<casute[i][j].culoare;
            */
    return 0;
}
