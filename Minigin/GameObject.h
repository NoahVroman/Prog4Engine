#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>
#include <typeindex>
#include <string>
#include <utility>
#include <type_traits>
namespace dae
{
	class Texture2D;
	class Component;
	class TransfomComponent;


	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;

		template <class T,class ... Args>
		T* AddComponent(Args&& ... args)
		{
			
			//static_assert(std::is_constructible<T, Args...>, "Component must be constructible with given arguments");
			T* pComponent = new T(this, std::forward<Args>(args)...);
			
			components.emplace_back(pComponent);

			return pComponent;
		}

		template <class T>
		T* GetComponent() const
		{

			for (const auto& pComponent : components)
			{
				T* derivedComponent{ dynamic_cast<T*>(pComponent.get()) };

				if (derivedComponent) return derivedComponent;
			}

			return nullptr;
		}

		template <class T>
		T* GetComponentInChildren() const
		{

			for (const auto& child : m_pChildren)
			{
				for (const auto& pComponent : child->components)
				{
					T* derivedComponent{ dynamic_cast<T*>(pComponent.get()) };

					if (derivedComponent) return derivedComponent;
				}
			}

			return nullptr;
		}

		template <class T>
		void RemoveComponent()
		{

			for (auto itr{ components.begin() }; itr < components.end(); ++itr)
			{
				T* component{ dynamic_cast<T*>((*itr).get()) };
				if (component != nullptr)
				{
					components.erase(itr);
					return;
				}
			}
		}

		void SetParent(GameObject* pParent);
		GameObject* GetParent() const { return m_pParent; }
	
		void RemoveAllChildren()
		{
			m_pChildren.clear();
		}


		TransfomComponent* GetTransform() const
		{
			return m_pTransformComponent;
		}


		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		const std::vector<GameObject*>& GetChildren() const { return m_pChildren; }

		void Destroy() { m_isDestroyed = true; }
		bool IsDestroyed() const { return m_isDestroyed; }

	private:

		bool m_isDestroyed{ false };
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren;
		std::vector<std::unique_ptr<Component>> components;

		TransfomComponent* m_pTransformComponent{ nullptr };

	};
};
	