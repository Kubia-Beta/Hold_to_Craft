///////////////////////////
// By:                 ///
// Kubia              ///
// 08 Mar. 2023      ///
///////////////////////

//this program runs an ini constructor if the ini does not exist, then launches an AutoHotkey executable which reads from the file.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <conio.h>
#include <regex>
//the following #include are used only for one line to show the user that the program is successfully exiting:
#include <chrono>
#include <thread>


void pressAnyKeyToContinue() { //just a simple halt for the user that doesn't enter anything into our buffer
	std::cout << "\nPress any key to continue...";
	(void)_getch(); //assigns _getch() to embrace nothingness
	std::cout << std::endl;
}

int GetMenuChoice() {
	int input = -1; //initialized at -1 in case of user error

	while (true) { //always runs until we break; or return; out of it
		std::cout << "Enter your choice: ";
		std::cin >> input;
		if (!std::cin) { //hello failbit, I see someone tried to put a non int again
			std::cin.clear();
			std::cin.ignore();
			std::cerr << "\nInvalid input. ";
		} else if (input == 0 || input == 1) {
			return input; //this is the only way out, put in a 0 or 1
		} else {
			std::cerr << "\nInvalid input. ";
		}
	}
}

std::string ReplaceWords(const std::string& input) { //scans the input line and replaces the word with 
	std::regex altRegex("\\balt\\b\\s?", std::regex_constants::icase); //checks for the word "alt" as well as a whitespace after, ignoring case
	std::regex altGrRegex("\\baltgr\\b\\s?", std::regex_constants::icase); //checks for "altgr" for EU keyboards
	std::regex ctrlRegex("\\bctrl\\b\\s?", std::regex_constants::icase); //captures "ctrl"
	std::regex controlRegex("\\bcontrol\\b\\s?", std::regex_constants::icase); //captures "control" instead of "ctrl"
	std::regex shiftRegex("\\bshift\\b\\s?", std::regex_constants::icase); //captures "shift"
	#pragma warning(disable: 4129) //The compiler is not always right, so it thinks "<\^>!" is an escape sequence when it is a literal string of characters being written to a file (warning C4129)
	std::string output = std::regex_replace(input, altGrRegex, "<\^>!"); //begin constructing the output string, replacing any instance of altGr. If none are found, output = input
	#pragma warning(default: 4129) //Restores the warning on everything else so if it ACTUALLY is a problem, it will alert you, unlike the string above which does not have any issues
	output = std::regex_replace(output, altRegex, "!"); //continue for alt
	output = std::regex_replace(output, ctrlRegex, "^"); //continue for ctrl
	output = std::regex_replace(output, controlRegex, "^"); //as well as control
	output = std::regex_replace(output, shiftRegex, "+"); //then finally shift
	return output; //send the new string back
}

std::string ReplaceSymbols(const std::string& input) { //scans just like above, but the process is "reversed"
	std::regex altGrRegex("<\\^>!"); //checks for the AHK AltGr for EU keyboards
	std::regex altRegex("!"); //checks for "!", the next two check for "^" and "+" respectively
	std::regex ctrlRegex("\\^");
	std::regex shiftRegex("\\+");
	std::string output = std::regex_replace(input, altGrRegex, "altGr "); //again we construct our output string, replacing any "<\^>!" with "altGr ", if none are found, output = input
	output = std::regex_replace(output, altRegex, "alt ");
	output = std::regex_replace(output, ctrlRegex, "control ");
	output = std::regex_replace(output, shiftRegex, "shift ");
	return output; //returns the control characters plus whatever the hell the actual input key is
}


