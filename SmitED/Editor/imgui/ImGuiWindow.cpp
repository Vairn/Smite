#include "ImGuiWindow.h"

SmitED::ImGuiWindow::ImGuiWindow()
	: show(true)
{
	WindowName("Base Window");
}

SmitED::ImGuiWindow::~ImGuiWindow()
{

}

void SmitED::ImGuiWindow::update()
{
	begin();
	end();
}

bool SmitED::ImGuiWindow::begin()
{
	return ImGui::Begin(sWindowName.c_str(), &show, ImGuiWindowFlags_MenuBar);
}

void SmitED::ImGuiWindow::end()
{
	ImGui::End();
}

