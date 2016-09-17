#include "nodeUtils.h"

#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MObject.h>
#include <maya/MQuaternion.h>

#define MAKE_INPUT(attr)        \
    attr.setKeyable(true);      \
    attr.setChannelBox(false);  \
    attr.setStorable(true);     \
    attr.setWritable(true);     

#define MAKE_OUTPUT(attr)       \
    attr.setKeyable(false);     \
    attr.setChannelBox(false);  \
    attr.setStorable(false);    \
    attr.setWritable(false);    

MQuaternion inputQuaternionValue(MDataBlock &data, MObject &attr,  MObject &attrX, MObject &attrY, MObject &attrZ, MObject &attrW)
{
    MDataHandle attrHandle = data.inputValue(attr);
    
    double x = attrHandle.child(attrX).asDouble();
    double y = attrHandle.child(attrY).asDouble();
    double z = attrHandle.child(attrZ).asDouble();
    double w = attrHandle.child(attrW).asDouble();

    return MQuaternion(x, y, z, w);
}

MStatus outputQuaternionValue(MDataBlock &data, MQuaternion &value, MObject &attr,  MObject &attrX, MObject &attrY, MObject &attrZ, MObject &attrW)
{
    MDataHandle attrHandle = data.outputValue(attr);
    
    attrHandle.child(attrX).setDouble(value.x);
    attrHandle.child(attrY).setDouble(value.y);
    attrHandle.child(attrZ).setDouble(value.z);
    attrHandle.child(attrW).setDouble(value.w);

    attrHandle.setClean();
     
    return MStatus::kSuccess;    
}