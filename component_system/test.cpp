#include "entity_container.h"
#include "transform.h"

int main()
{
	using namespace wx2;

	EntityContainer container;

	auto a = container.CreateEntity("alpha");

	container.CreateEntity("beta");
	auto b = container.FindEntity("beta");
	
	container.CreateEntity("gamma");
	container.CreateEntity("gamma");
	auto gammas = container.FindEntities("gamma");

	a->AddComponent<Transform>();
	a->AddComponent<Transform>();
	auto transform = a->GetComponent<Transform>();
	auto transforms = a->GetComponents<Transform>();

	transform->SetPosition(0.0f, 1.0f, 2.0f);

	a->RemoveComponent(transforms[1]);
	transforms = a->GetComponents<Transform>();

	return 0;
}