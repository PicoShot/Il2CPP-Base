#include "framework/framework.h"
#include "framework/sdk.h"
#include "Game/Menu.h"
#include "Game/Lists.hpp"
#include "Game/Functions.h"
#include "Utils/PatternScan.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool init = false;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void CreateConsole()
{
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    SetConsoleTitle("Il2Cpp Base by Pico");
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
}

void initvars()
{
    if (IL2CPP::Initialize(true))
    {
        printf("[ DEBUG ] Il2Cpp Base initialized\n");
    }
    else
    {
        printf("[ DEBUG ] Il2Cpp Base initialize failed, quitting...");
        Sleep(300);
        exit(0);
    }
    sdk::Base = (uintptr_t)GetModuleHandleA(NULL);
    printf("[ DEBUG ] Base Address: 0x%llX\n", sdk::Base);
    sdk::GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
    printf("[ DEBUG ] GameAssembly Base Address: 0x%llX\n", sdk::GameAssembly);
    sdk::UnityPlayer = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");
    printf("[ DEBUG ] UnityPlayer Base Address: 0x%llX\n", sdk::UnityPlayer);
}

bool find_sigs()
{
    //Unity::il2cppClass* PlayerControllerClass = IL2CPP::Class::Find("PlayerController");
    //printf("[ DEBUG ] PlayerControllerClass: 0x%llX\n", (uintptr_t)PlayerControllerClass);

    //Offsets::example = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(PlayerControllerClass, "ExampleFunction");
    //printf("[ DEBUG ] example: 0x%llX\n", Offsets::example);

    printf("----------------------------------------------------------\n");
    printf("\n");
    return true;
}

