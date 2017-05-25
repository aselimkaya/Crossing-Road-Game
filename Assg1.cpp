#include <time.h>
#include <iostream>
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

void drawCars() {
	glColor3f(0.0, 1.0, 0.0);

	for (auto& row : vehicleList) {
		for (auto& col : row) {
			if (col.type) { // means this vehicle is a square

				if (col.direction) { // for positive direction
					glBegin(GL_POLYGON);
					glVertex2f(col.x, col.y);
					glVertex2f(col.x - hTriangle, col.y);
					glVertex2f(col.x - hTriangle, col.y - hTriangle);
					glVertex2f(col.x, col.y - hTriangle);
					glEnd();
				}

				else { // for negative direction
					glBegin(GL_POLYGON);
					glVertex2f(col.x, col.y);
					glVertex2f(col.x + hTriangle, col.y);
					glVertex2f(col.x + hTriangle, col.y - hTriangle);
					glVertex2f(col.x, col.y - hTriangle);
					glEnd();
				}
			}

			else { // means this vehicle is a rectangle
				if (col.direction) { // for positive direction
					glBegin(GL_POLYGON);
					glVertex2f(col.x, col.y);
					glVertex2f(col.x - 2 * hTriangle, col.y);
					glVertex2f(col.x - 2 * hTriangle, col.y - hTriangle);
					glVertex2f(col.x, col.y - hTriangle);
					glEnd();
				}

				else { // for negative direction
					glBegin(GL_POLYGON);
					glVertex2f(col.x, col.y);
					glVertex2f(col.x + 2 * hTriangle, col.y);
					glVertex2f(col.x + 2 * hTriangle, col.y - hTriangle);
					glVertex2f(col.x, col.y - hTriangle);
					glEnd();
				}
			}
		}
	}
}

void drawVehicles() {
	glColor3f(0.0, 1.0, 0.0);
	
	for (int index = 0; index < vehicleList.size(); ++index) {
		
		for (int j = 0; j < vehicleList[index].size(); j++) {
			if (vehicleList[index][j].type) { // means this vehicle is a square
				
				if (vehicleList[index][j].direction) { // for positive direction
					glBegin(GL_POLYGON);
						glVertex2f(vehicleList[index][j].x, vehicleList[index][j].y);
						glVertex2f(vehicleList[index][j].x-hTriangle, vehicleList[index][j].y);
						glVertex2f(vehicleList[index][j].x - hTriangle, vehicleList[index][j].y-hTriangle);
						glVertex2f(vehicleList[index][j].x, vehicleList[index][j].y - hTriangle);
					glEnd();
				}
				
				else { // for negative direction
					glBegin(GL_POLYGON);
						glVertex2f(vehicleList[index][j].x, vehicleList[index][j].y);
						glVertex2f(vehicleList[index][j].x + hTriangle, vehicleList[index][j].y);
						glVertex2f(vehicleList[index][j].x + hTriangle, vehicleList[index][j].y - hTriangle);
						glVertex2f(vehicleList[index][j].x, vehicleList[index][j].y - hTriangle);
					glEnd();
				}
			}
			
			else { // means this vehicle is a rectangle
				if (vehicleList[index][j].direction) { // for positive direction
					glBegin(GL_POLYGON);
						glVertex2f(vehicleList[index][j].x, vehicleList[index][j].y);
						glVertex2f(vehicleList[index][j].x - 2 * hTriangle, vehicleList[index][j].y);
						glVertex2f(vehicleList[index][j].x - 2 * hTriangle, vehicleList[index][j].y - hTriangle);
						glVertex2f(vehicleList[index][j].x, vehicleList[index][j].y - hTriangle);
					glEnd();
				}
				
				else { // for negative direction
					glBegin(GL_POLYGON);
						glVertex2f(vehicleList[index][j].x, vehicleList[index][j].y);
						glVertex2f(vehicleList[index][j].x + 2 * hTriangle, vehicleList[index][j].y);
						glVertex2f(vehicleList[index][j].x + 2 * hTriangle, vehicleList[index][j].y - hTriangle);
						glVertex2f(vehicleList[index][j].x, vehicleList[index][j].y - hTriangle);
					glEnd();
				}
			}
		}
	}
}

