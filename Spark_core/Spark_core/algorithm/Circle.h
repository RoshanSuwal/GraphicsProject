#pragma once

#include<iostream>
#include<vector>

#include"../Renderer/batchrenderer2D.h"

#include"../graphics/static_sprite.h"
#include"../graphics/sprite.h"
#include"../maths/maths.h"

namespace sparky {namespace graphics {namespace algorithm {

		class Circle {

			int radius;
			int  centerX, centerY;
			float linearspeed, tx, ty;
			std::vector<Renderable2D*> circle_sprites;
			std::vector <maths::vec3*> circle_points;
			
		public:

			Circle(){}
			Circle(int cx, int cy,int r) {
				centerX = cx;
				centerY = cy;
				this->tx = centerX;
				this->ty = centerY;
				this->linearspeed = 0.0f;
				this->radius = r;
				draw();
				createSprites();

			}

			void setCenter(int cx, int cy) {
				centerX = cx;
				centerY = cy;
			}
			
			void setCenterX(int cx) {centerX = cx;}
			void setCenter(int cy) {centerY = cy;}
			void setRadius(int r) {radius = r;}
			maths::vec3 getCenter() {return maths::vec3(centerX, centerY,0);}
			int getCenterX() { return centerX; }
			int getCenterY() { return centerY; }
			int getRadius() { return radius; }

			void setLinearSpeed(float ls) {
				this->linearspeed = ls;
			}

			void update() {
				this->tx =this->tx+ linearspeed;
				createSprites();
			}
				
			void draw() {
				float x = 0.0f;
				float y=0.0f;
				int  a = 0;
				int b = radius*50;
				int p = 1 - radius*50;

				while (a < b) {
					x= a;
					y = b ;
					
					//std::cout << x << "," << y<<std::endl;

					circle_points.push_back(new maths::vec3(x, y, 0));
					circle_points.push_back(new maths::vec3(-x, y, 0));
					circle_points.push_back(new maths::vec3(-x, -y, 0));
					circle_points.push_back(new maths::vec3(x, -y, 0));
					circle_points.push_back(new maths::vec3(y, x, 0));
					circle_points.push_back(new maths::vec3(-y, x, 0));
					circle_points.push_back(new maths::vec3(-y,-x, 0));
					circle_points.push_back(new maths::vec3(y, -x, 0));
				
					if (p < 0) {
						a +=1;
						p = p + 2 * a + 1;
					}
					else {
						a = a + 1;
						b = b - 1;
						p = p + 2 * a - 2 * b + 1;
					}
				}
			}

		

			void createSprites() {
				circle_sprites.clear();

				maths::vec3 vec;
				//std::cout << centerX << "," << centerY << std::endl;
				for (int i = 0; i < circle_points.size(); i++) {
					vec = circle_points[i]->rotate(*circle_points[i],0).
						translate(maths::vec3(this->tx*50, this->centerY*50, 0));
					circle_sprites.push_back(new Sprite(vec.x*16.0f / 800.0f,vec.y*12.0f / 600.0f, 0.04, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
				}

			}

			
			void submit(BatchRenderer2D& renderer,Shader& shader) {
				//maths::mat4 mat = maths::mat4::translation(maths::vec3(centerX, centerY, 0));
				//shader.setUniformMat4("ml_matrix", mat);

				for (int i = 0; i < circle_sprites.size(); i++) {

					renderer.submit(circle_sprites[i]);
				}
				//shader.setUniformMat4("ml_matrix", maths::mat4::translation(maths::vec3(-centerX, -centerY, 0)));

			}




		};


}}}