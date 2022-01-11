#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <random>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>


#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)



//player 
double playerX = 0.5;
double playerY = 0;
double playerZ = 0.5;
double playerAngle = 0;
//present One
double presentOneX = 1.2;
double presentOneY = 0.05;
double presentOneZ = 0.5;
//present Two
double presentTwoX = 0.9;
double presentTwoY = 0.05;
double presentTwoZ = 0.1;
//present Three
double presentThreeX = 0.9;
double presentThreeY = 0.05;
double presentThreeZ = 0.7;
// presents bool and angle
bool presentOne = true;
bool presentTwo = true;
bool presentThree = true;
double presentAngle = 0;
bool presentAnim = false;
// rgb Fence
double r = 0.588;
double g = 0.294;
double b = 0;
// Snowman
double snowManX = 0.25;
double snowManY = 0.1;
double snowManZ = 0.2;
int snowaManAngle = 0;
bool snowManAnim = false;
// tree one
double treeOneX = -0.1;
double treeOneY = 0.2;
double treeOneZ = -0.2;
int treeOneAngle = 0;
//tree two
double treeTwoX = -0.1;
double treeTwoY = 0.2;
double treeTwoZ = 1.2;
int treeTwoAngle = 0;
bool treeAnim = false;
//build one
double buildOneX = 0.7;
double buildOneY = 0.285;
double buildOneZ = 1.2;
// build two
double buildTwoX = 0.7;
double buildTwoY = 0.285;
double buildTwoZ = -0.2;
double s = 5;
bool buildAnim = false;
bool Up = true;
// light
bool UpLight = true;
//light one
double lightOneX = 0.9;
double lightOneY = 0.05;
double lightOneZ = 0.9;
// light two
double lightTwoX = 0.3;
double lightTwoY = 0.05;
double lightTwoZ = 0.9;
// light three
double lightThreeX = 0.5;
double lightThreeY = 0.05;
double lightThreeZ = 0.2;
int lightAngle = 0;
bool lightAnim = false;
// timer
int timer = 0;
// timer position
double positionX = -2.9;
double positionY = 0.8;
double positionZ = 0.5;
// finish 
bool finish = false;
bool win = false;



class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 2.9f, float eyeY = 0.8f, float eyeZ = 0.5f, float centerX = 0.5f, float centerY = 0.5f, float centerZ = 0.5f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void rotateZ(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
	}

	void rotateY(float d) {
		eye = eye + up.unit() * d;
	}

	void moveX(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
	}

	void topView() {
		eye.x = 0.5f;
		eye.y = 2.0f;
		eye.z = 0.325f;
	}
	void sideView() {
		eye.x = 0.5f;
		eye.y = 0.5f;
		eye.z = -2.5f;
	}
	void frontView() {
		eye.x = 2.9f;
		eye.y = 0.8f;
		eye.z = 0.5f;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

void drawFenceBack(int x, int y, int z)
{

	glColor3f(r, g, b);
	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z - 0.45);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z - 0.25);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z - 0.05);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z + 0.2);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z + 0.45);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z + 0.65);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z + 0.85);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z + 1.05);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z + 1.25);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.18, z + 1.45);
	glScaled(0.01, 0.3, 0.09);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.5, y + 0.15, z + 0.55);
	glScaled(0.01, 0.1, 2);
	glutSolidCube(1);
	glPopMatrix();


}

void drawFenceRight(int x, int y, int z)
{

	glColor3f(r, g, b);
	glPushMatrix();
	glTranslated(x - 0.45, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.25, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.05, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.2, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.45, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.65, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.85, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 1.05, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 1.25, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 1.45, y + 0.18, z - 0.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.55, y + 0.15, z - 0.5);
	glScaled(2, 0.1, 0.01);
	glutSolidCube(1);
	glPopMatrix();


}

void drawFenceLeft(int x, int y, int z)
{

	glColor3f(r, g, b);
	glPushMatrix();
	glTranslated(x - 0.45, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.25, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.05, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.2, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.45, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.65, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.85, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 1.05, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 1.25, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 1.45, y + 0.18, z + 1.5);
	glScaled(0.09, 0.3, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.55, y + 0.15, z + 1.5);
	glScaled(2, 0.1, 0.01);
	glutSolidCube(1);
	glPopMatrix();


}

void drawFloor(double thickness) {

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(2);
	glPopMatrix();
}

