#include "Application.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"

#include <algorithm>
#include <iostream>
#include <chrono>

void Application::run()
{
	initWindow();
	initDriver();
	initSwapChain();
	initRenderScene();
	initRenderers();
	mainloop();
	shutdownRenderers();
	shutdownRenderScene();
	shutdownSwapChain();
	shutdownDriver();
	shutdownWindow();
}
void Application::update()
{
	
}


void Application::render()
{
	
}


void Application::mainloop()
{
	if (!window)
		return;

	while (!glfwWindowShouldClose(window))
	{
		/*ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();*/

		update();

		//ImGui::Render();

		render();
		glfwPollEvents();
	}

}


void Application::initWindow()
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(1024, 768, "Vulkan", nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, &Application::onFramebufferResize);
	glfwSetCursorPosCallback(window, &Application::onMousePosition);
	glfwSetMouseButtonCallback(window, &Application::onMouseButton);
	glfwSetScrollCallback(window, &Application::onScroll);
}

void Application::shutdownWindow()
{
	glfwDestroyWindow(window);
	window = nullptr;
}


void Application::onFramebufferResize(GLFWwindow* window, int width, int height)
{
	Application* application = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
	assert(application != nullptr);

	application->windowResized = true;
}

void Application::onMousePosition(GLFWwindow* window, double mouseX, double mouseY)
{
	
}

void Application::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	
}

void Application::onScroll(GLFWwindow* window, double deltaX, double deltaY)
{

}


void Application::initRenderScene()
{
	
}

void Application::shutdownRenderScene()
{
	
}


void Application::initRenderers()
{
	
}

void Application::shutdownRenderers()
{
	
}


void Application::initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForVulkan(window, true);
}

void Application::shutdownImGui()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

/*
 */
void Application::initDriver()
{
	
}

void Application::shutdownDriver()
{

}

/*
 */
void Application::initSwapChain()
{

}

void Application::shutdownSwapChain()
{
	
}

void Application::recreateSwapChain()
{
	
}