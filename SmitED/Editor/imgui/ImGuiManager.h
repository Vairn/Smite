#pragma once
#include <vector>
#include <memory>

#include <imgui.h>

#include "portable-file-dialogs.h"
struct GLFWwindow;

namespace SmitED
{
	class ImGuiWindow;
	class ImGuiUIManager
	{
	public:
		ImGuiUIManager() {}
		ImGuiUIManager(GLFWwindow* window);
		~ImGuiUIManager();
		void update();
		void render();

		bool AddWindow(SmitED::ImGuiWindow* pWindow);
		bool AddWindowNextFrame(SmitED::ImGuiWindow* pWindow);
	private:
		void initWindows(GLFWwindow* window);
		std::vector<ImGuiWindow*> windows;
		std::vector<ImGuiWindow*> next_windows;


		ImGuiWindowFlags window_flags;
		void ShowDockSpace(bool* p_open);
		void setstyle();
		void updateWindows();
		void deleteWindows();

		std::shared_ptr<pfd::select_folder> pack_folder;

		std::string project_location;
		void HandleProjectLocationSet();

	};

}