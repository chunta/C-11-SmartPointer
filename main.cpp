#include <memory>
#include <string>
#include <iostream>
using namespace std;


class String
{
    private:
        unsigned int m_Size;
        char * m_Buffer;
    public:
        String(const char *src)
        {
            m_Size = strlen(src);
            m_Buffer = new char[m_Size+1];
            memcpy(m_Buffer, src, m_Size);
            m_Buffer[m_Size] = 0;
        }

        String(const String &src)
        {
            m_Size = src.m_Size;
            m_Buffer = new char[m_Size+1];
            memcpy(m_Buffer, src.m_Buffer, m_Size);
            m_Buffer[m_Size] = 0;
        }

        char& operator[](unsigned int index)
        {
            return m_Buffer[index];
        }

        void echo()
        {
            printf("%s %lu %u\n", m_Buffer, strlen(m_Buffer), m_Size);
        }

        ~String()
        {
            delete[] m_Buffer;
            printf("~String()\n");
        }
};

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
    
    String a = "Hello";
    String b = a;
    b[2] = 'a';
    a.echo();
    b.echo();
    
    return 0;
}
