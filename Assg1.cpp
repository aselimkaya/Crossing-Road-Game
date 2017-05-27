#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <gl/glut.h>

GLfloat hViewport = 600.0, wViewport = 500.0;
GLfloat hTriangle = hViewport / 25.0, wTriangle = wViewport / 25.0;
GLfloat xTriangle = wViewport / 2, yTriangle = hTriangle;

typedef struct{
	int x;
	int y; // One of coordinate of a vehicle which is our reference point for drawing.
	
	int type; // If 1, it means this vehicle is a square. If 0, a rectangle.
	
	int direction; // If 1, the vehicle goes +x direction. If 0, it goes -x direction.
} Vehicle;

typedef struct {
	int x;
	int y; 
	int r = hTriangle / 2;
	int duration = 300;
} Circle;


std::vector<std::vector<Vehicle>> vehicleList (19);
std::vector<Circle> coins;

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
	glColor3f(0.6, 0.6, 0.6);

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

void drawCircle(float cx, float cy, float r)
{
	int num_segments = 90;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

void drawCoins() {
	glColor3f(1.0, 1.0, 0.0);
	for (auto& coin : coins) 
		drawCircle(coin.x, coin.y, coin.r);
}

static void up() {
	int count = 2; // this count is the # of road. because of the first one is a safe place, we started with 2
	for (auto& road : vehicleList) {
		if (count == 6 || count == 10 || count == 15 || count == 20) // this count is for determining the # of road. This numbers are safe places, not road.
			count++; // Then, we increase the count for skipping safe places.

		for (auto& vehicle : road) { // updating vehicles' places
			if (vehicle.direction)
				vehicle.x += (count % 3) * 2 + 3;
			else
				vehicle.x -= (count % 3) * 3 + 2;

			// this part is for determining if a vehicle crushes to our triangle or not

			if (isUpper == 1) { // means our triangle goes up
				if (vehicle.y == yTriangle && vehicle.x >= xTriangle - wTriangle / 2 && vehicle.x <= xTriangle + wTriangle/2)
					exit(0); // ADD A CLOSING METHOD HERE

				else {
					if (vehicle.direction) { // +x
						if (vehicle.type) { // square
							if (vehicle.y == yTriangle && xTriangle <= vehicle.x && xTriangle >= vehicle.x - hTriangle)
								exit(0);
						}
						else { // rectangle
							if (vehicle.y == yTriangle && xTriangle <= vehicle.x && xTriangle >= vehicle.x - 2 * hTriangle)
								exit(0);
						}
					}
					else { // -x
						if (vehicle.type) { // square
							if (vehicle.y == yTriangle && xTriangle >= vehicle.x && xTriangle <= vehicle.x + hTriangle)
								exit(0);
						}
						else { // rectangle
							if (vehicle.y == yTriangle && xTriangle >= vehicle.x && xTriangle <= vehicle.x + 2 * hTriangle)
								exit(0);
						}
					}
				}
			}
			else { // means our triangle goes down
				if (vehicle.y == yTriangle + hTriangle && vehicle.x >= xTriangle - wTriangle / 2 && vehicle.x <= xTriangle + wTriangle / 2)
					exit(0);

				else {
					if (vehicle.direction) { // +x
						if (vehicle.type) { // square
							if (vehicle.y == yTriangle + hTriangle && xTriangle <= vehicle.x && xTriangle >= vehicle.x - hTriangle)
								exit(0);
						}
						else { // rectangle
							if (vehicle.y == yTriangle + hTriangle && xTriangle <= vehicle.x && xTriangle >= vehicle.x - 2 * hTriangle)
								exit(0);
						}
					}
					else { // -x
						if (vehicle.type) { // square
							if (vehicle.y == yTriangle + hTriangle && xTriangle >= vehicle.x && xTriangle <= vehicle.x + hTriangle)
								exit(0);
						}
						else { // rectangle
							if (vehicle.y == yTriangle + hTriangle && xTriangle >= vehicle.x && xTriangle <= vehicle.x + 2 * hTriangle)
								exit(0);
						}
					}
				}
			}
		}

		std::vector<Vehicle>::iterator it = road.begin(); // with this iterator, we will delete the vehicles which exit the screen

		while (it != road.end()) { // iteration over the road
			Vehicle vhc = *it;
			if (vhc.direction) { // means this vehicle goes +x way
				if (vhc.type) { // means this is a square
					if (vhc.x - hTriangle >= wViewport) // means this square is out of road. we can delete it
						it = road.erase(it);
					else
						++it; // if not, we skip at this time
				}
				else { // means this vehicle is a rectangle
					if (vhc.x - 2 * hTriangle >= wViewport) // means this square is out of road. we can delete it
						it = road.erase(it);
					else
						++it; // if not, we skip at this time
				}
			}
			else { // means this vehicle goes -x way
				if (vhc.type) { // means this is a square
					if (vhc.x + hTriangle <= 0) // means this square is out of road. we can delete it
						it = road.erase(it);
					else
						++it; // if not, we skip at this time
				}
				else { // means this vehicle is a rectangle
					if (vhc.x + 2 * hTriangle <= 0) // means this square is out of road. we can delete it
						it = road.erase(it);
					else
						++it; // if not, we skip at this time
				}
			}
		}

		if (!(rand() % 100)) { // adding new vehicle to the road
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

			road.push_back(v);
		}
		count++;
	}

	for (int i = 0; i < coins.size(); i++) { // every single coin has a duration. when duration ends, the coin will disappear from the screen
		coins[i].duration--;
		if (!coins[i].duration)
			coins.erase(coins.begin() + i);
	}

	std::vector<Circle>::iterator it = coins.begin(); // this is an iteration for collecting coins. if the coins center overlaps with our triangle, it means we collected this coin

	while (it != coins.end()) {
		Circle c = *it;
		if (c.x <= (xTriangle + (wTriangle / 2)) && c.x >= (xTriangle - (wTriangle / 2))) {
			if (isUpper == 1 && c.y <= yTriangle && c.y >= yTriangle - hTriangle)
				it = coins.erase(it);
			else if (isUpper == -1 && c.y >= yTriangle && c.y <= yTriangle + hTriangle)
				it = coins.erase(it);
			else
				++it;
		}
		else ++it;
	}
		
	if (!(rand() % 100)) { // generating a coin randomly
		Circle c;
		c.x = rand() % 476 + 12;
		c.y = (1 + (2 * rand()) % 50)*(hTriangle / 2);
		coins.push_back(c);
	}
}


void myTimer(int val) {
	up();
	glutPostRedisplay();
	glutTimerFunc(50, myTimer, val);
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
	drawCoins();
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