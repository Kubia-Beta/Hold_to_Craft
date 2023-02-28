///////////////////////////
// By:                 ///
// Kubia              ///
// 28 Feb. 2023      ///
///////////////////////

//this program runs an ini constructor if the ini does not exist, then launches an AutoHotkey executable which reads from the file.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <conio.h>
//the following #include are used only for one line to show the user that the program is successfully exiting:
#include <chrono>
#include <thread>


void pressAnyKeyToContinue() { //just a simple halt for the user that doesn't enter anything into our buffer
	std::cout << "\nPress any key to continue...";
	_getch();
	std::cout << std::endl;
}

int InputValidation() {
	int input = -1; //initialized at -1 in case of user error

	while (true) { //always runs until we break; or return; out of it
		std::cout << "Enter your choice: ";
		std::cin >> input;
		if (!std::cin) { //hello failbit, I see someone tried to put a non int again
			std::cin.clear();
			std::cin.ignore();
			std::cerr << "\nInvalid input. Enter input: ";
		} else if (input == 0 || input == 1) {
			return input;
		} else {
			std::cerr << "\nInvalid input. Enter input: ";
		}
	}
}

void Keybinding() { //one time setup, called only if .\lib\htcprefs.ini does not exist

	std::string filename = ".\\lib\\htcprefs.ini"; //The . represents the current dir, and the \\ is used to escape the backslash and create a valid path string
	std::ofstream outfile(filename); //open or create htcprefs.ini
	if (!outfile) { //something went wrong!
		std::cerr << "Error: could not open file htcprefs.ini. Make sure the program has access to the directory.\n";
		pressAnyKeyToContinue();
		return;
	}
	std::string pauseKey, exitKey, noiseVal;
	int navigator = 0; //initialize at 0 for safety.
	std::cout << "Use the Default keybinds [1] or Custom keybinds [0]?\n";
	navigator = InputValidation();
	if (navigator == 0) { //TODO: custom keybinds
		outfile << "Custom inputs not yet implemented.\n[controls]\npause=F1\nexit=F4";
		pressAnyKeyToContinue();
	}
	else if (navigator == 1) {
		outfile << "[controls]\npause=F1\nexit=F4";
		pressAnyKeyToContinue();
	}
	else {
		std::cerr << "\n\nSomething went wrong with the one time setup.\nAll defaults assumed.\nCustom controls can be manually entered into \\lib\\htcprefs.ini.\n";
		outfile << "Unexpected error on file creation process. Defaults assumed.\n[controls]\npause=F1\nexit=F4\n[sound]\nnoise=0";
		return;
	}
	navigator = 0; //reset
	std::cout << "Have the sound beeps OFF [1] or have them ON [0]?\n";
	navigator = InputValidation();
	if (navigator == 0) { //TODO: custom keybinds
		outfile << "\n[sound]\nnoise=0";
	}
	else if (navigator == 1) {
		outfile << "\n[sound]\nnoise=1";
	}
	else {
		std::cerr << "\n\nSomething went wrong with the one time setup.\nSound defaulted of off (0).\nSound option can be manually entered into \\lib\\htcprefs.ini.\n";
		outfile << "\n[sound]\nnoise=0";
		return;
	}


	//[sound]\nnoise=0
	outfile.close(); //always close the file at the end of one time setup
	std::cout << "One time setup finished. You can always modify the settings in \\lib\\htcprefs.ini.\n";
	pressAnyKeyToContinue();
	/*	open file as ini
			"\ndefault keybinds [0] or one button custom keybinds [1] ?"
			if 1{
			cin >> pauseKey
			cout << "Pause keybind set to: " << pausekey << endl;

			cin >> exitKey
			"Sound beeps off [0] or on [1]?"

			cin >> noiseVal
			} else {
			cout << "Using default keys F1 to pause and F4 to exit with sound OFF";
			pauseKey = "F1"
			exitKey = "F4"
			noiseVal = "0"; //1 is on 0 is off


			write to file:
			"[controls]"
			"pause = "pauseKey
			"exit = "exitKey

			"[sound]"
			"noise = "noiseVal

			close file */
}

int main() {
	std::cout << "///////////////////////////\n// By:                 ///\n// Kubia              ///\n// 28 Feb. 2023      ///\n///////////////////////\n\n";
	std::string filePath = ".\\lib\\htcprefs.ini";
	if (!std::filesystem::exists(filePath)) { //if it DOESNT exist
		std::cout << "Now running one time setup.\nAfter inputting your option, press [Enter] to continue.\nOptions will be displayed in braces, so option 0 is [0].\n";
		Keybinding();
	} else {
		std::cout << "htcprefs.ini detected.\n";
	}


	std::cout << "\nNow running 'Hold to Craft' for No Man's Sky.\nThis terminal will exit when 'Hold to Craft' has exited.\nClosing this terminal will not terminate 'Hold to Craft'.\n";
	system(".\\lib\\secondTest.ahk"); //launches the AHK responsible for the game interaction
	std::cout << "\n\n'Hold to Craft' exited. Now closing host program...";
	std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //user can see the closing message for 5 seconds.
	return 0;
}
