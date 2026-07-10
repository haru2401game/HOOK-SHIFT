class ColliderManager;
class ObjectManager;

class PhysicsManager
{
public:
    void Update(
        ObjectManager& objectManager,
        ColliderManager& colliderManager,
        float deltaTime);
};