/*
	This file declares the external interface for the graphics system
*/

#ifndef EAE6320_GRAPHICS_H
#define EAE6320_GRAPHICS_H

// Include Files
//==============

#include "Configuration.h"

#include <cstdint>
#include <Engine/Results/Results.h>
#include "cTexture.h"
#if defined( EAE6320_PLATFORM_WINDOWS )
	#include <Engine/Windows/Includes.h>
#endif

// Interface
//==========
class cEffect;
class cSprite;
class cTexture;
namespace eae6320
{
	namespace Graphics
	{
		// Submission
		//-----------

		struct renderData {
			cEffect * effect;
			cSprite * sprite;
			cTexture::Handle textureHandle;

			renderData() = default;

			renderData(cEffect* iEffect, cSprite * iSprite, cTexture::Handle iTextureHandle)
				: effect(iEffect), sprite(iSprite), textureHandle(iTextureHandle) {}

		};
		// These functions should be called from the application (on the application loop thread)

		// As the class progresses you will add your own functions for submitting data,
		// but the following is an example (that gets called automatically)
		// of how the application submits the total elapsed times
		// for the frame currently being submitted
		void SubmitElapsedTime( const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_simulationTime );

		void SubmitBackgroundColor(const float r, const float g, const float b, const float a);

		// When the application is ready to submit data for a new frame
		// it should call this before submitting anything
		// (or, said another way, it is not safe to submit data for a new frame
		// until this function returns successfully)
		cResult WaitUntilDataForANewFrameCanBeSubmitted( const unsigned int i_timeToWait_inMilliseconds );
		// When the application has finished submitting data for a frame
		// it must call this function
		cResult SignalThatAllDataForAFrameHasBeenSubmitted();

		// Render
		//-------

		// This is called (automatically) from the main/render thread.
		// It will render a submitted frame as soon as it is ready
		// (i.e. as soon as SignalThatAllDataForAFrameHasBeenSubmitted() has been called)
		void RenderFrame();

		// Initialization / Clean Up
		//--------------------------

		struct sInitializationParameters
		{
#if defined( EAE6320_PLATFORM_WINDOWS )
			HWND mainWindow = NULL;
	#if defined( EAE6320_PLATFORM_D3D )
			uint16_t resolutionWidth, resolutionHeight;
	#elif defined( EAE6320_PLATFORM_GL )
			HINSTANCE thisInstanceOfTheApplication = NULL;
	#endif
#endif
		};
		void SubmitEffectAndSprite(eae6320::Graphics::renderData);
		cResult Initialize( const sInitializationParameters& i_initializationParameters );
		cResult CleanUp();
	}
}

#endif	// EAE6320_GRAPHICS_H