static void up() {
	int count = 2;
	for (auto& row : vehicleList) {
		if (count == 6 || count == 10 || count == 15 || count == 20) // this count is for determining the # of road. This numbers are safe places, not road.
			count++; // Then, we increase the count for skipping safe places.

		for (auto& col : row) {

			if (col.direction)
				col.x += (count % 5) * 5 + 10;
			else
				col.x -= (count % 3) * 2 + 10;
		}

		if (!(rand() % 35)) {
			Vehicle v;
			if (count % 2) { // If the # of road is a odd number, we assign its direction +x.
				v.direction = 1;
				v.x = 0;
				v.y = count * hTriangle;
			}
			else {
				v.direction = 0;
				v.x = wViewport;
				v.y = count * hTriangle;
			}

			if (rand() % 2) v.type = 1;

			else v.type = 0;

			row.push_back(v);
		}
		count++;
	}
}

static void update() {
	int count = 1;
	for (int index = 0; index < vehicleList.size(); ++index) {
		if (count == 6 || count == 10 || count == 15 || count == 20) // this count is for determining the # of road. This numbers are safe places, not road.
			count++; // Then, we increase the count for skipping safe places.

		for (int j = 0; j < vehicleList[index].size(); j++) {
			vehicleList[index][j];

			if (vehicleList[index][j].direction)
				vehicleList[index][j].x += 2;
			else
				vehicleList[index][j].direction -= 2;
		}

		if (!(rand() % 5)) {
			Vehicle v;
			if (count % 2) { // If the # of road is a odd number, we assign its direction +x.
				v.direction = 1;
				v.x = 0;
				v.y = count * hTriangle;
			}
			else {
				v.direction = 0;
				v.x = wViewport;
				v.y = count * hTriangle;
			}

			if (rand() % 2) v.type = 1;

			else v.type = 0;

			vehicleList[index].push_back(v);
		}
	}
}

static void updateVehicles() {
	std::cout << "Working\n";
	int count = 1;
	//for (int index = 0; index < vehicleList.size(); ++index)
	for (std::vector<std::vector<Vehicle>>::iterator listIterator = vehicleList.begin(); listIterator != vehicleList.end(); ++listIterator) {
		std::vector<Vehicle> listTemp = *listIterator;
		count++;
		std::cout << count << std::endl;
		std::cout << "Size ";
		std::cout << listTemp.size() << std::endl;

		if (count == 6 || count == 10 || count == 15 || count == 20) // this count is for determining the # of road. This numbers are safe places, not road.
			count++; // Then, we increase the count for skipping safe places.

		for (std::vector<Vehicle>::iterator it = listTemp.begin(); it != listTemp.end(); ++it) {
			Vehicle tmp = *it;

			if (tmp.direction)
				tmp.x += 2;
			else
				tmp.direction -= 2;
		}

		if (!(rand() % 5)) {
			std::cout << "Girdi" << std::endl;
			Vehicle v;
			if (count % 2) { // If the # of road is a odd number, we assign its direction +x.
				v.direction = 1;
				v.x = 0;
				v.y = count * hTriangle;
			}
			else {
				v.direction = 0;
				v.x = wViewport;
				v.y = count * hTriangle;
			}

			if (rand() % 2) v.type = 1; 
			
			else v.type = 0;

			listTemp.push_back(v);

			std::cout << "Eklendikten sonra ";
			std::cout << listTemp.size() << std::endl;
		}
	}

}

void myTimer(int val) {
	up();
	glutPostRedisplay();
	glutTimerFunc(500, myTimer, 0);
}

void myinit(void){

	glViewport(0, 0, wViewport, 600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, wViewport, 0.0, hViewport);
	glClearColor(0.0, 0.0, 0.0, 1.0);

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
	drawCars();
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
	//glutTimerFunc(2000, myTimer, 0);
	myTimer(0);
	glutMainLoop();
}