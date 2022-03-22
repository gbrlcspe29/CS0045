#define GLEW_STATIC
#define STBI_ASSERT(x)
#define  STB_IMAGE_IMPLEMENTATION

#define BUFFER_OFFSET(i) ((void*)(i))
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

#include "stb_image.h"
#include <iostream>

using namespace std;


float angle = 1.0f;

void animatePyramid(int value);
void displayObject();
void init();
void GLAPIENTRY
MessageCallback(GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam);
				
GLfloat pyramidVertices[] = {
	
//---------------------- Pyramid
	0.0f, 1.0f, 0.0f,
   -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f,  1.0f,
	
	0.0f, 1.0f,  0.0f,
	1.0f, -1.0f,  1.0f, 
	1.0f, -1.0f,  -1.0f,
	
	0.0f, 1.0f, 0.0f, 
	1.0f, -1.0f, -1.0f,
   -1.0f,  -1.0f, -1.0f, 
	
	0.0f,  1.0f, 0.0f,
   -1.0f, -1.0f, -1.0f, 
   -1.0f, -1.0f, 1.0f
	
};

GLfloat colorsPyramid[] = {
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	
	0.0f, 1.0f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.0f, 0.0f,
	
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f
};


GLfloat texturecoord[] = {
//---------------------- Pyramid
	0.0f, 1.0f, 1.0f,
   -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f,  1.0f,
	
	0.0f, 1.0f, 1.0f,
   -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f,  1.0f,
	
	0.0f, 1.0f, 1.0f,
   -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f,  1.0f,
	
	0.0f, 1.0f, 1.0f,
   -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f,  1.0f,
	

};

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitWindowSize(1024,768);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("simple");
	init();
	glutDisplayFunc(displayObject);
	
	GLenum err = glewInit();
		if(err == GLEW_OK){
			glEnable ( GL_DEBUG_OUTPUT );
			glDebugMessageCallback( MessageCallback, 0 );
			printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
			printf("OpenGL vendor (%s): \n", glGetString(GL_VENDOR));
			glutMainLoop();
		}
}

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1024.0/768.0, 1.0, 10.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}

void displayObject(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,4.0,4.0,0.0,0.0,0.0,0.0,1.0,0.0);
	//Generate Texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width = 0, height = 0, nrChannels;
	unsigned char *data = stbi_load("texture.jpg", &width, &height, &nrChannels, 0);
		if(data){
			cout << width << " " << height << " " << nrChannels << endl;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, 
			GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else{
			cout << "Failed to load texture" << std::endl;
			exit(0);
		}
	stbi_image_free(data);
	
	//Display Pyramid
	GLuint VBOid;
	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, 1000, pyramidVertices, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 500, 500, colorsPyramid);
	glBufferSubData(GL_ARRAY_BUFFER, 500, 500, texturecoord);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glTexCoordPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(500)); 
	glRotatef(angle,0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);
		for(int i=0; i < 24; i++){
			glArrayElement(i);
		}
	glEnd();  
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDeleteBuffers(1, &VBOid);
	glutTimerFunc(10,animatePyramid,1);
	glFlush();
}

void animatePyramid(int value){
	if(angle>720)
		angle=0;
		angle++;
		glutPostRedisplay();
}

void GLAPIENTRY MessageCallback(GLenum source, 
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar* message,
								const void* userParam){
	fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
	type, severity, message );
}
