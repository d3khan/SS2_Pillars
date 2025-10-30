#include "FreeCamera.h"

FreeCamera::FreeCamera(const SpawnParams& params) : Script(params),

spd(500.0f), spdMul(1.0f), camSmooth(20.0f),
cam(nullptr), 
pitch(0.0f), yaw(0.0f), // x and y rotations
mouseSensitivity(0.2f)

{
	// Enable ticking OnUpdate function
	_tickUpdate = true;
}

void FreeCamera::OnEnable() {
	if (!cam)return;

	//Screen::SetCursorLock(CursorLockMode::Locked);
	Screen::SetCursorVisible(false);
}

void FreeCamera::OnDisable() {
	//Screen::SetCursorLock(CursorLockMode::None);
	Screen::SetCursorVisible(true);
}

void FreeCamera::OnUpdate() {
	if (!cam)return;

	Transform camTransform = cam->GetTransform();
	Quaternion camOrientation = camTransform.Orientation;

	// Rotation

    Float2 screenCenter = Screen::GetSize() * 0.5f;
    Float2 mouseDelta = Input::GetMousePositionDelta();

    // reset cursor to center for next frame
    Input::SetMousePosition(screenCenter);

	yaw += mouseDelta.X * mouseSensitivity;
	pitch += mouseDelta.Y * mouseSensitivity;

	//DebugLog::Log(String::Format(TEXT("Mouse Delta: {0}, {1}"), yaw, pitch)); // Debug mouse delta

	pitch = Math::Clamp(pitch, -89.0f, 89.0f); // To avoid gimbal lock

	Quaternion targRotation = Quaternion::Euler(pitch, yaw, 0.0f);
	camTransform.Orientation = // The Camera rotation
		Quaternion::Slerp(camOrientation, targRotation, camSmooth * Time::GetDeltaTime()); // To avoid gimbal lock


	// Movement

	Vector3 moveDir = Vector3::Zero; 
	
	if (Input::GetKey(KeyboardKeys::W)) moveDir += Vector3::Forward;
	if (Input::GetKey(KeyboardKeys::A)) moveDir += Vector3::Left;
	if (Input::GetKey(KeyboardKeys::S)) moveDir += Vector3::Backward;
	if (Input::GetKey(KeyboardKeys::D)) moveDir += Vector3::Right;

	if (Input::GetKey(KeyboardKeys::E)) moveDir += Vector3::Up;
	if (Input::GetKey(KeyboardKeys::Q)) moveDir += Vector3::Down;

	spd = 500.f; // Reset speed to default
	if (Input::GetKey(KeyboardKeys::Shift)) spd *= 2; // Speed boost
	

	// Adjust speed multiplier with mouse scroll
	float mScroll = Input::GetMouseScrollDelta();
	if (mScroll > 0.0f) spdMul += 0.2f;
	if (mScroll < 0.0f) spdMul -= 0.2f;

	if (spdMul < 0.1f) spdMul = 0.2f; // Minimum speed multiplier
	if (spdMul > 10.0f) spdMul = 10.0f; // Maximum speed multiplier

	//DebugLog::Log(String::Format(TEXT("MouseScrollDelta: {0}, speedMultiplier: {1}"), mScroll, spdMul)); // Debug dynamic speed

	moveDir.Normalize(); // normalization removes spd effect so it comes first
	moveDir *= spd * spdMul;

	if ( (moveDir != Vector3::Zero) && cam) {

		moveDir = camTransform.Orientation * moveDir; // Gets Movement direction from rotation
		camTransform.Translation += moveDir * Time::GetDeltaTime(); // Move camera
		
	}

	cam->SetTransform(camTransform);
}
