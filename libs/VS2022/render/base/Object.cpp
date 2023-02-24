#include "RenderObject.h"

ll::RenderObject::RenderObject(ObjectType type)
	: _objectType(type),
	_objectID(GenerateObjectID<RenderObject>())
{
}