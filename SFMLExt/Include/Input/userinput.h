#pragma once
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Touch.hpp>
#include <SFML\Window\Sensor.hpp>
#include <SFML\Window\Joystick.hpp>

namespace ext
{
    enum class CommandType : unsigned int
    {
        Mouse,
        Keyboard,
        Touch,
        Joystick,
        Sensor
    };

    using UpdateFunction = void(*)(float);
    //using RenderFunction = void(*)(RenderContext);

    class Updater
    {
    public:
    };

    class Input final
    {
    public:
        void AddCommand(CommandType cmdType, );

    private:
    };
}