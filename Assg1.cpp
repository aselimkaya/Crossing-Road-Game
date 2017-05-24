#include <time.h>
#include <stdlib.h>
#include <vector>
#include <gl/glut.h>

typedef struct{
	int x;
	int y; // One of coordinate of a vehicle which is our reference point for drawing.
	
	int type; // If 1, it means this vehicle is a square. If 0, a rectangle.
	
	int direction; // If 1, the vehicle goes +x direction. If 0, it goes -x direction.
} Vehicle;

GLfloat hViewport = 600.0, wViewport = 500.0;
GLfloat hTriangle = hViewport / 25.0, wTriangle = wViewport / 25.0;
GLfloat xTriangle = wViewport / 2, yTriangle = hTriangle;

std::vector<std::vector<Vehicle>> vehicleList (19);

//This variable is a flag for triangle's direction. If it is 1, it means the triangle is going up. If it is -1, it means down.
int isUpper = 1;

void drawTriangle() {
	//glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(xTriangle, yTriangle);
		glVertex2f(xTriangle - (wTriangle / 2), yTriangle - (isUpper * hTriangle));  //In here, we are using the flag.
		glVertex2f(xTriangle + (wTriangle / 2), yTriangle - (isUpper * hTriangle));
	glEnd();
}

void drawRoad(){
	//glClear(GL_COLOR_BUFFER_BIT);
	
	//First road
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 5 * hTriangle);
		glVertex2f(wViewport, 5 * hTriangle);
		glVertex2f(wViewport, hTriangle);
		glVertex2f(0, hTriangle);
	glEnd();

	//Enabling dotted painting and distance between lines
	glLineStipple(6, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	
	//First road's lines
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(0, 2 * hTriangle);
		glVertex2f(wViewport, 2 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 3 * hTriangle);
		glVertex2f(wViewport, 3 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 4 * hTriangle);
		glVertex2f(wViewport, 4 * hTriangle);
	glEnd();

	//Second road
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 9 * hTriangle);
		glVertex2f(wViewport, 9 * hTriangle);
		glVertex2f(wViewport, 6 * hTriangle);
		glVertex2f(0, 6 * hTriangle);
	glEnd();

	//Lines of second road
	glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(0, 7 * hTriangle);
		glVertex2f(wViewport, 7 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 8 * hTriangle);
		glVertex2f(wViewport, 8 * hTriangle);
	glEnd();

	//Third road
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 14 * hTriangle);
		glVertex2f(wViewport, 14 * hTriangle);
		glVertex2f(wViewport, 10 * hTriangle);
		glVertex2f(0, 10 * hTriangle);
	glEnd();

	//Lines of third road
	glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(0, 11 * hTriangle);
		glVertex2f(wViewport, 11 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 12 * hTriangle);
		glVertex2f(wViewport, 12 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 13 * hTriangle);
		glVertex2f(wViewport, 13 * hTriangle);
	glEnd();

	//4th road
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 19 * hTriangle);
		glVertex2f(wViewport, 19 * hTriangle);
		glVertex2f(wViewport, 15 * hTriangle);
		glVertex2f(0, 15 * hTriangle);
	glEnd();

	//Lines of 4th
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(0, 16 * hTriangle);
		glVertex2f(wViewport, 16 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 17 * hTriangle);
		glVertex2f(wViewport, 17 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 18 * hTriangle);
		glVertex2f(wViewport, 18 * hTriangle);
	glEnd();

	//Last road
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 24 * hTriangle);
		glVertex2f(wViewport, 24 * hTriangle);
		glVertex2f(wViewport, 20 * hTriangle);
		glVertex2f(0, 20 * hTriangle);
	glEnd();

	//Last lines
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(0, 21 * hTriangle);
		glVertex2f(wViewport, 21 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 22 * hTriangle);
		glVertex2f(wViewport, 22 * hTriangle);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 23 * hTriangle);
		glVertex2f(wViewport, 23 * hTriangle);
	glEnd();
}

void drawVehicles() {
	glColor3f(0.0, 1.0, 0.0);
	
	for (std::vector<std::vector<Vehicle>>::iterator listIterator = vehicleList.begin(); listIterator != vehicleList.end(); ++listIterator) {
		
		std::vector<Vehicle> listTemp = *listIterator;
		
		for (std::vector<Vehicle>::iterator it = listTemp.begin(); it != listTemp.end(); ++it) {
			Vehicle temp = *it;
			if (temp.type) { // means this vehicle is a square
				
				if (temp.direction) { // for positive direction
					glBegin(GL_POLYGON);
						glVertex2f(temp.x, temp.y);
						glVertex2f(temp.x-hTriangle, temp.y);
						glVertex2f(temp.x - hTriangle, temp.y-hTriangle);
						glVertex2f(temp.x, temp.y - hTriangle);
					glEnd();
				}
				
				else { // for negative direction
					glBegin(GL_POLYGON);
						glVertex2f(temp.x, temp.y);
						glVertex2f(temp.x + hTriangle, temp.y);
						glVertex2f(temp.x + hTriangle, temp.y - hTriangle);
						glVertex2f(temp.x, temp.y - hTriangle);
					glEnd();
				}
			}
			
			else { // means this vehicle is a rectangle
				if (temp.direction) { // for positive direction
					glBegin(GL_POLYGON);
						glVertex2f(temp.x, temp.y);
						glVertex2f(temp.x - 2 * hTriangle, temp.y);
						glVertex2f(temp.x - 2 * hTriangle, temp.y - hTriangle);
						glVertex2f(temp.x, temp.y - hTriangle);
					glEnd();
				}
				
				else { // for negative direction
					glBegin(GL_POLYGON);
						glVertex2f(temp.x, temp.y);
						glVertex2f(temp.x + 2 * hTriangle, temp.y);
						glVertex2f(temp.x + 2 * hTriangle, temp.y - hTriangle);
						glVertex2f(temp.x, temp.y - hTriangle);
					glEnd();
				}
			}
		}
	}
}

void myinit(void){

	glViewport(0, 0, wViewport, 600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, wViewport, 0.0, hViewport);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	Vehicle v1; v1.type = 1; v1.direction = 1; v1.x = 100; v1.y = 2 * hTriangle;
	std::vector<Vehicle> list1; list1.push_back(v1);
	vehicleList.push_back(list1);


	glutPostRedisplay();
}


void handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (isUpper == 1) {
			yTriangle += hTriangle;
			
			if (yTriangle == hViewport){
				isUpper = -1;
				yTriangle -= hTriangle;
			}
		}
		break;

	case GLUT_KEY_RIGHT:
		if (xTriangle + wTriangle < wViewport) xTriangle += wTriangle;
		break;

	case GLUT_KEY_LEFT:
		if (xTriangle - wTriangle > 0) xTriangle -= wTriangle;
		break;

	case GLUT_KEY_DOWN:
		if (isUpper == -1) {
			yTriangle -= hTriangle;
			
			if (yTriangle == 0) {
				isUpper = 1;
				yTriangle += hTriangle;
			}
		}
	}
	glutPostRedisplay();
}


void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	drawRoad();
	drawTriangle();
	drawVehicles();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wViewport, hViewport);
	glutCreateWindow("Assignment 1 - 141101005");
	myinit();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(handleSpecialKeypress);
	glutMainLoop();
}