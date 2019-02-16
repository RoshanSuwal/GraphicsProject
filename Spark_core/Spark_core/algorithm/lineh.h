#pragma once

#include<iostream>
#include<vector>

#include"../Renderer/batchrenderer2D.h"

#include"../graphics/static_sprite.h"
#include"../graphics/sprite.h"
#include"../maths/maths.h"

namespace sparky {namespace graphics {namespace algorithm {

	class Line {
		int x, y;
		float tx, ty;
		float rotangle;
		int vecX, vecY;
		int rotX, rotY;
		float angle,linearspeed;
		std::vector<Renderable2D*> line_sprites;
		std::vector<maths::vec3*> line_points;

		public:
			Line(int x, int y, int vecX, int vecY) {
				this->x = x;
				this->y = y;
				tx = x;
				ty = y;
				this->vecX = vecX;
				this->vecY = vecY;
				this->rotangle = 0;
				rotX = x;
				rotY = y;
				this->angle = 0;
				this->linearspeed = 0;
				draw();
				createSprites();
			}

			void setX(int newX) { this->x = newX; }
			void setY(int newY) { this->y = newY; }
			void setVecX(int newVecX) { this->vecX = newVecX; }
			void setVecY(int newVecY) { this->vecY = newVecY; }
			void setPosition(int x, int y) { this->x = x; this->y = y; }
			void setVec(int vx, int vy) { this->vecX = vx; this->vecY = vy; }

			int getX() { return x; }
			int getY() { return y; }
			int getvecX() { return vecX; }
			int getVecY() { return vecY; }

			maths::vec3 getPosition() { return maths::vec3(x, y, 0); }
			maths::vec2 getVecXY() { return maths::vec2(vecX, vecY); }

			float getRotationalSpeed() { return angle; }
			float getLinearSpeed() { return linearspeed; }

			void setLinearMotion(float ls){
				linearspeed = ls;
			}

			void setRotatingMotion(float ls) {
				this->angle = ls;
			}

			void setRotation(float angle) {
				this->angle = angle;
				//createSprites();
			}
			void update() {
				tx =tx+ linearspeed;
				rotangle =rotangle+ angle;
				createSprites();
			}

			void draw() {

				int vx = vecX * 50;
				int vy = vecY * 50;

				int p,px,py;

				px = 0;
				py = 0;
				p = 2 * vy - vx;

				std::cout << vx << "," << vy << std::endl;

				if (vecX == 0) {
					for (int i = 0; i < (vy<0?-vy:vy); i++) {
						py = (vy < 0 ? (py - 1) : (py + 1));
						std::cout << px << "," << py << "," << p << std::endl;
						line_points.push_back(new maths::vec3(px, py, 0));
						//line_sprites.push_back(new Sprite(px * 16.0f / 800.0f, py* 12.0f / 600.0f, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
					}
				}
				else if (vecY==0)
				{
					for (int i = 0; i < (vx < 0 ? -vx : vx); i++) {
						px = (vx < 0 ? (px - 1) : (px + 1));
						std::cout << px << "," << py << "," << p << std::endl;
						line_points.push_back(new maths::vec3(px, py, 0));
						//line_sprites.push_back(new Sprite(px * 16.0f / 800.0f, py* 12.0f / 600.0f, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
					}

				}
				else {
					while ((px < 0 ? -px : px) < (vx <= 0 ? -vx : vx)) {
						std::cout << px << "," << py << "," << p << std::endl;
						line_points.push_back(new maths::vec3(px, py, 0));
						//line_sprites.push_back(new Sprite(px * 16.0f / 800.0f, py* 12.0f / 600.0f, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));

						if (p >= 0) {
							py = vy <= 0 ? (py) : (py + 1);
							p = p + 2 * vy - 2 * vx;
						}
						else {
							p = p + 2 * vy;
							py = vy <= 0 ? (py - 1) : (py);
						}

						px = vx < 0 ? (px - 1) : (px + 1);

					}
				}
			}

	

			void createSprites() {
				line_sprites.clear();
				maths::vec3 vec;
				float angle = maths::toRadians(this->rotangle);
				for (int i = 0; i < line_points.size(); i++) {
					vec = line_points[i]->rotate(maths::vec3(rotX, rotY, 0), angle).translate(maths::vec3(this->tx * 50, this->ty * 50, 0));
					//vec = (line_points[i]->translate(maths::vec3(this->x*50, this->y*50, 0)))
					
					line_sprites.push_back(new Sprite(vec.x* 16.0f / 800.0f, vec.y* 12.0f / 600.0f, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
				}
			}

			void submit(BatchRenderer2D& renderer, Shader& shader) {
				maths::mat4 mat = maths::mat4::translation(maths::vec3(x, y, 0));
				//shader.setUniformMat4("ml_matrix", mat);

				for (int i = 0; i < line_sprites.size(); i++) {

					renderer.submit(line_sprites[i]);
				}

				//shader.setUniformMat4("ml_matrix", maths::mat4::translation(maths::vec3(-x,-y,0)));


			}


	};
}}}