/**
Copyright (c) 2016 Ryan Porter - arrayNodes
You may use, distribute, or modify this code under the terms of the MIT license.
*/

/*-----------------------------------------------------------------------------
    quatToAxisAngle node
    Converts a quaternion to a pivot vector and a rotation around that vector.

    inputQuat  (i1q)
        Quaternion to be converted

    axis  (axis)
        The axis about which the rotation occurs.

    angle (an)
        The angle of rotation about the axis.

-----------------------------------------------------------------------------*/

#include "quatToAxisAngle.h"
#include "nodeUtils.h"

#include <maya/MAngle.h>
#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MPlug.h>
#include <maya/MQuaternion.h>
#include <maya/MVector.h>

MObject QuatToAxisAngleNode::inputQuat_attr;
    MObject QuatToAxisAngleNode::inputQuatX_attr;
    MObject QuatToAxisAngleNode::inputQuatY_attr;
    MObject QuatToAxisAngleNode::inputQuatZ_attr;
    MObject QuatToAxisAngleNode::inputQuatW_attr;

MObject QuatToAxisAngleNode::outputAxis_attr;
    MObject QuatToAxisAngleNode::outputAxisX_attr;
    MObject QuatToAxisAngleNode::outputAxisY_attr;
    MObject QuatToAxisAngleNode::outputAxisZ_attr;

MObject QuatToAxisAngleNode::outputAngle_attr;

void* QuatToAxisAngleNode::creator()
{
    return new QuatToAxisAngleNode();
}


MStatus QuatToAxisAngleNode::initialize()
{
    MStatus status;

    MFnCompoundAttribute c;
    MFnNumericAttribute n;
    MFnUnitAttribute u;

    inputQuatX_attr = n.create("inputQuatX", "iqx", MFnNumericData::kDouble, 0.0, &status);
    MAKE_INPUT(n)

    inputQuatY_attr = n.create("inputQuatY", "iqy", MFnNumericData::kDouble, 0.0, &status);
    MAKE_INPUT(n);

    inputQuatZ_attr = n.create("inputQuatZ", "iqz", MFnNumericData::kDouble, 0.0, &status); 
    MAKE_INPUT(n);

    inputQuatW_attr = n.create("inputQuatW", "iw", MFnNumericData::kDouble, 1.0, &status);
    MAKE_INPUT(n);

    inputQuat_attr = c.create("inputQuat", "iq", &status);
    c.addChild(inputQuatX_attr);
    c.addChild(inputQuatY_attr);
    c.addChild(inputQuatZ_attr);
    c.addChild(inputQuatW_attr);

    outputAxisX_attr = n.create("axisX", "asx", MFnNumericData::kDouble, 1.0, &status);
    MAKE_OUTPUT(n);

    outputAxisY_attr = n.create("axisY", "asy", MFnNumericData::kDouble, 1.0, &status);
    MAKE_OUTPUT(n);

    outputAxisZ_attr = n.create("axisZ", "asz", MFnNumericData::kDouble, 1.0, &status);
    MAKE_OUTPUT(n);

    outputAxis_attr = c.create("axis", "as", &status);
    c.addChild(outputAxisX_attr);
    c.addChild(outputAxisY_attr);
    c.addChild(outputAxisZ_attr);

    outputAngle_attr = u.create("angle", "an", MFnUnitAttribute::kAngle, 0.0);
    MAKE_OUTPUT(u);

    addAttribute(inputQuat_attr);
    addAttribute(outputAxis_attr);
    addAttribute(outputAngle_attr);

    attributeAffects(inputQuat_attr, outputAngle_attr);
    attributeAffects(inputQuat_attr, outputAxis_attr);

    return MStatus::kSuccess;
}


MStatus QuatToAxisAngleNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != outputAxis_attr && plug != outputAngle_attr && plug.parent() != outputAxis_attr)
        return MStatus::kUnknownParameter;

    MQuaternion inputQuat = inputQuaternionValue(
        data, 
        inputQuat_attr,
        inputQuatX_attr,
        inputQuatY_attr,
        inputQuatZ_attr,
        inputQuatW_attr 
    );

    double angle = 0.0;
    MVector axis;

    bool nonZero = inputQuat.getAxisAngle(axis, angle);

    MDataHandle axisHandle = data.outputValue(outputAxis_attr);
    MDataHandle angleHandle = data.outputValue(outputAngle_attr);

    axisHandle.set(axis.x, axis.y, axis.z);
    axisHandle.setClean();

    angleHandle.setMAngle(MAngle(angle, MAngle::kRadians));
    angleHandle.setClean();

    return MStatus::kSuccess;   
}