void ShowKeybinds(std::string filename) { //get the key values of pause and exit
	std::ifstream inFile(filename);
	std::string line;
	std::string pauseText, exitText;
	while (std::getline(inFile, line)) {
		if (line.find("pause=") != std::string::npos) {
			pauseText = line.substr(line.find("pause=") + 6); //print the rest of the line after going past "pause="
		}
		else if (line.find("exit=") != std::string::npos) { 
			exitText = line.substr(line.find("exit=") + 5); //print the rest of the line after going past "exit="
		}
	}
	inFile.close(); //we are done with the file, close it

	//tell the user what their binds are as read in plaintext
	std::cout << "\nPause keybind: " << ReplaceSymbols(pauseText) << std::endl;
	std::cout << "\nExit keybind: " << ReplaceSymbols(exitText) << std::endl;

}

void SetupPreferences() { //one time setup, called only if .\lib\htcprefs.ini does not exist

	std::string filename = ".\\lib\\htcprefs.ini"; //The . represents the current dir, and the \\ is used to escape the backslash and create a valid path string
	std::ofstream outfile(filename); //open or create htcprefs.ini
	if (!outfile) { //something went wrong!
		std::cerr << "Error: could not open file htcprefs.ini. Make sure the program has access to the directory.\n";
		pressAnyKeyToContinue();
		throw std::runtime_error("\nPlease extract the program into a folder that is not protected.\nThe folder you are using is protected."); //caught in the try block in main
		return;
	}
	std::string pauseKey, exitKey, noiseVal;
	int navigator = 0; //initialize at 0 for safety.
	std::cout << "Use the Default keybinds [1] or Custom keybinds [0]?\n";
	navigator = GetMenuChoice();
	if (navigator == 0) { //TODO: Input validation for whatever the user just threw into the line, because god knows what they are going to put in
		std::cout << "Custom Keybinds selected.\nWhen typing the keybind, check your spelling and leave a single space in between inputs.\n";
		std::cout << "-----Examples:\ncontrol shift a\nAlt pgdn\nControl Shift CapsLock\nALT F12\n----------";
		pressAnyKeyToContinue();
		std::cout << "\nPlease type the custom PAUSE key with no spaces: ";
		std::cin.clear();
		std::cin.ignore();
		std::getline(std::cin, pauseKey); //grab the line for pause
		pauseKey = ReplaceWords(pauseKey); //transform the input into something AHK can read
		std::cout << "\nPlease type the custom EXIT key with no spaces : ";
		std::getline(std::cin, exitKey);
		exitKey = ReplaceWords(exitKey);
		std::cout << "\nCreating \\lib\\htcprefs.ini. Remember that you can edit this at any time.\n";
		outfile << "[controls]\npause=" << pauseKey << "\nexit=" << exitKey;
		pressAnyKeyToContinue();
	}
	else if (navigator == 1) {
		std::cout << "Defaults selected.\n";
		outfile << "[controls]\npause=F1\nexit=F4";
		pressAnyKeyToContinue();
	}
	else {
		std::cerr << "\n\nSomething went wrong with the one time setup.\nAll defaults assumed.\nCustom controls can be manually entered into \\lib\\htcprefs.ini.\n";
		outfile << "[error]\nerrorlevel=2[controls]\npause=F1\nexit=F4\n[sound]\nnoise=0";
		return;
	}
	navigator = 0; //reset
	std::cout << "Have the sound beeps OFF [1] or have them ON [0]?\n";
	navigator = GetMenuChoice();
	if (navigator == 0) {
		outfile << "\n[sound]\nnoise=1";
	}
	else if (navigator == 1) {
		outfile << "\n[sound]\nnoise=0";
	}
	else {
		std::cerr << "\n\nSomething went wrong with the one time setup.\nSound defaulted of off (0).\nSound option can be manually entered into \\lib\\htcprefs.ini.\n";
		outfile << "\n[sound]\nnoise=0\n[error]\nerrorlevel=3";
		return;
	}

	outfile.close(); //always close the file at the end of one time setup
	std::cout << "One time setup finished. You can always modify the settings in \\lib\\htcprefs.ini.\n";
	pressAnyKeyToContinue();
}

