// Creator: Ariel G.
// NOTE: The version here is not completed, so code format (since A.G. is the only one working on the project) may be hard to understand; if others would like to use some of the code base, I will be fine to clean up the code
// 

#define WINVER 0x0500
#define WIN32_LEAN_AND_MEAN //remove the unneeded

#include <cstdlib>
#include <windows.h>
#include <iostream>
#include <MMSystem.h> // sounds come from mm lib
#include <String>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <exception>

std::string nameOfFile = "";

auto mdown = MOUSEEVENTF_LEFTDOWN;
auto mup = MOUSEEVENTF_LEFTDOWN;

HWND currentWindow;

bool pause = FALSE;

unsigned long int noppr = 0; // number of presses per rotation

int mousePosCount = 0; // positions mouse had stored
int y = 0; // handler for where I am in replicating key presses

std::string keyPArray[200] = {};//array of key's that were pressed, store like this to allow keycodes for non character and character

std::string temp;
std::string te = "te"; // restart or not

float delayTimerOfPress[200] = {}; // delay of each round of pressing

char typeOfMouseCheck; //left or right mouse
char windowReClick = 'r'; //restart window click
char mouseOrKeyboard = 'm';

POINT cordnate[200] = {}; // screen cordinates


int fileSaveM() { // mouse version of file save
	/*
null --> null

saves to file...
	*/

	std::ofstream fileSave; // make file loader

	fileSave.open(nameOfFile); // make file person wants (its seperate for my sanity, since I dont worry about the efficency with the console only app
	//fileSave.open(nameOfFile, std::ofstream::out | std::ofstream::trunc); // clear in case it was already used for cleanleness

	fileSave << mousePosCount << "\n"; // add number of mouse presses to run through

	for (int i = 0; i < 200; i++) { //for loop to save keys in txt

		if (cordnate[i].x == NULL){
			i = 200;
		} 

		else {
			fileSave << int(cordnate[i].x) << "\n" << int(cordnate[i].y) << "\n" << int(delayTimerOfPress[i]) << "\n"; // save files one by one, x,y,x,y pattern
		}
	}

	fileSave.close(); // end file save

	return 0;

}

int fileLoadM() { // mouse version of file load
	/*
	null --> null

	loads from file...
	*/

	bool first = TRUE;

	bool newDelay = FALSE;

	int xORy = 0; // which part of the file am I loading regulator
	int linecountI = 0; //line number I have set to string already

	std::ifstream fileRead; // read

	std::string linecountS; // string of file read, results in cleaner code, I realized a proformance hit when not macroing does not matter, so rather make the code easy to read


	std::cout << "If you want to enter new delay values click r, else click n\n\n";

	windowReClick = _getch();

	if (windowReClick == 'r') { // make a new delay in between each click

		newDelay = TRUE;

	}


	fileRead.open(nameOfFile); // open the reader

	while (std::getline(fileRead, linecountS)) { // add line by line into cordnates for mouse pos

		if (first == TRUE) {

			mousePosCount = stof(linecountS);

			first = FALSE;
		}

		else if (xORy == 0){

			xORy +=1;
			cordnate[linecountI].x = stof(linecountS); // add to mouse pont var
		
		}
		else if (xORy == 1){

			xORy +=1;
			cordnate[linecountI].y = stof(linecountS); // add to mouse var

		}
		else if (xORy == 2) {

			xORy = 0;

			if (newDelay == FALSE) {
				delayTimerOfPress[linecountI] = stof(linecountS); // add to mouse var
			}
			
			else {

				std::cout << "Enter the new delay and then click enter (use only numbers, but 0.1 - IE decimals - are allowed\n\n";
				std::cout << delayTimerOfPress[linecountI];

			}
			
			linecountI += 1; // line that is added already

		}
				
		
	}
	
	return 0;

}



