#define GLEW_STATIC
#define BUFFER_OFFSET(i) ((void*)(i))

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>

using namespace std;

void displayObject();
void displayTriangle();
void animateTriangle
(int value);
void GLAPIENTRY
MessageCallback(GLenum source, GLenum type, GLuint id,
GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

GLuint VBOid;
void keyMonitor(unsigned char key, int x, int y);
bool initTriangle = true;
float angle=1.0f;

GLfloat vertices[] = {
//------------------- Triangle
 1.0f, 1.0f, -1.0f, 
-1.0f, 1.0f, -1.0f,
-1.0f, 1.0f,  1.0f,
 1.0f, 1.0f,  1.0f,

 1.0f, -1.0f,  1.0f,
-1.0f, -1.0f,  1.0f,
-1.0f, -1.0f, -1.0f,
 1.0f, -1.0f, -1.0f,

 1.0f,  1.0f, 1.0f,
-1.0f,  1.0f, 1.0f,
-1.0f, -1.0f, 1.0f,
 1.0f, -1.0f, 1.0f,

 1.0f, -1.0f, -1.0f,
-1.0f, -1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,
 1.0f,  1.0f, -1.0f,

-1.0f,  1.0f,  1.0f,
-1.0f,  1.0f, -1.0f,
-1.0f, -1.0f, -1.0f,
-1.0f, -1.0f,  1.0f,

 1.0f,  1.0f, -1.0f,
 1.0f,  1.0f,  1.0f,
 1.0f, -1.0f,  1.0f,
 1.0f, -1.0f, -1.0f

};

GLfloat colorstriangle[] = {
	0.0f, 1.0f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f
};

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0,4.0,-4.0,4.0, -4.0,4.0);
}

void displayObject(){
	glClear(GL_COLOR_BUFFER_BIT);
	displayTriangle();
	glutTimerFunc(50,animateTriangle,1);
	glFlush();
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
(type == GL_DEBUG_TYPE_ERROR ? "* GL ERROR *" : "" ), type, severity, message );
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutCreateWindow("simple");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	
	init();
	
	glutDisplayFunc(displayObject);
	glutKeyboardFunc(keyMonitor);
	glutInitWindowSize(800,600);
	
	GLenum err = glewInit();
	if(err == GLEW_OK){
		glEnable ( GL_DEBUG_OUTPUT );
		glDebugMessageCallback( MessageCallback, 0 );
		printf("OpenGL version supported by this platform (%s): \n", 
		glGetString(GL_VERSION));
		printf("OpenGL vendor (%s): \n", glGetString(GL_VENDOR));
		glutMainLoop();
	}
}

void displayTriangle(){
	if(initTriangle){
		glGenBuffers(1, &VBOid);
		glBindBuffer(GL_ARRAY_BUFFER, VBOid);
		
		glBufferData(GL_ARRAY_BUFFER, 1000, vertices, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 1000, 1000, colorstriangle);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glColorPointer(3, GL_FLOAT,0,0);
		
		initTriangle = false;
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(angle,0.0f,1.0f,1.0f);
	glBegin(GL_QUADS); 
	
	for(int i=0; i < 24; i++) {
		glArrayElement(i);
	}
	glEnd(); 
	glFlush();
	glPopMatrix();
}

void animateTriangle(int value){
	if(angle>720)
		angle=0;
		angle++;
		glutPostRedisplay();
}

void keyMonitor(unsigned char key, int x, int y){
	if(key=='x'){
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBOid);
	exit(0);
	}

}