void ClearFile(std::string file) { //function called only to clear htcprefs.ini
	std::ofstream ofs(file, std::ofstream::trunc); //call this only when something goes wrong with the file
	ofs.close();
}

bool VerifyIni(std::string file) { //reads the user file to make sure the settings are actually there
	using namespace std;
	ifstream infile(file);
	if (!infile) { //could not open htcprefs.ini
		cerr << "Error: could not open file htcprefs.ini. Make sure the program has access to the directory.\n";
		pressAnyKeyToContinue();
		throw std::runtime_error("\nPlease extract the program into a folder that is not protected.\nThe folder you are using is protected."); //caught in the try block in main
	}
	string line;

	bool isError = false; //just in case, normally not functional

	while (getline(infile, line)) { //while reading the ini line by line, check for each of the following
		if (line.find("pause=") != string::npos) { //does pause exist
			if (line.substr(line.find("pause=") + 6).empty()) { //if it does, does anything exist after it
				cerr << "\nError: nothing after 'pause=' in file " << file << " .\n"; //if not, we have a problem
				isError = true; //just in case this somehow doesn't end up with a return
				return true;
			}
		}
		else if (line.find("exit=") != string::npos) {
			if (line.substr(line.find("exit=") + 5).empty()) {
				cerr << "\nError: nothing after 'exit=' in file " << file << " .\n";
				isError = true;
				return true;
			}
		}
		else if (line.find("noise=") != string::npos) {
			if (line.substr(line.find("noise=") + 6).empty()) {
				cerr << "\nError: nothing after 'noise=' in file " << file << " .\n";
				isError = true;
				return true;
			}
		}
	}

	if (!isError){ //if there is NO error, i.e. isError is false
		return false; //send that there is no error
		}
	else { //if we caught an error in any of the above checks and it somehow exited normally
		return true; //tell the function call that it DID have an error
	}
}

int main() {
	std::cout << "///////////////////////////\n// By:                 ///\n// Kubia              ///\n// 08 Mar. 2023      ///\n///////////////////////\n\n";
	std::string filePath = ".\\lib\\htcprefs.ini";
	if (!std::filesystem::exists(filePath)) { //if it DOESNT exist, do our one time setup
		std::cout << "Now running one time setup.\nAfter inputting your option, press [Enter] to continue.\nOptions will be displayed in braces, so option 0 is [0].\n";
		try {
			pressAnyKeyToContinue();
			SetupPreferences(); //Launches the preference menu
		}
		catch (const std::exception& error) { //something went wrong, we cannot access the file
			std::cerr << error.what() << '\n'; //prints the error message
			pressAnyKeyToContinue();
			return 2; //exits
		}
	}//if the user already has the file, continue

	try { //now we check if the file HAS information
		bool integrity = VerifyIni(filePath); //false is working, true is fixable but not working
		if (integrity) { //we use this set of calls to deconstruct and reconstruct the file
			std::cerr << "\nError: " << "\nAn error was detected with your htcprefs.ini. Setup will now restart to fix the file.\n";
			pressAnyKeyToContinue();
			ClearFile(filePath);
			SetupPreferences();
		}
	}
	catch (const std::exception& error) { //something went wrong, we cannot access the file
		std::cerr << error.what() << '\n';
		pressAnyKeyToContinue();
		return 2;
	}
	//now that all the error checking is done:
	std::cout << "htcprefs.ini detected.\nYou can always modify the settings in \\lib\\htcprefs.ini.\n";


	std::cout << "\nNow running 'Hold to Craft' for No Man's Sky.\nThis terminal will exit when 'Hold to Craft' has exited.\nClosing this terminal will not terminate 'Hold to Craft'.\n";
	ShowKeybinds(filePath);
	system(".\\lib\\htc.exe"); //launches the AHK responsible for the game interaction
	std::cout << "\n\n'Hold to Craft' exited. Now closing host program...";
	std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //user can see the closing message for 5 seconds.
	return 0;
}