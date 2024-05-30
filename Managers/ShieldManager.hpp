#pragma once

#include "../Entities/Shield.hpp"

namespace ms
{
	class ShieldManager
	{
	public:
		friend class Shield;

		ShieldManager(GameDataRef& _data);
		
		void Init();
		void DrawShields();

		void CheckForCollisions(Object& other);
		std::vector<Shield*> getShields();

		void RemoveDeadShields();

	private:
		std::vector<Shield*> _shields;

		GameDataRef _data;
	};
}