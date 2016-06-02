#include "Camera.h"

using namespace Trireme;

using glm::vec3;

#define frameTime EngineProperties::frameTime
#define windowWidth EngineProperties::windowWidth
#define windowHeight EngineProperties::windowHeight
#define DEFAULT_FIELD_OF_VIEW 70.f
#define DEFAULT_Z_NEAR_CLIP 0.2f
#define DEFAULT_Z_FAR_CLIP 750.f

Camera::Camera()
{
	up = vec3(0.f, 0.f, 1.f);
	forward = vec3(0.f, 1.f, 0.f);
	target = vec3(0.f, 0.f, 0.f);
	fov = 70.f;
	zFar = 100.f;
	zNear = 0.2f;

	viewMatrix = glm::perspective(fov, float(*windowWidth) / float(*windowHeight), zNear, zFar);
}

Camera::Camera(vec3 targetPos) : Camera::Camera()
{
	target = targetPos;

	viewMatrix = glm::perspective(fov, float(*windowWidth) / float(*windowHeight), zNear, zFar);
}

Camera::Camera(vec3 upDir, vec3 forwardDir, vec3 targetPos, float aspect, float fovy, float zFarClip, float zNearClip)
{
	up = upDir;
	forward = forwardDir;
	target = targetPos;
	fov = fovy;
	zFar = zFarClip;
	zNear = zNearClip;

	viewMatrix = glm::perspective(fov, float(*windowWidth)/float(*windowHeight)*aspect, zNear, zFar);
}

glm::mat4 Camera::getViewProjectionMatrix(const vec3& position)const
{
	// return viewMatrix * lookAt(position);
	return viewMatrix * glm::lookAt(position/1.5f, target, up);
}

void Camera::input(SDL_Event& e)
{
	if (e.type == SDL_WINDOWEVENT)
	{
		if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			viewMatrix = glm::perspective(fov, float(*windowWidth) / float(*windowHeight), zNear, zFar);
	}
}

void* Camera::operator new(std::size_t sz)
{
	return _aligned_malloc(sz, 16);
}

void Camera::operator delete(void* p)
{
	_aligned_free(p);
}

Camera::~Camera()
{
	
}