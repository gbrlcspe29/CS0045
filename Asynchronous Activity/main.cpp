//Caspe
#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

using namespace std;

void triangle();
void points();
void display();

//Cordero
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitWindowSize(500,350);
	glutInitWindowPosition(200,50);
	glutCreateWindow("Vertex Arrays");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

//Cutaran
void triangle(){
	GLfloat triangleVertex[] = {
		//x	y      z
		0.0f, 0.75f, 0.0f,
	       -0.75f, 0.0f, 0.0f,
		0.75f, 0.0f, 0.0f
	};
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, triangleVertex);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//Buama
void points(){
	glPointSize(20.0);
	
	GLfloat pointVertex[] = {
	    //x       y     z
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
	glColor4f(0.16f, 0.72f, 0.08f, 1.0f);
	triangle();
	points();
	glFlush();
}
