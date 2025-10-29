#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Input/Input.h"

API_CLASS() class GAME_API ExitOnEsc : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(ExitOnEsc);

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
};
