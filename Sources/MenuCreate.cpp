#include <CTRPluginFramework.hpp>
#include <vector>
#include "cheats.hpp"
#define Author SleepyFish

namespace CTRPluginFramework {
	static MenuEntry* EntryWithHotkey(MenuEntry* entry, const Hotkey& hotkey)
	{
		if (entry != nullptr)
		{
			entry->Hotkeys += hotkey;
			entry->SetArg(new std::string(entry->Name()));
			entry->Name() += " " + hotkey.ToString();
			entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry* entry, int index)
				{
					std::string* name = reinterpret_cast<std::string*>(entry->GetArg());
					entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
				});
		}
		return (entry);
	}
	static MenuEntry* EntryWithHotkey(MenuEntry* entry, const std::vector<Hotkey>& hotkeys)
	{
		if (entry != nullptr)
		{
			for (const Hotkey& hotkey : hotkeys)
				entry->Hotkeys += hotkey;
		}
		return (entry);
	}
	void InitMenu(PluginMenu* menu) {

		//online wait folder
		ONWAIT = new MenuFolder("Online room Codes");
			ONWAIT->Append(new MenuEntry("Kick Online Player's", nullptr, kickOnlinePlayers, "Works only in Online Match")),
			ONWAIT->Append(new MenuEntry("Force Online Match to End", nullptr, ForceOnlineMatchToEnd, "Only work's on your Char")),
			ONWAIT->Append(new MenuEntry("Online Wait room mode Changer", nullptr, OnlineWait)),
			ONWAIT->Append(new MenuEntry("Online Wait room Ghost", onlineGhost, "Only work's in Waitig Room")),
			ONWAIT->Append(new MenuEntry("Win Camera", WinCam, "Only work's on your Char")),
		menu->Append(ONWAIT);

		//movement folder
		MOVE = new MenuFolder("Movement Codes");
		ANIM = new MenuFolder("Animation Codes");
			ANIM->Append(new MenuEntry("Animation Modifier 1", nullptr, ModAnima1, "Only in Offline matches")),
			ANIM->Append(new MenuEntry("Animation Modifier 2", nullptr, ModAnima2, "Only in Offline matches")),
			ANIM->Append(new MenuEntry("Speed Animation", SpeedAnima, "Speed up your Animation's\n  Only in Offline matches")),
			ANIM->Append(new MenuEntry("No Walk Animation", noWalkAnim, "Not work's on every map")),
			ANIM->Append(new MenuEntry("No Aim Animation", noAimAnim, "Not work's on every map")),
		MOVE->Append(ANIM);
			MOVE->Append(new MenuEntry("Restart Offline Game", nullptr, RestartOfflineGame, "Resets Position, Timer, Kills")),
			MOVE->Append(new MenuEntry("Player Size Modifier", nullptr, Playersize, "Modifies your Hight")),
			MOVE->Append(new MenuEntry("Speed Hack Modifier", nullptr, speedModifier, "Speed (1-9)\n- 1 = Default\n- 9 = Fastest")),
			MOVE->Append(new MenuEntry("Speed Hack", speedHack, "Your Charakter is fast as Usain bolt")),
			MOVE->Append(new MenuEntry("Coord Modifier", CoordMod, " Initial Button : \uE000\n Move Button : \uE079")),
			MOVE->Append(new MenuEntry("No Position Updates", NoPositionUpdates)),
			MOVE->Append(EntryWithHotkey(new MenuEntry("Moon Jump", MoonJump), { Hotkey(Key::ZL, "Go up"), Hotkey(Key::B, "Dont do anythink") })),
			MOVE->Append(new MenuEntry("Auto Sprint", AutoSprint, "Automaticly sprint's for you")),
			MOVE->Append(new MenuEntry("Smooth Walk", smoothWalk)),
			MOVE->Append(new MenuEntry("Smooth Run", smoothRun)),
			MOVE->Append(new MenuEntry("NoClip (Big)", NoClipBig)),
			MOVE->Append(new MenuEntry("NoClip (Small)", NoClipSma)),
			MOVE->Append(EntryWithHotkey(new MenuEntry("Freeze Bot's", freezeBot, "Hold down the hotkeys to use this cheat\n\nIf you are not in an Offline match it may Crash due to Data Abort"), { Hotkey(Key::DPadDown, "Freeze") })),
			MOVE->Append(new MenuEntry("Freeze Bot's Toggle", freezeBotToggle, "If you are not in an Offline match it may Crash due to Data Abort")),
			MOVE->Append(new MenuEntry("Stand on Small Wall", StandOnSmall)),
			MOVE->Append(new MenuEntry("Crouch on Wall", CrouchOnWall)),
		menu->Append(MOVE);

		//weapon folder
		AMMO = new MenuFolder("Weapon Codes");
			AMMO->Append(new MenuEntry("Reload Modes", nullptr, Reload)),
			AMMO->Append(new MenuEntry("Unlimited Ammo", InfinteAmmo, " Works with every Weapon\nWorks Offline / Online")),
			AMMO->Append(new MenuEntry("Auto Shoot", autoShoot, " Works with every Weapon\nWorks Offline / Online")),
			AMMO->Append(new MenuEntry("Rapid Fire (normal)", Rapid, " Please DONT use in Online Match\n\n Code not stable")),
			AMMO->Append(new MenuEntry("Rapid Fire (legit)", Rapid2, " Please DONT use in Online Match\n\n Code not stable")),
			AMMO->Append(new MenuEntry("No Recoil", noRecoil, " Disable Recoil when shoot")),
			AMMO->Append(new MenuEntry("Shoot through walls", shootWall, " Shoot through walls\n Only Offline")),
			AMMO->Append(new MenuEntry("- - -", empty)),
			AMMO->Append(new MenuEntry("Disable Shoot", disShoot, " If you want Peace")),
			AMMO->Append(new MenuEntry("Disable spamm Shoot", disSpammShoot, " Works with every Weapon\nWorks Offline / Online")),
			AMMO->Append(EntryWithHotkey(new MenuEntry("Aimbot Touch", AimBot, " Hold down the hotkeys to use this cheat"), { Hotkey(Key::R, "Aim") })),
			AMMO->Append(EntryWithHotkey(new MenuEntry("Aimbot C-Stick", AimBot, " Hold down the hotkeys to use this cheat"), { Hotkey(Key::L, "Aim") })),
			AMMO->Append(new MenuEntry("Fix  Big weapon", fixBig, " Big Weapom like: Sniper, Rocket-Launcher")),
			AMMO->Append(new MenuEntry("Fix Small weapon", fixSma, " Small Weapon like: BotGun, AR, Shotgun")),
			AMMO->Append(new MenuEntry("Delete Weapon", delWeapon, " Works with every Weapon\nWorks Offline / Online")),
			AMMO->Append(new MenuEntry("No Weapon Sound", NoWeaponSound, " Beta Code")),
		menu->Append(AMMO);

			//account folder
		ACC = new MenuFolder("Account Codes");
			ACC->Append(new MenuEntry("Name Changer (normal)", nullptr, nameChanger, " Play one game to save the New Name")),
			ACC->Append(new MenuEntry("Name Changer (costum)", nullptr, nameChanger2, " Play one game to save the New Name\n\n Costum mode: more charakters")),
			ACC->Append(new MenuEntry("Credit Changer", nullptr, CreditChange, " Play one game to save the New Credits")),
			ACC->Append(new MenuEntry("Delete Account's", nullptr, delAcc, " Are you sure?\n Deleting Account's\nCANNOT restored if they not Saved")),
			ACC->Append(new MenuEntry("Save Account File", nullptr, dumpSave, " Save account's to dont Loose them")),
			ACC->Append(new MenuEntry("Restore Account File", nullptr, restoreSave, " Restore the Saved account's to use them")),
		menu->Append(ACC);

		//camera folder
		CAMA = new MenuFolder("Camera Codes");
			CAMA->Append(new MenuEntry("View Method", nullptr, Methode, " Changes your Camera input Methode")),
			CAMA->Append(new MenuEntry("Blur Camera", nullptr, blurCam, " Blur Camera like you hav low HP")),
			CAMA->Append(new MenuEntry("Bigger FOV", FOVMod, "FOV: 120")),
			CAMA->Append(new MenuEntry("Memz Virus Visuals", memzVisual, "Thats not a virus\nOnly a visual change")),
			CAMA->Append(EntryWithHotkey(new MenuEntry("Zoom", zoom, " Hold down the hotkeys to use this cheat"), { Hotkey(Key::ZR, " Zoom") })),
			CAMA->Append(EntryWithHotkey(new MenuEntry("X-Ray", xray, " Hold down the hotkeys to use this cheat"), { Hotkey(Key::DPadLeft, " Activate") })),
			CAMA->Append(new MenuEntry("X-Ray Toggle", xraytoggle)),
			CAMA->Append(new MenuEntry("Only Render one Room", onlyRender1room)),
			CAMA->Append(new MenuEntry("Buncy Run Camera", buncyRunCama)),
			CAMA->Append(new MenuEntry("Wierd Run Camera", wierdCama)),
			CAMA->Append(new MenuEntry("Upside Down Camera", upsideDownCama)),
			CAMA->Append(EntryWithHotkey(new MenuEntry("Detach Camera", detachCamera), { Hotkey(Key::DPadRight, " Detch/Reattach") })),
			CAMA->Append(new MenuEntry("Map Free-Look", MapFreelook, " Other name: Camera modifier")),
			CAMA->Append(new MenuEntry("Diable Death Screen", disDeathScreen, " If you are scared from the Skeleton Skull")),
		menu->Append(CAMA);

			//hud folder
		HUD = new MenuFolder("HUD Codes");
			HUD->Append(new MenuEntry("Credit         HUD", CreditCount)),
			HUD->Append(new MenuEntry("Name          HUD", NameCount)),
			HUD->Append(new MenuEntry("- - -", empty)),
			HUD->Append(new MenuEntry("Shoot          HUD", autoShootCount)),
			HUD->Append(new MenuEntry("Blur           HUD", blurCount)),
			HUD->Append(new MenuEntry("Recoil         HUD", recoilCounter)),
			HUD->Append(new MenuEntry("FOV             HUD", FOVCount)),
			HUD->Append(new MenuEntry("Menu           HUD", MenuCount)),
			HUD->Append(new MenuEntry("Animation    HUD", animCount, " Only Offline")),
			HUD->Append(new MenuEntry("- - -", empty)),
			HUD->Append(new MenuEntry("Kill HUD Offline", customKillCountOffline)),
			HUD->Append(new MenuEntry("Kill HUD Online Text Mode", customKillCount, " Color: Gray not added yet")),
			HUD->Append(new MenuEntry("Kill HUD Online Color Mode", customKillCount2, " Color: Gray not added yet")),
		menu->Append(HUD);

		//heart folder
		HEART = new MenuFolder("HP Codes");
		KILLS = new MenuFolder("Kill Codes");
			KILLS->Append(new MenuEntry("999  Highscore Kills", nullptr, HighScore, " Set the kill count in Highscore mode to 999")),
			KILLS->Append(new MenuEntry("   0    Highscore Kills", nullptr, HighScore0, " Set the kill count in Highscore mode to 0")),
			KILLS->Append(new MenuEntry("- - -", nullptr, empty)),
			KILLS->Append(new MenuEntry("100  Online Kills", nullptr, kills100, " Modifies Kills to 100\n  Color: Gray not added yet")),
			KILLS->Append(new MenuEntry("   0    Online Kills", nullptr, kills0, " Modifies Kills to 0\n  Color: Gray not added yet")),
			HEART->Append(KILLS);
		HEART->Append(new MenuEntry("Self Destruct", nullptr, selfDestruct, " Ur charakter does suidcide")),
			HEART->Append(new MenuEntry("Heart Rate Moditor Modifier", nullptr, heartRate, " 0 heart rate will not kill you")),
			HEART->Append(new MenuEntry("GodMode", Invincibility, " Have Infinite HP!")),
			HEART->Append(new MenuEntry("You Die in One Shot", YouDie1, " Use this if you want to lose")),
		menu->Append(HEART);

		BOT = new MenuFolder("Bot Codes", "All codes here are Beta Codes");
		BOT->Append(new MenuEntry("No Dyxbot", BotNoDyx)),
		BOT->Append(new MenuEntry("Speed Dyxbot", BotSpeed)),
		BOT->Append(new MenuEntry("Kill Bots", BotKill)),
		BOT->Append(new MenuEntry("Reset Bot", BotReset)),
		BOT->Append(new MenuEntry("No Clip Bot", BotNoClip)),
		menu->Append(BOT);

		//misc Folder
		MISC = new MenuFolder("Misc");
		JUMP = new MenuFolder("Jump to Menu");
			JUMP->Append(new MenuEntry("Jump to : - Input ID", nullptr, ModMenu)),
			JUMP->Append(new MenuEntry("- - Show Menu ID - -", MenuCount)),
			JUMP->Append(new MenuEntry("Jump to : - Main Menu", nullptr, jumpToMainMenu, " Jump to Main Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Quest Menu", nullptr, jumpToQuest, " Jump to Quest Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Online Menu", nullptr, jumpToOnline, " Jump to Online Match Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Fast Online Menu", nullptr, jumpToFastOn, " Jump to Fast Onlibe Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Online Match", nullptr, jumpToOnMatch, " Jump to Online Match")),
			JUMP->Append(new MenuEntry("Jump to : - Jukebox Menu", nullptr, jumpToOnJukebox, " Jump to Jukebox Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Account Menu", nullptr, jumpToAcc, " Jump to Account Menu")),
			JUMP->Append(new MenuEntry("Jump to : - C-Stick Menu", nullptr, jumpToCStick, " Jump to C-Stick Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Game Mode Menu", nullptr, jumpToGameMode, " Jump to Game Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Multiplayer Menu", nullptr, jumpToMultiplayer, " Jump to Multiplayer Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Survive Menu", nullptr, jumpToSurvive, " Jump to Survive Menu")),
			JUMP->Append(new MenuEntry("Jump to : - Setting Menu", nullptr, jumpToSett, " Jump to  Menu")),
			MISC->Append(JUMP);
		FPS = new MenuFolder("FPS Codes");
			FPS->Append(new MenuEntry("-10              FPS", fpsM10)),
			FPS->Append(new MenuEntry("0                   FPS", fps0)),
			FPS->Append(new MenuEntry("40                 FPS", fps40)),
			FPS->Append(new MenuEntry("60                 FPS", fps60)),
			FPS->Append(new MenuEntry("120              FPS", fps120)),
			FPS->Append(new MenuEntry("Much             FPS", fps999)),
			FPS->Append(new MenuEntry("Disable FPS counter", emptyOSD)),
			FPS->Append(new MenuEntry("SleepyFish   FPS", fpsSleepy)),
		MISC->Append(FPS);
			MISC->Append(new MenuEntry("Rickroll", nullptr, Rickroll, " May new update: Rickroll Sound's\n\n\n In Version 2.2")),
			MISC->Append(EntryWithHotkey(new MenuEntry("Crasher", Crash, " Dont minimize with SELECT\nif it's active!\n Minimize with the red X"), { Hotkey(Key::L | Key::R | Key::DPadDown, "Crash") })),
			MISC->Append(EntryWithHotkey(new MenuEntry("Plugin Crasher", CrashPLGs, " Breaks CTRPF & NTR void headers."), { Hotkey(Key::L | Key::R | Key::DPadUp, "Crash") })),
			MISC->Append(new MenuEntry("Freeze Highscore Time Offline", FreezeTime, " Freeze Highscore timer to 0:01")),
			MISC->Append(new MenuEntry("Auto Clicker", ac, " Removed the input for Auto Clicking")),
			MISC->Append(new MenuEntry("Fast Input's", fastinput, " Lower the input for faster button spamm")),
			MISC->Append(new MenuEntry("Disable Pause menu", disMenu)),
			MISC->Append(new MenuEntry("RGB LED", rgbled, " RGB Notifications LED")),
		menu->Append(MISC);

		//settings folder
		SETT = new MenuFolder("Settings");
			SETT->Append(new MenuEntry("Uninject Plugin", uninject, " Uses Crash plugin for Uninject")),
			SETT->Append(new MenuEntry("Plugin Author Text", author)),
			SETT->Append(new MenuEntry("- - -", nullptr, empty)),
			SETT->Append(new MenuEntry("\uE002 and \uE003 Invert", nullptr, YandXInvert)),
			SETT->Append(new MenuEntry("Perfect Sound", nullptr, PerfectSound)),
			SETT->Append(new MenuEntry("Realife Sensi", realifeSensi, " X : Sensitivity : 100%\n Y : Sensitivity : 100%")),
			SETT->Append(new MenuEntry("Sleepy's Settings", nullptr, SleepySettings, " Set the sensitivity and the sound\n to the same as SleepyFish uses")),
			SETT->Append(new MenuEntry("- - -", nullptr, empty)),
			SETT->Append(new MenuEntry("Game Version", nullptr, showGameVer)),
			SETT->Append(new MenuEntry("IronVape Version", nullptr, showPlgVer)),
			SETT->Append(new MenuEntry("IronVape Install path", nullptr, showPath)),
			SETT->Append(new MenuEntry("- - -", nullptr, empty)),
			SETT->Append(new MenuEntry("Discord Link", nullptr, dc, "IronVape official Discord link")),
			SETT->Append(new MenuEntry("GitHub Link", nullptr, gh, "IronVape official GitHub link")),
			SETT->Append(new MenuEntry("Web Link", nullptr, web, "IronVape official Web link")),
			SETT->Append(new MenuEntry("- - -", nullptr, empty)),
			SETT->Append(new MenuEntry("Toggle Theme", toggleTheme, " You have to rename or delete the \n/luma/plugins/000400000015B100/Background.bmp's to use this right\n\nLike Night / Day Mode")),
			SETT->Append(new MenuEntry("Plugin Settings", nullptr, Settings)),
			SETT->Append(new MenuEntry("Exit Game", nullptr, exitgame)),
		menu->Append(SETT);

		menu->Append(new MenuEntry("RGB LED", rgbled, " RGB Notifications LED"));
		menu->Append(new MenuEntry("Plugin Settints", nullptr, Settings));
		menu->Append(new MenuEntry("Exit Game", nullptr, exitgame));
	}
}