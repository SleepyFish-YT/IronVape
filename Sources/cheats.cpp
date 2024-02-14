#include "cheats.hpp"
#include "Codes.hpp"  //<-- Here are the Codes and u dont get them ;)
#include <vector>
#include <ctr-led-brary.hpp> //<-- LED Function
#define Author SleepyFish
#define codeSteal "The codes are saved on a other file so dont try to get them u noob lmaoo"

//OSD::Notify(" : On");
//OSD::Notify(" : Off");
//Sleep(Milliseconds(200));

namespace CTRPluginFramework {
//--------------------------------------------------------------------------------------------
//headers start
	Keyboard *optKb = new Keyboard(" Choose option :");
	std::vector<std::string> AbleOpt{
			"-   Enable   -",
			"-  Disable  -",
	};

	Keyboard* optKbS = new Keyboard(" Size :");
	Keyboard* optKbH = new Keyboard(" Heart rate codes :");
	Keyboard* optKbSETT = new Keyboard(" Plugin settings :");
	Keyboard* optKbMetho = new Keyboard(" Camera methode :");
	Keyboard* optKbKills = new Keyboard(" Kill codes :");
	Keyboard* optKbReload = new Keyboard(" Reload modes :");
	Keyboard* optKbDelAcc = new Keyboard(" Delete account :");
	Keyboard* optKbBlurCam = new Keyboard(" Blur Cam modes :");
	Keyboard* optKbName = new Keyboard(" Name changer :");
	Keyboard* optKbOWait = new Keyboard(" Online Wait room codes :");
	Keyboard* kbCredit = new Keyboard(" Enter Credits :");
	Keyboard* kbCoord = new Keyboard(" Enter Speed :");
	Keyboard* kbAnima1 = new Keyboard(" Enter Animation 1 :");
	Keyboard* kbAnima2 = new Keyboard(" Enter Animation 2 :");
	Keyboard* kbMenu = new Keyboard(" Enter Menu_ID :\n Dont Use jump to when you're in a Match");
	Keyboard* speedKb = new Keyboard(" Enter Speed (1-9) :\n 1 = Default\n 9 = Fastest");
//headers close
//--------------------------------------------------------------------------------------------
	bool doNameKeyboard(u32 addr) {
		std::string textval;
		Keyboard keyboard("Enter your new name:");
		keyboard.SetMaxLength(8);
		int op = keyboard.Open(textval);
		if (op < 0)
		return 0;
		Process::WriteString(addr, textval, StringFormat::Utf16);
		MessageBox("Name changed to \"" + textval + "\"")();
		return 1;
	}
	bool doNameKeyboard2(u32 addr) {
		std::string textval;
		Keyboard keyboard("Enter your new name:");
		keyboard.SetMaxLength(16);
		int op = keyboard.Open(textval);
		if (op < 0)
		return 0;
		Process::WriteString(addr, textval, StringFormat::Utf16);
		MessageBox("Name changed to \"" + textval + "\"")();
		return 1;
	}
//codes start
//--------------------------------------------------------------------------------------------
	void nameChanger(MenuEntry* entry) {
		std::vector<std::string> NameList;
		std::string txt;
		NameList.clear();
		for (int i = 0; i < 3; i++) {
			txt = "-  ";
			Process::ReadString(delAcc1 + i * 0x2000, txt, 16, StringFormat::Utf16);
			NameList.push_back(txt + Utils::Format("  - (Acc. %i)", i + 1));
		}
		optKbName->Populate(NameList);
		switch (optKbName->Open())
		{
		case 0://Name 1
		doNameKeyboard(delAcc1);
		OSD::Notify("Name 1 changed");
		break;
		case 1://Name 2
		doNameKeyboard(delAcc2);
		OSD::Notify("Name 2 changed");
		break;
		case 2://Name 3
		doNameKeyboard(delAcc3);
		OSD::Notify("Name 3 changed");
		break;
		default: break;
		}
	}

	void nameChanger2(MenuEntry* entry) {
		std::vector<std::string> NameList;
		std::string txt;
		NameList.clear();
		for (int i = 0; i < 3; i++) {
		txt = "-  ";
		Process::ReadString(delAcc1 + i * 0x2000, txt, 16, StringFormat::Utf16);
		NameList.push_back(txt + Utils::Format("  - (Acc. %i)", i + 1));
		}
		optKbName->Populate(NameList);
		switch (optKbName->Open())
		{
		case 0://Name 1
		doNameKeyboard2(delAcc1);
		OSD::Notify("Name 1 changed");
		break;
		case 1://Name 2
		doNameKeyboard2(delAcc2);
		OSD::Notify("Name 2 changed");
		break;
		case 2://Name 3
		doNameKeyboard2(delAcc3);
		OSD::Notify("Name 3 changed");
		break;
		default: break;
		}
	}

	void InfinteAmmo(MenuEntry* entry) {
		if (entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(AmmoInfcode1, 0xE2433000);
			Process::Write32(AmmoInfcode2, 0xE2400000);
		}
		else if (!entry->IsActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(AmmoInfcode1, 0xE2433001);
			Process::Write32(AmmoInfcode2, 0xE2400001);
			OSD::Notify("Unlimited Ammo : Off");
		}
	}

	void YouDie1(MenuEntry *entry) {
		if (entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(dieCode, nineninenine);
			MessageBox("Info\n This Not work's for everyone")();
		}
		else if (!entry->IsActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(dieCode, nullval);
		}
	}

	void shootWall(MenuEntry *entry) {
		if (entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(shootWallCode, 0xEA000032);
			Process::Write32(shootWallCode2, 0x1A00009B);
		}
		else if (!entry->IsActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(shootWallCode, 0x1A000032);
			Process::Write32(shootWallCode2, 0x0A000000);
		}
	}
	void AimBot(MenuEntry* entry) {
		if (entry->Hotkeys[0].IsDown()) {
			Process::Write32(aimCode1, aimBott1);
			Process::Write32(aimCode2, nullval);
		}
		else {
			Process::Write32(aimCode1, 0x0A000162);
		}
	}

	void xraytoggle(MenuEntry *entry) {
		if (entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(xrayCode, 0xEA000032);
		}
		else if (!entry->IsActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(xrayCode, 0x1A000032);
			OSD::Notify("XRay : Off");
		}
	}

	void xray(MenuEntry* entry) {
		if (entry->Hotkeys[0].IsDown()) {
			Process::Write32(xrayCode, 0xEA000032);
			const Screen& BottomScreen = OSD::GetBottomScreen();
			BottomScreen.Draw(Color(CPAWRED) << "XRay", 295, 230);
		} else {
			Process::Write32(xrayCode, 0x1A000032);
		}
	}

