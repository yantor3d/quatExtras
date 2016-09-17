#ifndef NODE_UTILS_H
#define NODE_UTILS_H

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

MQuaternion inputQuaternionValue(MDataBlock &data, MObject &attr,  MObject &attrX, MObject &attrY, MObject &attrZ, MObject &attrW);
MStatus outputQuaternionValue(MDataBlock &data, MQuaternion &value, MObject &attr,  MObject &attrX, MObject &attrY, MObject &attrZ, MObject &attrW);
#endif