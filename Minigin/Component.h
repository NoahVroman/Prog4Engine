#pragma once
namespace dae
{
    class GameObject;
	class Component
	{
        public:

        virtual ~Component() ;
        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator=(const Component& other) = delete;
        Component& operator=(Component&& other) = delete;


        virtual void Render() const {};
        virtual void Update() {};
        virtual void FixedUpdate() {};

        void SetOwner(GameObject* const pOwner) { m_Owner = pOwner; }

        protected:
            Component(GameObject* const pParent);

			GameObject* GetOwnerObject() const { return m_Owner; }

        private:
            GameObject* m_Owner;
	};

};