int fileSave() {
	/*
null --> null

saves to file...
	*/

	std::ofstream fileSave; // make file loader

	fileSave.open(nameOfFile); // make file person wants (its seperate for my sanity, since I dont worry about the efficency with the console only app
	//fileSave.open(nameOfFile, std::ofstream::out | std::ofstream::trunc); // clear in case it was already used for cleanleness

	for (int i = 0; i < keyPArray->size(); i++) { //for loop to save keys in txt
	
		fileSave << keyPArray[i] + "\n"; // saves files
		
	}

	fileSave.close(); // end file save

	return 0;
	
}

int fileLoad() {
	/*
	null --> null
	
	loads from file...
	*/

	std::ifstream fileRead; // read

	std::string linecountS; // string of file read, results in cleaner code, I realized a proformance hit when not macroing does not matter, so rather make the code easy to read
	
	int linecountI = 0; //line I have set to string already

	fileRead.open(nameOfFile); // open the reader
	
	while (std::getline(fileRead, linecountS)){ // add line by line into keyPArray

		keyPArray[linecountI] = linecountS; // add lines

		linecountI += 1; // line that is added already

	}

	return 0;

}

std::string keyCodet(char key) { // translates key codes

	std::string hexcode;
	/*
	char --> string

	gets key to switch case to keycode
	*/

	switch (key) {

	case 'a':
		hexcode = "0x41";
		break;
	case 'b':
		hexcode = "0x42";
		break;
	case 'c':
		hexcode = "0x43";
		break;
	case 'd':
		hexcode = "0x44";
		break;
	case 'e':
		hexcode = "0x45";
		break;
	case 'f':
		hexcode = "0x46";
		break;
	case 'g':
		hexcode = "0x47";
		break;
	case 'h':
		hexcode = "0x48";
		break;
	case 'i':
		hexcode = "0x49";
		break;
	case 'j':
		hexcode = "0x4A";
		break;
	case 'k':
		hexcode = "0x4B";
		break;
	case 'l':
		hexcode = "0x4C";
		break;
	case 'm':
		hexcode = "0x4D";
		break;
	case 'n':
		hexcode = "0x4E";
		break;
	case 'o':
		hexcode = "0x4F";
		break;
	case 'p':
		hexcode = "0x50";
		break;
	case 'q':
		hexcode = "0x51";
		break;
	case 'r':
		hexcode = "0x52";
		break;
	case 's':
		hexcode = "0x53";
		break;
	case 't':
		hexcode = "0x54";
		break;
	case 'u':
		hexcode = "0x55";
		break;
	case 'v':
		hexcode = "0x56";
		break;
	case 'w':
		hexcode = "0x57";
		break;
	case 'x':
		hexcode = "0x58";
		break;
	case 'y':
		hexcode = "0x59";
		break;
	case 'z':
		hexcode = "0x5A";
		break;
	case '0':
		hexcode = "0x30";
		break;
	case '1':
		hexcode = "0x31";
		break;
	case '2':
		hexcode = "0x32";
		break;
	case '3':
		hexcode = "0x33";
		break;
	case '4':
		hexcode = "0x34";
		break;
	case '5':
		hexcode = "0x35";
		break;
	case '6':
		hexcode = "0x36";
		break;
	case '7':
		hexcode = "0x37";
		break;
	case '8':
		hexcode = "0x38";
		break;
	case '9':
		hexcode = "0x39";
		break;
	}


	return hexcode; // funny how this took like 2 min, not long at all
}



