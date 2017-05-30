#include <time.h>
#include <stdlib.h>
#include <vector>
#include <gl/glut.h>
#include<GL/freeglut.h>
#include <string>

void myTimer(int val);

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

typedef struct {
	int x;
	int y;
	int r = hTriangle / 2;
	int duration = 100;
} SpecialCircle;


std::vector<std::vector<Vehicle>> vehicleList (19);
std::vector<Circle> coins;
std::vector<SpecialCircle> specialCoins;

//This variable is a flag for triangle's direction. If it is 1, it means the triangle is going up. If it is -1, it means down.
int isUpper = 1;

int score = 0, collectedCoins = 0, collectedSuperCoins = 0;

int powerUp = 0, powerUpDuration = 150;

int pauseFlag = 0, exitFlag = 0, debugFlag = 0;

void drawTriangle() {
	//glClear(GL_COLOR_BUFFER_BIT);
	
	if(powerUp) glColor3f((rand() / ((double)RAND_MAX)), (rand() / ((double)RAND_MAX)), (rand() / ((double)RAND_MAX)));
	else glColor3f(1.0, 0.0, 0.0);
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
	
	if (powerUp) glColor3f((rand() / ((double)RAND_MAX)), (rand() / ((double)RAND_MAX)), (rand() / ((double)RAND_MAX)));
	else glColor3f(0.6, 0.6, 0.6);

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
	for (auto& specialCoin: specialCoins){
		glColor3f((rand() / ((double)RAND_MAX)), (rand() / ((double)RAND_MAX)), (rand() / ((double)RAND_MAX)));
		drawCircle(specialCoin.x, specialCoin.y, specialCoin.r);
	}
}

void bitMapString(float x, float y, char s[]) {
	int i = 0;
	glRasterPos2f(x, y);
	while (s[i] != '\0') {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
		++i;
	}
}

void closureScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::string total("You collected ");
	total += std::to_string(collectedCoins);
	total += " coins and ";
	total += std::to_string(collectedSuperCoins);
	total += " Super coins."; 
	std::string total2 = "Your score is ";
	total2 += std::to_string(score + 5 * collectedCoins + 10 * collectedSuperCoins);
	
	char temp[1024];
	char temp2[1024];
	strcpy(temp, total.c_str());
	strcpy(temp2, total2.c_str());
	glColor3f(1.0, 1.0, 0.0);
	bitMapString(200,350, "GAME OVER");
	bitMapString(80, 300, temp);
	bitMapString(180, 250, temp2);
}

void writeCoordinates() {
	glColor3f(0.0, 0.0, 1.0);

	std::string coordinateTriangle("(x = ");
	coordinateTriangle += std::to_string(xTriangle);
	coordinateTriangle += ", y = ";
	coordinateTriangle += std::to_string(yTriangle);
	coordinateTriangle += ", direction = ";
	coordinateTriangle += std::to_string(isUpper);
	coordinateTriangle += ")";

	char tempTriangle[1024];
	strcpy(tempTriangle, coordinateTriangle.c_str());
	bitMapString(xTriangle, yTriangle, tempTriangle);

	for (auto& road : vehicleList) {
		for (auto& vehicle : road) {
			std::string coordinateVehicle("(x = ");
			coordinateVehicle += std::to_string(vehicle.x);
			coordinateVehicle += ", y = ";
			coordinateVehicle += std::to_string(vehicle.y);
			coordinateVehicle += ", direction = ";
			coordinateVehicle += std::to_string(vehicle.direction);
			coordinateVehicle += ", type = ";
			coordinateVehicle += std::to_string(vehicle.type);
			coordinateVehicle += ")";

			char tempVehicle[1024];
			strcpy(tempVehicle, coordinateVehicle.c_str());
			bitMapString(vehicle.x, vehicle.y, tempVehicle);
		}
	}

	for (auto& coin : coins) {
		std::string coordinateCoin("(x = ");
		coordinateCoin += std::to_string(coin.x);
		coordinateCoin += ", y = ";
		coordinateCoin += std::to_string(coin.y);
		coordinateCoin += ", radius = ";
		coordinateCoin += std::to_string(coin.r);
		coordinateCoin += ", duration = ";
		coordinateCoin += std::to_string(coin.duration);
		coordinateCoin += ")";

		char tempCoin[1024];
		strcpy(tempCoin, coordinateCoin.c_str());
		bitMapString(coin.x, coin.y, tempCoin);
	}

	for (auto& coin : specialCoins) {
		std::string coordinateSpecialCoin("(x = ");
		coordinateSpecialCoin += std::to_string(coin.x);
		coordinateSpecialCoin += ", y = ";
		coordinateSpecialCoin += std::to_string(coin.y);
		coordinateSpecialCoin += ", radius = ";
		coordinateSpecialCoin += std::to_string(coin.r);
		coordinateSpecialCoin += ", duration = ";
		coordinateSpecialCoin += std::to_string(coin.duration);
		coordinateSpecialCoin += ")";

		char tempSpecialCoin[1024];
		strcpy(tempSpecialCoin, coordinateSpecialCoin.c_str());
		bitMapString(coin.x, coin.y, tempSpecialCoin);
	}
}

