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

// Function prototypes for the threads that will execute system calls
DWORD WINAPI sysDir(LPVOID);
DWORD WINAPI sysHelp(LPVOID);
DWORD WINAPI sysVol(LPVOID);
DWORD WINAPI sysPath(LPVOID);
DWORD WINAPI sysTaskList(LPVOID);
DWORD WINAPI sysNotepad(LPVOID);
DWORD WINAPI sysEcho(LPVOID);
DWORD WINAPI sysColor(LPVOID);
DWORD WINAPI sysPing(LPVOID);

int main()
{

    cout << "Welcome to myShell. Type 'quit' to terminate. \n";


    DWORD ThreadID;
    HANDLE ThreadHandle;
    int Parameter;

    // List of commands: dir, help, vol, path, tasklist, notepad, echo, color, ping
    string quit = "quit",
   	 dir = "dir",
   	 help = "help",
   	 vol = "vol",
   	 path = "path",
   	 tasklist = "tasklist",
   	 notepad = "notepad",
   	 echo = "echo",
   	 color = "color",
   	 ping = "ping";

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
   	 else if (input == dir) {
   		 // CreateThread() function and arguments adapted from ch4 PowerPoint slides
   		 ThreadHandle = CreateThread(
   			 NULL, // Security attributes
   			 0, // Stack size
   			 sysDir, // Thread function
   			 NULL, // Parameter to thread function
   			 0, // Creation flags
   			 &ThreadID); // Thread identifier
   		 if (ThreadHandle != NULL) {
   			 WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
   			 cout << "Thread " << ThreadID << " closing." << endl;
   			 CloseHandle(ThreadHandle);
   		 }
   	 }
   	 else if (input == help) {
   		 ThreadHandle = CreateThread(
   			 NULL,
   			 0,
   			 sysHelp,
   			 NULL,
   			 0,
   			 &ThreadID);
   			 if (ThreadHandle != NULL) {
   				 WaitForSingleObject(ThreadHandle, INFINITE);
   				 cout << "Thread " << ThreadID << " closing." << endl;
   				 CloseHandle(ThreadHandle);
   		 }
   	 }
   	 else if (input == vol) {
   		 ThreadHandle = CreateThread(
   			 NULL,
   			 0,
   			 sysVol,
   			 NULL,
   			 0,
   			 &ThreadID);
   			 if (ThreadHandle != NULL) {
   				 WaitForSingleObject(ThreadHandle, INFINITE);
   				 cout << "Thread " << ThreadID << " closing." << endl;
   				 CloseHandle(ThreadHandle);
   			 }
   	 }
   	 else if (input == path) {
   		 ThreadHandle = CreateThread(
   			 NULL,
   			 0,
   			 sysPath,
   			 NULL,
   			 0,
   			 &ThreadID);
   			 if (ThreadHandle != NULL) {
   				 WaitForSingleObject(ThreadHandle, INFINITE);
   				 cout << "Thread " << ThreadID << " closing." << endl;
   				 CloseHandle(ThreadHandle);
   			 }
   	 }
   	 else if (input == tasklist) {
   		 ThreadHandle = CreateThread(
   			 NULL,
   			 0,
   			 sysTaskList,
   			 NULL,
   			 0,
   			 &ThreadID);
   			 if (ThreadHandle != NULL) {
   				 WaitForSingleObject(ThreadHandle, INFINITE);
   				 cout << "Thread " << ThreadID << " closing." << endl;
   				 CloseHandle(ThreadHandle);
   			 }
   	 }
   	 else if (input == notepad) {
   		 ThreadHandle = CreateThread(
   			 NULL,
   			 0,
   			 sysNotepad,
   			 NULL,
   			 0,
   			 &ThreadID);
   			 if (ThreadHandle != NULL) {
   				 WaitForSingleObject(ThreadHandle, INFINITE);
   				 cout << "Thread " << ThreadID << " closing." << endl;
   				 CloseHandle(ThreadHandle);
   			 }
   	 }
   	 // If user types echo with no arguments, print this message
   	 else if (input == echo) {
   		 cout << "ECHO is on." << endl;
   	 }
   	 else if (strstr (input, "echo ")) { // Substring string (strstr) checks char array "input" if it contains "echo".
   		 //    Assumes user enters echo followed by a space.
   		 input2 = &input[5]; // input2 starts at index 5 because "echo " is 5 characters
   		 ThreadHandle = CreateThread(
   			 NULL,
   			 0,
   			 sysEcho,
   			 NULL,
   			 0,
   			 &ThreadID);
   		 if (ThreadHandle != NULL) {
   			 WaitForSingleObject(ThreadHandle, INFINITE);
   			 cout << "Thread " << ThreadID << " closing." << endl;
   			 CloseHandle(ThreadHandle);
   		 }
   		 
   	 }
   	 else if (strstr(input, "color ")) {
   		 //input2 = &input[6];
   		 ThreadHandle = CreateThread(
   			 NULL,
   			 0,
   			 sysColor,
   			 NULL,
   			 0,
   			 &ThreadID);
   			 if (ThreadHandle != NULL) {
   				 WaitForSingleObject(ThreadHandle, INFINITE);
   				 cout << "Thread " << ThreadID << " closing." << endl;
   				 CloseHandle(ThreadHandle);
   			 }
   	 }
   	 else if (strstr(input, "ping ")) {
   		 ThreadHandle = CreateThread(
   			 NULL,
   			 0,
   			 sysPing,
   			 NULL,
   			 0,
   			 &ThreadID);
   			 if (ThreadHandle != NULL) {
   				 WaitForSingleObject(ThreadHandle, INFINITE);
   				 cout << "Thread " << ThreadID << " closing." << endl;
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

// Function definitions for the threads that will execute system calls
DWORD WINAPI sysDir(LPVOID Parameter)
{
    cout << "Thread successfully created." << endl;
    system("dir");
    return 0;
}
DWORD WINAPI sysHelp(LPVOID Parameter)
{
    cout << "Thread successfully created." << endl;
    system("help");
    return 0;
}
DWORD WINAPI sysVol(LPVOID Parameter)
{
    cout << "Thread successfully created." << endl;
    system("vol");
    return 0;
}
DWORD WINAPI sysPath(LPVOID Parameter)
{
    cout << "Thread successfully created." << endl;
    system("path");
    return 0;
}
DWORD WINAPI sysTaskList(LPVOID Parameter)
{
    cout << "Thread successfully created." << endl;
    system("tasklist");
    return 0;
}
DWORD WINAPI sysNotepad(LPVOID Parameter)
{
    cout << "Thread successfully created. Opening Notepad..." << endl;
    system("notepad");
    return 0;
}
DWORD WINAPI sysEcho(LPVOID Parameter)
{
    cout << "Thread successfully created." << endl;
    cout << input2 << endl << endl;
    return 0;
}
DWORD WINAPI sysColor(LPVOID Parameter)
{
    cout << "Thread successfully created." << endl;
    system(input);
    return 0;
}
DWORD WINAPI sysPing(LPVOID Parameter)
{
    cout << "Thread successfully created." << endl;
    system(input);
    return 0;
}