	void xray2(MenuEntry* entry) {
		if (entry->Hotkeys[0].IsDown()) {
			Process::Write32(xrayCode2, 0xEA000032);
			const Screen& BottomScreen = OSD::GetBottomScreen();
			BottomScreen.Draw(Color(CPAWRED) << "XRay2", 290, 230);
		}
		Process::Write32(xrayCode2, 0x1A000032);
	}

	void Crash(MenuEntry *entry) {
		if (entry->Hotkeys[0].IsDown()) {
			MessageBox("Info :\n Crasher not work's for everyone")();
			Sleep(Milliseconds(200));
			Process::Write32(fps0Code, hundert);
			Process::Write16(fps0Code, 0);
			Process::Write8(fps0Code, hundert);
		}
	}

	void NoPositionUpdates(MenuEntry *entry) {
		if (entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(nopos1, 0xE1A00000);
		}
		else if (!entry->IsActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(nopos1, 0xEB0014CF);
			OSD::Notify("NoPos : Off");
		}
	}

	void Settings(MenuEntry* entry) {
		;
		std::vector<std::string> ColorList{
		Color(0xFFFFFFFF) << "White",
		Color(0xFFFF00FF) << "Yellow",
		Color(0x00FFFFFF) << "Blue",
		Color(0x88001BFF) << "Red",
		Color(0x90EE90FF) << "Green",
		Color(0x808080FF) << "Grey",
		};
		std::vector<std::string> Settingsini{
				"New3DS Buttons Message",
				"-  Color Mode  -",
		};
		u32 ColorChoiche = 0;
		int MessageChoiche = 2;
		optKbSETT->Populate(Settingsini);
		switch (optKbSETT->Open())
		{
		case 0://button message
		{
			optKb->Populate(AbleOpt);
			switch (optKb->Open())
			{
			case 0://Enable
				MessageChoiche = 1;
				break;
			case 1://Disable
				MessageChoiche = 0;
				break;
			default: break;
			}
			break;
		}
		case 1://color
		{
			optKbSETT->Populate(ColorList);
			switch (optKbSETT->Open())
			{
			case 0://White
				settings.MainTextColor = 0xFFFFFFFF;
				settings.MenuSelectedItemColor = 0xFFFFFFFF;
				settings.MenuUnselectedItemColor = 0xFFFFFFFF;
				settings.BackgroundBorderColor = 0xFFFFFFFF;
				ColorChoiche = 0xFFFFFFFF;
				break;
			case 1://Yellow
				settings.MainTextColor = 0xFFFF00FF;
				settings.MenuSelectedItemColor = 0xFFFF00FF;
				settings.MenuUnselectedItemColor = 0xFFFF00FF;
				settings.BackgroundBorderColor = 0xFFFF00FF;
				ColorChoiche = 0xFFFF00FF;
				break;
			case 2://Blue
				settings.MainTextColor = 0x00FFFFFF;
				settings.MenuSelectedItemColor = 0x00FFFFFF;
				settings.MenuUnselectedItemColor = 0x00FFFFFF;
				settings.BackgroundBorderColor = 0x00FFFFFF;
				ColorChoiche = 0x00FFFFFF;
				break;
			case 3://Red
				settings.MainTextColor = Red;
				settings.MenuSelectedItemColor = Red;
				settings.MenuUnselectedItemColor = Red;
				settings.BackgroundBorderColor = Red;
				ColorChoiche = Red;
				break;
			case 4://Green
				settings.MainTextColor = 0x90ee90FF;
				settings.MenuSelectedItemColor = 0x90ee90FF;
				settings.MenuUnselectedItemColor = 0x90ee90FF;
				settings.BackgroundBorderColor = 0x90ee90FF;
				ColorChoiche = 0x90ee90FF;
				break;
			case 5://and finaly Grey
				settings.MainTextColor = 0x808080FF;
				settings.MenuSelectedItemColor = 0x808080FF;
				settings.MenuUnselectedItemColor = 0x808080FF;
				settings.BackgroundBorderColor = 0x808080FF;
				ColorChoiche = 0x808080FF;
				break;
			default: break;
			}
			break;
		}
		default: break;
		}
		const int* c_fwk = GetSettings();
		if (MessageChoiche != 2) {//means you picked Message
			File::Create(settingstxt);
			File file(settingstxt);
			file.WriteLine(Utils::Format("Color :: %08X", c_fwk[0]));
			file.WriteLine(Utils::Format("new3DS_Button_Message :: %i", MessageChoiche));
			file.Close();
		}
		if (ColorChoiche != 0) {//means you picked color
			File::Create(settingstxt);
			File file(settingstxt);
			file.WriteLine(Utils::Format("Color :: %08X", ColorChoiche));
			file.WriteLine(Utils::Format("new3DS_Button_Message :: %i", c_fwk[1]));
			file.Close();
		}
		else return; //You get nothing! You lose! Good day sir!			A:ok foofoo :c
	}

	void MapFreelook(MenuEntry *entry) {
		if (entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(mapFreelookCode, 0x43900000);
		}
		else if (!entry->IsActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(mapFreelookCode, 0x43800000);
			OSD::Notify("Freelook : Off");
		}
	}

	void Playersize(MenuEntry *entry) {
		std::vector<std::string> Sizes{
		"-  Bigger  -",  //0
		"-  Normal  -",  //1
		"-  Smaller  -", //2
		"-    Invis    -",   //3
		};
		optKbS->Populate(Sizes);
		switch (optKbS->Open())
		{
		case 0: Process::Write32(playerSize, 0x3F900000);
			OSD::Notify("Bigger Player size");
			break;
		case 1: Process::Write32(playerSize, 0x3F800000);
			OSD::Notify("Normal Player size");
			break;
		case 2: Process::Write32(playerSize, 0x3F400000);
			OSD::Notify("Smaller Player size");
			break;
		case 3: Process::Write32(playerSize, 0xFFF00000);
			OSD::Notify("Invis Player size");
			break;
		default: break;
		}
	}

	void heartRate(MenuEntry *entry) {
		std::vector<std::string> heartRateOpt{
			"- Default -",					//0
			"No Heart Rate Monitor",		//1
			"Faster Heart Rate Monitor",	//2
			"Slower Heart Rate Monitor",	//3
			"Red Heart Rate Monitor",		//4
			"Fancy Heart Rate Monitor",		//5
			"0 Heart Rate Monitor",			//6
		};
		optKbH->Populate(heartRateOpt);
		switch (optKbH->Open()) {
		case 0:
			Process::Write32(heartRate1, 0x280100);
			Process::Write32(heartRate2, nullval);
			break;
		case 1:
			Process::Write16(heartRate1, 0xE0FF);
			break;
		case 2:
			Process::Write16(heartRate1, 0x1388);
			break;
		case 3:
			Process::Write16(heartRate1, oneval);
			break;
		case 4:
			Process::Write16(heartRate1, 0x3E7);
			break;
		case 5:
			Process::Write32(heartRate2, 0x06363636);
			break;
		case 6:
			Process::Write16(heartRate3, nullval);
		}
	}

