#include <iostream>
#include <GL/glew.h>

using namespace std;

typedef unsigned int uint;

class shader
{
private:
	uint vs,fs;
public:
	uint program;
	void load_shader(const char *vsShader,const char *fsShader);
	void create_program();
	void use_program();
	void error_shader(uint &shader);
	void error_program(uint &program);
	shader();
	~shader();
};