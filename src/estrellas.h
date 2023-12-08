#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include <stdio.h>
#include <math.h>
#include <time.h>

//constantes matemáticas
#define N_PI 3.14159265358979f

//constantes estrellas
#define NUM_ESTRELLAS 15
#define MAX_PUNTAS 9
#define MIN_PUNTAS 4

bool	teclaPresionada=FALSE;
bool	ratonMovido=FALSE;
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
int numMovimientosRaton=0;

struct rotacion {
	float rot_x;
	float aum_x;
	float x;
	float rot_y;
	float aum_y;
	float y;
};
struct traslacion {
	float x;
	float y;
};
struct punto {
	float x;
	float y;
};
struct estrella {
	float radio;
	float grosor;
	int num_puntas;
	struct punto puntos[MAX_PUNTAS*2+2];
	struct rotacion rot;
	struct traslacion tras;
};
struct estrella estrellas[NUM_ESTRELLAS+1];

void iniciarEstrella(int i);
int aleatorio(int a, int b);
GLvoid ExitGL(void);