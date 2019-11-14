#include<bits/stdc++.h>
#include<GL/glut.h>


#define MAX_CARS 3

void drawCar();
void drawFootPath();
void drawDivider();
void drawSurroundings();
void stopGame();
void drawOtherCars(int);
void drawOther();
void setCars();
void moveOtherCars();
int detectCollision();
void drawString(std::string);
void drawMainMenu();
void drawExitMenu();
void drawTime();
void stopGame();
void resumeGame();
void drawScore(int);
void moveEnd();
void drawFuelBar();
void fuelMessage();
void drawFuel();

int foot_y = 200;
int div_y = 220;
int end_y = 16000;

int a = 0;
int speed = 1;
int steerSpeed = 2;
int temp = 0;
int seconds = 0;
int distance = 178;
int fuel = 178;

int game_state = 0;

void moveDivider();
void moveRoad();
void moveCar();
void periodicFunction(int);
void moveFuel();

int lane[MAX_CARS];
int pos[MAX_CARS];
int speeds[MAX_CARS];
int speedsTemp[MAX_CARS];

GLdouble width=1200, height=800;

bool carMoveLeft = false, carMoveRight = false, carMoveFast = false, carStopped = false, gameStopped = false, horn = false;
bool highlightStart = false, highlightExit = false;
bool reachedEnd = false, gameCompleted = false, fuelOver = false;
int car_x = 0;
int car_y = -100;

int fuel_x = 0;
int fuel_y = -80;

void maindisp()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

    switch(game_state)
	{

        case 0 : drawMainMenu();
            break;

        case 1 : glClearColor(0.5, 0.5, 0.5, 0.0);
            drawFootPath();
            drawSurroundings();
            drawDivider();
            drawCar();
            drawOther();
            drawTime();
            drawFuelBar();
            drawFuel();
            break;

        

        case 2 : glClearColor(0.5, 0.5, 0.5, 0.0);
            drawFootPath();
            drawSurroundings();
            drawDivider();
            if(fuelOver)
                fuelMessage();

            drawCar();
            drawOther();
            drawFuelBar();
            drawExitMenu();
            drawTime();
            break;
	}

	glFlush();
	glutSwapBuffers();
}

void keyBoardFunc(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT : carMoveLeft = true; carMoveRight = false; break;
		case GLUT_KEY_RIGHT : carMoveRight = true; carMoveLeft = false; break;
		case GLUT_KEY_UP 	: carMoveFast = true; break;
	}
}

void keyboard_up_func(int k, int x, int y)
{
    switch(k)
    {
        case GLUT_KEY_LEFT: carMoveLeft=false; break;
        case GLUT_KEY_RIGHT: carMoveRight=false; break;
		case GLUT_KEY_UP : carMoveFast = false; break;
		case GLUT_KEY_DOWN : carStopped = false; break;
    }
}

void reset()
{
	gameStopped = false;
    gameCompleted = false;
    reachedEnd = false;
    seconds = 0;
    distance = 178;
    fuel = 178;
    fuelOver = false;
    end_y = 16000;
    setCars();
    game_state = 1;
    car_x = 0;    
}

void normalKeyBoardFunc(unsigned char key, int x, int y)
{
    if(game_state == 1)
    {
        switch(key)
        {
            case 'H':
            case 'h': horn = true; break;

        }
    }

    else
    {
    	switch(key)
        {
            case 's':
            case 'S': 	
            			reset();
            			break;
            case 'x':
            case 'X':
            			exit(0);

        }
    }
}

void mouse_func(int button, int state, int x, int y)
{
    switch(game_state)
    {
        case 0 : if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                 {
                    if(x >=  525 && x <= 675 && y >= 285 && y <= 355)
                    {
                    	reset();
                    }
                    else if(x >=  525 && x <= 675 && y >= 445 && y <= 515)
                        exit(0);
                 }
                 break;

        case 2 : if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                 {
                    if(x >=  525 && x <= 675 && y >= 285 && y <= 355)
                    {
                    	reset();
                    }
                    else if(x >=  525 && x <= 675 && y >= 445 && y <= 515)
                        exit(0);
                 }
                 break;
    }
}

