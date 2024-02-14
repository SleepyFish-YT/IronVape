#include "cheats.hpp"
#include <ctr-led-brary.hpp>
#include <CTRPluginFramework.hpp>
#define Author SleepyFish
#define IV_name "IronVape by SleepyFish"
#define IV_info " A plugin for Ironfall Invasion (EUR)\n\nAuthor:\n- SleepyFish\n\n Helpers:\n- Foofoo_The_Guy: Function's\n- Lukas: Function's\n- PabloMK7: Function's"
#define IV_warn " CTRPF ignores new 3DS buttons\n if you want to fix this, enable :\n\n Rosalina> Misc> Start InputRedirection"

namespace CTRPluginFramework {

	void CreateDefaultSettings() {
		File::Create(settingstxt);
		File file(settingstxt);
		file.WriteLine("Color :: FFFFFFFF\n"
			"new3DS_Button_Message :: 1");
		file.Close();
		return;
	}

	const int* GetSettings() { //from vapecord
		if (!File::Exists(settingstxt)) { CreateDefaultSettings(); }
		fwkparser->Parse(settingstxt);
		static const int c_Custom[2] = {
		int(std::stoul(fwkparser->Get("Color"), 0, 16)),
		int(std::stoul(fwkparser->Get("new3DS_Button_Message"), 0, 16))
		};
		return c_Custom;
	}

	bool WrapFWK() { //from vapecord
		const int* c_fwk = GetSettings();
		SetFWK(settings, Color(c_fwk[0]));
		return 1;
	}

	// 1 = didnt show message 0 = showed message //
	int ShowMessage() {
		const int* c_fwk = GetSettings();
		if (c_fwk[1] == 1) {
			Sleep(Milliseconds(200));
			MessageBox(IV_warn)();
			return 1;
		}
		else return 0;
	}

	void StoreBatteryPercentage(float& percentage) { //from Vapecord
		u8 data[4];
		mcuHwcInit();
		MCUHWC_ReadRegister(0xA, data, 4);
		percentage = data[1] + data[2] / 256.0f;
		percentage = (u32)((percentage + 0.05f) * 10.0f) / 10.0f;
		mcuHwcExit();
	}

	void OnNewFrameCallback(Time ttime) { //from Vapecord
		const FwkSettings& settings = FwkSettings::Get();
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		time_t rawtime;
		struct tm* timeinfo;
		char timestamp[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timestamp, 80, "  %r   |   %F", timeinfo);
		float percentage = 0;
		StoreBatteryPercentage(percentage);
		int coordx = 30, coordy1 = 2, coordy2 = 216;
		TopScreen.DrawRect(coordx, coordy1, 340, 20, settings.BackgroundMainColor, true);
		TopScreen.DrawRect(coordx + 2, coordy1 + 2, 340 - 4, 20 - 2, settings.BackgroundBorderColor, false);
		TopScreen.DrawSysfont(timestamp, coordx + 5, coordy1 + 3, settings.MainTextColor);
		TopScreen.DrawSysfont(Utils::Format("|    %d%%", (u32)percentage), coordx+260, coordy1+3, settings.MainTextColor);
		TopScreen.Draw("sites.google.com/view/ironvape/start", coordx + 62, coordy2 + 8);
		BottomScreen.Draw("by VengeanceTeam", 20 + 100, 2 + 20);
		coordx = 20, coordy1 = 2, coordy2 = 216;
		BottomScreen.DrawRect(coordx, coordy1, 280, 20, settings.BackgroundMainColor, true);
		BottomScreen.DrawRect(coordx + 2, coordy1 + 2, 280 - 4, 20 - 2, settings.BackgroundBorderColor, false);
		BottomScreen.DrawSysfont(" -  Discord: discord.gg/KpgaCsZxSN  -", coordx + 2, coordy1 + 1);
	}

	std::string GetExceptionType(ERRF_ExceptionType& type) {
		switch (type) {
		case ERRF_ExceptionType::ERRF_EXCEPTION_PREFETCH_ABORT:
		return "- Prefetch Abort -";
		case ERRF_ExceptionType::ERRF_EXCEPTION_DATA_ABORT:
		return "- Data Abort -";
		case ERRF_ExceptionType::ERRF_EXCEPTION_UNDEFINED:
		return "- Undefined Instruction -";
		case ERRF_ExceptionType::ERRF_EXCEPTION_VFP:
		return "- VFP Exception -";
		}
		return "- Unknown Error -";
	}

