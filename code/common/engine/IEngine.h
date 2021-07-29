/// @file

#pragma once

constexpr auto ENGINE_API_VERSION{1};

struct engine_export_t
{
	int version{ENGINE_API_VERSION};
	
	struct InitProps
	{
		//char *sCmdLine{nullptr};
		int argc{0};
		char **argv{nullptr};
		
#ifdef _WIN32
		void *hInstance{}; // TODO: HINSTANCE
#endif
	};

	///
	bool (*Init)(const InitProps &aInitProps);
	
	///
	void (*Shutdown)();
	
	///
	void (*Frame)();
};

using pfnGetEngineAPI = engine_export_t *(*)(int nAPIVersion);