void mouse_hover(int x, int y)
{
        if(x >=  525 && x <= 675 && y >= 285 && y <= 355)
        {
            highlightStart = true;
            highlightExit = false;
        }

        else if(x >=  525 && x <= 675 && y >= 445 && y <= 515)
        {
            highlightStart = false;
            highlightExit = true;
        }

        else
        {
            highlightExit = false;
            highlightStart = false;
        }
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize((int) width, (int) height);
	glutCreateWindow("Galaxian");
    glEnable(GL_MULTISAMPLE);

	gluOrtho2D(-240.0, 240.0, -160.0, 160.0);

	glutDisplayFunc(maindisp);
	glutTimerFunc(1, periodicFunction, 0);

    glutSpecialFunc(keyBoardFunc);
    glutSpecialUpFunc(keyboard_up_func);
    glutKeyboardFunc(normalKeyBoardFunc);
    glutMouseFunc(mouse_func);
    glutPassiveMotionFunc(mouse_hover);

	glutMainLoop();
	return 0;
}

void drawCar(void)
{
    glPushMatrix();

    glTranslated(car_x, car_y, 0.0);

    glColor3f(0.14,0.19,0.21);
    glRectd(-6,9,6,10);
    glColor3f(0.21,0.27,0.30);
    glRectd(-11,-16,-7,-9);
    glRectd(-10,6,-6,13);
    glRectd(11,-16,7,-9);
    glRectd(10,6,6,13);

    glColor3f(1.0, 0.23, 0.0);
    glRectd(-9,-19,9,-14);
    glColor3f(0.86, 0.17, 0.0);
    glRectd(-7,11,7,14);
    glColor3f(1.0, 0.23, 0.0);
    glBegin(GL_QUADS);
        glVertex2d(-1,15);
        glVertex2d(1,15);
        glVertex2d(3,0);
        glVertex2d(-3,0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(-3,0);
        glVertex2d(3,0);
        glVertex2d(7,-3);
        glVertex2d(3,-12);
        glVertex2d(-3,-12);
        glVertex2d(-7,-3);
    glEnd();
    glColor3f(0.32,0.42,0.47);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(7,-3);
        glVertex2d(7,-14);
        glVertex2d(2,-14);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(-7,-3);
        glVertex2d(-2,-14);
        glVertex2d(-7,-14);
    glEnd();
    glColor3f(0.14,0.19,0.21);
    glRectd(-7,-13,7,-12);
    glColor3f(0.86, 0.17, 0.0);
    glBegin(GL_QUADS);
        glVertex2d(-3,-12);
        glVertex2d(3,-12);
        glVertex2d(2,-14);
        glVertex2d(-2,-14);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glRectd(-2,-3,2,0);
    glRectd(-2,-6,2,-4);
	glPopMatrix();
}

void carColor1(int i)
{
    switch(speeds[i])
    {
        case 2 : glColor3f(0.0, 1.0, 0.0); break;
        case 3 : glColor3f(0.2, 0.2, 1.0); break;
        case 4 :
        case 5 :
        case 6 :
        case 7 :
        case 8 : glColor3f(1.0, 1.0, 0.0); break;
        case 0 : glColor3f(0.0, 0.0, 0.0); break;
    }
}

void carColor2(int i)
{
    switch(speeds[i])
    {
        case 2 : glColor3f(0.0, 0.0, 0.0); break;
        case 3 : glColor3f(0.0, 0.0, 0.0); break;
        case 4 :
        case 5 :
        case 6 :
        case 7 :
        case 8 : glColor3f(0.0, 0.0, 0.0); break;
        case 0 : glColor3f(0.0, 0.0, 0.0); break;
    }
}

void drawOtherCars(int i)
{
    glPushMatrix();
    glTranslated((lane[i] - 1)*37, pos[i], 0.0);


    glColor3f(0.14,0.19,0.21);
    glRectd(-6,9,6,10);
    glColor3f(0.21,0.27,0.30);
    glRectd(-11,-16,-7,-9);
    glRectd(-10,6,-6,13);
    glRectd(11,-16,7,-9);
    glRectd(10,6,6,13);
    carColor2(i);
    glRectd(-7,11,7,14);
    carColor1(i);
    glRectd(-9,-19,9,-14);
    glBegin(GL_QUADS);
        glVertex2d(-1,15);
        glVertex2d(1,15);
        glVertex2d(3,0);
        glVertex2d(-3,0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(-3,0);
        glVertex2d(3,0);
        glVertex2d(7,-3);
        glVertex2d(3,-12);
        glVertex2d(-3,-12);
        glVertex2d(-7,-3);
    glEnd();
    glColor3f(0.32,0.42,0.47);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(7,-3);
        glVertex2d(7,-14);
        glVertex2d(2,-14);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(-7,-3);
        glVertex2d(-2,-14);
        glVertex2d(-7,-14);
    glEnd();
    glColor3f(0.14,0.19,0.21);
    glRectd(-7,-13,7,-12);
    carColor2(i);
    glBegin(GL_QUADS);
        glVertex2d(-3,-12);
        glVertex2d(3,-12);
        glVertex2d(2,-14);
        glVertex2d(-2,-14);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glRectd(-2,-3,2,0);
    glRectd(-2,-6,2,-4);
	glPopMatrix();
}

void drawFootPath()
{
	int i, y;
	glPushMatrix();
	glTranslated(0, 0, 0);
	y = foot_y + 20;

	for(i = 0; i < 20; i++)
	{
		if(a == 0)
		{
			if(i % 2 == 0)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(0.0, 0.0, 0.0);
		}

		else
		{
			if(i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(0.0, 0.0, 0.0);
		}


		y -= 20;
		glRectd(65, y, 55, y - 20);
        glRectd(-55, y, -65, y - 20);
	}
	glPopMatrix();

}

void drawDivider()
{
	int i;
	int y = div_y + 80;
	glColor3f(1.0, 1.0, 1.0);

	for(i = 0 ; i < 5; i++)
	{
		y-=80;
		glRectd(22, y, 18, y-40);
		glRectd(-18, y, -22, y-40);
	}

}

void drawSurroundings()
{
	glColor3f(0.0, 1.0, 0.0);
	glRectd(240, 160, 65, -160);
	glRectd(-240, 160, -65, -160);
}

void stopGame()
{
	speed = 0;
	steerSpeed = 0;
}

void resumeGame()
{
    speed = 2;
    steerSpeed = 2;
}

void drawOther()
{
	int i;
	for(i = 0; i < MAX_CARS; i++)
	{
		drawOtherCars(i);
	}
}

void setCars()
{
	int i;
	for(i = 0; i < MAX_CARS; i++)
	{
		lane[i] = i;
		pos[i] = 110 + rand()%100;
        speeds[i] = 1 + i + rand()%4;
	}
}

void moveDivider()
{
	div_y -= speed;
	if(div_y < 120)
    {
        div_y = 200;

        if(carMoveFast)
        {
            distance -= 1.5;
            fuel -=4;
        }
        else
        {

            distance -= 0.5;
            fuel -= 2;
        }

        if(fuel < 0)
            fuelOver = true;
    }
}

void moveCar()
{
	if(carMoveLeft)
		car_x -= steerSpeed;


	else if(carMoveRight)
		car_x += steerSpeed;

	if(car_x > 45 || car_x < -45)
    {
        game_state = 2;
        gameStopped = true;
    }
}

void moveRoad()
{
	foot_y -= speed;
	if(foot_y < 160)
	{
		foot_y = 180;
		if(a == 0)
			a = 1;
		else
			a = 0;
	}
}

void periodicFunction(int v)
{
    if(gameStopped)
        stopGame();

    else
        resumeGame();

	if(speed != 0)
	{
		if(carMoveFast)
            speed = 7;

		else
            speed = 3;

	}

	if(fuelOver)
	{
        gameStopped = true;
        game_state = 2;

	}

	moveRoad();
	moveDivider();
	moveCar();
    moveOtherCars();
    moveEnd();
    moveFuel();

    if(!detectCollision() && !gameStopped && game_state == 1)
        temp += 50;

	if(temp > 1000)
    {
        temp  = 0;
        seconds+=(speed/2);
    }

	glutPostRedisplay();
	glutTimerFunc(10, periodicFunction, v);
}

void moveOtherCars()
{
    int i;
    for(i = 0; i < MAX_CARS; i++)
    {
        pos[i] += -speed + speeds[i];

        if(pos[i] < -200 || pos[i] > 200)
        {
            pos[i] = 200 + rand()%100;
            speeds[i] = 2 + rand()%5;
        }
        bool flag = 1;
        for (int j=0;j<MAX_CARS;j++)
        {
	    if (speeds[j] != speeds[i])
	        flag = 0;
        }
        if (flag)
	    speeds[i]++;
    }
    if(horn)
    {
        speeds[(car_x + 60)/40]++;
        if(speeds[(car_x + 60)/40] > 8)
            speeds[(car_x + 60)/40] = 8;
        horn = false;
        fuel -= 15;
    }
}

int detectCollision()
{
    if(game_state != 1)
        return 0;

    int i, limit;
    for(i = 0; i < MAX_CARS; i++)
    {
        if(pos[i] < -70 && pos[i] > -130)
        {
            limit = (i - 1)*40;
            if(car_x < limit + 22 && car_x > limit - 22)
            {
                speeds[i] = 0;
                gameStopped = true;
                game_state = 2;
                return 1;
            }
        }
    }

    if((fuel_x >= car_x && fuel_x - car_x < 20) || (fuel_x <= car_x && car_x - fuel_x < 20))
    {
        if(fuel_y < -70 && fuel_y > -140)
        {
            fuel+=55;
            if(fuel > 178)
                fuel = 178;
            fuel_y = 600 + rand()%150;
            fuel_x = (rand()%3 - 1)*37;
        }
    }

    return 0;

}

void draw_string(std::string str)
{
    for(unsigned int i=0;i<str.length();i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin()+i));
    }
}

void drawMainMenu()
{
    //Draw start button
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    drawFootPath();
    drawSurroundings();
    drawDivider();
    drawCar();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0, 30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-20, 25, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 1.0, 1.0);
    draw_string("START");

    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslated(0, -30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-12, -35, 0);
    glScalef(0.1, 0.1, 0.1);
    draw_string("EXIT");

    glPopMatrix();

    if(highlightStart)
    {
        glColor3f(1.0, 0.0, 0.0);

        glPushMatrix();
        glTranslated(0, 30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }

    if(highlightExit)
    {
        glColor3f(1.0, 0.0, 0.0);

        glPushMatrix();
        glTranslated(0, -30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }
}

void drawExitMenu()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0, 30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-27, 25, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 1.0, 1.0);
    draw_string("RESTART");

    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslated(0, -30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-12, -35, 0);
    glScalef(0.1, 0.1, 0.1);
    draw_string("EXIT");

    glPopMatrix();

    if(highlightStart)
    {
        glColor3f(1.0, 0.0, 0.0);

        glPushMatrix();
        glTranslated(0, 30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }

    if(highlightExit)
    {
        glColor3f(1.0, 0.0, 0.0);

        glPushMatrix();
        glTranslated(0, -30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }
}

void drawTime()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(-200, 90, 0);
    // glBegin(GL_LINE_LOOP);
    //     glVertex2f(50, 15);
    //     glVertex2f(50, -15);
    //     glVertex2f(-30, -15);
    //     glVertex2d(-30, 15);
    // glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-220, 85, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 1.0, 1.0);
    draw_string("Score: ");
    glPopMatrix();

    glPushMatrix();
    glTranslated(-180, 85, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 0.0, 0.0);
    drawScore(seconds);
    glPopMatrix();
}

void drawScore(int score)
{
    int temp = score;
    int str[20],i=0;

    while(temp>0)
    {
        str[i++] = (temp%10);
        temp /= 10;
    }
    i--;
    while(i>=0)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i--]+'0');
    }
    if(score == 0) glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
}

