//Caspe
#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void triangle();
void points();
void display();

//Cordero
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(200,50);
	glutCreateWindow("My First OpenGL");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

//Cutaran
void triangle(){
	GLfloat triangleVertex[] = {
		//x	    y      z
		0.0f, 0.75f, 0.0f,
	    -0.65f, 0.30f, 0.0f,
		0.65f, 0.30f, 0.0f,
		
		-0.65f, -0.15f, 0.0f,
	    0.0f, 0.30f, 0.0f,
		0.65f, -0.15f, 0.0f,
		
		-0.65f, -0.60f, 0.0f,
	    0.0f, -0.15f, 0.0f,
		0.65f, -0.60f, 0.0f
	};
    
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, triangleVertex);
	glDrawArrays(GL_TRIANGLES, 0, 9);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//Buama
void points(){
	glPointSize(20.0);
	
	GLfloat pointVertex[] = {
	-0.75f, -0.75f, 0.0f,
	-0.75f, 0.75f, 0.0f,
	0.75f, 0.75f, 0.0f,
	0.75f, -0.75f, 0.0f
	};
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pointVertex);
	glDrawArrays(GL_POINTS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//Bernardino
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(2.0f, 0.5f, 1.0f); //Lilac
	triangle();
	points();
	glFlush();
}
