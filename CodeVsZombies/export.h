#pragma once

#ifdef CODEVSZOMBIES_EXPORTS
	#define CVZ_EXPORT __declspec(dllexport)
#else
	#define CVZ_EXPORT __declspec(dllimport)
#endif