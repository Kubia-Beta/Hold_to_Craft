///////////////////////////
// By:                 ///
// Kubia              ///
// 28 Feb. 2023      ///
///////////////////////

// First DLL I have made, followed instructions similar to https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170
// While also making sure it will be compatibile according to https://www.autohotkey.com/docs/v2/lib/DllCall.htm
// as well as https://www.autohotkey.com/docs/v2/Compat.htm 

#include "pch.h"




void __cdecl Keybinding () { //force __cdecl to ensure the .dll works with AHK v2, "thiscall" does not work with AHK v2

	std::string filename = "htcprefs.ini"; //name provided by the text
	std::ofstream outfile(filename); //open or create htcprefs.ini
	if (!outfile) { //something went wrong!
		std::cerr << "Error: could not open file " << filename << " ." << std::endl; //cerr is used to IMMEDIATELY display to console
		return;
	}
	std::string pauseKey, exitKey, noiseVal;


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
};