void drawFuelBar()
{
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);

    glTranslated(75, 40, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(5, 90);
        glVertex2f(5, -90);
        glVertex2f(-5, -90);
        glVertex2d(-5, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(75, -49, 0);
    float green = fuel/178.0;
    glColor3f(1.0, green, 0);
    glRectd(4, 0, -4, fuel);
    glPopMatrix();

}

void fuelMessage()
{
    glPushMatrix();
    glTranslated(75, -70, 0);
    glScalef(0.1,0.1,0.1);
    glColor3f(1.0, 0,0);
    draw_string("Fuel Exhausted\n");
    glPopMatrix();
}

void moveEnd()
{
    if(reachedEnd)
        end_y-= speed;
}

void drawFuel()
{
    glPushMatrix();
    glTranslated(fuel_x, fuel_y, 0);
    glColor3f(0.0, 1.0, 0.0);
    glRectf(5, 5, -5, -5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(fuel_x, fuel_y+5, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(5, 0);
        glVertex2f(5, 5);
        glVertex2f(-3, 5);
        glVertex2d(-5, 0);
    glEnd();
    glPopMatrix();

}

void moveFuel()
{
    fuel_y-=speed;

    if(fuel_y < -200)
    {
        fuel_y = 600 + rand()%150;
        fuel_x = (rand()%3 - 1)*37;
    }
}
