#ifndef QUAT_TO_AXIS_ANGLE_H
#define QUAT_TO_AXIS_ANGLE_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class QuatToAxisAngleNode : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    static  void*           creator();
    static  MStatus         initialize();

public:
    static MTypeId          NODE_ID;
    static MString          NODE_NAME;

    static MObject          inputQuat_attr;
        static MObject          inputQuatX_attr;
        static MObject          inputQuatY_attr;
        static MObject          inputQuatZ_attr;
        static MObject          inputQuatW_attr;

    static MObject          outputAngle_attr;
    static MObject          outputAxis_attr;
        static MObject          outputAxisX_attr;
        static MObject          outputAxisY_attr;
        static MObject          outputAxisZ_attr;    
};

#endif