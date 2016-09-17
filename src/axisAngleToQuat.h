#ifndef AXIS_ANGLE_TO_QUAT_H
#define AXIS_ANGLE_TO_QUAT_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class AxisAngleToQuatNode : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    static  void*           creator();
    static  MStatus         initialize();

public:
    static MTypeId          NODE_ID;
    static MString          NODE_NAME;

    static MObject          inputAngle_attr;
    static MObject          inputAxis_attr;
        static MObject          inputAxisX_attr;
        static MObject          inputAxisY_attr;
        static MObject          inputAxisZ_attr;

    static MObject          outputQuat_attr;
        static MObject          outputQuatX_attr;
        static MObject          outputQuatY_attr;
        static MObject          outputQuatZ_attr;
        static MObject          outputQuatW_attr;
};

#endif