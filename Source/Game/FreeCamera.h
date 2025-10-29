#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Level/Actor.h"
#include "Engine/Input/Input.h"
#include "Engine/Engine/Screen.h"
#include "Engine/Engine/Time.h"
#include "Engine/Core/Math/Math.h"
#include "Engine/Core/Math/Vector3.h"
#include "Engine/Core/Math/Quaternion.h"
#include "Engine/Core/Log.h"
#include "Engine/Debug/DebugLog.h"
#include "Engine/Level/Actors/Camera.h"
#include "Engine/Serialization/Serialization.h"

API_CLASS() class GAME_API FreeCamera : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(FreeCamera);

    // [Script]

    public:
        API_FIELD() float spd;
        API_FIELD() float camSmooth;
		API_FIELD() float mouseSensitivity;
        API_FIELD() Camera *cam;

    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

    private:
        float pitch;
		float yaw;

};
