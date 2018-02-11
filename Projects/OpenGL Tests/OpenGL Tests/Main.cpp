#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

// setup code

Uint32 startclock = 0;
Uint32 deltaclock = 0;
Uint32 currentFPS = 0;

int main() {

	// at beginning of loop

	startclock = SDL_GetTicks();

	Display display(800, 600, "Hello World!");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
						  Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

	unsigned int indices[] = { 0, 1, 2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Camera camera(glm::vec3(0, 0, -2), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while (!display.IsClosed()) {

		// actual fps calculation inside loop

		deltaclock = SDL_GetTicks() - startclock;
		startclock = SDL_GetTicks();

		if (deltaclock != 0)
			currentFPS = 1000 / deltaclock;

		std::cout << currentFPS << std::endl;

		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinCounter;
		transform.GetPos().z = cosCounter;
		transform.GetRot().x = counter;
		transform.GetRot().y = counter;
		transform.GetRot().z = counter;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh.Draw();

		display.Update();
		counter += 0.01f;
	}

	return 0;
}