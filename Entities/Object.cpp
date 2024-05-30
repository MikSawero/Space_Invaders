#include "Object.hpp"

namespace ms
{
	Object::Object(GameDataRef&_data)
		: _data(_data)
	{

	}
	
	bool Object::CheckCollision(Object& other)
	{
		if (GetBox().intersects(other.GetBox()))
		{
			OnCollision(other);
			other.OnCollision(*this);
			return true;
		}
		return false;
	}

	sf::FloatRect Object::GetBox()
	{
		return { GetPosition().x, GetPosition().y, _size.x, _size.y };
	}
}