	void Invincibility(MenuEntry *entry) {
		Process::Write32(0x6034C5CC, 0x00000000);
		Process::Write32(0xB034C5CC, 0x00000000);
		Process::Write32(0x000001A4, 0x12000000);
		Process::Write32(0xD2000000, 0x00000000);
		Process::Write32(0x0011F048, 0xE3500000);
	}

	void selfDestruct(MenuEntry *entry) {
		u32 val = 0xAE;
		Process::Write32(0x3194690C, val);
		Process::Write32(0x312DA75C, val);
		Process::Write32(0x315866DC, val);
		Process::Write32(0x318EF4DC, val);
		Process::Write32(0x3094690C, val);
		Process::Write32(0x302DA75C, val);
		Process::Write32(0x305866DC, val);
		Process::Write32(0x308EF4DC, val);
	}

	void MoonJump(MenuEntry *entry) {
		if (Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			Process::WriteFloat(moonJump1, 1.0f);
			if (Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys()))
				Process::WriteFloat(moonJump2, 2.0f);
			else
				Process::WriteFloat(moonJump2, 10.0f);
		}
		else {
			Process::WriteFloat(moonJump1, -10.0f);
			Process::WriteFloat(moonJump2, -10.0f);
		}
	}

	void detachCamera(MenuEntry* entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		if (Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			if (*(u32*)detatchCamCode == 0xE3500000) {//if default
				OSD::Notify("Dettached");
				Process::Write32(detatchCamCode, 0xE3500001); //detached
				BottomScreen.Draw(Color(CPAWRED) << "Detached", 295, 230);
			}
			else {
				OSD::Notify("Attached");
				Process::Write32(detatchCamCode, 0xE3500000); //else reattach
			}
		}
	}

	void FOVMod(MenuEntry* entry) {
		if (entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			OSD::Notify("FOV : 120");
			Process::Write32(foV, 0xE3A05B19);
		}
		else if (!entry->IsActivated()) {
			Sleep(Milliseconds(200));
			OSD::Notify("FOV : 90");
			Process::Write32(foV, 0xE0805009);
		}
	}

	void exitgame(MenuEntry *entry) {
		Sleep(Milliseconds(300));
		if ((MessageBox("Info:\n  Exit? \n   You may lose unsaved data ", DialogType::DialogOkCancel)).SetClear(ClearScreen::Both)())
		{
			Process::ReturnToHomeMenu();
		}
		else return;
	}

	void FreezeTime(MenuEntry *entry) {
		if (entry->IsActivated()) {
			Process::Write32(FreezeTimerCode, thenval);
		}
		else if (!entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			OSD::Notify("Timer Freeze : Off");
			Process::Write32(FreezeTimerCode, nullval);
		}
	}

	void AutoSprint(MenuEntry *entry) {
		Process::Write32(AutoSprintCode, 0x1000001);
	}

	void CrashPLGs(MenuEntry *entry) {
		if (Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			OSD::Notify("CrashPlugins need's a other server Plugin to work");
			Sleep(Milliseconds(200));
			Process::Write32(0x7C836, 0);
			for (int i = 0; i <= 2; i++) Process::Write32(0x7C83A + i, 0);
			Process::Write32(0x7C83D, 0x43);
			Process::Write32(0x1C7, 0x52);
			for (int i = 0; i <= 1; i++) Process::Write32(0x1CC + i, 0x41 + i * 2);
			for (int i = 0; i <= 1; i++) Process::Write32(0x2B0 + i * 0xF5, 0x54 + i);
			Process::Write32(0x32B, 0x53);
			for (int i = 0; i <= 2; i++) Process::Write32(0x7C83E + i, 0 + i * 0x4B);
			Process::Write32(0x1FD, 0x4F);
			Process::Write32(0x7C841, 0x4C);
			Process::Write32(0x60, nullval);
			Process::Write32(0x7F, nullval);
			Process::Write32(0x6D, nullval);
			Process::Write32(0x84, nullval);
			for (int i = 0; i <= 2; i++) Process::Write32(0x7C842 + i, 0);
		}
	}

	void HighScore(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(highScoreCode, hundertHey);
		OSD::Notify("High Score Kills set to 999");
	}

	void HighScore0(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(highScoreCode, nullval);
		OSD::Notify("High Score Kills set to 0");
	}

	void RestartOfflineGame(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(RestartOfflineGameCode, RestartOfflineGameVal);
		OSD::Notify("Restarted Game");
	}

	void kickOnlinePlayers(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(kickall, 6030603);
		OSD::Notify("Kicked Online players");
	}

	void StandOnSmall(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(crouchWall, 0x00010001);
		}
		else if (!entry->WasJustActivated()) { //off
			Sleep(Milliseconds(200));
			Process::Write32(crouchWall, 0x00010017);
			OSD::Notify("Stand on small Wall : Off");
		}
	}

	void CrouchOnWall(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(crouchWall, nullval);
		}
		else if (!entry->WasJustActivated()) { //off
			Sleep(Milliseconds(200));
			Process::Write32(crouchWall, 0x10017);
			OSD::Notify("Crouch on Wall : Off");
		}
	}

	void SpeedAnima(MenuEntry *entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Milliseconds(200));
			Process::Write32(speedAnim, 0xD2);
			OSD::Notify("SpeedAnimaion's : On");
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(speedAnim, nullval);
			OSD::Notify("SpeedAnimaion's : Off");
		}
	}

	void WinCam(MenuEntry *entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Milliseconds(200));
			Process::Write32(winCam, 0x307CDC10);
			OSD::Notify("WinCam : On");
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(winCam, nullval);
			OSD::Notify("WinCam : Off");
		}
	}

	void disMenu(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(disMenuCode, nullval); //8
		}
		else if (!entry->WasJustActivated()) {
			Sleep(Milliseconds(200));
			Process::Write32(disMenuCode, 8);
			OSD::Notify("Disable Pause Menu");
		}
	}
	void ForceOnlineMatchToEnd(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(OnlinematchEnd, 0x2000000);
		OSD::Notify("Send command to server...");
	}

	void Methode(MenuEntry *entry) {
		std::vector<std::string> Methodekb{
		"-   C-Stick   -", // 0 Cstick
		"-   Touch   -",   // 1 Touch
		};
		optKbMetho->Populate(Methodekb);
		switch (optKbMetho->Open()) {
		case 0:
			Process::Write32(methode, hundert);  //0 / 100val
			OSD::Notify("Camera : C-Stick");
			break;
		case 1:
			Process::Write32(methode, nullval);  //1
			OSD::Notify("Camera : Touch");
			break;
		}
	}

	void YandXInvert(MenuEntry *entry) {
		MessageBox("Save Y and X invert...")();
	
		Process::Write32(YandX, 0x1010000);
	}
	void SleepySettings(MenuEntry *entry) {
		MessageBox("Save Sound and Sensi...")();
		Process::Write32(sensi, 0x12120E0E);
		Process::Write32(sound, 0xF0090500);
	}

	void PerfectSound(MenuEntry *entry) {
		MessageBox("Save Sound...")();
		Process::Write32(sound, 0xF0090500);
	}

	void noWalkAnim(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(noAnim, 0x30AD1620);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(noAnim, 0x30AB57B8);
			OSD::Notify("NoWalk Animation : Off");
		}
	}

	void noAimAnim(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(noAnim, 0x30AF00C0);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(noAnim, 0x30AB57B8);
			OSD::Notify("NoAim Animation : Off");
		}
	}

	void kills100(MenuEntry* entry) {
		std::vector<std::string> kills100kb{
			"Red",        // 0
			"Dark Blue",  // 1
			"Yellow",     // 2
			"Green",      // 3
			"Light Blue", // 4
			"Gray"        // 5
		};
		optKbKills->Populate(kills100kb);
		switch (optKbKills->Open())
		{
		case 0: Process::Write32(kill1, hundert); //0
			break;
		case 1: Process::Write32(kill2, hundert); //1
			break;
		case 2: Process::Write32(kill3, hundert); //2
			break;
		case 3: Process::Write32(kill4, hundert); //3
			break;
		case 4: Process::Write32(kill5, hundert); //4
			break;
		case 5: Process::Write32(kill6, nullval); //5
			break;
		}
	}

	void kills0(MenuEntry *entry) {
		std::vector<std::string> kills0kb{
			"Red",        // 0
			"Dark Blue",  // 1
			"Yellow",     // 2
			"Green",      // 3
			"Light Blue", // 4
			"Gray"        // 5
		};
		optKbKills->Populate(kills0kb);
		switch (optKbKills->Open())
		{
		case 0: Process::Write32(kill1, nullval); //0
			break;
		case 1: Process::Write32(kill2, nullval); //1
			break;
		case 2: Process::Write32(kill3, nullval); //2
			break;
		case 3: Process::Write32(kill4, nullval); //3
			break;
		case 4: Process::Write32(kill5, nullval); //4
			break;
		case 5: Process::Write32(kill6, nullval); //5
		}
	}

	void Reload(MenuEntry *entry) {
		std::vector<std::string> Reloadkb{
			"Never Stop Reload",	// 0
			"Disable Reload",		// 1
			"Fast Reload",			// 2
			"Instant Fail",			// 3
			"- Default -",			// 4
		};
		optKbReload->Populate(Reloadkb);
		switch (optKbReload->Open())
		{
		case 0:
			Process::Write32(reload, 0x20000000);
			break;
		case 1:
			Process::Write32(reload, nullval);
			break;
		case 2:
			Process::Write32(reload, oneval);
			break;
		case 3:
			Process::Write32(reload, 20);
			break;
		case 4:
			Process::Write32(reload, nullval);
			break;
		}
	}
	void Rickroll(MenuEntry *entry) {
		(MessageBox("Never gonna give you up.\nNever gonna let you down.\nNever gonna run around and desert you.\nNever gonna make you cry.\nNever gonna say goodbye.\nNever gonna tell a lie and hurt you.", DialogType::DialogOk)).SetClear(ClearScreen::Both)();
	}

	void delAcc(MenuEntry *entry) {
		if ((MessageBox("Info:\n  Are you sure ? \n  Deleting Accounts cannot be Un-Done ", DialogType::DialogOkCancel)).SetClear(ClearScreen::Both)()) {
			Sleep(Milliseconds(200));
			std::vector<std::string> delAcckb{
				"-  All  -",     // 0
				"- First -",   // 1
				"Secound", // 2
				"- Third -",   // 3
				"-  All  -",     // 4
			};
			optKbDelAcc->Populate(delAcckb);
			switch (optKbDelAcc->Open())
			{
			case 0:
				Process::Write32(delAcc1, nullval);
				Process::Write32(delAcc2, nullval);
				Process::Write32(delAcc3, nullval);
				OSD::Notify("Acc deleted: All");
				break;
			case 1:
				Process::Write32(delAcc1, nullval);
				OSD::Notify("Acc deleted :   1");
				break;
			case 2:
				Process::Write32(delAcc2, nullval);
				OSD::Notify("Acc deleted :   2");
				break;
			case 3:
				Process::Write32(delAcc3, nullval);
				OSD::Notify("Acc deleted :   3");
				break;
			case 4:
				Process::Write32(delAcc1, nullval);
				Process::Write32(delAcc2, nullval);
				Process::Write32(delAcc3, nullval);
				OSD::Notify("Acc deleted: All");
				break;
			}
		}
		else return;
	}

	void toglescreen(MenuEntry *entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Milliseconds(200));
			Process::Write32(toggleScreen, hundert);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(toggleScreen, nullval);
			OSD::Notify("Toggle Screen's : Off");
		}
	}

	void ac(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(click, nullval);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(click, 0x3E3CF0);
			OSD::Notify("Auto Clicker : Off");
		}
	}

	void fastinput(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(click, 0x2E3C00);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(click, 0x3E3CF0);
			OSD::Notify("Fast input : Off");
		}
	}

	void ModMenu(MenuEntry *entry) {
		u32 val = 0;
		kbMenu->GetMessage() = " Enter Menu_ID :";
		kbMenu->IsHexadecimal(false);
		kbMenu->SetMaxLength(6);
		if (kbMenu->Open(val, val) == 0)
		{
			Sleep(Milliseconds(200));
			Process::Write32(menu, val);
		}
	}

	void jumpToOnline(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 0x7EB1D05);
		OSD::Notify("Jumped to Online Menu");
	}

	void jumpToMainMenu(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, nullval);
		OSD::Notify("Jumped to Main Menu");
	}

	void jumpToOnJukebox(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 0x504);
		OSD::Notify("Jumped to Jukebox Menu");
	}

	void jumpToQuest(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 0x503);
		OSD::Notify("Jumped to Quest Menu");
	}

	void jumpToAcc(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 0xC);
		OSD::Notify("Jumped to Account Menu");
	}

	void jumpToCStick(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 0xD000011);
		OSD::Notify("Jumped to C-Stick Menu");
	}

	void jumpToGameMode(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 0xC010000);
		OSD::Notify("Jumped to Game Mode Menu");
	}

	void jumpToMultiplayer(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 3000202);
		OSD::Notify("Jumped to Multiplayer Menu");
	}

	void jumpToSurvive(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 4141);
		OSD::Notify("Jumped to Survive Menu");
	}

	void jumpToSett(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 606);
		OSD::Notify("Jumped to Setting Menu");
	}

	void jumpToFastOn(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 0x4040);
		OSD::Notify("Jumped to Fast Online Menu");
	}

	void jumpToOnMatch(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		Process::Write32(menu, 0xC);
		OSD::Notify("Jumped to Online Match");
	}

	void disShoot(MenuEntry *entry) {
		Sleep(Milliseconds(200));
		if (entry->IsActivated()) { //on
			Process::Write32(disShootCode, 0x4);
		}
		else if (!entry->WasJustActivated()) { //off
			Sleep(Milliseconds(200));
			Process::Write32(disShootCode, nullval);
			OSD::Notify("Disable Shoot : Off");
		}
	}

	void fixBig(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(fixWeapon, 0x200);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(fixWeapon, nullval);
			OSD::Notify("Fix Big weapon : Off");
		}
	}

	void fixSma(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(fixWeapon, 0x100);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(fixWeapon, nullval);
			OSD::Notify("Fix Small weapon : Off");
		}
	}

	void disDeathScreen(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(disDeathScreenCode, 0x300000);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(disDeathScreenCode, nullval);
			OSD::Notify("Disable Death screen : Off");
		}
	}

	void blurCam(MenuEntry *entry) {
		std::vector<std::string> blurCam{
			"Blur Cam : On",  //0
			"Blur Cam : Off",  //1
			"- Motion Blur -",  //2
			"Disable Blur Cam : On", //3
			"Disable Blur Cam : Off",   //4
		};
		optKbBlurCam->Populate(blurCam);
		switch (optKbBlurCam->Open())
		{
		case 0:
			Process::Write32(blur, 0xFFFFFFFF);
			Sleep(Milliseconds(200));
			OSD::Notify("Blur Cam : On");
			break;
		case 1:
			Process::Write32(blur, nullval);
			Sleep(Milliseconds(200));
			OSD::Notify("Blur Cam : Off");
			break;
		case 2:
			Process::Write32(blur, 0x00AAA000);
			Sleep(Milliseconds(200));
			OSD::Notify("Motion Blur : On");
			break;
		case 3:
			Process::Write32(blur, oneval);
			Sleep(Milliseconds(200));
			OSD::Notify("No Blur Cam : On");
			break;
		case 4:
			Process::Write32(blur, nullval);
			Sleep(Milliseconds(200));
			OSD::Notify("No Blur Cam : Off");
			break;
		}
	}

	void zoom(MenuEntry *entry) {
		const Screen& BottomScreen = OSD::GetBottomScreen();
		if (entry->Hotkeys[0].IsDown()) { //on
			Process::Write32(zoomCode, 0xE0805008);
			BottomScreen.Draw(Color(CPAWRED) << "Zoom", 295, 230);
		}
		else { //off
			Process::Write32(zoomCode, 0xE0805009);
		}
	}

	void OnlineWait(MenuEntry *entry) {
		std::vector<std::string> OnlineWait{
			"-  Ready 1  -",	//0
			"-  Ready 2  -",	//1
			"- Flicker -",		//2
			"-  Bonus 1  -",	//3
			"-  Bonus 2  -",	//4
		};
		optKbOWait->Populate(OnlineWait);
		switch (optKbOWait->Open())
		{
		case 0:
			Process::Write32(onlinewait1, oneval);
			Sleep(Milliseconds(200));
			OSD::Notify("Mode : Ready 1");
			break;
		case 1:
			Process::Write32(onlinewait2, 0x0A514BDB);
			Sleep(Milliseconds(200));
			OSD::Notify("Mode : Ready 2");
			break;
		case 2:
			Process::Write32(onlinewait3, oneval);
			Sleep(Milliseconds(200));
			OSD::Notify("Mode : Flicker");
			break;
		case 3:
			Process::Write32(onlinewait4, 0xE40000);
			Sleep(Milliseconds(200));
			OSD::Notify("Mode : Bonus 1");
			break;
		case 4:
			Process::Write32(onlinewait5, 0xE0100);
			Sleep(Milliseconds(200));
			OSD::Notify("Mode : Bonus 2");
			break;
		}
	}

	void Rapid(MenuEntry *entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Milliseconds(200));
			(MessageBox("Info:\n Please DONT use Rapid Fire\n in Online Match\n Dont shoot with Small weapons Online", DialogType::DialogOk)).SetClear(ClearScreen::Both)();
			Process::Write32(RapidCode, 0xE0A00004);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(RapidCode, 0xE1A00004);
			OSD::Notify("Rapid Fire (normal) : Off");
		}
	}

	void Rapid2(MenuEntry *entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Seconds(1));
			(MessageBox("Info:\n Please DONT use Rapid Fire\n in Online Match\n Dont shoot with Small weapons Online", DialogType::DialogOk)).SetClear(ClearScreen::Both)();
			Process::Write32(RapidCode, 0xE320F000);
			Process::Write32(autoShootOnCode, 0x0A000000);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(RapidCode, 0xE1A00004);
			Process::Write32(autoShootOnCode, 0x0A000004);
			OSD::Notify("Rapid Fire (legit) : Off");
		}
	}

	void author(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		BottomScreen.Draw("IronVape by SleepyFish", 5, 5);
	}

	void uninject(MenuEntry *entry) {
		u32 addr = 0;
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		Process::WriteString(uninjectCode, 0, StringFormat::Utf16);
		BottomScreen.DrawSysfont("If you can read this your plugin dont Uninject properply", 55, 55);
	}

	void showPlgVer(MenuEntry *entry) {
		(MessageBox("Info:\n Installed Ver. 2.2", DialogType::DialogOk)).SetClear(ClearScreen::Both)();
	}

	void showPlgVerText(MenuEntry *entry) {
		const Screen& BottomScreen = OSD::GetBottomScreen();
		BottomScreen.Draw("Version: 2.1", 240, 5);
	}

	void showGameVer(MenuEntry *entry) {
		MessageBox(Utils::Format("Info:\n  Ironfall Verison: %04X", GetVersion))();
	}

	void showGameText(MenuEntry *entry) {
		const Screen& BottomScreen = OSD::GetBottomScreen();
		BottomScreen.Draw("Version: %04X", GetVersion, 10, 40);
	}

	void showPath(MenuEntry *entry) {
		(MessageBox("Info:\nInstall Phath:\nSD:/luma/plugins/000400000015B100", DialogType::DialogOk)).SetClear(ClearScreen::Both)();
	}

	std::vector<std::string> saveNames = {
			"-  Account 1  -", //Data0
			"-  Account 2  -", //Data1
			"-  Account 3  -", //Data2
	};

	void dumpSave(MenuEntry *entry) {
		Keyboard* saveKB = new Keyboard("Choose which account to Save :");
		std::string SaveName;
		u32 addr = 0;
		saveKB->Populate(saveNames);
		switch (saveKB->Open()) {
		case 0:
		Sleep(Milliseconds(200));
		addr = savecode0; //Data0
		break;
		case 1:
		Sleep(Milliseconds(200));
		addr = savecode1; //Data1
		break;
		case 3:
		Sleep(Milliseconds(200));
		addr = savecode2; //Data2
		break;
		}
		Keyboard keyboard("Rename the Save File :");
		keyboard.SetMaxLength(30);
		if (keyboard.Open(SaveName) != -1) {
			Sleep(Seconds(0.1f));
			Directory SaveDir;
			if (Directory::IsExists("Saves") == 0)
				Directory::Create("Saves");

			File SaveFile;
			File::Open(SaveFile, "Saves/" + SaveName + ".sav", File::RWC);//this has to have .sav or else we wont be able to get it later
			SaveFile.Dump(addr, 0x2000);
			SaveFile.Close();
			MessageBox("Info:\n Dump complete!")();
		}
	}

	void restoreSave(MenuEntry *entry) {
		Keyboard* saveKB = new Keyboard("Choose which account to restore to");
		std::vector<std::string> FileList;
		Directory SaveDir;
		u32 addr = 0;

		Directory::Open(SaveDir, "Saves", true);
		SaveDir.ListFiles(FileList, ".sav");
		Keyboard keyboard("Choose a save file!", FileList);
		int FileChoice = keyboard.Open();

		if (FileChoice < 0)
		return;

		saveKB->Populate(saveNames);
		switch (saveKB->Open()) {
		case 0:
		addr = 0x3B4BCC;
		break;
		case 1:
		addr = 0x3B6120;
		break;
		case 3:
		addr = 0x34C798;
		break;
		}

		Sleep(Seconds(0.1f));
		File SaveFile;
		SaveDir.OpenFile(SaveFile, FileList[FileChoice], File::READ);
		SaveFile.Inject(addr, 0x2000);
		MessageBox("Info:\n Save restored!")();
	}

	void rgbled(MenuEntry *entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Milliseconds(200));
			LED::PlayLEDPattern(LED::GeneratePattern(LED_Color(0xFF, 0xFF, 0xFF), LED_PatType::WAVE_DESC, 4, 0, 0x10, 0, 2.0 / 3, 1.0 / 3));
			OSD::Notify("RGB Led : On");
		}
		else if (!entry->IsActivated()) { //off
			LED::StopLEDPattern();
			OSD::Notify("RGB Led : Off");
		}
	}

	void freezeBot(MenuEntry *entry) {
		const Screen& BottomScreen = OSD::GetBottomScreen();
		if (entry->Hotkeys[0].IsDown()) { //on
			Process::Write32(freezeBotCode, nullval);
			BottomScreen.Draw(Color(CPAWRED) << "FreezeBot", 260, 230);
		}
		else { //off
			Process::Write32(freezeBotCode, oneval);
		}
	}

	void freezeBotToggle(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(freezeBotCode, nullval);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(freezeBotCode, oneval);
			OSD::Notify("FreezeBotToggle : Off");
		}
	}

	void dc(MenuEntry *entry) {
		(MessageBox("Info:\n DC Link:\ndiscord.gg/KpgaCsZxSN", DialogType::DialogOk)).SetClear(ClearScreen::Both)();
	}

	void gh(MenuEntry *entry) {
		(MessageBox("Info:\n GitHub Link:\ngithub.com/SleepyFishYT/IronVape", DialogType::DialogOk)).SetClear(ClearScreen::Both)();
	}

	void web(MenuEntry *entry) {
		(MessageBox("Info:\n Web Link:\n sites.google.com/view/ironvape", DialogType::DialogOk)).SetClear(ClearScreen::Both)();
	}

	void empty(MenuEntry *entry) {
		Process::Write32(0, 0);
	}

	void toggleTheme(MenuEntry *entry) {
		FwkSettings& settings = FwkSettings::Get();
		if (entry->WasJustActivated()) {
			settings.BackgroundMainColor = Color::White;
			settings.BackgroundSecondaryColor = Color::White;
			settings.BackgroundBorderColor = Color::Silver;
			settings.MainTextColor = Color::Black;
			settings.WindowTitleColor = Color::Black;
			settings.MenuSelectedItemColor = Color::Black;
			settings.MenuUnselectedItemColor = Color::Black;
			settings.Keyboard.Background = Color::White;
			settings.Keyboard.KeyBackground = Color::DarkGrey;
			settings.Keyboard.KeyBackgroundPressed = Color::DimGrey;
			settings.Keyboard.KeyText = Color::Black;
			settings.Keyboard.KeyTextPressed = Color::Black;
			settings.Keyboard.Cursor = Color::Black;
			settings.Keyboard.Input = Color::Black;
			settings.CustomKeyboard.BackgroundMain = Color::White;
			settings.CustomKeyboard.BackgroundSecondary = Color::White;
			settings.CustomKeyboard.BackgroundBorder = Color::Silver;
			settings.CustomKeyboard.KeyBackground = Color::White;
			settings.CustomKeyboard.KeyBackgroundPressed = Color::Gainsboro;
			settings.CustomKeyboard.KeyText = Color::Black;
			settings.CustomKeyboard.KeyTextPressed = Color::Black;
			settings.CustomKeyboard.ScrollBarBackground = Color::DimGrey;
			settings.CustomKeyboard.ScrollBarThumb = Color::Silver;
		}
		else if (!entry->IsActivated()) {
			settings.BackgroundMainColor = Color::Black;
			settings.BackgroundSecondaryColor = Color::Black;
			settings.MainTextColor = Red;
			settings.MenuSelectedItemColor = Red;
			settings.MenuUnselectedItemColor = Red;
		}
	}
	//OSD stuff ----------------------------------------------/
	void emptyOSD(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		TopScreen.Draw(Color(CPAWRED) << "FPS: ---", 10, 10);
	}

	void customKillCount(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		if (entry->IsActivated()) { //on
			TopScreen.Draw(Color(CPAWRED) << Utils::Format("Red        : %i", *(u32*)kill1), 305, 5);
			TopScreen.Draw(Color(DarkBlue) << Utils::Format("Dark Blue  : %i", *(u32*)kill2), 305, 15);
			TopScreen.Draw(Color(Yellow) << Utils::Format("Yellow     : %i", *(u32*)kill3), 305, 25);
			TopScreen.Draw(Color(Green) << Utils::Format("Greeen     : %i", *(u32*)kill4), 305, 35);
			TopScreen.Draw(Color(LightBlue) << Utils::Format("LightBlue  : %i", *(u32*)kill5), 305, 45);
			TopScreen.Draw(Color(Gray) << Utils::Format("Gray       : -"), 305, 55);//not added yet
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(0, 0);
		}
	}

	void customKillCount2(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		if (entry->IsActivated()) { //on
			TopScreen.Draw(Color(CPAWRED) << Utils::Format("%i", *(u32*)kill1),		385, 5);
			TopScreen.Draw(Color(DarkBlue) << Utils::Format("%i", *(u32*)kill2),	385, 15);
			TopScreen.Draw(Color(Yellow) << Utils::Format("%i", *(u32*)kill3),		385, 25);
			TopScreen.Draw(Color(Green) << Utils::Format("%i", *(u32*)kill4),		385, 35);
			TopScreen.Draw(Color(LightBlue) << Utils::Format("%i", *(u32*)kill5),	385, 45);//not added yet
			TopScreen.Draw(Color(Gray) << Utils::Format("-"),						385, 55);//not added yet
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(0, 0);
		}
	}

	void MenuCount(MenuEntry* entry) {
	//	const u8 MenU = *(u8*)menu;
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
	//	BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Menu       : %d", MenU), 10, 180)
		BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Menu       : %i", *(u32*)menu), 10, 180);
	}

	void customKillCountOffline(MenuEntry *entry) {
		const u8 kills = *(u8*)highScoreCode;
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		TopScreen.Draw(Color(CPAWRED) << Utils::Format("Kills : %d", kills), 335, 10);
	}

	void animCount(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
	//		const u8 count1 = *(u8*)noAnim;
	//		const u8 count2 = *(u8*)speedAnim;
			const Screen& BottomScreen = OSD::GetBottomScreen();
	//		BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Animation1 : %d", count1), 10, 190);
			BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Animation1 : %i", *(u32*)noAnim), 10, 190);
	//		BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Animation2 : %d", count2), 10, 200);
			BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Animation2 : %i", *(u32*)speedAnim), 10, 200);
		}
		if (entry->WasJustActivated()) { //off
			Process::Write32(0x0, 0x0);
		}
	}

	void FOVCount(MenuEntry *entry) {
	//	const u8 FOVC = *(u8*)foV;
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
	//		BottomScreen.Draw(Color(CPAWRED) << Utils::Format("FOV        : %d", FOVC), 10, 170);
			BottomScreen.Draw(Color(CPAWRED) << Utils::Format("FOV        : %i", *(u32*)foV), 10, 170);
	}

	void recoilCounter(MenuEntry* entry) {
	//	const u8 nRcode = *(u8*)noRecoilCode;
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
	//	BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Recoil     : %d", nRcode), 10, 150);
		BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Recoil     : %i", *(u32*)noRecoilCode), 10, 160);
	}

	void blurCount(MenuEntry *entry) {
	//	const u8 blrCode = *(u8*)blur;
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
	//	BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Blur       : %d", blrCode), 10, 140);
		BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Blur       : %i", *(u32*)blur), 10, 150);
	}

	void autoShootCount(MenuEntry *entry) {
	//	const u8 autoShoot = *(u8*)autoShootOnCode;
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
	//	BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Shoot        : %d", autoShoot), 10, 130);
		BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Shoot      : %i", *(u32*)autoShootOnCode), 10, 140);
	}

	void CreditCount(MenuEntry *entry) {									  
		const Screen& TopScreen = OSD::GetTopScreen();						  
		const Screen& BottomScreen = OSD::GetBottomScreen();				  
		if (entry->IsActivated()) { //on									  
			BottomScreen.Draw(Color(CPAWRED) << Utils::Format("Credits    : %i", *(u32*)credit), 10, 10);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(0, 0);
		}
	}

	void NameCount(MenuEntry *entry) {
		std::string name1 = "";
		Process::ReadString(delAcc1, name1, 16, StringFormat::Utf16);
		std::string name2 = "";
		Process::ReadString(delAcc2, name2, 16, StringFormat::Utf16);
		std::string name3 = "";
		Process::ReadString(delAcc3, name3, 16, StringFormat::Utf16);
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		BottomScreen.Draw("Name Acc 1 : " + name1, 10, 20, Color(CPAWRED));
		BottomScreen.Draw("Name Acc 2 : " + name2, 10, 30, Color(CPAWRED));
		BottomScreen.Draw("Name Acc 3 : " + name3, 10, 40, Color(CPAWRED));
	}

	void fps40(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			const Screen& TopScreen = OSD::GetTopScreen();
			TopScreen.Draw(Color(CPAWRED) << "FPS: 40", 10, 10);
			Process::Write32(fps40Code, oneval);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(fps40Code, nullval);
		}
	}

	void fps120(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		TopScreen.Draw(Color(CPAWRED) << "FPS: 120", 10, 10);
	}

	void fps60(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		TopScreen.Draw(Color(CPAWRED) << "FPS: 60", 10, 10);
	}

	void fps999(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		TopScreen.Draw(Color(CPAWRED) << "FPS: 999999999999999999", 10, 10);
	}

	void fps0(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		TopScreen.Draw(Color(CPAWRED) << "FPS:  0", 10, 10);
		Process::Write32(fps0Code, hundert);
	}

	void fpsM10(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		TopScreen.Draw(Color(CPAWRED) << "FPS: -10", 10, 10);
	}

	void fpsSleepy(MenuEntry *entry) {
		const Screen& TopScreen = OSD::GetTopScreen();
		TopScreen.Draw(Color(CPAWRED) << "FPS: SleepyFish", 10, 10);
	}

	//OSD stuff ----------------------------------------------/
	void onlineGhost(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(onGhost, 0x700049);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(onGhost, 0x700049);
			OSD::Notify("Online Ghost : Off");
		}
	}

	void CreditChange(MenuEntry *entry) {
		u32 val = 0;
		kbCredit->GetMessage() = " Enter Credits :";
		kbCredit->IsHexadecimal(false);
		kbCredit->SetMaxLength(8);
		if (kbCredit->Open(val, val) == 0)
		{
			if (val > 0xFFFFFFD2) val = 0xFFFFFFD2;
			Process::Write32(credit, val);
		}
	}

	void autoShoot(MenuEntry *entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Milliseconds(200));
			Process::Write32(autoShootOnCode, 0x0A000001);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(autoShootOnCode, 0x0A000004);
			OSD::Notify("Auto shoot : Off");
		}
	}

	void disSpammShoot(MenuEntry *entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Milliseconds(200));
			Process::Write32(autoShootOnCode, 0x0A000000);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(autoShootOnCode, 0x0A000004);
			OSD::Notify("Dis Spamm shoot : Off");
		}
	}

	void delWeapon(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(delWeaponCode, 0xE3A03000);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(delWeaponCode, 0xE3A03002);
			OSD::Notify("Delete weapon : Off");
		}
	}

	void noRecoil(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(noRecoilCode, 0xE1821200);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(noRecoilCode, 0xE0821201);
			OSD::Notify("No Recoil : Off");
		}
	}

	void speedHack(MenuEntry * entry) {
		if (entry->WasJustActivated()) { //on
			Sleep(Milliseconds(200));
			Process::Write32(speedHackCode, 0x45F00000);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(speedHackCode, 0x45800000);
			OSD::Notify("SpeedHack : Off");
		}
	}

	void speedModifier(MenuEntry* entry) {
		u32 val = 0;
		speedKb->GetMessage() = " Enter Speed :";
		speedKb->IsHexadecimal(false);
		speedKb->SetMaxLength(1);
		if (speedKb->Open(val, val) == 0)
		{
			if (val = 1) val = 0x45800000;
			if (val = 2) val = 0x45900000;
			if (val = 3) val = 0x45A00000;
			if (val = 4) val = 0x45B00000;
			if (val = 5) val = 0x45C00000;
			if (val = 6) val = 0x45D00000;
			if (val = 7) val = 0x45E00000;
			if (val = 8) val = 0x45F00000;
			if (val = 9) val = 0x45F00000;
			Process::Write32(speedHackCode, val);
		}
	}

	void ModAnima1(MenuEntry *entry) {
		u32 val = 0;
		kbAnima1->GetMessage() = " Enter Animation 1 :";
		kbAnima1->IsHexadecimal(false);
		kbAnima1->SetMaxLength(4);
		if (kbAnima1->Open(val, val) == 0)
		{
		if (val > 0xFFFFFFFF) val = 0xFFF;
		Process::Write32(Anim1, val);
		}
	}

	void ModAnima2(MenuEntry *entry) {
		u32 val = 0;
		kbAnima2->GetMessage() = " Enter Animation 2 :";
		kbAnima2->IsHexadecimal(false);
		kbAnima2->SetMaxLength(4);
		if (kbAnima2->Open(val, val) == 0)
		{
		if (val > 0xFFFFFFFF) val = 0xFFF;
		Process::Write32(Anim2, val);
		}
	}

	void memzVisual(MenuEntry *entry) {
		if (entry->IsActivated()) { //on
			Process::Write32(memzCode, 0x1A000004);
		}
		else if (!entry->WasJustActivated()) { //off
			Process::Write32(memzCode, 0x0A000004);
			OSD::Notify("Memz Visuals : Off");
		}
	}
	void realifeSensi(MenuEntry *entry) {
	  if (entry->WasJustActivated()) { //on
			Process::Write32(irlsens, 0x4EFFFFFF);
	  }
	  else if (!entry->IsActivated()) { //off
		Process::Write32(irlsens, 0x4E000000);
		OSD::Notify("Realife Sens : Off");
	  }
	}

	void onlyRender1room(MenuEntry* entry) {
		if (entry->WasJustActivated()) { //on
			Process::Write32(onlyRender1, 0x0AFFFFF9);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(onlyRender1, 0x1AFFFFF9);
			OSD::Notify("Only Render 1 Room : Off");
		}
	}

	void smoothRun(MenuEntry* entry) {
		if (entry->WasJustActivated()) { //on
			Process::Write32(smoothRunCode, 0x0A000040);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(smoothRunCode, camDefaultCode);
			OSD::Notify("Smooth Run: Off");
		}
	}

	void smoothWalk(MenuEntry* entry) {
		if (entry->WasJustActivated()) { //on
			Process::Write32(smoothWalkCode, 0xE1D00000);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(smoothWalkCode, camDefaultCode);
			OSD::Notify("Smooth Walk : Off");
		}
	}

	void buncyRunCama(MenuEntry* entry) {
		if (entry->WasJustActivated()) { //on
			Process::Write32(smoothRunCode, 0x1AD00052);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(smoothRunCode, 0x0AD00052);
			OSD::Notify("Buncy Run : Off");
		}
	}

	void wierdCama(MenuEntry* entry) {
		if (entry->WasJustActivated()) { //on
			Process::Write32(smoothRunCode, 0x1AD00051);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(smoothRunCode, 0x0AD00051);
			OSD::Notify("Wierd Camera : Off");
		}
	}

	void upsideDownCama(MenuEntry* entry) {
		if (entry->WasJustActivated()) { //on
			Process::Write32(smoothWalkCode, 0xE1F00427);
		}
		else if (!entry->IsActivated()) { //off
			Process::Write32(smoothWalkCode, camDefaultCode);
			OSD::Notify("Wierd Camera : Off");
		}
	}

	void CoordMod(MenuEntry* entry) {
		Process::Write32(0xDD000000, 0x11);
		Process::Write32(0x6034C5CC, 0);
		Process::Write32(0xB034C5CC, 0);
		Process::Write32(0xF1000118, 0x500);
		Process::Write32(0xDD000000, 0x21);
		Process::Write32(0x6034C5CC, 0);
		Process::Write32(0xB034C5CC, 0);
		Process::Write32(0xF1000118, 0xFFFFFB00);
		Process::Write32(0xDD000000, 0x41);
		Process::Write32(0x6034C5CC, 0);
		Process::Write32(0xB034C5CC, 0);
		Process::Write32(0xF1000110, 0xB00);
		Process::Write32(0xDD000000, 0x81);
		Process::Write32(0x6034C5CC, 0);
		Process::Write32(0xB034C5CC, 0);
		Process::Write32(0xF1000110, 0xFFFFFB00);
	}

	void NoClipSma(MenuEntry* entry) {
		Process::Write32(0x6034C5CC, 0);
		Process::Write32(0xB034C5CC, 0);
		Process::Write32(0xF1000114, 0x150);
	}

	void NoClipBig(MenuEntry* entry) {
		Process::Write32(0x6034C5CC, 0);
		Process::Write32(0xB034C5CC, 0);
		Process::Write32(0xF1000114, 0x300);
	}

	void BotKill(MenuEntry* entry) {
		Process::Write32(BotCode1, 0);
	}

	void BotReset(MenuEntry* entry) {
		Process::Write32(BotCode2, 0x15C50013);
	}

	void BotNoDyx(MenuEntry* entry) {
		Process::Write32(BotCode2Rese, 0xE883FF00);
	}

	void BotNoClip(MenuEntry* entry) {
		Process::Write32(0xD3000000, 0);
		Process::Write32(BotNoClipCode, 0xE88305FF);
	}

	void BotSpeed(MenuEntry* entry) {
		Process::Write32(BotCodeSpeed, 0xE88302FF);
	}

	void NoWeaponSound(MenuEntry* entry) {
		Process::Write32(WeaponSoundCode, 0);
	}


}

/*
void (MenuEntry *entry) {
	if (entry->IsActivated()) { //on
		Process::Write32(, );
	}
	else if (!entry->WasJustActivated()) { //off
		Process::Write32(, );
		OSD::Notify(" : Off");
	}
}
*/