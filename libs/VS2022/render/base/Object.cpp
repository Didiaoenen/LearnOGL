#include "Object.h"

ll::Object::Object(ObjectType type)
	: _objectType(type),
	_objectID(generateObjectID<Object>())
{
}