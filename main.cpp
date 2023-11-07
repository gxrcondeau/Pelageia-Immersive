#include "Core/Timer/Timer.h"
#include "Core/Engine.h"
#include "Core/Vendor/TinyXml/tinyxml.h"

int main(int argc, char *args[]) {
    Engine::GetInstance()->Init();

    TiXmlElement* element = nullptr;

    while(Engine::GetInstance()->IsRunning()){
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();
    return 0;
}