void drawBuilding(double x, double y, double z, double r, double g, double  b, double s)
{

	// s = 5
	glColor3f(r, g, b);
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(1, s, 1);
	glutSolidCube(0.1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(x + 0.05, y + 0.115, z + 0.025);
	glScaled(0.1, 0.7, 0.3);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.05, y + 0.115, z - 0.025);
	glScaled(0.1, 0.7, 0.3);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.05, y + 0.015, z + 0.025);
	glScaled(0.1, 0.7, 0.3);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.05, y + 0.015, z - 0.025);
	glScaled(0.1, 0.7, 0.3);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.05, y - 0.085, z + 0.025);
	glScaled(0.1, 0.7, 0.3);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.05, y - 0.085, z - 0.025);
	glScaled(0.1, 0.7, 0.3);
	glutSolidCube(0.1);
	glPopMatrix();
}

void drawSnowMan(double x, double y, double z)
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(x, y, z);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y + 0.175, z);
	glutSolidSphere(0.075, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y + 0.3, z);
	glutSolidSphere(0.05, 15, 15);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(x + 0.05, y + 0.3, z);
	glutSolidSphere(0.01, 15, 15);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(x, y + 0.32, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.25, 0.25, 0.25);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();

}

void drawPresent(double x, double y, double z, double r, double g, double  b)
{
	glColor3f(r, g, b);
	glPushMatrix();
	glTranslated(x, y, z);
	glutSolidCube(0.05);
	glPopMatrix();

	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslated(x + 0.03, y, z);
	glScaled(0.025, 0.4, 0.2);
	glutSolidCube(0.1);
	glPopMatrix();


	glPushMatrix();
	glTranslated(x + 0.01, y + 0.03, z);
	glRotated(90, 0, 0, 1);
	glScaled(0.025, 0.5, 0.2);
	glutSolidCube(0.1);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(x, y + 0.03, z);
	glutSolidSphere(0.009, 15, 15);
	glPopMatrix();
}

void drawTreeBig(double x, double y, double z)
{
	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslated(x, y - 0.2, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(1.1, 1.1, 1.1);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.9, 0.9, 0.9);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y + 0.2, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.7, 0.7, 0.7);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(x, y + 0.55, z);
	glScaled(0.7, 0.7, 0.7);
	glutSolidSphere(0.05, 15, 15);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(x + 0.2, y, z);
	glScaled(0.7, 0.7, 0.7);
	glutSolidSphere(0.05, 15, 15);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(x + 0.15, y + 0.2, z);
	glScaled(0.7, 0.7, 0.7);
	glutSolidSphere(0.05, 15, 15);
	glPopMatrix();
}

void drawTreeSmall(double x, double y, double z)
{
	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.7, 0.7, 0.7);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y + 0.2, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.5, 0.5, 0.5);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y + 0.4, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.3, 0.3, 0.3);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(x, y + 0.55, z);
	glScaled(0.4, 0.4, 0.4);
	glutSolidSphere(0.05, 15, 15);
	glPopMatrix();
}

void drawLights(double x, double y, double z)
{
	glColor3f(0.588, 0.294, 0);
	glPushMatrix();
	glTranslated(x, y + 0.1, z);
	glScaled(0.1, 1, 0.1);
	glutSolidCube(0.2);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(x, y + 0.2, z);
	glScaled(0.4, 0.4, 0.4);
	glutSolidSphere(0.08, 15, 15);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(0.4, 0.1, 0.4);
	glutSolidSphere(0.08, 15, 15);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(x, y + 0.22, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.2, 0.2, 0.2);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();
}

