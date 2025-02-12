#include "main.h"
#include "EntityComponentSystem/Components/Transform.h"

int main(int argc, char** argv)
{
	Application::Logger::Initialize(); // Logger is seperate from the Engine.

	//Application::Engine Engine;
	//Engine.Run();
	
	ECS::Registry<ECS::Entity> registry;
	registry.Add<ECS::Transform>(1, 5.7f, 1.5f);
	
	auto& comp = registry.Get<ECS::Transform>(1);
	LOG_INFO("X: {0}, Y: {1}", comp.GetPosition().x, comp.GetPosition().y);
	comp.SetPosition({ 7.3f, 9.1f });
	LOG_INFO("X: {0}, Y: {1}", comp.GetPosition().x, comp.GetPosition().y);

	return 0;
}