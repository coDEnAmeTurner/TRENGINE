#include "trpch.h"
#include <Trengine.h>
#include "../../vendor/imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Trengine::Layer {
private:
	std::shared_ptr<Trengine::VertexArray> vertexArray;
	std::shared_ptr<Trengine::Shader> shader;
	std::shared_ptr<Trengine::Shader> solidColorShader;
	Trengine::OrthographicCamera camera;
	glm::vec3 tranform;
	glm::vec4 uColor;
public: 
	ExampleLayer()
		: Layer("Layer 1"), camera(-4, 4, -4.5 / 2, 4.5 / 2), tranform(0, 0, 0), uColor({ 1, 1, 1, 1 })

	{
		float vertices[7 * 4] = {
			-0.5f, -0.5f, 0.0f, 1.f, 1.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.f, 0.0f, 0.5f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.f, 0.6f, 0.1f, 1.0f,
			-0.5f, 0.5f, 0.0f, 1.f, 0.6f, 0.1f, 1.0f,
		};

		vertexArray.reset(Trengine::VertexArray::Create());

		std::shared_ptr<Trengine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Trengine::VertexBuffer::Create(vertices, sizeof(vertices)));

		Trengine::BufferLayout layout = {
			{Trengine::ShaderDataType::Float3, "a_Position"},
			{Trengine::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->setLayout(layout);

		vertexArray->addVertexBuffer(vertexBuffer);

		unsigned int indices[6] = {
			0, 1, 2,
			0, 2, 3
		};

		vertexArray->addIndexBuffer(std::shared_ptr<Trengine::IndexBuffer>(Trengine::IndexBuffer::Create(indices, sizeof(indices))));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main() {
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			in vec4 v_Color;

			uniform vec4 u_Color;

			layout(location = 0) out vec4 color;

			void main() {
				color = u_Color;
			}
		)";

		std::string solidFragmentSrc = R"(
			#version 330 core
			
			in vec4 v_Color;

			uniform vec4 u_Color;

			layout(location = 0) out vec4 color;

			void main() {
				color = u_Color;
			}
		)";

		shader.reset(new Trengine::OpenGLShader(vertexSrc, fragmentSrc));
		solidColorShader.reset(new Trengine::OpenGLShader(vertexSrc, solidFragmentSrc));
	}


	void onUpdate(Trengine::Timestep timeStep) {
		Trengine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Trengine::RenderCommand::clear();

		glm::vec3 cameraPosition = camera.getPosition();
		float cameraRotation = camera.getRotation();

		float cameraMoveSpeed = 0.9f;
		float cameraRotationSpeed = 8.7f;

		if (Trengine::Input::isKeyPressed(TR_KEY_LEFT))
			cameraPosition.x -= cameraMoveSpeed * timeStep;	

		if (Trengine::Input::isKeyPressed(TR_KEY_RIGHT))
			cameraPosition.x += cameraMoveSpeed * timeStep;

		if (Trengine::Input::isKeyPressed(TR_KEY_UP))
			cameraPosition.y += cameraMoveSpeed * timeStep;

		if (Trengine::Input::isKeyPressed(TR_KEY_DOWN))
			cameraPosition.y -= cameraMoveSpeed * timeStep;

		if (Trengine::Input::isKeyPressed(TR_KEY_A))
			cameraRotation -= cameraRotationSpeed * timeStep;

		if (Trengine::Input::isKeyPressed(TR_KEY_D))
			cameraRotation += cameraRotationSpeed * timeStep;

		glm::vec3 squarePosition = tranform;
		float squareMoveSpeed = 0.9f;

		if (Trengine::Input::isKeyPressed(TR_KEY_J))
			squarePosition.x -= squareMoveSpeed * timeStep;

		if (Trengine::Input::isKeyPressed(TR_KEY_L))
			squarePosition.x += squareMoveSpeed * timeStep;

		if (Trengine::Input::isKeyPressed(TR_KEY_I))
			squarePosition.y += squareMoveSpeed * timeStep;

		if (Trengine::Input::isKeyPressed(TR_KEY_K))
			squarePosition.y -= squareMoveSpeed * timeStep;


		camera.setPosition(cameraPosition);
		camera.setRotation(cameraRotation);

		tranform = squarePosition;

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		Trengine::Renderer::beginScene(camera);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.3f, y * 0.3f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Trengine::OpenGLShader* sCSObj = (Trengine::OpenGLShader*)solidColorShader.get();

				if (x % 2 == 0)
					sCSObj->uploadUniformFloat4("u_Color", redColor);
				else
					sCSObj->uploadUniformFloat4("u_Color", blueColor);

				Trengine::Renderer::submit(vertexArray, solidColorShader, transform);
			}
		}

		Trengine::OpenGLShader* sObj = (Trengine::OpenGLShader*)shader.get();
		sObj->uploadUniformFloat4("u_Color", uColor);

		Trengine::Renderer::submit(vertexArray, shader, glm::translate(glm::mat4(1.0f), tranform));

		Trengine::Renderer::endScene();
	}

	void onImGuiRender() {
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Main Square Color", glm::value_ptr(uColor));
		ImGui::End();
	}
};

class Sandbox : public Trengine::Application {
public:
	Sandbox() {
		layerStack.PushLayer(new ExampleLayer());
	}

	~Sandbox() {
	}
};

//the client defines CreateApplication
Trengine::Application* Trengine::CreateApplication() {
	return new Sandbox();
}