	std::string StoreCrashData(ERRF_ExceptionInfo* excep, CpuRegisters* regs) {
		std::string str;
		str += ("IronVape Crash Handler\n\n\n");
		str += ("Exception Type: " + GetExceptionType(excep->type)) + "\n\n\n";
		std::string name = "";
		Process::GetName(name);
		str += ("Process  : " + name) + "\n";
		str += (Utils::Format("Title ID : %016llX", Process::GetTitleID())) + "\n\n\n";
		for (int i = 0; i < 13; ++i)
		str += (Utils::Format("R%02d   :   %08X", i, regs->r[i])) + "\n";
		str += "\n" + (Utils::Format("SP    :   %08X", regs->sp)) + "\n";
		str += (Utils::Format("LR    :   %08X", regs->lr)) + "\n";
		str += (Utils::Format("PC    :   %08X", regs->pc)) + "\n\n";
		str += (Utils::Format("CPSR  :   %08X", regs->cpsr)) + "\n";
		str += (Utils::Format("FPEXC :   %08X", excep->fpexc)) + "\n";
		str += (Utils::Format("FAR   :   %08X", excep->far)) + "\n\n";
		str += ("IronVape Crash Handler");
		return str;
	}

	std::vector<std::string> SplitCrashData(char* sentence) {
		std::vector<std::string> vec;
		char* token = strtok(sentence, "\n");
		while (token != nullptr) {
		vec.push_back(token);
		token = strtok(nullptr, "\n");
		}
		return vec;
	}

	int SaveCrashDump(const char* str) {
		File file;
		time_t rawtime;
		struct tm* timeinfo;
		char timestamp[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timestamp, 80, " [%F_%I-%M%p]", timeinfo);
		std::string filename = "Crashes/Crash Dump";
		filename += timestamp;
		filename += ".txt";
		if (Directory::IsExists("Crashes") == 0)
		Directory::Create("Crashes");
		File::Open(file, filename, File::Mode::WRITE | File::Mode::CREATE);
		file.Write(str, strlen(str));
		file.Flush();
		file.Close();
		return 1;
	}

	void StringVectorToString(std::string& Str, std::vector<std::string>& Vec, bool ClearVector = false) {
		for (const std::string& i : Vec)
		Str.append(i);
		if (ClearVector) Vec.clear();
	}

	Process::ExceptionCallbackState CustomExceptionHandler(ERRF_ExceptionInfo* excep, CpuRegisters* regs) { //from vapecord
		Sleep(Milliseconds(200));
		const Screen& TopScreen = OSD::GetTopScreen();
		const Screen& BottomScreen = OSD::GetBottomScreen();
		std::string datastr = StoreCrashData(excep, regs);
		const char* data = datastr.c_str();
		TopScreen.DrawRect(0, 0, 400, 240, Color::Black);
		TopScreen.DrawSysfont("Looks like your Game Crashed :(", 10, 10, Color::Red);
		TopScreen.DrawSysfont("Press \uE000 Save Crash file : Soon", 10, 65, Color::White);
		TopScreen.DrawSysfont("Press \uE001 to close Crash Handler", 10, 35, Color::White);
		TopScreen.DrawSysfont("Discord: discord.gg/KpgaCsZxSN", 10, 115, Color::White);
		TopScreen.Draw("           Thanks to: FooFooTheGuy, Lukas for Help <3", 10, 220, Color::Gray);
		BottomScreen.DrawRect(0, 0, 320, 240, Color::Black);
		char datachar[datastr.length() + 1];
		strcpy(datachar, datastr.c_str());
		std::vector<std::string> vec = SplitCrashData(datachar);
		BottomScreen.Draw(vec[0], 15, 15, Color::Red);				//title
		BottomScreen.Draw(vec[1], 15, 30, Color::Red);				//Exception Type
		BottomScreen.Draw(vec[2], 15, 45);							//Process Name
		BottomScreen.Draw(vec[3], 15, 55);							//Title ID
		for (int i = 4; i < 18; i += 2)
		BottomScreen.Draw(vec[i], 15, 75 + (10 * ((i / 2) - 2)));
		for (int i = 5; i < 16; i += 2)
		BottomScreen.Draw(vec[i], 135, 75 + (10 * ((i / 2) - 2)));
		BottomScreen.Draw(vec[18], 15, 75 + (10 * 6) + 10);			//LR
		BottomScreen.Draw(vec[20], 15, 75 + (10 * 6) + 20);			//CPSR
		BottomScreen.Draw(vec[22], 15, 75 + (10 * 6) + 30);			//FAR
		BottomScreen.Draw(vec[17], 135, 75 + (10 * 5) + 10);		//SP
		BottomScreen.Draw(vec[19], 135, 75 + (10 * 5) + 20);		//PC
		BottomScreen.Draw(vec[21], 135, 75 + (10 * 5) + 30);		//FPEXC
		BottomScreen.Draw(vec[23], 15, 205, Color::Red);			//title2
		OSD::SwapBuffers();
		Controller::Update();
		if (Controller::IsKeyPressed(Key::B))
		return Process::ExceptionCallbackState::EXCB_RETURN_HOME;
		return Process::ExceptionCallbackState::EXCB_LOOP;
		if (Controller::IsKeyPressed(Key::A)) {
			std::string crashstr = "";
			StringVectorToString(crashstr, vec, true);
			SaveCrashDump(crashstr.c_str());
			return Process::ExceptionCallbackState::EXCB_LOOP;
		}
	}

