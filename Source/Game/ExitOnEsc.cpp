#include "ExitOnEsc.h"

ExitOnEsc::ExitOnEsc(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void ExitOnEsc::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void ExitOnEsc::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void ExitOnEsc::OnUpdate(){
    // Here you can add code that needs to be called every frame
    if(Input::GetKeyDown(KeyboardKeys::Escape)){
		Engine::RequestExit();
    }
}
