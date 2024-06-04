#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "TransfomComponent.h"

namespace dae
{
	class Texture2D;
	class TextureComponent : public Component
	{
		public:

		struct SpriteInfo
		{
			float width;
			float height;
			float SrcX;
			float SrcY;
			float SrcWidth;
			float SrcHeight;

		};

	 	explicit TextureComponent(GameObject* const pParentObject,const std::string& path, const SpriteInfo& spriteInfo );
		virtual ~TextureComponent();
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;
		void Update() override;
		void FixedUpdate() override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);

		void SetSourceInfo(float sourceX,float SourceY,float SourceWidth,float SourceHeight) 
		{

			m_SpriteInfo.SrcX = sourceX;
			m_SpriteInfo.SrcY = SourceY;
			m_SpriteInfo.SrcWidth = SourceWidth;
			m_SpriteInfo.SrcHeight = SourceHeight;

		}
		void SetHidden(bool hidden) { isHidden = hidden; }

		const std::string& GetFilename() const { return m_Filename; }


		
		private:
		std::shared_ptr<Texture2D> m_Texture{};
		std::string m_Filename{};
		bool m_NeedsUpdate{ true };

		SpriteInfo m_SpriteInfo;
		bool isHidden{ false };

	};

};
