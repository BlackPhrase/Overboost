/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.
Copyright (C) 2020-2021 BlackPhrase

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

#include <cstdlib>
#include <stdexcept>

#include "engine/IEngine.h"

#ifdef _WIN32
#	include <windows.h>
#elif __unix__
#	include <dlfcn.h>
#endif

engine_export_t *gpEngine{nullptr};

engine_export_t::InitProps InitProps;

void *Sys_LoadLibrary(const char *sName)
{
#ifdef _WIN32
	return LoadLibrary(sName);
#elif __unix__
	return dlopen(sName, DL_NOW);
#else
#	error "Unsupported platform!"
#endif
};

void *Sys_GetExport(void *pLib, const char *sName)
{
#ifdef _WIN32
	return reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(pLib), sName));
#elif __unix__
	return dlsym(pLib, sName);
#else
#	error "Unsupported platform!"
#endif
};

void Sys_FreeLibrary(void *pLib)
{
#ifdef _WIN32
	FreeLibrary(reinterpret_cast<HMODULE>(pLib));
#elif __unix__
	dlclose(pLib);
#else
#	error "Unsupported platform!"
#endif
};

void LoadEngineModule()
{
	auto pEngineLib{Sys_LoadLibrary("engine")};
	
	if(!pEngineLib)
		throw std::runtime_error("Failed to load the engine module!");
	
	auto pfnGetEngineAPI{reinterpret_cast<GetEngineAPI>(Sys_GetExport(pEngineLib, "GetEngineAPI"))};
	
	if(!pfnGetEngineAPI)
		throw std::runtime_error("Failed to get the 'GetEngineAPI' export from the engine module!");
	
	gpEngine = pfnGetEngineAPI();
	
	if(!gpEngine)
		throw std::runtime_error("Failed to get the engine API!");
};

int main(int argc, char **argv)
{
	LoadEngineModule();
	
	if(!gpEngine->Init(InitProps))
		throw std::runtime_error("Failed to initialize the engine!");

    // main game loop
	while( 1 )
	{
		gpEngine->Frame();
	};
	
	//Sys_FreeLibrary(gpEngineLib);

	// never gets here
	return EXIT_SUCCESS;
};

#ifdef _WIN32

#include <windows.h>

/*
==================
WinMain

==================
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// should never get a previous instance in Win32
    if(hPrevInstance)
        return 0;
	
	InitProps.hInstance = hInstance;
	//g_wv.hInstance = hInstance; // TODO
	
	InitProps.sCmdLine = lpCmdLine;
	//Q_strncpyz( sys_cmdline, lpCmdLine, sizeof( sys_cmdline ) );
	
	return main(__argc, __argv);
};
#endif