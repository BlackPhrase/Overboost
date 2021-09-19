/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.
Copyright (C) 2019, 2021 BlackPhrase

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

/// @file

#include "Engine.hpp"
#include "engine/IEngine.h"

extern "C"
{
#include "qcommon/qcommon.h"

void Sys_CreateConsole();
void Sys_InitStreamThread();
void IN_Frame();
};

#ifdef _WIN32
#	include <direct.h>
#	include "qcommon/win/win_local.h"

#	define EXPORT [[dllexport]]
#elif defined(__unix__) || defined(__APPLE__)
#	define EXPORT [[visibility("default")]]
#endif

#define C_EXPORT extern "C" EXPORT

namespace
{

void Sys_PrintBinVersion(const char *name)
{
	const char *date = __DATE__;
	const char *time = __TIME__;
	const char *sep = "==============================================================";
	
	fprintf( stdout, "\n\n%s\n", sep );
#ifdef DEDICATED
	fprintf( stdout, "Overboost Engine Dedicated Server [%s %s]\n", date, time );
#else
	fprintf( stdout, "Overboost Engine [%s %s]\n", date, time );
#endif
	fprintf( stdout, " local install: %s\n", name );
	fprintf( stdout, "%s\n\n", sep );
};

void Sys_ParseArgs(int argc, char *argv[])
{
	if(argc == 2)
	{
		if ( (!strcmp( argv[1], "--version" ))
		|| ( !strcmp( argv[1], "-v" )) )
		{
			Sys_PrintBinVersion( argv[0] );
			exit(0); // TODO: Sys_Exit(0);
		};
	};
};

bool Engine_Init(const engine_export_t::InitProps &aInitProps)
{
	Sys_ParseArgs(aInitProps.argc, aInitProps.argv);
	
#ifdef _WIN32
	g_wv.hInstance = reinterpret_cast<HINSTANCE>(aInitProps.hInstance);
#endif

	// done before Com/Sys_Init since we need this for error output
	Sys_CreateConsole();

#ifdef _WIN32
	// no abort/retry/fail errors
	SetErrorMode( SEM_FAILCRITICALERRORS );
#endif

	// get the initial time base
	Sys_Milliseconds();
	
#if 0
	// if we find the CD, add a +set cddir xxx command line
	Sys_ScanForCD();
#endif

	Sys_InitStreamThread();

	// TODO
	
	// merge the command line, this is kinda silly
	int len{0};
	int i{0};
	for(len = 1, i = 1; i < aInitProps.argc; ++i)
		len += strlen(aInitProps.argv[i]) + 1;
	char *cmdline = reinterpret_cast<char*>(malloc(len)); // TODO: free
	*cmdline = 0;
	for(i = 1; i < aInitProps.argc; ++i)
	{
		if(i > 1)
			strcat(cmdline, " ");
		strcat(cmdline, aInitProps.argv[i]);
	};
	
	//Q_strncpyz(sys_cmdline, cmdline, sizeof(sys_cmdline));
	
	Com_Init(cmdline); // TODO: was sys_cmdline
	NET_Init();

#ifdef _WIN32
	char cwd[MAX_OSPATH];
	_getcwd (cwd, sizeof(cwd));
	Com_Printf("Working directory: %s\n", cwd);
#endif

	// hide the early console since we've reached the point where we
	// have a working graphics subsystems
	if ( !com_dedicated->integer && !com_viewlog->integer )
		Sys_ShowConsole( 0, qfalse );
	
#ifdef __UNIX__
	Sys_ConsoleInputInit();

	fcntl(0, F_SETFL, fcntl (0, F_GETFL, 0) | FNDELAY);
	
#	ifdef DEDICATED
		// init here for dedicated, as we don't have GLimp_Init
		InitSig();
#	endif
#endif
	
	return true;
};

void Engine_Frame()
{
#ifdef _WIN32
	static int totalMsec, countMsec;
	int startTime, endTime;
	
	// if not running as a game client, sleep a bit
	if ( g_wv.isMinimized || ( com_dedicated && com_dedicated->integer ) )
		Sleep( 5 );

	// set low precision every frame, because some system calls
	// reset it arbitrarily
//		_controlfp( _PC_24, _MCW_PC );
//    _controlfp( -1, _MCW_EM  ); // no exceptions, even if some crappy
							// syscall turns them back on!

	startTime = Sys_Milliseconds();

	// make sure mouse and joystick are only called once a frame
	IN_Frame();
#endif

#ifdef __linux__
    Sys_ConfigureFPU();
#endif

	// run the game
	Com_Frame();

#ifdef _WIN32
	endTime = Sys_Milliseconds();
	totalMsec += endTime - startTime;
	countMsec++;
#endif
};

engine_export_t gEngine =
{
	ENGINE_API_VERSION,
	Engine_Init,
	Com_Shutdown,
	Engine_Frame
};

}; // namespace

C_EXPORT engine_export_t *GetEngineAPI(int nAPIVersion)
{
	if(nAPIVersion == ENGINE_API_VERSION)
		return &gEngine;
	
	return nullptr;
};