void EnableHooks()
{
    /*if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::example), &Functions::example_hk, (LPVOID*)&Functions::example) == MH_OK)
    {
        MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::example));
    }*/
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProcA(oWndProc, hWnd, uMsg, wParam, lParam);
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromMemoryTTF((void*)TTSquaresCondensedBold, sizeof(TTSquaresCondensedBold), 16.0f);
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

static DWORD lasttick = 0;

void renderloop()
{
	DWORD currentTime = GetTickCount64(); // Get current time in milliseconds

	if (!vars::initil2cpp)
		return;

	if (vars::fov_changer)
	{
		Unity::CCamera* CameraMain = Unity::Camera::GetMain();
		if (CameraMain != nullptr)
		{
			CameraMain->CallMethodSafe<void*>("set_fieldOfView", vars::CameraFOV);
		}
	}

	if (vars::crosshair)
	{
		ImColor coltouse = vars::CrossColor;
		if (vars::crosshairRainbow)
		{
			coltouse = ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z);
		}
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(vars::screen_center.x - vars::crosshairsize, vars::screen_center.y), ImVec2((vars::screen_center.x - vars::crosshairsize) + (vars::crosshairsize * 2), vars::screen_center.y), coltouse, 1.2f);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(vars::screen_center.x, vars::screen_center.y - vars::crosshairsize), ImVec2(vars::screen_center.x, (vars::screen_center.y - vars::crosshairsize) + (vars::crosshairsize * 2)), coltouse, 1.2f);
	}

	if (vars::fov_check)
	{
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(vars::screen_center.x, vars::screen_center.y), vars::aim_fov, ImColor(255, 255, 255), 360);
	}

	if (PlayerList.size() > 0)
	{
		for (const auto& player : PlayerList)
		{
			if (!player)
				continue;

			auto playerPosition = player->GetTransform()->GetPosition();

			auto headPosition = playerPosition;
			headPosition.y += 1.8f;
			auto feetPosition = playerPosition;

			Vector2 headScreenPos, feetScreenPos;

			if (Functions::worldtoscreen(headPosition, headScreenPos) &&
				Functions::worldtoscreen(feetPosition, feetScreenPos))
			{
				ImColor Colortouse = vars::PlayerSnaplineColor;

				float boxHeight = abs(headScreenPos.y - feetScreenPos.y);
				float boxWidth = boxHeight * 0.6f;

				ImVec2 topLeft(feetScreenPos.x - boxWidth / 2, headScreenPos.y);
				ImVec2 topRight(feetScreenPos.x + boxWidth / 2, headScreenPos.y);
				ImVec2 bottomLeft(feetScreenPos.x - boxWidth / 2, feetScreenPos.y);
				ImVec2 bottomRight(feetScreenPos.x + boxWidth / 2, feetScreenPos.y);

				auto drawList = ImGui::GetBackgroundDrawList();

				if (vars::PlayerBox)
				{
					drawList->AddLine(topLeft, topRight, Colortouse, 1.5f);          // Top
					drawList->AddLine(topRight, bottomRight, Colortouse, 1.5f);      // Right
					drawList->AddLine(bottomRight, bottomLeft, Colortouse, 1.5f);    // Bottom
					drawList->AddLine(bottomLeft, topLeft, Colortouse, 1.5f);        // Left
				}

				if (vars::PlayerSnaplines)
				{
					ImVec2 screenTopCenter(vars::screen_size.x / 2, 0);
					drawList->AddLine(ImVec2(headScreenPos.x, headScreenPos.y), screenTopCenter, Colortouse, 1.5f);
				}
			}
		}
	}

	if (currentTime - lasttick > 5)
	{

		lasttick = currentTime;
	}
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			ImGui::GetIO().Fonts->AddFontDefault();
			ImFontConfig font_cfg;
			font_cfg.GlyphExtraSpacing.x = 1.2;
			gameFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(TTSquaresCondensedBold, 14, 14, &font_cfg);
			ImGui::GetIO().Fonts->AddFontDefault();
			// Grab A shader Here If You want
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	pContext->RSGetViewports(&vars::vps, &vars::viewport);
	vars::screen_size = { vars::viewport.Width, vars::viewport.Height };
	vars::screen_center = { vars::viewport.Width / 2.0f, vars::viewport.Height / 2.0f };

	auto begin_scene = [&]()
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
		};

	auto end_scene = [&]()
		{
			ImGui::Render();
		};

	begin_scene();

	auto isFrames = ImGui::GetFrameCount();
	static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;
	if (isFrames % 1 == 0)
	{
		if (isGreen == 0.01f && isBlue == 0.0f)
		{
			isRed += 0.01f;
		}
		if (isRed > 0.99f && isBlue == 0.0f)
		{
			isRed = 1.0f;

			isGreen += 0.01f;
		}
		if (isGreen > 0.99f && isBlue == 0.0f)
		{
			isGreen = 1.0f;

			isRed -= 0.01f;
		}
		if (isRed < 0.01f && isGreen == 1.0f)
		{
			isRed = 0.0f;

			isBlue += 0.01f;
		}
		if (isBlue > 0.99f && isRed == 0.0f)
		{
			isBlue = 1.0f;

			isGreen -= 0.01f;
		}
		if (isGreen < 0.01f && isBlue == 1.0f)
		{
			isGreen = 0.0f;

			isRed += 0.01f;
		}
		if (isRed > 0.99f && isGreen == 0.0f)
		{
			isRed = 1.0f;

			isBlue -= 0.01f;
		}
		if (isBlue < 0.01f && isGreen == 0.0f)
		{
			isBlue = 0.0f;

			isRed -= 0.01f;

			if (isRed < 0.01f)
				isGreen = 0.01f;
		}
	}
	vars::Rainbow = ImVec4(isRed, isGreen, isBlue, 1.0f);

	if (vars::watermark)
	{
		render::DrawOutlinedText(gameFont, ImVec2(vars::screen_center.x, vars::screen_size.y - 20), 13.0f, ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z), true, "[ Il2Cpp Base By Pico ]");
		render::DrawOutlinedText(gameFont, ImVec2(vars::screen_center.x, 5), 13.0f, ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z), true, "[ %.1f FPS ]", ImGui::GetIO().Framerate);
	}

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(window, &mousePos);

	if (show_menu)
	{
		// X Mouse Cursor
		render::DrawOutlinedTextForeground(gameFont, ImVec2(mousePos.x, mousePos.y), 13.0f, ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z), false, "X");
		DrawMenu();
	}
	// Render
	try
	{
		renderloop();
	}
	catch (...)
	{
	}

	end_scene();

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show_menu = !show_menu;
		ImGui::GetIO().MouseDrawCursor = show_menu;
	}

	if (GetKeyState(VK_END) & 1)
	{
		show_menu = false;
		FreeConsole();
		kiero::shutdown();
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	IL2CPP::Thread::Detach(m_pThisThread);

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void CachePlayers()
{
	while (true)
	{
		if (!vars::initil2cpp)
			continue;

		void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

		LocalPlayer = NULL;
		PlayerList.clear();
		try
		{

			auto list = Unity::Object::FindObjectsOfType<Unity::CComponent>("PlayerController");

			for (int i = 0; i < list->m_uMaxLength;)
			{
				auto Player = list->operator[](i);
				if (!Player)
					continue;

				Unity::CComponent* PlayerSettings = Player->GetGameObject()->GetComponent("PlayerController");
				if (PlayerSettings)
				{
					Unity::CTransform* playerTransform = list->operator[](i)->GetTransform();

					int playerChilds = playerTransform->GetChildCount();

					if (playerChilds == 22)
					{
						LocalPlayer = Player->GetGameObject();
						continue;
					}
				}
				PlayerList.push_back(Player->GetGameObject());
			}
		}
		catch (...)
		{
			printf("error!");
		}

		IL2CPP::Thread::Detach(m_pThisThread);
		Sleep(1000);
	}
}

void  initchair()
{
    CreateConsole();
    system("cls");
    initvars();
    find_sigs();
    IL2CPP::Callback::Initialize();
    EnableHooks();
    kiero::bind(8, (void**)&oPresent, hkPresent);
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CachePlayers, NULL, NULL, NULL);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            initchair();
            init_hook = true;
            vars::initil2cpp = true;
        }
    } while (!init_hook);
    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		FreeLibraryAndExitThread(hModule, 0);	
		break;
	}
	return TRUE;
}

