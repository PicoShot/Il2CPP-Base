#pragma once
#include "../framework/framework.h"
#include "../framework/sdk.h"
#include "../Utils/Dumper.hpp"

using namespace ImGui;

void HelpMarker(const char* desc)
{
	TextDisabled("[?]");
	if (IsItemHovered())
	{
		BeginTooltip();
		PushTextWrapPos(GetFontSize() * 35.0f);
		TextUnformatted(desc);
		PopTextWrapPos();
		EndTooltip();
	}
}

void ImGuiTheme()
{
	ImVec4* colors = GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	ImGuiStyle& style = GetStyle();
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.WindowRounding = 4;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
}

void DrawInspector() {
	SetNextWindowSize(ImVec2(600.000f, 1300.000f), ImGuiCond_Once);
	if (!Begin("Inspector", nullptr, 2)) {
		End();
		return;
	}

	static std::vector<std::string> components;
	static std::vector<std::string> classes;
	static std::vector<std::string> methods;
	static std::string current_comp = "";

	Text("Components");
	if (Button("Update##comp")) {
		components = Dumper::DumpComponentsString();
	}
	SetNextItemWidth(150.000f);
	static int component_current_idx = 0;
	static ImGuiTextFilter c_filter;
	c_filter.Draw("Search##compfilter");
	if (BeginListBox("##Components", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < components.size(); n++)
		{
			if (!c_filter.PassFilter(components[n].c_str())) {
				continue;
			}
			const bool comp_is_selected = (component_current_idx == (int)n);
			if (Selectable(components[n].c_str(), comp_is_selected))
				component_current_idx = (int)n;

			if (comp_is_selected)
				SetItemDefaultFocus();
		}
		EndListBox();
	}
	Spacing();
	Text("Classes");
	if (Button("Update##class")) {
		classes = Dumper::DumpClassesString(components[component_current_idx]);
		current_comp = components[component_current_idx];
	}

	SetNextItemWidth(150.000f);
	static int class_current_idx = 0;
	static ImGuiTextFilter cl_filter;
	cl_filter.Draw("Search##classfilter");
	if (BeginListBox("##Class", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < classes.size(); n++)
		{
			if (!cl_filter.PassFilter(classes[n].c_str())) {
				continue;
			}
			const bool class_is_selected = (class_current_idx == (int)n);
			if (Selectable(classes[n].c_str(), class_is_selected)) {
				class_current_idx = (int)n;
			}

			if (class_is_selected)
				SetItemDefaultFocus();
		}
		EndListBox();
	}

	Spacing();
	Text("Methods");
	if (Button("Update##Methods")) {
		methods = Dumper::DumpMethodsString(current_comp, classes[class_current_idx]);
	}

	SetNextItemWidth(150.000f);
	static int method_current_idx = 0;
	static ImGuiTextFilter me_filter;
	me_filter.Draw("Search##methodfilter");
	if (BeginListBox("##Methods", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < methods.size(); n++)
		{
			if (!me_filter.PassFilter(methods[n].c_str())) {
				continue;
			}
			const bool meth_is_selected = (method_current_idx == (int)n);
			if (Selectable(methods[n].c_str(), meth_is_selected))
				method_current_idx = (int)n;

			if (meth_is_selected)
				SetItemDefaultFocus();
		}
		EndListBox();
	}
	End();
}

void DrawMenu()
{
	ImGuiTheme();
	if (vars::Inspector)
	{
		DrawInspector();
	}
	static int page = 0;
	if (Begin("[  Il2Cpp Base By Pico  ]", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
	{
		SetWindowPos(ImVec2(500, 500), ImGuiCond_Once);
		SetWindowSize(ImVec2(375, 400), ImGuiCond_Once);
		static int tabb = 0;
		SameLine();
		if (Button("Visual"))
		{
			tabb = 0;
		}
		SameLine();
		if (Button("Aimbot"))
		{
			tabb = 1;
		}
		SameLine();
		if (Button("Misc"))
		{
			tabb = 2;
		}
		SameLine();
		if (Button("Scale"))
		{
			tabb = 3;
		}
		SameLine();
		if (Button("Teleport"))
		{
			tabb = 4;
		}
		Separator();
		switch (tabb) {
		case 0:
			Checkbox("Player Snapline", &vars::PlayerSnaplines);

			Checkbox("Player Box", &vars::PlayerBox);

			Checkbox("Player Name", &vars::PlayerName);

			Checkbox("Item Snapline", &vars::ItemSnaplines);

			Checkbox("Item Box", &vars::ItemBox);

			Checkbox("Crosshair", &vars::crosshair);
			SameLine();
			ColorEdit3("##CrosshairColor", (float*)&vars::CrossColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
			SameLine();
			Checkbox("##RGB6", &vars::crosshairRainbow);

			Checkbox("Fov Changer", &vars::fov_changer);
			if (vars::fov_changer)
			{
				SliderFloat("##CamFOV", &vars::CameraFOV, 20, 180, "Camera FOV: %.0f");
			}
			Checkbox("Watermark", &vars::watermark);
			break;
		case 1:
			Checkbox("Aim", &vars::aimbot);
			if (IsItemHovered())
				SetTooltip("Aimbot");


			Checkbox("Silentp", &vars::silentp);
			if (IsItemHovered())
				SetTooltip("Aimbot without moving camera");


			Checkbox("Aim FOV", &vars::fov_check);
			if (IsItemHovered())
				SetTooltip("Aim FOV Check");
			if (vars::fov_check)
			{
				SliderFloat("Aimbot FOV", &vars::aim_fov, 0, 1000.0f);
				if (IsItemHovered())
					SetTooltip("Circle FOV");
			}
			SliderFloat("Aimbot Smoothing", &vars::smooth, 1, 10.0f);
			if (IsItemHovered())
				SetTooltip("Humanized Aim");


			Combo("Aim Bone", &vars::boneselected, vars::bones, IM_ARRAYSIZE(vars::bones));
			break;
		case 2:
			Checkbox("Draw Inspector", &vars::Inspector);
			break;
		case 3:
			break;
		case 4:
			break;
		}

		End();
	}
}

