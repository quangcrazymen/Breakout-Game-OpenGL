#pragma once
#include "core/types.h"

namespace DalatEngine {
	namespace Video {
		class ICompileData {
		public:
			virtual ~ICompileData();
			//virtual 
		protected:
			ICompileData(){}
		};

		// method to createDevice
	
		class IVideoDriver {

	
		// IDevice

		//CMaterilalRenderManager& 

		// IShaderManager* 

		// CLookupTableManager* 

		// CGlobalMaterialParameterManager

		// ----------------------------------
		// Scene manager and draw calls
		// ----------------------------------

		//virtual bool beginScene(int displayId = 0);

		// virtual void draw3DTriangle

		// ----------------------------------
		// Transform feedback
		// ----------------------------------

		//--------------------------------------------------------------------------
		// Driver informations (Maybe unnecessary)
		//--------------------------------------------------------------------------

		//----------------------------------------------------------------------------
		// Transformations and materials 
		//----------------------------------------------------------------------------

		//----------------------------------------------------------------------------
		// Texture and render targets tools
		//----------------------------------------------------------------------------

		//-------------------------------------------------------------------------
		// Shader tool
		//-------------------------------------------------------------------------
			
			void clearBuffers(int clearMask);
		};

		// Test function
		//std::cout


		// ENUM
		enum E_DRIVER_FLAG
		{
			EDF_INITIALIZED = 1,
			EDF_NEEDS_CLEAR_SCREEN_BORDER = EDF_INITIALIZED << 1,
			EDF_IS_RENDERING_FRAME = EDF_NEEDS_CLEAR_SCREEN_BORDER << 1,
			EDF_IS_DRAWING = EDF_IS_RENDERING_FRAME << 1,
			EDF_IS_COMMITTING_SHADER = EDF_IS_DRAWING << 1,
			EDF_NEEDS_BUFFER_CONFIG = EDF_IS_COMMITTING_SHADER << 1,
			EDF_OWNS_MATERIAL_RENDERER_MANAGER = EDF_NEEDS_BUFFER_CONFIG << 1,
			EDF_OWNS_TEXTURE_MANAGER = EDF_OWNS_MATERIAL_RENDERER_MANAGER << 1,
			EDF_OWNS_LOOKUPTABLE_MANAGER = EDF_OWNS_TEXTURE_MANAGER << 1,
			EDF_OWNS_GLOBAL_MATERIAL_PARAMETERS = EDF_OWNS_LOOKUPTABLE_MANAGER << 1,
			EDF_RESTORE_SHADOWSTATE_ON_NEXT_SETMATERIAL = EDF_OWNS_GLOBAL_MATERIAL_PARAMETERS << 1,
			EDF_MATERIAL_CHANGED_SINCE_LAST_DRAW = EDF_RESTORE_SHADOWSTATE_ON_NEXT_SETMATERIAL << 1,
			EDF_BATCHING_SWITCHED_OFF = EDF_MATERIAL_CHANGED_SINCE_LAST_DRAW << 1,
			EDF_RASTERIZER_DISCARDED = EDF_BATCHING_SWITCHED_OFF << 1
		};

		u8 init = EDF_INITIALIZED;
		u8 clear = EDF_NEEDS_CLEAR_SCREEN_BORDER;
		u8 rendering = EDF_IS_RENDERING_FRAME;
	}
}
