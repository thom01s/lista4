/* Hello Triangle - c�digo adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr�fico - Jogos Digitais - Unisinos
 * Vers�o inicial: 7/4/2017
 * �ltima atualiza��o em 09/08/2021
 *
 */

#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>


using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "Shader.h"

#include "Object.h"




// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
int loadTexture(string path);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 800;


// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	//Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	//Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	//Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "lista 4", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Compilando e buildando o programa de shader
	Shader* shader = new Shader("./shaders/sprite.vs", "./shaders/colorizblue.fs");
	Shader* shader1 = new Shader("./shaders/sprite.vs", "./shaders/colorizverm.fs");
	Shader* shader2 = new Shader("./shaders/sprite.vs", "./shaders/grey.fs");
	Shader* shader3 = new Shader("./shaders/sprite.vs", "./shaders/invers.fs");

	GLuint texID = loadTexture("./textures/lena.jpg");
	GLuint texID2 = loadTexture("./textures/RGB.png");


	Object obj;
	obj.initialize();
	obj.setTexture(texID);
	obj.setShader(shader);
	obj.setDimensions(glm::vec3(5.0, 5.0, 0.0));
	obj.setPosition(glm::vec3(7.0, -5.0, 0.0));

	Object obj2;
	obj2.initialize();
	obj2.setTexture(texID2);
	obj2.setShader(shader);
	obj2.setDimensions(glm::vec3(5.0, 5.0, 1.0));
	obj2.setPosition(glm::vec3(7.0, 5.0, 0.0));

	Object obj3;
	obj3.initialize();
	obj3.setTexture(texID);
	obj3.setShader(shader1);
	obj3.setDimensions(glm::vec3(5.0, 5.0, 0.0));
	obj3.setPosition(glm::vec3(2.5, -5.0, 0.0));

	Object obj4;
	obj4.initialize();
	obj4.setTexture(texID2);
	obj4.setShader(shader1);
	obj4.setDimensions(glm::vec3(5.0, 5.0, 1.0));
	obj4.setPosition(glm::vec3(2.5, 5.0, 0.0));

	Object obj5;
	obj5.initialize();
	obj5.setTexture(texID);
	obj5.setShader(shader2);
	obj5.setDimensions(glm::vec3(5.0, 5.0, 0.0));
	obj5.setPosition(glm::vec3(-2.5, -5.0, 0.0));

	Object obj6;
	obj6.initialize();
	obj6.setTexture(texID2);
	obj6.setShader(shader2);
	obj6.setDimensions(glm::vec3(5.0, 5.0, 1.0));
	obj6.setPosition(glm::vec3(-2.5, 5.0, 0.0));

	Object obj7;
	obj7.initialize();
	obj7.setTexture(texID);
	obj7.setShader(shader3);
	obj7.setDimensions(glm::vec3(5.0, 5.0, 0.0));
	obj7.setPosition(glm::vec3(-7.0, -5.0, 0.0));

	Object obj8;
	obj8.initialize();
	obj8.setTexture(texID2);
	obj8.setShader(shader3);
	obj8.setDimensions(glm::vec3(5.0, 5.0, 1.0));
	obj8.setPosition(glm::vec3(-7.0, 5.0, 0.0));

	//Ativando o shader que ser� usado
	shader->Use();

	

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a vari�veis do tipo uniform em GLSL para armazenar esse tipo de info
	// que n�o est� nos buffers

	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	assert(projLoc > -1);

	glUniform1i(glGetUniformLocation(shader->Program, "tex1"), 0);

	shader1->Use();

	GLint projLoc1 = glGetUniformLocation(shader1->Program, "projection");
	assert(projLoc1 > -1);

	glUniform1i(glGetUniformLocation(shader1->Program, "tex1"), 0);

	shader2->Use();

	GLint projLoc2 = glGetUniformLocation(shader2->Program, "projection");
	assert(projLoc2 > -1);

	glUniform1i(glGetUniformLocation(shader2->Program, "tex1"), 0);

	shader3->Use();

	GLint projLoc3 = glGetUniformLocation(shader3->Program, "projection");
	assert(projLoc3 > -1);

	glUniform1i(glGetUniformLocation(shader3->Program, "tex1"), 0);

	glm::mat4 ortho = glm::mat4(1); //inicializa com a matriz identidade

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		ortho = glm::ortho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		//Enviar a matriz de proje��o ortogr�fica para o shader
		shader->Use();
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));
		shader1->Use();
		glUniformMatrix4fv(projLoc1, 1, GL_FALSE, glm::value_ptr(ortho));
		shader2->Use();
		glUniformMatrix4fv(projLoc2, 1, GL_FALSE, glm::value_ptr(ortho));
		shader3->Use();
		glUniformMatrix4fv(projLoc3, 1, GL_FALSE, glm::value_ptr(ortho));

		glLineWidth(10);
		glPointSize(10);

		obj.update();
		obj.draw();

		obj2.update();
		obj2.draw();

		obj3.update();
		obj3.draw();

		obj4.update();
		obj4.draw();

		obj5.update();
		obj5.draw();

		obj6.update();
		obj6.draw();

		obj7.update();
		obj7.draw();

		obj8.update();
		obj8.draw();
		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}

	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// Esta fun��o est� bastante harcoded - objetivo � criar os buffers que armazenam a 
// geometria de um tri�ngulo
// Apenas atributo coordenada nos v�rtices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A fun��o retorna o identificador do VAO


int loadTexture(string path)
{
	GLuint texID;

	// Gera o identificador da textura na mem�ria 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Ajusta os par�metros de wrapping e filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Carregamento da imagem
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

