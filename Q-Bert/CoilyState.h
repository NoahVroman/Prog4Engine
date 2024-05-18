#pragma once
#include "PyramidMovementComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
namespace dae 
{
	class Coily;

	class CoilyState
	{
		public:
		enum class CoilyStateEnum
		{
			Egg,
			Snake
		};

		CoilyState(const CoilyStateEnum& state,GameObject* const pParent);
		virtual ~CoilyState() = default;
		CoilyState(const CoilyState& other) = delete;
		CoilyState(CoilyState&& other) = delete;
		CoilyState& operator=(const CoilyState& other) = delete;
		CoilyState& operator=(CoilyState&& other) = delete;

		virtual CoilyStateEnum GetNextState(Coily* coily) = 0;

		const CoilyStateEnum& GetState() const { return m_State; }
		
		virtual void Update(Coily* coily) = 0;

		protected:

		CoilyStateEnum m_State;
		PyramidMovementComponent* GetPyramidMovementComponent() const { return m_pPyramidMovementComponent; }
		TextureComponent* GetTextureComponent() const { return m_pTextureComponent; }


		bool IsOnLastCubeInRow(){return m_pPyramidMovementComponent->GetCurrentIndex() == GetLastCubeInRow(m_pPyramidMovementComponent->GetCurrentRow());}
		bool IsOnFirstCubeInRow(){return m_pPyramidMovementComponent->GetCurrentIndex() == GetFirstCubeInRow(m_pPyramidMovementComponent->GetCurrentRow());}



			
		private:
		PyramidMovementComponent* m_pPyramidMovementComponent;
		TextureComponent* m_pTextureComponent;

		unsigned int Factorial(unsigned int n)
		{
			return (n * (n + 1)) / 2;
		}
		int GetFirstCubeInRow(int row)
		{
			return Factorial(row);
		}
		int GetLastCubeInRow(int row)
		{
			return GetFirstCubeInRow(row) + row;
		}


	};

};

