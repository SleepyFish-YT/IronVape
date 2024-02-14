#ifndef MENUPOINTERS_HPP
#define MENUPOINTERS_HPP
#define Author SleepyFish

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
	extern MenuFolder *AMMO;
	extern MenuFolder *MOVE;
	extern MenuFolder *HEART;
	extern MenuFolder *MISC;
	extern MenuFolder *ANIM;
	extern MenuFolder *CAMA;
	extern MenuFolder *SETT;
	extern MenuFolder *KILLS;
	extern MenuFolder *JUMP;
	extern MenuFolder *FPS;
	extern MenuFolder *HUD;
	extern MenuFolder *ONWAIT;
	extern MenuFolder *ONPLAYERS;
	extern MenuFolder *ACC;
	extern MenuFolder *BOT;

	void PatchProcess(FwkSettings &settings);
	void SetFWK(FwkSettings &settings, const Color TxtColor);
}

#endif
