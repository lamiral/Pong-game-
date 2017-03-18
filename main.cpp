#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "shaders/shader.h"
#include "Player_count.h"
//#include "uTex.cpp"

using namespace std;

const int W = 800;
const int H = 800;

typedef unsigned int uint;

shader program;

uint player_1,player_2;
uint rocket_vao;


float step_P1;
float step_P2;

float step_rocket_x;
float step_rocket_y;

float p1_position;
float p2_position;

int count_p1;
int count_p2;

Player_count player_table_count1;
Player_count player_table_count2;

uint Texture;

struct position
{
	float x1;
	float y1;

	float x2;
	float y2;
};

position rocket;

void change_array_verticles(float *arr,float x1,float x2,float y1,float y2)
{
	arr[0] = x1; arr[1] = y1; arr[2] = 0.0f; 		arr[3] = 0.0f; arr[4] = 0.0f; 
	arr[5] = x1;  arr[6] = y2; arr[7] = 0.0f; 		arr[8] = 0.0f; arr[9] = 1.0f; 
	arr[10] = x2; arr[11] = y2; arr[12] = 0.0f; 	arr[13] = 1.0f; arr[14] = 1.0f; 
	arr[15] = x2; arr[16] = y1; arr[17] = 0.0f; 	arr[18] = 1.0f; arr[19] = 0.0f; 
}

void initVAO()
{
	uint VBO,IBO;

	float cube_verticles[] = 
	{
		-1.0,0.0,0.0,    0.0,0.0,
		-1.0,0.3,0.0,	 0.0,1.0,	
		-0.95,0.3,0.0,	 1.0,1.0,
		-0.95,0.0,0.0,	 1.0,0.0
	};

	uint elements[] = 
	{
		0,1,2,
		0,2,3
	};

	glGenVertexArrays(1,&player_1);

	glGenBuffers(1,&VBO);
	glGenBuffers(1,&IBO);

	glBindVertexArray(player_1);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(cube_verticles),cube_verticles,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elements),elements,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));

	glBindVertexArray(0);

	uint VBO1,IBO1;

	change_array_verticles(cube_verticles,1.0,0.95,0.0,0.3);

	glGenVertexArrays(1,&player_2);

	glGenBuffers(1,&VBO1);
	glGenBuffers(1,&IBO1);

	glBindVertexArray(player_2);

	glBindBuffer(GL_ARRAY_BUFFER,VBO1);
	glBufferData(GL_ARRAY_BUFFER,sizeof(cube_verticles),cube_verticles,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elements),elements,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));

	glBindVertexArray(0);


	uint VBO2,IBO2;

	change_array_verticles(cube_verticles,0.0,0.03,0.0,0.03);

	glGenVertexArrays(1,&rocket_vao);

	glGenBuffers(1,&VBO2);
	glGenBuffers(1,&IBO2);

	glBindVertexArray(rocket_vao);

	glBindBuffer(GL_ARRAY_BUFFER,VBO2);
	glBufferData(GL_ARRAY_BUFFER,sizeof(cube_verticles),cube_verticles,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elements),elements,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));

	glBindVertexArray(0);

	player_table_count1.init_table_count(-0.1,0.9);
	player_table_count2.init_table_count(0.1,0.9);
}

void initShader()
{
	const char *vsShader = 
	"#version 420 core\n"
	"layout(location = 0) in vec3 position;\n"
	"layout(location = 1) in vec2 UV;\n"
	"out vec2 outUV;\n"
	"uniform vec2 animation;\n"
	"void main(){\n"
	"	outUV = vec2(UV.x,1-UV.y);\n"
		"gl_Position = vec4(position.x+animation.x,position.y + animation.y,position.z,1.0f);}";

	const char *fsShader = 
	"#version 420 core\n"
	"out vec4 color;\n"
	"in vec2 outUV;\n"
	"uniform sampler2D samp;\n"
	"void main(){\n"
	"	color = texture(samp,outUV);}";

	program.load_shader(vsShader,fsShader);
	program.create_program();
}

