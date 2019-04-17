#include <memory>
#include <string>
#include <iostream>
using namespace std;

class Entity
{
public:
    Entity()
    {
        
    }
    ~Entity()
    {
        cout << "Deinit Entity" << endl;
    }
    
    void echo()
    {
        cout << "Hello Im Entity" << endl;
    }
};

int main()
{
    {
        unique_ptr<Entity> entity = make_unique<Entity>();
        entity->echo();
    }
    
    
    shared_ptr<Entity> shared_entity01;
    {
        shared_ptr<Entity> shared_entity00 = make_shared<Entity>();
        shared_entity01 = shared_entity00;
        shared_entity01.get()->echo();
    }

    weak_ptr<Entity> weak_entity01;
    {
        shared_ptr<Entity> shared_entity00 = make_shared<Entity>();
        weak_entity01 = shared_entity00;
        shared_ptr<Entity> spt = weak_entity01.lock();
        if (spt)
        {
            spt.get()->echo();
        }
        else
        {
            cout << "gw is expired\n";
        }
    }
    return 0;
}
