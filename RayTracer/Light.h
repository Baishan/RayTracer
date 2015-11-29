#pragma once

#include "Vector3.h"
#include "Config.h"

class Light
{
public:
	Vector3 pos;
	Real brightness;

	Light(const Vector3 & pos, const Real brightness):pos(pos),brightness(brightness){}
};