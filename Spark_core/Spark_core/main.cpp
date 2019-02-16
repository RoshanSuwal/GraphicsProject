#include"graphics/Windows.h"
#include"maths/maths.h"
#include"Utils/fileutils.h"
#include"graphics/shader.h"
#include"graphics/buffer.h"
#include"graphics/indexBuffer.h"
#include"graphics/vertexArray.h"
#include"Renderer/renderable2d.h"
#include"Renderer/simple2Drenderer.h"
#include"Renderer/batchrenderer2D.h"

#include"graphics/static_sprite.h"
#include"graphics/sprite.h"
#include"Utils/timer.h"

#include"algorithm/Circle.h"
#include"algorithm//lineh.h"
#include<time.h>


#define BATCH_RENDERER 1

int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace maths;
	//using namespace algorithm;

	Window window("Sparky", 800, 600);
	//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	/*GLuint vco;

	GLfloat vertices[] = {
		0,8, 0.0f,
		0, 3, 0.0f,
		 8, 3, 0.0f,
		 8,8, 0.0f

	};

	GLushort indices[] = {
		0,1,2,
		2,3,0
	};

	GLfloat colorA[] = {
	1, 0, 1, 1,
	1, 0, 1, 1,
	1, 0, 1, 1,
	1, 0, 1, 1	};

	GLfloat colorB[] = {
	0.2f, 0.3f, 0.f, 1,
	0.2f, 0.3f, 0.f, 1,
	0.2f, 0.3f, 0.f, 1,
	0.2f, 0.3f, 0.f, 1
	};

	glGenBuffers(1, &vco);
	glBindBuffer(GL_ARRAY_BUFFER, vco);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	VertexArray vao,sprite1,sprite2;
	//Buffer* vbo = new Buffer(vertices,4*3,3);
	IndexBuffer ibo(indices, 6);

	//vao.addBuffers(vbo, 0);

	sprite1.addBuffers(new Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffers(new Buffer(colorA, 4 * 4, 4),1);

	sprite2.addBuffers(new Buffer(vertices, 4 * 3, 3), 0);
	sprite2.addBuffers(new Buffer(colorB, 4 * 4, 4), 1);

	*/

	mat4 ortho = mat4::othographic(0.0f, 16.0f, 0.0f, 12.0f, -1.0f, 1.0f);


	Shader shader("Shader/basic.vert", "Shader/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	//shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 0, 0)));
	
	std::vector<Renderable2D*> sprites;
	srand(time(NULL));



	for (float y = 0; y < 9.0f;y+= 0.1) {
		for (float x = 0; x < 16.0f; x+=0.3) {

			//sprites.push_back(
#if BATCH_RENDERER
				//new Sprite(x, y, 0.05f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1))
#else
				//new StaticSprite(x, y, 0.3f, 0.05f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1),shader)
#endif

			//);
}
	}

	sprites.push_back(new Sprite(1, 2, 0.4, 0.4, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	sprites.push_back(new Sprite(2,1 , 0.4, 0.4, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	
	
	float x = 0.0f;
	float y = 0.5f;

	sprites.push_back(new Sprite(x, y, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	sprites.push_back(new Sprite(x, -y, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	sprites.push_back(new Sprite(-x, -y, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	sprites.push_back(new Sprite(-x, y, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	sprites.push_back(new Sprite(y, x, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	sprites.push_back(new Sprite(-y, x, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	sprites.push_back(new Sprite(-y, -x, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	sprites.push_back(new Sprite(y, -x, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));

#if BATCH_RENDERER
	Sprite sprite1(5, 5, 4, 4, maths::vec4(1, 0, 1, 1));
	BatchRenderer2D renderer;

	
	std::cout << "Batch Rendereer" << std::endl;
#else
	StaticSprite sprite1(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	Simple2DRenderer renderer;
	std::cout << "Simple Rendereer" << std::endl;
#endif // BATCH_RENDERER

//	Sprite sprite1(5, 5,4, 4, maths::vec4(1, 0, 1, 1));

	shader.setUniform2f("light_pos", vec2(5.5f, 5.5f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	//Renderable2D sprite2(maths::vec3(7, 1, 0), maths::vec2(2, 3), maths::vec4(0.2f, 0, 1, 1), shader);
	//Renderable2D sprite3(maths::vec3(0, 0, 0), maths::vec2(3, 3), maths::vec4(0.2f, 1, 1, 1), shader);
	//Renderable2D sprite4(maths::vec3(1, 1, 0), maths::vec2(4, 5), maths::vec4(1, 0, 0, 1), shader);
//	BatchRenderer2D renderer;
	//BatchRenderer2D batch;

	float start = 0;
	int fps = 0;

	Timer time;
	float timer = 0.0f;
	unsigned int frames = 0;

	//int x = 5;
	
	algorithm::Circle circle(1,2, 2);
	algorithm::Circle circle1(10, 6, 3);

	algorithm::Line line(1, 2, 0, 2);
	algorithm::Line line1(8, 6, 0, 3);
	line.setRotatingMotion(-.1f);
	line.setLinearMotion(0.001);

	circle.setLinearSpeed(0.001f);

	float tx = 0.0f;

	while (!window.closed()) {
		tx -= 0.0005f;
		mat4 mat = mat4::mat4(1);
		//mat = mat * mat4::rotation(time.elapsed()*100, vec3(0, 0, 5));
		mat = mat * mat4::translation(vec3(tx, 0, 0));
		shader.setUniformMat4("ml_matrix", mat);

		window.clear();
		
		double x, y;
		window.getMousePosition(x, y);
		//std::cout << x <<" , "<< y <<  std::endl;
		shader.setUniform2f("light_pos", vec2((float)x*16.0f/window.getWidth(), 9.0f-(float)y*9.0f/window.getHeight()));
		
		//glDrawArrays(GL_QUADS ,0,4);

		/*vao.bind();
		ibo.bind();

		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

		ibo.bind();
		vao.unbind();

		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(8, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();
		*/

#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++) {
			//renderer.submit(sprites[i]);
		}
		circle.submit(renderer, shader);
		//circle1.submit(renderer, shader);
		line.submit(renderer, shader);
		line1.submit(renderer, shader);
		

#if BATCH_RENDERER
		renderer.end();	
#endif
		//renderer.submit(&sprite2);
		//renderer.submit(&sprite3);
		//renderer.submit(&sprite4);
		renderer.flush();
		
		window.update();
		frames++;

		circle.update();
		line.update();
		
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			std::cout << "FPS = " << frames<< std::endl;
			circle.update();
			line.update();
			
			frames = 0;
		}
		
	}


	return 0;
}