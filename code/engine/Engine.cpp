/// @file

#include "Engine.hpp"
#include "engine/IEngine.h"

#ifdef _WIN32
#	include "qcommon/win/win_local.h"

#	define EXPORT [[dllexport]]
#elif defined(__unix__)
#	define EXPORT [[visibility("default")]]
#endif

#define C_EXPORT extern "C" EXPORT

namespace
{

bool Engine_Init(const InitProps &aInitProps)
{
	char		cwd[MAX_OSPATH];
	int			startTime, endTime;

	// done before Com/Sys_Init since we need this for error output
	Sys_CreateConsole();

	// no abort/retry/fail errors
	SetErrorMode( SEM_FAILCRITICALERRORS );

	// get the initial time base
	Sys_Milliseconds();
#if 0
	// if we find the CD, add a +set cddir xxx command line
	Sys_ScanForCD();
#endif

	Sys_InitStreamThread();
	
	Com_Init(aInitProps.sCmdLine); // sys_cmdline
	NET_Init();

	_getcwd (cwd, sizeof(cwd));
	Com_Printf("Working directory: %s\n", cwd);

	// hide the early console since we've reached the point where we
	// have a working graphics subsystems
	if ( !com_dedicated->integer && !com_viewlog->integer )
		Sys_ShowConsole( 0, qfalse );
};

void Engine_Frame()
{
	static int totalMsec, countMsec;
	
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

	// run the game
	Com_Frame();

	endTime = Sys_Milliseconds();
	totalMsec += endTime - startTime;
	countMsec++;
};

engine_export_t gEngine =
{
	Engine_Init,
	Com_Shudown,
	Engine_Frame
};

}; // namespace

C_EXPORT engine_export_t *GetEngineAPI(int nAPIVersion)
{
	if(nAPIVersion == ENGINE_API_VERSION)
		return gEngine;
	
	return nullptr;
};