#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

//Variables Globales
#define up 72
#define down 80
#define left 75
#define right 77
#define enter 13
#define Q 81
#define q 113
#define W 87
#define w 119
#define back 8
bool nuevo, rep = true, varx, vary;
int i, tecla, op, cont = 0;
int aux=-1, iz=0, io=0, ip=0;
int CoordX[2000];
int CoordY[2000];
int vida, auxv = 0;   	//Vida del personaje
int balas = 0, auxb = -1, balastotales=0;	//Balas
int ax, ay, x, y, X, Y;		//Coordenadas del personaje
char nombre[10];      		//Nombre del personaje
float idmap=0;

//Declaracion de Fuciones
int Random(int, int);
void Vida();
void Leer();
void Mapa01();
void Mapa02();
void Mapa11();
void Mapa12();
void Mapa13();
void Mapa14();
void Mapa15();
void Mapa16();
void Pintar();
void Guardar();
void Menu(int);
void Opciones();
void Disparar();
void Controles();
void Continuar();
void Capitulo1();
void Nuevo(bool);
void MapaGlobal();
void NuevoJuego();
void IntObjetos();
void Cursor(bool);
void IntPersonas();
void BorrarCoord();
void DibujarBalas();
void Borrar(string);
void RecargarBalas();
void MenuPrincipal();
void MoverZombie(int);
void gotoxy(int, int);
void Window(int, int);
void CrearZombie(int, int, int);
void CrearPersona(int, int, int);
void Lista(int, int, int, int, char);
void Cuadro(int, int, int, int, int);
void CrearObjeto(int, int, char, int);
void CuadroMapa(int, int, int, int, int);

//Personajes y Objetos
struct Zombies{
	char skin = 245;
	int x=-100, y=-100, stop = 0;
	int _x, _y, memx, memy;
	int v, vel, dir;
	bool vida = true;
}zombie[100];

struct ObjetosMapa{
	int x=-1, y=-1;
	int co;
	char id;
	bool disp = true;
}objeto[10];

struct PersonasMapa{
	char skin = 89;
	int x=-1, y=-1;
	int co;
	string dialogo;
}persona[10];

