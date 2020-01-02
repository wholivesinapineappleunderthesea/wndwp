#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

#define BACKGROUND_ONE R"!(D:\wa\FDR_1944_Color_Portrait.jpg)!"
#define BACKGROUND_TWO R"!(D:\wa\arg.jpg)!"
#define SWITCH_KEY VK_SUBTRACT

int main(int argc, const char* argv[]) {
	if (RegisterHotKey(0, 0, MOD_NOREPEAT, SWITCH_KEY)) {
		std::cout << "Registered successfully" << std::endl;
	} else {
		std::cout << "Failed to register hotkey" << std::endl;
		return EXIT_FAILURE;
	}
	bool wpswitch = false;
	while (true) {
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0) {
			if (msg.message == WM_HOTKEY) {
				std::cout << "WM_HOTKEY received" << std::endl;
				wpswitch = !wpswitch;
				if (wpswitch) {
					SystemParametersInfo(SPI_SETDESKWALLPAPER, NULL, (void*)BACKGROUND_ONE, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
				} else {
					SystemParametersInfo(SPI_SETDESKWALLPAPER, NULL, (void*)BACKGROUND_TWO, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
				}
			}
		}
	}
	return EXIT_SUCCESS;
}
