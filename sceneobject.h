#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H


#include "vertex.h"

class Scene;
class SceneObject
{
public:
    typedef enum _O_TYPE{
        CUBE,
        SPHERE,
    }O_TYPE;

    SceneObject(O_TYPE t, const V3& pos, int texture);
    virtual ~SceneObject();
    virtual void Render();
    virtual bool Update(const Scene* ps, float dt);

protected:
private:

    O_TYPE _type;

};

#endif // SCENEOBJECT_H