static void update() {
	int count = 2; // this count is the # of road. because of the first one is a safe place, we started with 2
	for (auto& road : vehicleList) {
		if (count == 6 || count == 10 || count == 15 || count == 20) // this count is for determining the # of road. This numbers are safe places, not road.
			count++; // Then, we increase the count for skipping safe places.

		for (auto& vehicle : road) { // updating vehicles' places
			if (vehicle.direction)
				vehicle.x += (count % 3) * 4 + 5;
			else
				vehicle.x -= (count % 3) * 5 + 4;

			// this part is for determining if a vehicle crushes to our triangle or not

			if (!powerUp) {
				if (isUpper == 1) { // means our triangle goes up
					if (vehicle.y == yTriangle && vehicle.x >= xTriangle - wTriangle / 2 && vehicle.x <= xTriangle + wTriangle / 2) 
						exitFlag = 1;

					else {
						if (vehicle.direction) { // +x
							if (vehicle.type) { // square
								if (vehicle.y == yTriangle && xTriangle <= vehicle.x && xTriangle >= vehicle.x - hTriangle) 
									exitFlag = 1;
							}
							else { // rectangle
								if (vehicle.y == yTriangle && xTriangle <= vehicle.x && xTriangle >= vehicle.x - 2 * hTriangle) 
									exitFlag = 1;
							}
						}
						else { // -x
							if (vehicle.type) { // square
								if (vehicle.y == yTriangle && xTriangle >= vehicle.x && xTriangle <= vehicle.x + hTriangle) 
									exitFlag = 1;
							}
							else { // rectangle
								if (vehicle.y == yTriangle && xTriangle >= vehicle.x && xTriangle <= vehicle.x + 2 * hTriangle) 
									exitFlag = 1;
							}
						}
					}
				}
				else { // means our triangle goes down
					if (vehicle.y == yTriangle + hTriangle && vehicle.x >= xTriangle - wTriangle / 2 && vehicle.x <= xTriangle + wTriangle / 2) 
						exitFlag = 1;

					else {
						if (vehicle.direction) { // +x
							if (vehicle.type) { // square
								if (vehicle.y == yTriangle + hTriangle && xTriangle <= vehicle.x && xTriangle >= vehicle.x - hTriangle) 
									exitFlag = 1;
							}
							else { // rectangle
								if (vehicle.y == yTriangle + hTriangle && xTriangle <= vehicle.x && xTriangle >= vehicle.x - 2 * hTriangle) 
									exitFlag = 1;
							}
						}
						else { // -x
							if (vehicle.type) { // square
								if (vehicle.y == yTriangle + hTriangle && xTriangle >= vehicle.x && xTriangle <= vehicle.x + hTriangle) 
									exitFlag = 1;
							}
							else { // rectangle
								if (vehicle.y == yTriangle + hTriangle && xTriangle >= vehicle.x && xTriangle <= vehicle.x + 2 * hTriangle) 
									exitFlag = 1;
							}
						}
					}
				}
				glutPostRedisplay();
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

	for (int i = 0; i < specialCoins.size(); i++) { // every single coin has a duration. when duration ends, the coin will disappear from the screen
		specialCoins[i].duration--;
		if (!specialCoins[i].duration)
			specialCoins.erase(specialCoins.begin() + i);
	}

	if (powerUp)
		powerUpDuration--;
	if (!powerUpDuration)
		powerUp = 0;

	std::vector<Circle>::iterator it = coins.begin(); // this is an iteration for collecting coins. if the coins center overlaps with our triangle, it means we collected this coin

	while (it != coins.end()) {
		Circle c = *it;
		if (c.x <= (xTriangle + (wTriangle / 2)) && c.x >= (xTriangle - (wTriangle / 2))) {
			if (isUpper == 1 && c.y <= yTriangle && c.y >= yTriangle - hTriangle) {
				it = coins.erase(it);
				collectedCoins++;
			}
			else if (isUpper == -1 && c.y >= yTriangle && c.y <= yTriangle + hTriangle) {
				it = coins.erase(it);
				collectedCoins++;
			}
			else
				++it;
		}
		else ++it;
	}

	std::vector<SpecialCircle>::iterator specIt = specialCoins.begin();

	while (specIt != specialCoins.end()) {
		SpecialCircle c = *specIt;
		if (c.x <= (xTriangle + (wTriangle / 2)) && c.x >= (xTriangle - (wTriangle / 2))) {
			if (isUpper == 1 && c.y <= yTriangle && c.y >= yTriangle - hTriangle) {
				powerUp = 1; powerUpDuration = 150;
				specIt = specialCoins.erase(specIt);
				collectedSuperCoins++;
			}
			else if (isUpper == -1 && c.y >= yTriangle && c.y <= yTriangle + hTriangle) {
				powerUp = 1; powerUpDuration = 150;
				specIt = specialCoins.erase(specIt);
				collectedSuperCoins++;
			}
			else
				++specIt;
		}
		else ++specIt;
	}

	if (!(rand() % 100)) { // generating a coin randomly
		Circle c;
		c.x = rand() % 476 + 12;
		c.y = (1 + (2 * rand()) % 50)*(hTriangle / 2);
		coins.push_back(c);
	}

	if (!(rand() % 200)) { // generating a special coin randomly
		SpecialCircle sc;
		sc.x = rand() % 476 + 12;
		sc.y = (1 + (2 * rand()) % 50)*(hTriangle / 2);
		specialCoins.push_back(sc);
	}
}


void myTimer(int value) {
		update();
		glutPostRedisplay();
		if(!pauseFlag)
			glutTimerFunc(50, myTimer, value);
}

void myinit(void){

	glViewport(0, 0, wViewport, hViewport);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, wViewport, 0.0, hViewport);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y){
	if (key == 'Q' || key == 'q')
		exit(0);
}

void mymouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		debugFlag = 0;
		if (pauseFlag) {
			pauseFlag = 0;
			myTimer(0);
		}
	}

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		pauseFlag = 1;
		myTimer(0);
	}

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		pauseFlag = 1;
		myTimer(0);
		debugFlag = 1;
	}
}

void handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (isUpper == 1) {
			if(!exitFlag)
			score++;
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
			if (!exitFlag)
			score++;
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
	
	if (exitFlag) closureScreen();
	else {
		drawRoad();
		drawTriangle();
		drawVehicles();
		drawCoins();
		if (debugFlag)
			writeCoordinates();
	}
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
	glutMouseFunc(mymouse);
	glutKeyboardFunc(myKeyboard);
	myTimer(0);
	glutMainLoop();
}