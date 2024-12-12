#pragma once

namespace Functions
{
#pragma region Hooks
	/*
	void(__fastcall* example_o)(DWORD*, uint64_t, int32_t, DWORD*);
	void __fastcall example_hk(DWORD* __this, uint64_t targetId, int32_t Damage, DWORD* methodinfo) {
		if (vars::giveDamage)
		{
			Damage = 500;
		}
		printf("[DEBUG] example Called! Damage set to 500.\n");
		return ServerDealDamage_o(__this, targetId, Damage, methodinfo);
	}*/
#pragma endregion

#pragma region Game Functions
	// UnityEngine_Camera$$Get_Main
	Unity::CCamera* GetMainCamera()
	{
		Unity::CCamera* (UNITY_CALLING_CONVENTION get_main)();
		return reinterpret_cast<decltype(get_main)>(sdk::GameAssembly + 0x0)();
	}


#pragma endregion

#pragma region Custom Functions
	bool worldtoscreen(Unity::Vector3 world, Vector2& screen)
	{
		Unity::CCamera* CameraMain = Unity::Camera::GetMain(); // Get The Main Camera
		if (!CameraMain) {
			return false;
		}

		//Unity::Vector3 buffer = WorldToScreenPoint(CameraMain, world, 2);

		Unity::Vector3 buffer = CameraMain->CallMethodSafe<Unity::Vector3>("WorldToScreenPoint", world, Unity::m_eCameraEye::m_eCameraEye_Center); // Call the worldtoscren function using monoeye (2)

		if (buffer.x > vars::screen_size.x || buffer.y > vars::screen_size.y || buffer.x < 0 || buffer.y < 0 || buffer.z < 0) // check if point is on screen
		{
			return false;
		}

		if (buffer.z > 0.0f) // Check if point is in view
		{
			screen = Vector2(buffer.x, vars::screen_size.y - buffer.y);
		}

		if (screen.x > 0 || screen.y > 0) // Check if point is in view
		{
			return true;
		}
	}
#pragma endregion
}
