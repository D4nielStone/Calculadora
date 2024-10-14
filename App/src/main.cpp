#include "painel_calc.hpp"
#include <windows.h>

GLFWwindow *janela;
std::shared_ptr<BubbleUI::Contexto> contextoUI;

static void defInputs(Bubble::Inputs::Inputs* inp)
{
	glfwSetWindowUserPointer(janela, inp);
	glfwSetCursorPosCallback(janela, mousePosCallBack);
	glfwSetKeyCallback(janela, callbackKey);
	glfwSetMouseButtonCallback(janela, mouseButtonCallBack);
	glfwSetCharCallback(janela, charCallback);
}
static void iniciar()
{
	auto inputs = std::make_shared<Bubble::Inputs::Inputs>();
	contextoUI = std::make_shared<BubbleUI::Contexto>();

	if (!glfwInit())
		return;
	
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	janela = glfwCreateWindow(400, 600, "Calculadora", NULL, NULL);

	glfwMakeContextCurrent(janela);

	if (!janela)return;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	
	defInputs(inputs.get());
	contextoUI->glfwWindow = janela; contextoUI->inputs = inputs;

	BubbleUI::Calculadora painelPrincipal(contextoUI);
	
	while (!glfwWindowShouldClose(janela))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		
		glfwGetFramebufferSize(janela, &contextoUI->tamanho.width, &contextoUI->tamanho.height);
		glViewport(0, 0, contextoUI->tamanho.width, contextoUI->tamanho.height);

		painelPrincipal.atualizar();
		painelPrincipal.renderizar();

		glfwSetCursor(janela, contextoUI->cursor);

		glfwSwapBuffers(janela);
	}
}

#ifdef NDEBUG
#define INIT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, int nCmdShow)
#else
#define INIT main()
#endif

int INIT
{
	iniciar();
return 0;
}
