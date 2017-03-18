#include "Player_count.h"

Player_count::Player_count()
{
	count = 0;
	VAO = 0;
	texture_count = 0;
}

void Player_count::init_vao_count(float x,float y)
{
	uint VBO,IBO;

	float verticles_count[] = 
	{
		x,y,0.0,				0.0,0.0,	
		x,y+0.1,0.0,			0.0,1.0,
		x+0.1,y+0.1,0.0,		1.0,1.0,
		x+0.1,y,0.0,			1.0,0.0
	};

	uint elements[] = 
	{
		0,1,2,
		0,2,3
	};

	glGenVertexArrays(1,&VAO);

	glGenBuffers(1,&VBO);
	glGenBuffers(1,&IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(verticles_count),verticles_count,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elements),elements,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));

	glBindVertexArray(0);
}

const char* Player_count::convert_const_str(int value)
{
	const char *str;

	switch(value)
	{
		case 0:str = "numbers/0.jpg";break;
		case 1:str = "numbers/1.jpeg";break;
		case 2:str = "numbers/2.jpeg";break;
		case 3:str = "numbers/3.jpeg";break;
		case 4:str = "numbers/4.jpg";break;
		case 5:str = "numbers/5.jpeg";break;
	}
	return str;
}

void Player_count::init_table_count(float x,float y)
{
	this->init_vao_count(x,y);

	const char* filepath = "numbers/0.jpg";

	this->init_texture_count(filepath);
}

void Player_count::change_texture_table(int value)
{
	 const char* filepath = this->convert_const_str(value);

	 this->init_texture_count(filepath);
}

void Player_count::draw_count()
{	
	if(VAO <= 0)
	{
		cout << "VAO is no init!" << endl;
		return;
	}
	else if(texture_count<= 0)
	{
		cout << "Texture table is no init!" << endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D,texture_count);

	glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D,0);

}

void Player_count::init_texture_count(const char *filepath)
{
	textureUtils  TextureUtils;
	if(filepath == NULL)
	{
		cout << "Bad filepath (texture(count))" << endl;
		return;
	}
	texture_count = TextureUtils.load_texture(filepath);
}