//Funciones
int main(){
	srand(time(NULL));
	SetConsoleTitle("The Game");
	Window(85,30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Cursor(false);
	BorrarCoord();
	Leer();
	MenuPrincipal();
	return 0;
}

void Borrar(string tipo){
	if(tipo == "dialogo"){
		int largo = 69;
		int alto = 6;
		int x = 7;
		int y = 23;
		gotoxy(x, y); printf("%c", 218);
		gotoxy(x + largo, y); printf("%c", 191);
		gotoxy(x, y + alto); printf("%c", 192);
		gotoxy(x + largo, y + alto); printf("%c", 217);
		
		for (i = 1; i < alto; i++) {
			gotoxy(x, y + i); printf("%c", 179);
			gotoxy(x + largo, y + i); printf("%c", 179);		
		}
		for (i = 1; i < largo; i++) {
			gotoxy(x + i, y); printf("%c", 196);
			gotoxy(x + i, y + alto); printf("%c", 196);
		}
		gotoxy(x + 1, y + 1); cout<<"                                                                    ";
		gotoxy(x + 1, y + 2); cout<<"                                                                    ";
		gotoxy(x + 1, y + 3); cout<<"                                                                    ";
		gotoxy(x + 1, y + 4); cout<<"                                                                    ";
		gotoxy(x + 1, y + 5); cout<<"                                                                    ";
	}else if(tipo == "mapa"){
		gotoxy(0,2);
		for(i=0;i<=20;i++){
			cout<<"                                           "
			<<"                                          "<<endl;
		}	
	}
}

void BorrarCoord(){
	io = 0; iz = 0, ip = 0;
	for(i=0;i<10;i++){
		persona[i].x = -1;
		persona[i].y = -1;
		objeto[i].x = -1;
		objeto[i].y = -1;
	}
	for(i=0;i<2000;i++){
		CoordX[i] = -1;
		CoordY[i] = -1;
	}
}

void Capitulo1(){
	bool repcap1 = true;
	cont = 1; x=42; y=9;
	Pintar();
	goto part2;

	//PARTES DEL MAPA	
	part1:
	repcap1=true;
	Mapa11();
	Pintar();
	while(repcap1){
		Controles();
		Vida();
		DibujarBalas();
		if(x>84 || y>22) repcap1 = false;
	}
	if(x>84){x=0;goto part2;}
	if(y>22){y=3;goto part4;}
	
	part2:
	repcap1=true;
	Mapa12();
	Pintar();
	while(repcap1){
		Controles();
		Vida();
		DibujarBalas();
		if(x<0 || x>84 || y>22) repcap1 = false;
	}
	if(x<0){x=84;goto part1;}
	if(x>84){x=0;goto part3;}
	if(y>22){y=3;goto part5;}
	
	part3:
	repcap1=true;
	Mapa13();
	Pintar();
	while(repcap1){
		Controles();
		Vida();
		DibujarBalas();
		if(x<0 || y>22) repcap1 = false;
	}
	if(x<0){x=84;goto part2;}
	if(y>22){y=3;goto part6;}
	
	part4:
	repcap1=true;
	Mapa14();
	Pintar();
	while(repcap1){
		Controles();
		Vida();
		DibujarBalas();
		if(x>84 || y<3) repcap1 = false;
	}
	if(x>84){x=0;goto part5;}
	if(y<3){y=22;goto part1;}
	
	part5:
	repcap1=true;
	Mapa15();
	Pintar();
	while(repcap1){
		Controles();
		Vida();
		DibujarBalas();
		if(x<0 || y<3 || x>84) repcap1 = false;
	}
	if(x<0){x=84;goto part4;}
	if(x>84){x=0;goto part6;}
	if(y<3){y=22;goto part2;}
	
	part6:
	repcap1=true;
	Mapa16();
	Pintar();
	while(repcap1){
		Controles();
		Vida();
		DibujarBalas();
		if(x<0 || y<3) repcap1 = false;
	}
	if(x<0){x=84;goto part5;}
	if(y<3){y=22;goto part3;}
}

void Continuar(){
	system("cls");
	gotoxy(10,3);
	cout<<"Hola "<<nombre<<" es un gusto volver a verte.";
	system("pause>null");
	system("cls");
	if(cont == 1); Capitulo1();
	//if(cont == 2); Capitulo2();
}

void Controles(){
	if(_kbhit()){
		int num = idmap*10;
		int auxmap = (num)%10;
		int n = 0;
		ax = x;
		ay = y;
		tecla = _getch();
		gotoxy(x,y); printf(" ");
		if(tecla == up) ay--;
		if(tecla == down) ay++;
		if(tecla == right) ax++;
		if(tecla == left) ax--;
		for(i = 0; i<2000; i++){
			if(ax != CoordX[i] || ay != CoordY[i]) n++;
		}
		if(n == 2000){
			x = ax;
			y = ay;
			if(auxmap == 1){X = x; Y = y;}
			if(auxmap == 2){X = 101 + x; Y = y;}
			if(auxmap == 3){X = 203 + x; Y = y;}
			if(auxmap == 4){X = x; Y = 30 + y;}
			if(auxmap == 5){X = 101 + x; Y = 30 + y;}
			if(auxmap == 6){X = 203 + x; Y = 30 + y;}
			if(auxmap == 7){X = x; Y = 60 + y;}
			if(auxmap == 8){X = 101 + x; Y = 60 + y;}
			if(auxmap == 9){X = 203 + x; Y = 60 + y;}
		}
		if(tecla == w || tecla == W) Disparar();
		if(tecla == back) RecargarBalas();
		CoordX[1999] = x; CoordY[1999] = y;
		gotoxy(x,y); printf("%c",190);
		if(tecla == q || tecla == Q){
			IntObjetos();
			IntPersonas();
		}
		if(tecla == enter) Menu(1);
	}
}

void CrearObjeto(int obx, int oby, char _id, int ncord){
	objeto[io].x = obx;
	objeto[io].y = oby;
	objeto[io].id = _id;
	objeto[io].co = ncord;
	CoordX[ncord] = obx; CoordY[ncord] = oby;
	gotoxy(objeto[io].x, objeto[io].y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout<<"?";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	io++;
}

void CrearPersona(int px, int py, int cp){
	persona[ip].x = px;
	persona[ip].y = py;
	gotoxy(persona[ip].x, persona[ip].y); cout<<persona[ip].skin;
	CoordX[cp] = persona[ip].x;
	CoordY[cp] = persona[ip].y;
	ip++;
}

void CrearZombie(int zx, int zy, int velz) {
	zombie[iz].vida = true;
	zombie[iz].x = zx;
	zombie[iz].y = zy;
	zombie[iz].vel = velz;
	zombie[iz].dir = Random(0,1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(zombie[iz].x, zombie[iz].y); cout<<zombie[iz].skin;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	iz++;
}

void Cuadro(int x, int y, int largo, int alto, int tipo) {
	int ho, ve, uno, dos, tres, cuatro;
	if(tipo == 1){
		ho = 196;
		ve = 179;
		uno=218, dos=191, tres=192, cuatro=217;
	}else{
		ho = 205;
		ve = 186;
		uno=201, dos=187, tres=200, cuatro=188;
	}
	gotoxy(x, y); printf("%c", uno);
	gotoxy(x + largo, y); printf("%c", dos);
	gotoxy(x, y + alto); printf("%c", tres);
	gotoxy(x + largo, y + alto); printf("%c", cuatro);
	for (i = 1; i < alto; i++) {
		gotoxy(x, y + i); printf("%c", ve);
		gotoxy(x + largo, y + i); printf("%c", ve);
	}
	for (i = 1; i < largo; i++) {
		gotoxy(x + i, y); printf("%c", ho);
		gotoxy(x + i, y + alto); printf("%c", ho);
	}
}

void CuadroMapa(int x, int y, int largo, int alto, int j) {
	gotoxy(x, y); printf("%c", 201);
	CoordX[j + 0] = x;	CoordY[j + 0] = y;
	gotoxy(x + largo, y); printf("%c", 187);
	CoordX[j + 1] = x + largo;	CoordY[j + 1] = y;
	gotoxy(x, y + alto); printf("%c", 200);
	CoordX[j + 2] = x;	CoordY[j + 2] = y + alto;
	gotoxy(x + largo, y + alto); printf("%c", 188);
	CoordX[j + 3] = x + largo;	CoordY[j + 3] = y + alto;
	
	for (i = 1; i < alto; i++) {
		gotoxy(x, y + i); printf("%c", 186);
		CoordX[j + 3 + i] = x;	CoordY[j + 3 + i] = y + i;
		gotoxy(x + largo, y + i); printf("%c", 186);
		CoordX[j + 2 + alto + i] = x + largo;	CoordY[j + 2 + alto + i] = y + i;
	}
	for (i = 1; i < largo; i++) {
		gotoxy(x + i, y); printf("%c", 205);
		CoordX[j + 1 + alto + alto + i] = x + i;	CoordY[j + 1 + alto + alto + i] = y;
		gotoxy(x + i, y + alto); printf("%c", 205);
		CoordX[j + alto + alto + largo + i] = x + i;	CoordY[j + alto + alto + largo + i] = y + alto;
	}
}

void Cursor(bool visible) {
	
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	if(visible == true) cci.bVisible = TRUE;
	if(visible == false) cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
}

void MenuPrincipal(){
	//Banner
	system("cls");
	gotoxy(39,3);  cout<<"THE";
	gotoxy(8,5);  cout<<"   *********         ****         ****         ****   *************";
	gotoxy(8,6);  cout<<"  **********        ******        *****       *****   *************";
	gotoxy(8,7);  cout<<" **                ***  ***       *** **     ** ***   ***          ";
	gotoxy(8,8);  cout<<"**    ******      ***    ***      ***  **   **  ***   ***********  ";
	gotoxy(8,9);  cout<<" **   ******     ************     ***   *****   ***   ***********  ";
	gotoxy(8,10); cout<<"  **      **    **************    ***    ***    ***   ***          ";
	gotoxy(8,11); cout<<"   *********   ***          ***   ***           ***   *************";
	gotoxy(8,12); cout<<"    ********  ***            ***  ***           ***   *************";
	
	op = 0;
	rep = true;
	Cuadro(2,1,80,22,2);
	if(nuevo == true){
		//Pintar el "continuar" de gris
		op = 1;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		gotoxy(37,16); cout<<"Continuar";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}else{
		gotoxy(37,16); cout<<"Continuar";    // Opcion 0
	}
	gotoxy(37,17); cout<<"Nuevo Juego";      // Opcion 1
	gotoxy(37,18); cout<<"Opciones";         // Opcion 2
	gotoxy(37,19); cout<<"Salir";            // Opcion 3
	gotoxy(35,16 + op); printf("%c",175);
	
	
	while(rep){
		tecla = _getch();
		gotoxy(35,16 + op); printf(" ");
		if (tecla == up) op--;
		if (tecla == down) op++;
		if (op == -1) op = 3;
		if (op == 4) op = 0;
		gotoxy(35,16 + op); printf("%c",175);
		if ((tecla == enter) && (op != 0 || nuevo != true)) rep = false;
	}
	switch(op){
	case 0:
		Continuar();
		break;
	case 1:
		NuevoJuego();
		break;
	case 2:
		Opciones();
		break;
	case 3:
		exit(0);
		break;
	default:
		main();
	}
}

void NuevoJuego(){
	system("cls");
	gotoxy(10,4); cout<<"Todavia recuerdo los dias cuando mi unico problema era ver";
	gotoxy(10,6); cout<<"que ropa ponerme ese dia. En fin...";
	
	Cursor(true);
	gotoxy(10,10); printf("%cC%cmo te llamas?", 168, 162);
	gotoxy(10,12); printf("%c%c%c%c%c%c%c%c%c%c", 238,238,238,238,238,238,238,238,238,238);
	gotoxy(10,11); cin.getline(nombre, 10);
	Cursor(false);
	
	gotoxy(10, 14); printf("Hola %s, acompa%came.", nombre, 164); system("pause>null");
	/*                        COMIENZA LA HISTORIA                            */
	system("cls");
	Mapa01();
	gotoxy(9,24); cout<<"Este querido amigo monocromatico minimalista eres tu.";
	gotoxy(42,9); printf("%c",190); system("pause>cls");
	gotoxy(9,26); cout<<"El que programo esto todavia es inexperto."; system("pause>cls");
	gotoxy(9,28); cout<<"Prueba a moverte por la habitacion y luego sal.";
	rep = true;
	vida = 25;
	x = 42; y = 9;
	while(rep){
		Controles();
		if(x==53 && y == 9) rep = false;
	}
	system("cls");
	Mapa01();
	gotoxy(x,y); printf("%c",190);
	for(i = 84;i > 53; i--){
		gotoxy(i + 1,9); cout<<" ";
		gotoxy(i,9); printf("Y");
		Sleep(75);
	}
	gotoxy(9,24); printf("???: Ya es hora de irnos."); system("pause>null");
	system("cls");
	Mapa01();
	gotoxy(x,y); printf("%c",190);
	gotoxy(x + 1,y); printf("Y");
	Sleep(100);
	for(i=53;i<86;i++){
		gotoxy(i-2,y); cout<<"   ";
		if(i<85){gotoxy(i,y); printf("%c",190);}
		if(i<84){gotoxy(i + 1,y); printf("Y");}
		Sleep(75);
	}
	system("cls");
	Mapa02();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(64,12); printf("%c",245);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for(i=0;i<15;i++){
		if(i>=2){gotoxy(i - 2,12); cout<<"  ";}
		if(i>=1){gotoxy(i - 1,12); printf("%c",190);}
		gotoxy(i,12); printf("Y");
		Sleep(75);
	}
	gotoxy(9,24); printf("???: Este es nuestro centro de entrenamiento."); system("pause>null");
	gotoxy(9,26); printf("???: Vamos a soltar a un zombie y tendras que matarlo,"); system("pause>null");
	gotoxy(9,28); printf("     Los controles son faciles..."); system("pause>null"); Borrar("dialogo");
	gotoxy(9,24); printf("???: Con la letra Q interactuas con las personas y objetos,");
	gotoxy(9,26); printf("     con la W disparas, y presiona enter si quieres abrir el menu."); system("pause>null");
	system("cls");
	Mapa02();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(64,12); printf("%c",245);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(12,12); printf("%c",190);
	gotoxy(13,12); printf("Y");
	Sleep(500);
	gotoxy(13,12); printf(" "); gotoxy(13,13); printf("Y"); Sleep(75);
	for(i=13;i>5;i--){
		gotoxy(i+1,13); printf(" ");
		gotoxy(i,13); printf("Y");
		Sleep(75);
	}
	gotoxy(6,13); printf(" "); gotoxy(6,12); printf("Y");
	gotoxy(9,24); printf("???: Yo te veo desde aqui."); system("pause>null");
	system("cls");
	Mapa02();
	balas=1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(64,12); printf("%c",245);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(12,12); printf("%c",190);
	gotoxy(6,12); printf("Y");
	Sleep(100);
	gotoxy(60,12); printf("%c",219); Sleep(100);
	gotoxy(60,12); printf("%c",220); Sleep(100);
	gotoxy(60,12); printf("_"); Sleep(100);
	gotoxy(60,12); cout<<" ";
	x=12; y=12;
	rep = true;
	CrearZombie(64,12,10);
	while(zombie[0].vida){
		Controles();
		MoverZombie(0);
		Sleep(10);
	}
	system("pause>null");
	Sleep(500);
	gotoxy(9,24); cout<<"???: Bien hecho, tu entrenamiento ha terminado.";
	gotoxy(9,26); cout<<"     Ahora sal afuera y busca el suero que perdimos, lo reconoceras";
	gotoxy(9,28); cout<<"     facil porque es de color verde y sabe feo."; system("pause>null");
	Borrar("dialogo");
	gotoxy(9,24); cout<<"???: Por cierto mi nombre es Victor, y estoy a cargo del";
	gotoxy(9,26); cout<<"     Proyecto de Erradicacion de Zombies.";
	gotoxy(9,28); cout<<"     Ten unas cuantas balas y mucho cuidado alla afuera.";
	balas=6; balastotales = 20; vida = 25; system("pause>null");
	system("cls");
	Sleep(500);
	Capitulo1();
}

void Opciones(){
	system("cls");
	Cuadro(2,1,80,22,2);
	gotoxy(37,8); cout<<"Borrar Partida";
	gotoxy(37,10); cout<<"Volumen";
	gotoxy(37,12); cout<<"Controles";
	gotoxy(37,14); cout<<"Regresar";
	Lista(35,8,4,2,175);
	switch(op){
	case 1:
		Nuevo(true);
		gotoxy(37,9); cout<<"Se ha borrado la partida";
		system("pause>null");
		MenuPrincipal();
		break;
	case 2:
		cout<<"Volumen";
		system("pause");
		break;
	case 3:
		cout<<"Controles";
		system("pause");
		break;
	default:                 //Esta es igual la opcion 4
		MenuPrincipal();
	}
}

void Mapa01(){
	BorrarCoord();
	CuadroMapa(32,4,20,10,0);
	Borrar("dialogo");
	gotoxy(52,9); cout<<" ";
	CoordX[17] = 0; CoordY[17] = 0;
}

void Mapa02(){
	idmap=0.2;
	BorrarCoord();
	CuadroMapa(5,2,73,20,0);
	Borrar("dialogo");
	gotoxy(5,12); cout<<" ";
	CoordX[13] = 6;   CoordY[13] = 12;
	CuadroMapa(60,10,10,4,186);
	gotoxy(60,12); printf("%c",219);
	CoordX[191] = -1;	CoordY[191] = -1;
}

void Mapa11(){
	idmap=1.1;
	system("cls");
	Borrar("dialogo");
	BorrarCoord();
	CuadroMapa(0,3,84,19,0);
	for(int i=0;i<5;i++){
		gotoxy(84,12+i);cout<<" ";
		CoordX[30+i]=-1;
		CoordY[30+i]=-1;
	}
	for(i=0;i<10;i++){
		gotoxy(38+i,22); cout<<" ";
		CoordX[160+i] = -1;
		CoordY[160+i] = -1;
	}
	/*gotoxy(0,0);
	for(i = 100; i<160;i++){
		cout<<i<<". ("<<CoordX[i]<<","<<CoordY[i]<<")\t";
	}*/
}

void Mapa12(){
	idmap=1.2;
	system("cls");
	BorrarCoord();
	gotoxy(40,4); cout<<"P.E.Z.";
	CuadroMapa(0,3,84,19,0);
	CuadroMapa(30,3,24,5,212);
	CuadroMapa(41,6,2,2,270);
	gotoxy(30,3); printf("%c",203);
	gotoxy(54,3); printf("%c",203);
	Borrar("dialogo");
	for(i=0;i<5;i++){
		gotoxy(0,12+i);cout<<" ";
		gotoxy(84,12+i);cout<<" ";
		CoordX[12+i] = -1;
		CoordY[12+i] = -1;
		CoordX[30+i] = -1;
		CoordY[30+i] = -1;
	}
	for(i=0;i<10;i++){
		gotoxy(38+i,22); cout<<" ";
		CoordX[160+i] = -1;
		CoordY[160+i] = -1;
	}
	CrearPersona(34,9,278);
	persona[0].dialogo = "Hola amigo";
	CrearPersona(35,9,279);
	persona[1].dialogo = "soy la persona numero 1";
	CrearPersona(48,20,280);
	persona[2].dialogo = "Cientifico: No vayas alla afuera, es peligroso";
	if(objeto[0].disp)CrearObjeto(82,5,'b',281);
	gotoxy(0,0);
}

void Mapa13(){
	idmap=1.3;
	system("cls");
	BorrarCoord();
	CuadroMapa(0,3,84,19,0);
	for(int i=0;i<5;i++){
		gotoxy(0,12+i);cout<<" ";
		CoordX[12+i]=-1;
		CoordY[12+i]=-1;
	}
	for(i=0;i<10;i++){
		gotoxy(38+i,22); cout<<" ";
		CoordX[160+i] = -1;
		CoordY[160+i] = -1;
	}
	Borrar("dialogo");
}

void Mapa14(){
	idmap=1.4;
	system("cls");
	Borrar("dialogo");
	BorrarCoord();
	CuadroMapa(0,3,84,19,0);
	for(int i=0;i<5;i++){
		gotoxy(84,12+i);cout<<" ";
		CoordX[30+i]=-1;
		CoordY[30+i]=-1;
	}
	for(i=0;i<10;i++){
		gotoxy(38+i,3); cout<<" ";
		CoordX[77+i] = -1;
		CoordY[77+i] = -1;
	}
}

void Mapa15(){
	idmap=1.5;
	system("cls");
	Borrar("dialogo");
	BorrarCoord();
	CuadroMapa(0,3,84,19,0);
	for(int i=0;i<5;i++){
		gotoxy(0,12+i);cout<<" ";
		gotoxy(84,12+i);cout<<" ";
		CoordX[12+i]=-1;
		CoordY[12+i]=-1;
		CoordX[30+i]=-1;
		CoordY[30+i]=-1;
	}
	for(i=0;i<10;i++){
		gotoxy(38+i,3); cout<<" ";
		CoordX[77+i] = -1;
		CoordY[77+i] = -1;
	}
}

void Mapa16(){
	idmap=1.6;
	system("cls");
	Borrar("dialogo");
	BorrarCoord();
	CuadroMapa(0,3,84,19,0);
	for(int i=0;i<5;i++){
		gotoxy(0,12+i);cout<<" ";
		CoordX[12+i]=-1;
		CoordY[12+i]=-1;
	}
	for(i=0;i<10;i++){
		gotoxy(38+i,3); cout<<" ";
		CoordX[77+i] = -1;
		CoordY[77+i] = -1;
	}
}

void Menu(int op){
	bool _rep = true;
	for(i = 0; i<13;i++){
		gotoxy(68, 6 + i); cout<<"                 ";
	}
	gotoxy(68, 6); printf("%c", 218);
	gotoxy(84, 6); printf("%c", 191);
	gotoxy(68, 18); printf("%c", 192);
	gotoxy(84, 18); printf("%c", 217);
	for (i = 1; i < 12; i++) {
		gotoxy(68, 6 + i); printf("%c", 179);
		gotoxy(84, 6 + i); printf("%c", 179);		
	}
	for (i = 1; i < 16; i++) {
		gotoxy(68 + i, 6); printf("%c", 196);
		gotoxy(68 + i, 18); printf("%c", 196);
	}
	gotoxy(69,8); cout<<" Mapa";
	gotoxy(69,10); cout<<" Objetos";
	gotoxy(69,12); cout<<" Guardar";
	gotoxy(69,14); cout<<" Menu Principal";
	gotoxy(69,16); cout<<" Regresar";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	if(op==1){gotoxy(69,8); cout<<"Mapa ";}
	else if(op==2){gotoxy(69,10); cout<<"Objetos ";}
	else if(op==3){gotoxy(69,12); cout<<"Guardar ";}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	while(_rep){
		tecla = _getch();
		gotoxy(69,8);  cout<<" Mapa";
		gotoxy(69,10); cout<<" Objetos";
		gotoxy(69,12); cout<<" Guardar";
		gotoxy(69,14); cout<<" Menu Principal";
		gotoxy(69,16); cout<<" Regresar";
		if (tecla == up) op--;
		if (tecla == down) op++;
		if (op == 0) op = 5;
		if (op == 6) op = 1;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		switch(op){
			case 1:
				gotoxy(69,8); cout<<"Mapa ";
				break;
			case 2:
				gotoxy(69,10); cout<<"Objetos ";
				break;
			case 3:
				gotoxy(69,12); cout<<"Guardar ";
				break;
			case 4:
				gotoxy(69,14); cout<<"Menu Principal ";
				break;
			case 5:
				gotoxy(69,16); cout<<"Regresar ";
				break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if (tecla == enter) _rep = false;
	}
	switch(op){
		case 1:
			MapaGlobal();
			break;
		case 2:
			gotoxy(71,10); cout<<"OBJETOS";
			break;
		case 3:
			Guardar();
			gotoxy(69,12);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout<<"Juego Guardado";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			_getch();
			Menu(3);
			break;
		case 4:
			system("cls");
			MenuPrincipal();
			break;
		case 5:
			break;
	}
	for(i = 0; i<13;i++){
		gotoxy(68, 6 + i); cout<<"                 ";
	}
	if(idmap==0.2f) Mapa02();
	else if(idmap==1.1f) Mapa11();
	else if(idmap==1.2f) Mapa12();
	else if(idmap==1.3f) Mapa13();
	else if(idmap==1.4f) Mapa14();
	else if(idmap==1.5f) Mapa15();
	else if(idmap==1.6f) Mapa16();
	Pintar();
}

void MapaGlobal(){
	int mmx = (X)/6;
	int mmy = (Y-4)/6;
	system("cls");
	if(cont == 1){
		gotoxy(40,3); cout<<"MAPA";
		Cuadro(17,5,15,4,1);
		Cuadro(34,5,15,4,1);
		Cuadro(51,5,15,4,1);
		
		Cuadro(17,10,15,4,1);
		Cuadro(34,10,15,4,1);
		Cuadro(51,10,15,4,1);
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(18+mmx,6+mmy); cout<<"o";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}else if(cont == 2){
		cout<<"Hola";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(38,23); cout<<"Regresar";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	do{tecla = _getch();}while(tecla != enter);
	system("cls");
}

void Disparar() {
	if(balas>0){
		int dist = 0, bala;
		int max = 1000;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 239);
		gotoxy(x, y); printf("%c", 190);
		for (int i = 0; i < 100; i++) {
			if (zombie[i].vida) { dist = sqrt(pow((x - zombie[i].x), 2) + pow((y - zombie[i].y), 2)); }else dist=1000;
			if (dist < max) { max = dist; bala = i; }
		}
		//PlaySound(TEXT("resources\\bala.wav"),NULL,SND_ASYNC);
		balas--;
		zombie[bala].vida = false;
		Sleep(25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}else RecargarBalas();
}

void MoverZombie(int nz) {
	if (zombie[nz].vida) {
		if(zombie[nz].v == zombie[nz].vel) {
			int n=0;
			int m=0;
			zombie[nz].v = 0;
			zombie[nz]._x = zombie[nz].x;
			zombie[nz]._y = zombie[nz].y;

			gotoxy(zombie[nz].x, zombie[nz].y); cout << " ";
			//Movimiento en X
			if (zombie[nz]._x < x) zombie[nz]._x++;
			if (zombie[nz]._x > x) zombie[nz]._x--;
			if (zombie[nz]._x != zombie[nz].x){
				for (i = 0; i < 2000; i++) {
				if ((zombie[nz]._x != zombie[nz].memx || zombie[nz]._y != zombie[nz].memy) && (zombie[nz]._y != CoordY[i] || zombie[nz]._x != CoordX[i])) n++;
				}
				if(n==2000){
					zombie[nz].x = zombie[nz]._x;
				}else{
					if(zombie[nz]._x == x && zombie[nz]._y == y) vida--;
					zombie[nz]._x = zombie[nz].x;
				}
			}
			//Movimiento en Y
			if (zombie[nz]._y < y) zombie[nz]._y++;
			if (zombie[nz]._y > y) zombie[nz]._y--;
			if (zombie[nz]._y != zombie[nz].y){
				for (i = 0; i < 2000; i++) {
				if ((zombie[nz]._x != zombie[nz].memx || zombie[nz]._y != zombie[nz].memy) && (zombie[nz]._y != CoordY[i] || zombie[nz]._x != CoordX[i])) m++;
				}
				if(m==2000){
					zombie[nz].y = zombie[nz]._y;
				}else{
					if(zombie[nz]._y == y && zombie[nz]._x == x) vida--;
					zombie[nz]._y = zombie[nz].y;
				}
			}
			//Codigo 3.0
			if(m != 2000 && n != 2000){
				if(zombie[nz].x == x) varx = true;
				if(varx){
					//Metodo 1.
					int o=0;
					zombie[nz]._x = zombie[nz].x;
					zombie[nz]._y = zombie[nz].y;
					
					if(zombie[nz].dir==0){zombie[nz]._x--;}else zombie[nz]._x++;			
					zombie[nz].memx = zombie[nz].x;
					zombie[nz].memy = zombie[nz].y;
					//Detectar bloques
					for(int i=0;i<2000;i++){
						if(zombie[nz]._x != CoordX[i] || zombie[nz]._y != CoordY[i]) o++;
					}
					if(o == 2000){
						zombie[nz].x = zombie[nz]._x;
					}else{varx = false;}
				}
				
				if(zombie[nz].y == y) vary = true;
				if(vary){
					//Metodo Y.
					int o=0;
					zombie[nz]._x = zombie[nz].x;
					zombie[nz]._y = zombie[nz].y;
					if(zombie[nz].dir==0){zombie[nz]._y--;}else zombie[nz]._y++;			
					zombie[nz].memx = zombie[nz].x;
					zombie[nz].memy = zombie[nz].y;
					//Detectar bloques
					for(int i=0;i<2000;i++){
						if(zombie[nz]._x != CoordX[i] || zombie[nz]._y != CoordY[i]) o++;
					}
					if(o == 2000){
						zombie[nz].y = zombie[nz]._y;
					}else{vary = false;}
				}
			}
			//Fin del codigo 3.0
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			gotoxy(zombie[nz].x, zombie[nz].y); cout << zombie[nz].skin;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		zombie[nz].v++;
	}else if(zombie[nz].stop<=200){//Zombie muerto
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		gotoxy(zombie[nz].x, zombie[nz].y); cout << zombie[nz].skin;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		zombie[nz].stop++;
	}else if(zombie[nz].stop==201){
		gotoxy(zombie[nz].x, zombie[nz].y); cout << " ";
		zombie[nz].stop++;
	}
}

void Vida(){
	char cocoro = 219;
	if(vida!=auxv){
		if(vida>12){
			gotoxy(6, 1); cout<<"                         ";
			for(i=1;i<=vida;i++){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				gotoxy(5+i, 1); cout<<cocoro;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}else if(vida>5){
			gotoxy(6, 1); cout<<"                         ";
			for(i=1;i<=vida;i++){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				gotoxy(5+i, 1); cout<<cocoro;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}else if(vida > 0){
			gotoxy(6, 1); cout<<"                         ";
			for(i=1;i<=vida;i++){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				gotoxy(5+i, 1); cout<<cocoro;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}else{
			gotoxy(6, 1); cout<<"                         ";
			Sleep(1000);
			Borrar("dialogo");
			gotoxy(9,18); cout<<"Has muerto";
			system("pause>null");
			main();
		}
		auxv=vida;
	}
}

void IntObjetos(){
	for(i=0;i<10;i++){
		int auxox = x - objeto[i].x;
		int auxoy = y - objeto[i].y;
		if(auxox==0) auxox = 1;
		if(auxoy==0) auxoy = 1;
		if(auxox<0) auxox*=-1;
		if(auxoy<0) auxoy*=-1;
		if(auxox==1 && auxoy==1){
			gotoxy(objeto[i].x, objeto[i].y); cout<<" ";
			objeto[i].x = -1; objeto[i].y = -1;
			CoordX[objeto[i].co] = -1;
			CoordY[objeto[i].co] = -1;
			gotoxy(9,24); cout<<"Has encontrado ";
			switch(objeto[i].id){
			case 'b':
				cout<<"25 balas";
				break;
			case 'p':
				cout<<"Hoola";
				break;
			}
			objeto[i].disp = false;
			system("pause>null");
			Borrar("dialogo");
			i=10; //salir del bucle
		}
	}		
}

void IntPersonas(){
	for(i=0;i<10;i++){
		int auxpx = x - persona[i].x;
		int auxpy = y - persona[i].y;
		if(auxpx<0) auxpx*=-1;
		if(auxpy<0) auxpy*=-1;
		if((auxpx==1 && auxpy==0) || (auxpx==0 && auxpy==1)){
			gotoxy(9,24);
			cout<<persona[i].dialogo;
			system("pause>null");
			Borrar("dialogo");
		}
	}		
}

void DibujarBalas(){
	char skinbala = 244;
	if(balas != auxb){
		gotoxy(34,1); cout<<"      ";
		for(i = 1; i <= balas; i++){
			gotoxy(33+i,1); cout<<skinbala;
		}
	}
	auxb=balas;
}

void RecargarBalas(){
	int faltante = 6 - balas;
	if(balastotales >= faltante){
		balas += faltante;
		balastotales -= faltante;
	}else{
		balas += balastotales;
		balastotales = 0;
	}
	//PlaySound(TEXT("resources\\recarga.wav"),NULL,SND_ASYNC);
	gotoxy(42,1); cout<<"     ";
	gotoxy(42,1); cout<<balastotales;
}

void Pintar(){
	auxb = -1; auxv = -1;
	gotoxy(42,1); cout<<balastotales;
	gotoxy(x,y); printf("%c",190);
}

void Lista(int x, int y, int n_opciones, int salto, char simbolo){
	op = 0;
	rep = true;
	gotoxy(x,y + op); cout<<simbolo;
	while(rep){
		tecla = _getch();
		gotoxy(x,y + op); cout<<" ";
		if (tecla == up) op-=salto;
		if (tecla == down) op+=salto;
		if (op == -salto) op = salto*n_opciones - salto;
		if (op == salto*n_opciones) op = 0;
		gotoxy(x,y + op); cout<<simbolo;
		if (tecla == enter){
			for(i = 0; i < n_opciones; i++){
				if(op == i*salto) op = i + 1;
			}
			rep = false;
		}
	}
}

void Nuevo(bool check){
	FILE *Nue;
	Nue = fopen("save\\new_game.bin", "rb");
	fread(&nuevo, sizeof(nuevo), 1, Nue);
	fclose(Nue);
	
	if(check == true) nuevo = true;
	if(check == false) nuevo = false;
	
	Nue = fopen("save\\new_game.bin", "wb");
	fwrite(&nuevo, sizeof(nuevo), 1, Nue);
	fflush(Nue);
	fclose(Nue);
}

void Guardar(){
	Nuevo(false);
	FILE *Guardar;
	
	Guardar = fopen("save\\data.bin", "wb");
	fwrite(&nombre, sizeof(nombre), 1, Guardar);          // Guardar el nombre del jugador
	fwrite(&cont, sizeof(cont), 1, Guardar);			  // Guardar en que parte de la historia
	fwrite(&balas, sizeof(balas), 1, Guardar);
	fwrite(&balastotales, sizeof(balastotales), 1, Guardar);
	fwrite(&vida, sizeof(vida), 1, Guardar);
	fflush(Guardar);
	fclose(Guardar);
}

void Leer(){
	FILE *new_game;
	new_game = fopen("save\\new_game.bin", "rb");
	fread(&nuevo, sizeof(nuevo), 1, new_game);
	fclose(new_game);
	
	FILE *data;
	data = fopen("save\\data.bin", "rb");
	fread(&nombre, sizeof(nombre), 1, data);
	fread(&cont, sizeof(cont), 1, data);
	fread(&balas, sizeof(balas), 1, data);
	fread(&balastotales, sizeof(balastotales), 1, data);
	fread(&vida, sizeof(vida), 1, data);
	fclose(data);
}

int Random(int min, int max) {
	bool rep = true;
	int nran, por;
	if (max < 10) {
		por = 10;
	}
	else if (max < 100) {
		por = 100;
	}
	else if (max < 1000) {
		por = 1000;
	}
	else if (max < 10000) {
		por = 10000;
	}
	if (rep != true) {
		do {
			do {
				nran = rand() % (por);
			} while (nran<min || nran>max);
		} while (nran == aux);
	}
	else {
		do {
			nran = rand() % (por);
		} while (nran<min || nran>max);
	}
	aux = nran;
	return nran;
}

void gotoxy(int x, int y) {
	HANDLE sc = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(sc, pos);
}

void Window(int ancho, int alto){ 
    _COORD cord; 
    cord.X = ancho; 
    cord.Y = alto; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = alto - 1; 
    Rect.Right = ancho - 1; 

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), cord);
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &Rect);
}
