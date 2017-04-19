// STVector3.cpp
#include "STVector3.h"
#include <iostream>

//

const STVector3 STVector3::Zero(0.0f, 0.0f, 0.0f);
const STVector3 STVector3::eX(1.0f, 0.0f, 0.0f);
const STVector3 STVector3::eY(0.0f, 1.0f, 0.0f);
const STVector3 STVector3::eZ(0.0f, 0.0f, 1.0f);

std::ostream& operator<< (std::ostream& stream, const STVector3& stVector)
{
	stream << "(" << stVector.x << ", " << stVector.y << ", " << stVector.z << ")";
	return stream;
}