// myShell.cpp: Simple Command Line Interpreter

// Copyright (c) Jarrett Chien 19 September 2018

#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <thread>
#include <Windows.h>

using namespace std;

// Global variables for thread access
char input[100];
string input2;
// List of commands: dir, help, vol, path, tasklist, notepad, echo, color, ping
const string dir = "dir",
			quit = "quit",
			help = "help",
			vol = "vol",
			path = "path",
			tasklist = "tasklist",
			notepad = "notepad",
			echo = "echo",
			color = "color",
			ping = "ping";;

DWORD WINAPI systemCall(LPVOID Param) {
	if (input == dir) {
		system("dir");
	}
	else if (input == help) {
		system("help");
	}
	else if (input == vol) {
		system("vol");
	}
	else if (input == path) {
		system("path");
	}
	else if (input == tasklist) {
		system("tasklist");
	}
	else if (input == notepad) {
		cout << "Opening Notepad..." << endl;
		system("notepad");
	}
	else if (strstr(input, "echo ")) {
		cout << input2 << endl << endl;
	}
	else if (strstr(input, "color ")) {
		system(input);
	}
	else if (strstr(input, "ping ")) {
		system(input);
	}
	return 0;
}

int main()
{
	cout << "Welcome to myShell. Type 'quit' to terminate. \n";
	
	DWORD ThreadID;
	HANDLE ThreadHandle;
	char Parameter = *input;

	while (1) {
		cout << "Enter a command: ";
		fflush(stdout); // Flush the stream since input [100] is uninitialized
		fgets(input, 100, stdin);
		strtok(input, "\n");  // Removes the \n fgets reads in when user presses Enter
		cout << "COMMAND TYPED BY USER: " << input << endl;

		if (input == quit) {
			cout << "Exiting myShell.\n";
			break;
		}
		else if (input == dir || input == help || input == vol || input == path || input == tasklist || input == notepad) {
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL, // Security attributes
				0, // Stack size
				systemCall, // Thread function
				0, // Parameter to thread function
				0, // Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL) {
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		// If user types echo with no arguments, print this message
		else if (input == echo) {
			cout << "ECHO is on." << endl;
		}
		else if (strstr(input, "echo ")) { // Substring string (strstr) checks char array "input" if it contains "echo".
										   //    Assumes user enters echo followed by a space.
			input2 = &input[5]; // input2 starts at index 5 because "echo " is 5 characters
			ThreadHandle = CreateThread(
				NULL,
				0,
				systemCall,
				NULL,
				0,
				&ThreadID);
			if (ThreadHandle != NULL) {
				WaitForSingleObject(ThreadHandle, INFINITE);
				CloseHandle(ThreadHandle);
			}
		}
		else if (strstr(input, "color ")) {
			//input2 = &input[6];
			ThreadHandle = CreateThread(
				NULL,
				0,
				systemCall,
				NULL,
				0,
				&ThreadID);
			if (ThreadHandle != NULL) {
				WaitForSingleObject(ThreadHandle, INFINITE);
				CloseHandle(ThreadHandle);
			}
		}
		else if (strstr(input, "ping ")) {
			ThreadHandle = CreateThread(
				NULL,
				0,
				systemCall,
				NULL,
				0,
				&ThreadID);
			if (ThreadHandle != NULL) {
				WaitForSingleObject(ThreadHandle, INFINITE);
				CloseHandle(ThreadHandle);
			}
		}
		else {
			cout << input << " is not a valid command. \n\n";
		}
	}
	system("pause");
	return 0;
}
