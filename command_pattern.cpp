// Question1

#include <iostream>
#include <vector>

// TV - Receiver
class TV
{
public:
    void turnOn()
    {
        std::cout << "TV is turned on." << std::endl;
    }

    void turnOff()
    {
        std::cout << "TV is turned off." << std::endl;
    }
};

// SoundSystem - Receiver
class SoundSystem
{
public:
    void changeVolume(int volume)
    {
        std::cout << "Sound System volume changed to " << volume << std::endl;
    }
};

// Light - Receiver
class Light
{
public:
    void dimLights(int level)
    {
        std::cout << "Lights dimmed to level " << level << std::endl;
    }

    void brightenLights(int level)
    {
        std::cout << "Lights brightened to level " << level << std::endl;
    }
};

// Command - Abstract class (Interface)
class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// concrete class
class TurnOnTVCommand : public Command
{
private:
    TV *tv;

public:
    TurnOnTVCommand(TV *_tv) : tv(_tv) {}

    void execute()
    {
        tv->turnOn();
    }

    void undo()
    {
        tv->turnOff();
    }
};

// concrete class
class ChangeVolumeCommand : public Command
{
private:
    SoundSystem *sys;
    int volume;

public:
    ChangeVolumeCommand(SoundSystem *_sys, int _volume) : sys(_sys), volume(_volume) {}
    void execute()
    {
        sys->changeVolume(volume);
    }
    void undo()
    {
        sys->changeVolume(0);
    }
};

// concrete class
class DimLightsCommand : public Command
{
private:
    Light *light;
    int level;

public:
    DimLightsCommand(Light *_light, int _level) : light(_light), level(_level) {}
    void execute()
    {
        light->dimLights(-level);
    }
    void undo()
    {
        light->brightenLights(level);
    }
};

// Invoker (sender) - RemoteControl
class RemotControl
{
private:
    std::vector<Command *> command_queue;
    Command *lastExecutedCommand;

public:
    void setCommand(Command *command)
    {
        command_queue.push_back(command);
    }

    void executeCommand(int index)
    {
        if (index >= 0 && index < command_queue.size())
        {
            command_queue[index]->execute();
            lastExecutedCommand = command_queue[index];
        }
    }

    void undoLastExecutedCommand()
    {
        if (lastExecutedCommand)
        {
            lastExecutedCommand->execute(); // Undo the last executed command
            lastExecutedCommand = nullptr;
        }
    }

    void undoAllExecutedCommand()
    {
        for (int i = command_queue.size() - 1; i >= 0; i--)
        {
            command_queue[i]->undo();
        }
    }
};

int main()
{
    TV tv;
    SoundSystem soundSystem;
    Light Light;

    RemotControl remotControl;

    // remotControl.setCommand(new TurnOnTVCommand(&tv));

    TurnOnTVCommand turnOnTv(&tv);
    ChangeVolumeCommand changeVolume(&soundSystem, 10);
    DimLightsCommand dimLights(&Light, 5);

    remotControl.setCommand(&turnOnTv);
    remotControl.setCommand(&changeVolume);
    remotControl.setCommand(&dimLights);

    std::cout << "Executing the commands:" << std::endl;

    remotControl.executeCommand(0);
    remotControl.executeCommand(1);
    remotControl.executeCommand(2);

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Tracking the last command:" << std::endl;
    remotControl.undoLastExecutedCommand();

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Undo the all executed commands:" << std::endl;
    remotControl.undoAllExecutedCommand();

    return 0;
}