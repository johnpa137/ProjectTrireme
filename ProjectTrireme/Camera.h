//-------------------------------------------------------------------------------------------------
#ifndef TRIREME_CAMERA_H
#define TRIREME_CAMERA_H

#include "constdef.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "SDL2\SDL.h"

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
			float fovy = 70.f, 
			float zFarClip = 0.2f, 
			float zNearClip = 750.f);

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
