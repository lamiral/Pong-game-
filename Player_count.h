#include <GL/glew.h>
#include "uTex.cpp"

typedef unsigned int uint;

class Player_count{
private:
	int count;
	uint VAO;
	uint texture_count;
public:
	Player_count();
	void init_vao_count(float , float );
	void draw_count();
	void init_table_count(float, float);
	void change_texture_table(int );
	void init_texture_count(const char* );
	const char* convert_const_str(int );
};