	int main() {
		#define Red	0x88001BFF
		settings.MainTextColor = Red;
		settings.MenuSelectedItemColor = Red;
		settings.MenuUnselectedItemColor = Red;
		settings.BackgroundBorderColor = Red;
		settings.CustomKeyboard.BackgroundBorder = Red;
		settings.CustomKeyboard.KeyTextPressed = Red;
		settings.Keyboard.KeyText = Color::Green;
		settings.Keyboard.KeyTextPressed = Color::Green;
		settings.Keyboard.Input = Color::Green;
		settings.BackgroundMainColor = Color::Black;
		settings.BackgroundSecondaryColor = Color::Black;
		settings.Keyboard.Background = Color::Black;
		settings.Keyboard.KeyBackground = Color::Black;
		settings.Keyboard.KeyBackgroundPressed = Color::DimGrey;
		settings.CustomKeyboard.BackgroundMain = Color::Black;
		settings.CustomKeyboard.BackgroundSecondary = Color::Black;
		settings.CustomKeyboard.KeyBackground = Color::Black;
		settings.CustomKeyboard.KeyBackgroundPressed = Color::Black;
		settings.CustomKeyboard.KeyText = Color::Green;
		settings.CustomKeyboard.ScrollBarBackground = Color::Black;
		//---
		if (Process::GetTitleID() == 0x000400000015B100) {
			Sleep(Milliseconds(200));
			WrapFWK();
			Sleep(Milliseconds(200));
			ShowMessage();
			Sleep(Milliseconds(200));
			PluginMenu* menu = new PluginMenu(Color(0x88001BFF) << IV_name, 2, 3, 0, Color(0x88001BFF) << IV_info, 1);
			menu->SynchronizeWithFrame(true);
			menu->ShowWelcomeMessage(false);
			const Screen& TopScreen = OSD::GetTopScreen();
			const Screen& BottomScreen = OSD::GetBottomScreen();
			Sleep(Milliseconds(200));
			LED::PlayLEDPattern(LED::GeneratePattern(LED_Color(0xFF, 0xFF, 0xFF), LED_PatType::WAVE_DESC, 4, 0, 0x10, 0, 2.0 / 3, 1.0 / 3));
			Sleep(Seconds(8));
			OSD::Notify(Color(0x88001BFF) << "IronVape Ready!");
			LED::StopLEDPattern();
			OSD::Notify(Color(0x88001BFF) << "Plugin Ver 2.3");
			Sleep(Milliseconds(200));
			InitMenu(menu);
			menu->OnNewFrame = OnNewFrameCallback;
			Process::exceptionCallback = CustomExceptionHandler;
			menu->Run();
			Sleep(Milliseconds(500));
			delete menu;
			return 0;
		} else {
			Sleep(Seconds(5));
			MessageBox(Color(0x88001BFF) << "Error 505 : Game not supported!\n IronVape is for Ironfall(EUR)\n\n\nReturning to the home menu...\n\n  - by SleepyFish")();
			Sleep(Milliseconds(200));
			Process::ReturnToHomeMenu();
		}
		return 0;
	}
}