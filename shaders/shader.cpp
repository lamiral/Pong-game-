#include "shader.h"

shader::shader()
{
	vs = 0;
	fs = 0;
	this->program = 0;
}

shader::~shader()
{
	glDeleteShader(vs);
	glDeleteShader(fs);
	glUseProgram(0);
	glDeleteProgram(this->program);
}

void shader::create_program()
{
 	if(vs == 0 || fs == 0)
 	{
 		cout << "Warning create program!Shaders not found!" << endl;
 		return;
 	}

 	this->program = glCreateProgram();
 	glAttachShader(program,vs);
 	glAttachShader(program,fs);
 	glLinkProgram(this->program);
 	
 	this->error_program(this->program);
}

void shader::load_shader(const char* vsShader,const char* fsShader)
{
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs,1,&vsShader,NULL);
	glCompileShader(vs);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs,1,&fsShader,NULL);
	glCompileShader(fs);

	this->error_shader(vs);
	this->error_shader(fs);
}

void shader::error_shader(uint &shader)
{
	int compile_status = 0;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&compile_status);
	if(!compile_status)
	{
		char log_buff[512];
		glGetShaderInfoLog(shader,512,NULL,log_buff);
		cout << log_buff << endl;
	}
}

void shader::error_program(uint &program)
{
	int link_status = 0;
	glGetProgramiv(program,GL_LINK_STATUS,&link_status);
	if(link_status < 0)
	{
		char log_buff[512];
		glGetProgramInfoLog(program,512,NULL,log_buff);
		cout << log_buff << endl;
	}
}

void shader::use_program()
{	
	glUseProgram(this->program);
}