int keyAutoClicker() {

	/*
	null --> null    note: the return ints are just for syntax

	goal is to loop until told not to, by auto clicking (key auto clicker variant)

	works by getting inputed keycode to repeat it
	*/
	

	while (te == "te") {

		while (windowReClick == 'r') {
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n IF you see no new text click enter to load it      ALSO stop the auto clicker with holding esc for the length of your delay set \n\n";
			std::cout << "left click the window you want to auto clicker on - wait 3-5 seconds with the window in the foreground until the windows beep \n\n";

			Sleep(5000);

			currentWindow = (GetForegroundWindow()); // check window

			PlaySound(TEXT("SystemStart"), NULL, NULL);

			std::cout << "if you want to reclick the window; click 'r', else, just click 'e' \n";
			windowReClick = _getch();
		}

		windowReClick = 'r';

		
		

		std::cout << "to turn on file loader, click l, else, click n to continue\n";

		if (_getch() == 'l') { // file loader if

			std::cout << "Enter file you would like to load (format: MyFileName.txt) \n";

			std::cin >> nameOfFile; // get file name

			fileLoad();
				
			windowReClick = 'a';
		}

		while (windowReClick == 'r') { 

			std::cout << "If you want to press a non character key (shift, ctrl, tab, bk space, enter, del, or alt click 'a')   -   - if you want a character key, click 'b' \n\n";
			windowReClick = _getch();

			if (windowReClick == 'a') {
				std::cout << "press down on one non character key and hold until the beep -        - SUPPORTED KEYS (shift, ctrl, tab, bk space, enter, del, or alt click 'a') -> if you want a missing key just contact me and I will add it\n\n";
				_getch();

				Sleep(3000);

				// get keys: funny how its more efficent to do this than sift through getkeyboardstate
				if (GetAsyncKeyState(VK_LSHIFT)) { // I have diffrent shifts and crtl's since if macro'ing in programs and games they can be diffrent
					temp = "0xA0";

					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}
				else if (GetAsyncKeyState(VK_RSHIFT)) {
					temp = "0xA1";

					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}
				else if (GetAsyncKeyState(VK_TAB)) {
					temp = "0x09";

					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}
				else if (GetAsyncKeyState(VK_BACK)) {
					temp = "0x08";

					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}
				else if (GetAsyncKeyState(VK_RETURN)) {
					temp = "0x0D";

					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}
				else if (GetAsyncKeyState(VK_LCONTROL)) {
					temp = "0xA2";

					keyPArray[y] = temp; // key array gets values of keyboard state         

					y += 1;
				}
				else if (GetAsyncKeyState(VK_RCONTROL)) {
					temp = "0xA3";


					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}
				else if (GetAsyncKeyState(VK_DELETE)) {
					temp = "0x2E";

					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}
				else if (GetAsyncKeyState(VK_LMENU)) {
					temp = "0xA4";

					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}
				else if (GetAsyncKeyState(VK_RMENU)) {
					temp = "0xA5";

					keyPArray[y] = temp; // key array gets values of keyboard state

					y += 1;
				}

				std::cout << "the key(s) accepted is: \n" << temp << "\n"; // tell you your key

				PlaySound(TEXT("SystemStart"), NULL, NULL);
			}
			else {

				std::cout << "The next key(s) you press will be the automated key ('esc' does not work well, since its the pause key) -   - the beep means it was sucssesful \n\n";

				temp = keyCodet(char(_getch()));

				keyPArray[y] = temp; // key array gets values of keyboard state

				

				PlaySound(TEXT("SystemStart"), NULL, NULL);

				std::cout << "the key(s) accepted is: \n" << temp << "\n\n"; // tell you your key

				std::cout << "Enter delay until key press rotation (in seconds) - - click enter after inputed \n\n";
				std::cin >> delayTimerOfPress[y];
				delayTimerOfPress[y] *= 1000;

				y += 1;
			}
			std::cout << "click r to add another key (else click e)\n\n";
			windowReClick = _getch(); // check for r or not to restart key check


		}
	

		std::cout << "Enter 's' if you want to save the file contents for later use, else click n\n\n";

		if (_getch() == 's') { // "Power Rangers GO!" file activated 

			std::cout << "Enter name of file you would like (only use a-z,and '_'  : other-wise errors may be encountered), also click enter after the name is entered -> format: myName.txt\n\n";
			std::cin >> nameOfFile; // writing down the same of the file

			fileSave(); //saving file

		}

		
		
		std::cout << "Enter number of key press(es) - - click enter after inputed \n\n";
		std::cin >> noppr;
		
		INPUT ip; // made mouse input'er

		ip.type = INPUT_KEYBOARD; // define mi as mouse
		ip.ki.time = 0; // ignore simulate time stamp
		ip.ki.dwExtraInfo = 0; // ignore extra info dump
		ip.ki.dwFlags = 0;

		SendInput(1, &ip, sizeof(INPUT));


		while (GetForegroundWindow() != currentWindow) { // wait until you enter window to start macro

		}

		for (int i = 0; i < noppr; i++) { // press multipule timer per rotation

			Sleep(delayTimerOfPress[i]);

			if (GetForegroundWindow() == currentWindow) {

				for (int i = 0; i < (keyPArray->size()); i++) { // press key up
					
					DWORD keywordHEX = std::strtoul(keyPArray[i].c_str(), NULL, 16);
					
					ip.ki.wVk = keywordHEX;
					ip.mi.dwFlags = KEYEVENTF_KEYUP; // simulates as up click so I do not simulate hold

					SendInput(1, &ip, sizeof(INPUT));

					if (GetKeyState(VK_ESCAPE) & 0x8000) { // stop auto

						pause = TRUE;

						Sleep(1000); // delay to not have the pause to be true to false very fast

					}

					while (pause == TRUE) {

						if (GetKeyState(VK_ESCAPE) & 0x8000) { // stop auto

							pause = FALSE;

						}
					}

				}

			}

		}

		std::cout << "Enter 't' if you want to continue \n\n";
		te = _getch();

		if (te != te) {
			abort();
		}

	}


	return 0;
}
int mouseAutoClicker() {
	LPPOINT pre = (LPPOINT)malloc(sizeof(LPPOINT));// pre pos
	
	te = "te";

		while (te == "te") {

			windowReClick = 'r'; // fix window loader to be right value to continue
		
		while (windowReClick == 'r') {
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n IF you see no new text click enter to load it      ALSO stop the auto clicker with holding esc for the length of your delay set \n\n";
			std::cout << "left click the window you want to auto clicker on - wait 3-5 seconds with the window in the foreground until the windows beep\n\n";

			Sleep(5000);

			currentWindow = (GetForegroundWindow()); // save foreground window

			PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS);

			std::cout << "if you want to reclick the window click 'r', else, just click 'e'\n\n";
			windowReClick = _getch();
		}

		std::cout << "Enter r for if you want right click, or l for left click, else it will automatically do left click -  - click enter after you input\n\n";
		typeOfMouseCheck = _getch();
		if (typeOfMouseCheck == 'l') {
			mdown = MOUSEEVENTF_LEFTDOWN;
			mup = MOUSEEVENTF_LEFTUP;
		}
		else {
			mdown = MOUSEEVENTF_RIGHTDOWN;
			mup = MOUSEEVENTF_RIGHTUP;
		}

		windowReClick = 'r'; // to start the key selector
		
		std::cout << "If you want to load cordinates: click l, else click (n) \n\n";
		
		windowReClick = _getch();

		if (windowReClick == 'l') { // want to load file*

			std::cout << "Enter the file name to load (must end with txt --> FileName.txt)   once entered click enter to submit\n\n";
			std::cin >> nameOfFile;

			fileLoadM();

			windowReClick = 'r';
		}
		else { // do not want to load file*

			windowReClick = 'r';

			while (windowReClick == 'r') {
				char redo = 'r';

				while (redo = 'r') {

					std::cout << "Now I want you to chose your cursor macro positions, move your mouse to the position wanted, then click any key (a-z) to record the spot (all while the program is in the foreground)\n\n";

					_getch(); // the wait for key

					GetCursorPos(&cordnate[mousePosCount]); // mouse pos "getter"

					PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS); // feed back

					std::cout << "To Test the mouse position click 't', by clicking t your mouse pos will teleport to the clicked position: if you want to skip this step click any other key\n\n";

					windowReClick = _getch();

					if (windowReClick == 't') {

						SetCursorPos(cordnate[mousePosCount].x, cordnate[mousePosCount].y);
						redo = 'r';
					}
					else {

						redo = 'g';

					}

				
				}

				std::cout << "Enter delay until the mouse press's down during the macro (in seconds) - - click enter after inputed -    -  0.2, 0.002 seconds and other decimals of a second are allowed \n\n";
				std::cin >> delayTimerOfPress[mousePosCount];

				delayTimerOfPress[mousePosCount] *= 1000;

				mousePosCount += 1; // keep track of mouse pos's added

				std::cout << "If you want to get another position click r, else, click e\n\n";
				windowReClick = _getch(); // chose to get another pos or not
				

			}

			std::cout << "If you want to save the cordinates: click s, else click (n) \n\n";
			windowReClick = _getch();

			if (windowReClick == 's') {

				std::cout << "Enter the file name (must end with txt --> FileName.txt)   once entered click enter to submit\n\n";
				std::cin >> nameOfFile;

				fileSaveM();

			}
		}

		

		std::cout << "Enter number of mouse press rotations - - click enter after inputed\n\n";
		std::cin >> noppr;

		std::cout << "If you want protection against auto clicker detectors, if you click 'p' and enter, you will turn on macro protection (it will cause each mouse click to be +- 5 pixels from one another)\n\n";
		std::cin >> windowReClick;

		INPUT ip; // made mouse input'er

		ip.type = INPUT_MOUSE; // define mi as mouse
		ip.mi.time = 0; // ignore simulate time stamp
		ip.mi.dwExtraInfo = 0; // ignore extra info dump
		ip.mi.dwFlags = 0;

		SendInput(1, &ip, sizeof(INPUT));
		

		while (GetForegroundWindow() != currentWindow) { // wait until you enter window to start macro

		}

		for (int a = 0; a < noppr; a++) {
			for (int i = 0; i < mousePosCount; i++) { // press multipul timer per rotation
				
				int randOInt = (int(rand()%100/20)); // random mouse variation

				Sleep(delayTimerOfPress[i]);
				
				if (GetForegroundWindow() == currentWindow) {

					GetCursorPos(pre);

					if (windowReClick == 'p') {
						
						SetCursorPos(cordnate[i].x+ randOInt, cordnate[i].y+ randOInt); // set cursor pos to be correct
						Sleep(100);
					}

					else {

						SetCursorPos(cordnate[i].x, cordnate[i].y);
						
					}

					

					ip.mi.dwFlags = mdown; // simulates as left click down

					SendInput(1, &ip, sizeof(INPUT));

					ip.mi.dwFlags = mup; // simulates as left click up so I do not simulate hold

					SendInput(1, &ip, sizeof(INPUT));

					SetCursorPos(pre->x,pre->y);

					if (GetKeyState(VK_ESCAPE) & 0x8000) { // stop auto
						pause = TRUE;
						Sleep(1000); // delay to not have the pause to be true to false very fast
					}

					while (pause == TRUE) {
						if (GetKeyState(VK_ESCAPE) & 0x8000) { // stop auto
							pause = FALSE;
						}
					}



				}

			}
		}

		abort();

	}


	return 0;
}

int main() {

	std::cout << "do you want key macro or mouse click macro? (click m for mouse, or k for key)\n\n\n";
	windowReClick = _getch(); // chose the macro

	if (windowReClick == 'k') {

		try {
			keyAutoClicker();
		}

		catch(std::runtime_error){

			throw("you chose a incorrect file most likley that was invalid");

		};

	}

	else if (windowReClick == 'm') {
	try{
		mouseAutoClicker(); // also I need to add a pattern if left and right clicks
	}

	catch (std::runtime_error) {

		throw("you chose a incorrect file most likley that was invalid");

	};
	}

	return 0;
}
