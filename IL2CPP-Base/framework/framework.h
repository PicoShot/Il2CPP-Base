#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>
#include <intrin.h>
#include <vector>
#include <utility>
#include <string>
#include <stdint.h>
// Il2Cpp Resolver
#include "../Libs/Il2CppResolver/IL2CPP_Resolver.hpp"
// Kiero
#include "../Libs/Kiero/kiero.h"
#include "../Libs/Kiero/minhook/include/MinHook.h"
// ImGui
#include "../Libs/ImGui/imgui.h"
#include "../Libs/ImGui/imgui_impl_dx11.h"
#include "../Libs/ImGui/imgui_impl_win32.h"
#include "../Libs/ImGui/Custom/Font.h"
#include "../Libs/ImGui/Custom/vec.h"
#include "../Libs/ImGui/Custom/vec2.h"
#include "../Libs/ImGui/Custom/Rendering.hpp"
// types
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;