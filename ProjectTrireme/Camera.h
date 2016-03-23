//-------------------------------------------------------------------------------------------------
#ifndef TRIREME_CAMERA_H
#define TRIREME_CAMERA_H

#include "constdef.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "SDL2\SDL.h"

#define DEFAULT_FIELD_OF_VIEW 70.f

#define DEFAULT_Z_NEAR_CLIP 0.2f

#define DEFAULT_Z_FAR_CLIP 750.f

namespace Trireme
{
	// a 3d perpective camera object
	class Camera
	{
	public:
		// default constructor
		Camera();

		Camera(glm::vec3 targetPos);

		// constructor
		Camera(glm::vec3 upDir, glm::vec3 forwardDir, glm::vec3 targetPos, 
			float aspect = 1.f,
			float fovy = DEFAULT_FIELD_OF_VIEW, 
			float zFarClip = DEFAULT_Z_FAR_CLIP, 
			float zNearClip = DEFAULT_Z_NEAR_CLIP);

		// returns camera matrix calculation
		glm::mat4 getViewProjectionMatrix(const glm::vec3& position)const;

		// camera object event handlers
		void input(SDL_Event& e);

		// destructor
		~Camera();

		static void* operator new(std::size_t sz);
		static void operator delete(void *p);

	private:
		glm::vec3 up;
		glm::vec3 forward;
		glm::vec3 target;
		float fov;
		float zFar; 
		float zNear;
		glm::mat4 viewMatrix;
	};
}

#endif
