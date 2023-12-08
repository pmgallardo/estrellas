#include "estrellas.h"

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	srand((unsigned)time(NULL));	//iniciamos los números aleatorios

	/*cosas de opengl*/
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	/*luz*/
	float ambientLight[4] = {0.2, 0.2, 0.2, 1.0};
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* Red diffuse light. */
	GLfloat light_position[] = {1.0, 0.0, 0.0, 0.0};  /* Infinite light location. */
	GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	/*rellenamos los valores de la estrella*/
	int i;
	for(i=0;i<NUM_ESTRELLAS;i++)
		iniciarEstrella(i);

	return TRUE;								// Initialization Went OK
}

void iniciarEstrella(int i)
{
	estrellas[i].num_puntas = aleatorio(MIN_PUNTAS,MAX_PUNTAS);
	estrellas[i].radio = aleatorio(5,10)/10.0f;
	estrellas[i].grosor = estrellas[i].radio/2;
	//traslacion
	estrellas[i].tras.x = (aleatorio(0,600)-300)/100.0f;
	estrellas[i].tras.y = (aleatorio(0,400)-200)/100.0f;
	//rotacion
	estrellas[i].rot.rot_x = (float) aleatorio(0,360);
	estrellas[i].rot.aum_x = (aleatorio(0,80)-40)/100.0f;
	estrellas[i].rot.x = aleatorio(0,100)/100.0f;
	estrellas[i].rot.rot_y = (float) aleatorio(0,360);
	estrellas[i].rot.aum_y = (aleatorio(0,80)-40)/100.0f;
	estrellas[i].rot.y = aleatorio(0,100)/100.0f;

	int num_puntos = estrellas[i].num_puntas*2;
	float r = estrellas[i].radio;

	float x, y, temp, n, cuarta_parte;
	cuarta_parte = num_puntos / 4.0f;
	n = (float) num_puntos;	//pasamos num_lados a float
	
	int j;
	for(j=0;j<=num_puntos;j++)
	{
		if(j%2 == 0)	{
			temp = tan(j*2*N_PI/n);
			x = (r*temp)/sqrt(1+temp*temp);
			y = sqrt(r*r-x*x);
		}
		else	{
			temp = tan(j*2*N_PI/n);
			x = (r*temp/2)/sqrt(1+temp*temp);
			y = sqrt((r*r/4)-x*x);
		}

		/*comprobar si se coge la raíz positiva o negativa*/
		if(j>num_puntos/2.0)	{
			if(x>0)
				x = -x;
		}
		else	{
			if(x<0)
				x = -x;
		}

		if(j>cuarta_parte && j<cuarta_parte*3)
			y = -y;

		estrellas[i].puntos[j].x=x;
		estrellas[i].puntos[j].y=y;
	}
}

void situarEstrella(int i, bool trasera)
{
	glLoadIdentity();	// Resetea la matriz de vista de modelo actual
	
	//traslacion
	float tras_x = estrellas[i].tras.x;
	float tras_y = estrellas[i].tras.y;

	glTranslatef(tras_x,tras_y,-6.0f);

	//rotacion
	float rot_x = estrellas[i].rot.rot_x;
	float aum_x = estrellas[i].rot.aum_x;
	float x = estrellas[i].rot.x;
	float rot_y = estrellas[i].rot.rot_y;
	float aum_y =estrellas[i].rot.aum_y;
	float y = estrellas[i].rot.y;
	
	if(trasera == false)	{
		glRotatef(rot_x,x,0.0f,0.0f);
		glRotatef(rot_y,0.0f,y,0.0f);
	}
	else
	{
		glRotatef(180,0.0f,1.0f,0.0f);
		glRotatef(rot_x,-x,0.0f,0.0f);
		glRotatef(-rot_y,0.0f,-y,0.0f);

		estrellas[i].rot.rot_x += aum_x;
		estrellas[i].rot.rot_y += aum_y;
	}
}

void dibujarEstrella(int i)
{
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    float mat_ambient_color[] = {0.5f, 0.5f, 0.2f, 0.5f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.6f, 1.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float no_shininess = 0.0f;
    float low_shininess = 5.0f;
    float high_shininess = 100.0f;
    float mat_emission[] = {0.3f, 0.3f, 0.2f, 0.0f};

	int num_puntos = estrellas[i].num_puntas*2;
	float r = estrellas[i].radio;
	float g = estrellas[i].grosor;
		
	int j;
	float x,y;
	float nx, ny, nz;

	glBegin(GL_TRIANGLE_FAN);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f,0.0f,g);
	for(j=0;j<num_puntos;j++)
	{
		x = estrellas[i].puntos[j].x;
		y = estrellas[i].puntos[j].y;

		if(j>0)	{
			nx=(estrellas[i].puntos[j].y-estrellas[i].puntos[j-1].y)*(-g);
			ny=-(estrellas[i].puntos[j].x-estrellas[i].puntos[j-1].x)*(-g);
			nz=(estrellas[i].puntos[j].x-estrellas[i].puntos[j-1].x)*(estrellas[i].puntos[j-1].y)-(estrellas[i].puntos[j-1].x)*(estrellas[i].puntos[j].y-estrellas[i].puntos[j-1].y);
			glNormal3f(nx,ny,nz);
		}

        glVertex3f(x,y,0.0f);		
	}
	nx=(estrellas[i].puntos[0].y-estrellas[i].puntos[num_puntos].y)*(-g);
	ny=-(estrellas[i].puntos[0].x-estrellas[i].puntos[num_puntos].x)*(-g);
	nz=(estrellas[i].puntos[0].x-estrellas[i].puntos[num_puntos].x)*(estrellas[i].puntos[num_puntos].y)-(estrellas[i].puntos[num_puntos].x)*(estrellas[i].puntos[0].y-estrellas[i].puntos[num_puntos].y);
	glNormal3f(nx,ny,nz);

	x = estrellas[i].puntos[0].x;
	y = estrellas[i].puntos[0].y;
    glVertex3f(x,y,0.0f);
	glEnd();
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	int i;
	for(i=0;i<NUM_ESTRELLAS;i++)
	{
		situarEstrella(i,false);
		dibujarEstrella(i);
		situarEstrella(i,true);	//dibujamos la parte de atrás de la estrella
		dibujarEstrella(i);
	}

	return TRUE;
}

int aleatorio(int a, int b)
{
	int resultado;
	resultado = rand()%(b+1-a)+a;
	return resultado;
}

GLvoid ExitGL(void) {

}