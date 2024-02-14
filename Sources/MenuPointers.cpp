#include <CTRPluginFramework.hpp>
#include "cheats.hpp"
#include "MenuPointers.hpp"
#define Author SleepyFish

extern "C" void _ZN18CTRPluginFramework10SearchMenu12ProcessEventERSt6vectorINS_5EventESaIS2_EERNS_4TimeE();

namespace CTRPluginFramework {
	MenuFolder *AMMO;
	MenuFolder *MOVE;
	MenuFolder *HEART;
	MenuFolder *MISC;
	MenuFolder *ANIM;
	MenuFolder *CAMA;
	MenuFolder *SETT;
	MenuFolder *KILLS;
	MenuFolder *JUMP;
	MenuFolder *FPS;
	MenuFolder *HUD;
	MenuFolder *ONWAIT;
	MenuFolder *ONPLAYERS;
	MenuFolder *ACC;
	MenuFolder *BOT;

    void PatchProcess(FwkSettings &settings)
    {
		*(u32*)((u32)(_ZN18CTRPluginFramework10SearchMenu12ProcessEventERSt6vectorINS_5EventESaIS2_EERNS_4TimeE));
    }
	//+ 0xB4) = 0xE1A00000;
	void SetFWK(FwkSettings &settings, const Color TxtColor) {
		settings.MainTextColor = TxtColor;
		settings.MenuSelectedItemColor = TxtColor;
		settings.MenuUnselectedItemColor = TxtColor;
	}
}
