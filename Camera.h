/*  Pinhole camera implementation that may be expanded to other types after
 *  refactorization update
    - RAB
 */
#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

class Camera {
	// Defines camera coordinate system
	glm::vec3 eye, center, up;

	// For defining the camera view frustum
	float fovy, near, far;

	// For defining camera movement
	float pitch, yaw;

	/// <summary>
	/// Makes sure up vector is orthogonal in camera coordinate system
	/// Will set the eyem center, and corrected up vector from given parameters
	/// </summary>
	/// <param name="eye"> new location of camera in 3D</param>
	/// <param name="center"> new 3D location where camera is looking </param>
	/// <param name="up"> new up vector (may not be orthogonal) </param>
	void fixCameraVecs(glm::vec3 eye,
	                   glm::vec3 center, 
		               glm::vec3 up);


	void calcPitchAndYaw(float& pitch, float& yaw) const;

public:
	/// <summary>
	/// Creates a cmaera with the standard settings above
	/// </summary>
	Camera();
	/// <summary>
	/// Creates a camera with given parameters
	/// </summary>
	/// <param name="eye"> location of camera in 3D </param>
	/// <param name="center"> point where camera is looking at </param>
	/// <param name="up"> the up vector </param>
	/// <param name="fovy"> y field of view in degrees </param>
	/// <param name="near"> location of the near clipping plane </param>
	/// <param name="far"> location of far clipping plane </param>
	Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up,
		   float fovy, float near, float far);

	/// <summary>
	/// Returns location of camera
	/// </summary>
	/// <returns> vec3 location of camera </returns>
	glm::vec3 getEye() const;
	/// <summary>
	/// Returns location where camera is looking at
	/// </summary>
	/// <returns> vec3 location where camera is looking at </returns>
	glm::vec3 getCenter() const;
	/// <summary>
	/// Returns up vector
	/// </summary>
	/// <returns> up vector </returns>
	glm::vec3 getUp() const;
	/// <summary>
	/// Returns inverse camera matrix (RH)
	/// </summary>
	/// <returns> Inverse camera matrix (RH) </returns>
	glm::mat4 getViewMat() const;
	/// <summary>
	/// Returns pinhole perspective projection matrix
	/// </summary>
	/// <param name="width"> width of window </param>
	/// <param name="height"> height of window </param>
	/// <returns></returns>
	glm::mat4 getProjMat(int width, int height) const;

	/// <summary>
	/// Sets location of camera
	/// </summary>
	/// <param name="eye"> 3D location of camera </param>
	void setEye(glm::vec3 eye);
	/// <summary>
	/// Sets where camera is looking at in 3D
	/// </summary>
	/// <param name="center"> 3D location where camera is looking </param>
	void setCenter(glm::vec3 center);
	/// <summary>
	/// Sets up vector
	/// </summary>
	/// <param name="up"> up vector </param>
	void setUp(glm::vec3 up);
	/// <summary>
	/// Sets all 3 members that define the camera coordinate system
	/// </summary>
	/// <param name="eye"> 3D location of camera </param>
	/// <param name="center"> 3D location where camera is looking </param>
	/// <param name="up"> up vector </param>
	void setCameraCoordSystem(glm::vec3 eye,
		                      glm::vec3 center,
		                      glm::vec3 up);

	/// <summary>
	/// Translates the camera
	/// </summary>
	/// <param name="translate"> translation vector </param>
	void moveCam(glm::vec3 translate);


	/// <summary>
	/// Rotates camera based on mouse cursor movement
	/// </summary>
	/// <param name="offsetX"> X offset of camera movement</param>
	/// <param name="offsetY"> Y offset of camera movement</param>
	void rotateCamFromMouseMove(float offsetX, float offsetY);


};