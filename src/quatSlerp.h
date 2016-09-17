#ifndef QUAT_SLERP_H
#define QUAT_SLERP_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class QuatSlerpNode : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    static  void*           creator();
    static  MStatus         initialize();

public:
    static MTypeId          NODE_ID;
    static MString          NODE_NAME;

    static MObject          input1Quat_attr;
        static MObject          input1QuatX_attr;
        static MObject          input1QuatY_attr;
        static MObject          input1QuatZ_attr;
        static MObject          input1QuatW_attr;

    static MObject          input2Quat_attr;
        static MObject          input2QuatX_attr;
        static MObject          input2QuatY_attr;
        static MObject          input2QuatZ_attr;
        static MObject          input2QuatW_attr;

    static MObject          interpolationValue_attr;
    static MObject          spin_attr;

    static MObject          outputQuat_attr;
        static MObject          outputQuatX_attr;
        static MObject          outputQuatY_attr;
        static MObject          outputQuatZ_attr;
        static MObject          outputQuatW_attr;
};

#endif