void drawPlayer(double x, double y, double z)
{


	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(x, y + 0.02, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.3, 0.3, 0.3);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();


	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(x, y + 0.2, z);
	glutSolidSphere(0.05, 15, 15);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(x + 0.05, y + 0.2, z + 0.02);
	glutSolidSphere(0.01, 15, 15);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(x + 0.05, y + 0.2, z - 0.02);
	glutSolidSphere(0.01, 15, 15);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(x, y + 0.22, z);
	glRotated(-90, 1, 0.0, 0.0);
	glScaled(0.25, 0.25, 0.25);
	glutSolidCone(0.15, 0.5, 10, 8);
	glPopMatrix();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void Display() {
	setupCamera();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setupLights();


	// Displaying the timer
	glColor3f(0.5, 0.5, 0.5);
	glRasterPos3f(-camera.eye.x, camera.eye.y, camera.eye.z + 1);
	char* scoreDisplay = "Timer   ";

	while (*scoreDisplay) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *scoreDisplay++);
	}


	glColor3f(1, 1, 1);
	glColor3f(0.5, 0.5, 0.5);
	glRasterPos3f(-camera.eye.x, camera.eye.y, camera.eye.z);
	int c = timer;
	int i = 4;
	while (i >= 0)
	{

		int a = c / pow(10, i);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, a + 48);
		int z = pow(10, i);
		c = c % z;
		i--;
	}


	//Snow Man

	glPushMatrix();
	glTranslatef(snowManX, snowManY, snowManZ);
	glRotatef(snowaManAngle, 0, 1, 0);
	drawSnowMan(0, 0, 0);
	glPopMatrix();

	// buildings 

	glPushMatrix();
	glTranslatef(buildOneX, buildOneY, buildOneZ);
	drawBuilding(0, 0, 0, 0, 1, 1, s);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(buildTwoX, buildTwoY, buildTwoZ);
	drawBuilding(0, 0, 0, 0, 0, 1, s);
	glPopMatrix();


	//Presents collectibles
	if (((playerX + 0.1 >= presentOneX) && playerX < presentOneX + 0.05 && (playerZ <= presentOneZ + 0.05 && playerZ >= presentOneZ)) && !finish) {
		presentOne = false;
	}
	if (((playerX + 0.1 >= presentTwoX) && playerX < presentTwoX + 0.05 && (playerZ <= presentTwoZ + 0.05 && playerZ >= presentTwoZ)) && !finish) {
		presentTwo = false;
	}
	if (((playerX + 0.1 >= presentThreeX) && playerX < presentThreeX + 0.05 && (playerZ <= presentThreeZ + 0.05 && playerZ >= presentThreeZ)) && !finish) {
		presentThree = false;
	}
	if (presentOne)
	{
		glPushMatrix();
		glTranslated(presentOneX, presentOneY, presentOneZ);
		glRotated(presentAngle, 0, 1, 0);
		drawPresent(0, 0, 0, 1, 1, 0);
		glPopMatrix();

	}
	if (presentTwo)
	{
		glPushMatrix();
		glTranslated(presentTwoX, presentTwoY, presentTwoZ);
		glRotated(presentAngle, 0, 1, 0);
		drawPresent(0, 0, 0, 1, 0, 1);
		glPopMatrix();

	}
	if (presentThree)
	{
		glPushMatrix();
		glTranslated(presentThreeX, presentThreeY, presentThreeZ);
		glRotated(presentAngle, 0, 1, 0);
		drawPresent(0, 0, 0, 1, 0, 0);
		glPopMatrix();
	}



	// draw christmass tree 
	glPushMatrix();
	glTranslatef(treeOneX, treeOneY, treeOneZ);
	glRotatef(treeOneAngle, 0, 1, 0);
	drawTreeBig(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treeTwoX, treeTwoY, treeTwoZ);
	glRotatef(treeTwoAngle, 0, 1, 0);
	drawTreeBig(0, 0, 0);
	glPopMatrix();



	// draw lights
	glPushMatrix();
	glTranslatef(lightOneX, lightOneY, lightOneZ);
	glRotatef(lightAngle, 0, 1, 0);
	drawLights(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lightTwoX, lightTwoY, lightTwoZ);
	glRotatef(lightAngle, 0, 1, 0);
	drawLights(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lightThreeX, lightThreeY, lightThreeZ);
	glRotatef(lightAngle, 0, 1, 0);
	drawLights(0, 0, 0);
	glPopMatrix();


	// draw floor
	drawFloor(0.02);

	//draw back fence

	drawFenceBack(0, 0, 0);


	// draw right fence

	drawFenceRight(0, 0, 0);


	// draw left fence

	drawFenceLeft(0, 0, 0);


	//draw player

	glPushMatrix();
	glTranslated(playerX, playerY, playerZ);
	glRotated(playerAngle, 0, 1, 0);
	drawPlayer(0, 0, 0);
	glPopMatrix();

	// win 
	if (!presentOne && !presentThree && !presentTwo && !finish)
	{
		win = true;
	}
	//win 
	if (win)
	{
		glColor3f(0.5, 0.5, 0.5);
		glRasterPos3f(-camera.eye.x, camera.eye.y + 2, camera.eye.z + 1);
		char* scoreDisplay2 = "Congratulations";

		while (*scoreDisplay2) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *scoreDisplay2++);
		}
	}

	//fail
	if (finish && !win)
	{
		glColor3f(0.5, 0.5, 0.5);
		glRasterPos3f(-camera.eye.x, camera.eye.y + 1, camera.eye.z + 1);
		char* scoreDisplay2 = "Hard Luck...........Time is Up";

		while (*scoreDisplay2) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *scoreDisplay2++);
		}
	}

	if (finish)
	{
		if (presentOneY <= 0.5) {
			presentOneY += 0.02;
			presentThreeY += 0.02;
			presentTwoY += 0.02;
		}
	}





	glFlush();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;
	float a = 0.125;

	switch (key) {

	case 'q':
		camera.moveX(d);
		break;
	case 'e':
		camera.moveX(-d);
		break;
	case 'f':
		camera.frontView();
		break;
	case 's':
		camera.sideView();
		break;
	case 't':
		camera.topView();
		break;
	case 'w':
		camera.rotateY(-a);
		break;
	case 'x':
		camera.rotateY(a);
		break;
	case 'a':
		camera.rotateZ(a);
		break;
	case 'd':
		camera.rotateZ(-a);
		break;
	case 'o':
		if (snowManAnim == false)
		{
			snowManAnim = true;
			PlaySound(TEXT("hohoho"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else
		{
			snowManAnim = false;
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);

		}
		break;
	case 'p':
		if (treeAnim == false)
		{
			treeAnim = true;
			PlaySound(TEXT("jingle-bell-1"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else
		{
			treeAnim = false;
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		}
		break;
	case 'i':
		if (buildAnim == false)
		{
			buildAnim = true;
			PlaySound(TEXT("sfx_point.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else
		{
			buildAnim = false;
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		}
		break;
	case 'u':
		if (lightAnim == false)
		{
			lightAnim = true;
			PlaySound(TEXT("xmasbell"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else
		{
			lightAnim = false;
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		}
		break;
	case 'y':
		if (presentAnim == false)
		{
			presentAnim = true;
			PlaySound(TEXT("sfxOZAR04"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else
		{
			presentAnim = false;
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		}
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}

void Special(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:

		if (playerAngle >= 360)
		{
			playerAngle -= 360;
		}
		if (playerAngle < 0)
		{
			playerAngle += 360;
		}
		if (playerAngle == 0 && playerX + 0.1 < 1.45) {
			playerX += 0.1;
		}
		else if (playerAngle == 180 && playerX - 0.1 > -0.35)
		{
			playerX -= 0.1;
		}
		else
			if (playerAngle == 90 && playerZ - 0.1 > -0.25) {
				playerZ -= 0.1;
			}
			else if (playerAngle == 270 && playerZ < 1.35)
			{
				playerZ += 0.1;
			}
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		playerAngle -= 90;
		break;
	case GLUT_KEY_RIGHT:
		playerAngle += 90;
		break;
	}

	glutPostRedisplay();
}

void Timer(int value)
{

	srand(time(0));
	r = float(rand()) / float(RAND_MAX);
	g = float(rand()) / float(RAND_MAX);
	b = float(rand()) / float(RAND_MAX);



	//Snow man
	if (snowManAnim)
	{
		snowaManAngle += 10;
	}
	else
	{
		snowaManAngle = 0;
	}

	//Tree
	if (treeAnim)
	{
		treeOneAngle += 10;
		treeTwoAngle += 10;
	}
	else
	{
		treeOneAngle = 0;
		treeTwoAngle = 0;
	}

	//Present
	if (presentAnim)
	{
		presentAngle += 10;
	}
	else
	{
		presentAngle = 0;
	}

	//Light
	if (lightAnim)
	{
		lightAngle += 10;

		if (lightOneY >= 1)
		{
			UpLight = false;
		}

		if (lightOneY <= 0.05)
		{
			UpLight = true;
		}


		if (UpLight) {
			lightOneY += 0.02;
			lightTwoY += 0.02;
			lightThreeY += 0.02;
		}
		else
		{
			lightOneY -= 0.02;
			lightTwoY -= 0.02;
			lightThreeY -= 0.02;
		}
	}
	else
	{
		lightAngle = 0;
		lightOneY = 0.05;
		lightTwoY = 0.05;
		lightThreeY = 0.05;
	}

	//Buildings
	if (buildAnim)
	{
		if (s >= 10)
		{
			Up = false;

		}
		if (s <= 5)
		{
			Up = true;
		}


		if (!Up)
		{
			s -= 0.2;
			buildOneY -= 0.01;
			buildTwoY -= 0.01;
		}
		else
		{
			s += 0.2;
			buildOneY += 0.01;
			buildTwoY += 0.01;
		}

	}
	else
	{
		s = 5;
		buildOneY = 0.285;
		buildTwoY = 0.285;
	}



	glutPostRedisplay();

	glutTimerFunc(200, Timer, r);

}

void Timer2(int value)
{

	timer++;
	if (timer >= 25 || win)
	{
		finish = true;
		glutTimerFunc(1000, NULL, 0);
	}
	else {
		glutPostRedisplay();

		glutTimerFunc(1000, Timer2, 0);
	}

}

//void Timer3(int value)
//{
//
//	PlaySound(TEXT("xmasbell"), NULL, SND_ASYNC | SND_FILENAME );
//	if (timer >= 25 || win)
//	{
//		finish = true;
//		glutTimerFunc(3000, NULL, 0);
//	}
//	else {
//		glutPostRedisplay();
//
//		glutTimerFunc(5000, Timer3, 0);
//	}
//
//}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Assignment Two");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutTimerFunc(200, Timer, 0);
	glutTimerFunc(1000, Timer2, 0);
	/*glutTimerFunc(5000, Timer3, 0);*/
	/*PlaySound(TEXT("song"), NULL, SND_ASYNC | SND_FILENAME);*/


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.7, 0.7, 0.7, 0.7);



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