void initTexture()
{
	textureUtils text;
	Texture = text.load_texture("numbers/cuad.jpg");
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
}

void draw_table()
{
	player_table_count1.draw_count();
	player_table_count2.draw_count();
}

void render()
{

	glClearColor(0.0,0.0,0.0,0.0);

	glClear(GL_COLOR_BUFFER_BIT);

	const char *uni_name = "animation";

	uint uniform_anim = glGetUniformLocation(program.program,uni_name);

	program.use_program();

	glBindTexture(GL_TEXTURE_2D,Texture);

	glUniform2f(uniform_anim,0,p1_position);
	glBindVertexArray(player_1);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);

	glUniform2f(uniform_anim,0,p2_position);
	glBindVertexArray(player_2);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);

	glUniform2f(uniform_anim,rocket.x1,rocket.y1);
	glBindVertexArray(rocket_vao);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);

	glUniform2f(uniform_anim,0,0);

	draw_table();

	glutSwapBuffers();
}

void rocketDirection()
{
	if((rocket.y1 > p1_position && rocket.y1< p1_position+0.3) && (rocket.x1 < -0.95 && rocket.x1 > -1.0))
	{
		step_rocket_x = -step_rocket_x;
		return;
	}

	else if((rocket.y1 > p2_position && rocket.y1 < p2_position+0.3) && (rocket.x2 > 0.95 && rocket.x2 < 0.97))
	{
		step_rocket_x = -step_rocket_x;
		return;
	}

	if(rocket.x1 < -1.0) 
		{
			step_rocket_x = 0.03;
			count_p2++;
			player_table_count2.change_texture_table(count_p2);
		}
	else if(rocket.x2 > 0.97)
	 	{
	  		step_rocket_x = -0.03;	
	  		count_p1++;
	  		player_table_count1.change_texture_table(count_p1);
	    }	
	if(rocket.y1 < -1.0)
	{
	 		step_rocket_y = 0.03;
	}
	else if(rocket.y1 > 0.97) 
		{
			step_rocket_y = -0.03;
		}
}

void changeRocketPosition()
{
	rocket.x1 += step_rocket_x;
	rocket.x2 += step_rocket_x;

	rocket.y1 += step_rocket_y;
	rocket.y2 += step_rocket_y;
}

void start_init()
{
	count_p2 = 0;
	count_p1 = 0;

	p1_position = 0.0;
	p2_position = 0.0;

	step_rocket_y = 0.03;
	step_rocket_x = -0.03;

	rocket.x1 = 0.0;
	rocket.y1 = 0.0;

	rocket.x2 = 0.03;
	rocket.y2 = 0.03;

	initVAO();
}

void chek_winner()
{
	if(count_p2 > 5 || count_p1 > 5)
		start_init();
}

void timer(int value = 0)
{		
	chek_winner();

	p1_position += step_P1;
	p2_position += step_P2;

	rocketDirection();
	changeRocketPosition();

	render();

	step_P1 = 0.0;
	step_P2 = 0.0;

	glutTimerFunc(33,timer,0);
}

void key(unsigned char Key,int x,int y)
{	
if(Key == 'W' || Key == 'w')		
		{
			if(p1_position < 0.7) step_P1 = 0.03;
		}
else if(Key == 'S' || Key == 's')
		{
			if(p1_position > -1.0) step_P1 = -0.03;
		}
  
if(Key == 'I' || Key == 'i')
		{
			if(p2_position < 0.7)	step_P2 = 0.03;
		}
else if(Key == 'K' || Key == 'k')
		{	
			if(p2_position > -1.0 ) step_P2 = -0.03;
		}
}

void Main()
{
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(W,H);
	glutCreateWindow("Pong");

	if(glewInit() != GLEW_OK)
	{
		cout << "Error glew! Exit program" << endl;
	}

	initShader();
	start_init();
	initTexture();

	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutTimerFunc(33,timer,0);
	glutKeyboardFunc(key);

	glutMainLoop();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	Main();

	return 0;
}