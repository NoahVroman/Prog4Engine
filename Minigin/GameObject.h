#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>
#include <typeindex>

namespace dae
{
	class Texture2D;
	class Component;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render() const;

		template <class T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> newComponent = std::make_shared<T>();
			components[typeid(T)] = newComponent;
			return newComponent;
		}

		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			auto it = components.find(typeid(T));
			if (it != components.end())
			{
				return std::static_pointer_cast<T>(it->second);
			}
			return nullptr;
		}

		template <class T>
		void RemoveComponent()
		{
			auto it = components.find(typeid(T));
			if (it != components.end())
			{
				components.erase(it);
			}
		}

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::unordered_map<std::type_index, std::shared_ptr<Component>> components;

		std::shared_ptr<Texture2D> m_texture{};
	};
};
	