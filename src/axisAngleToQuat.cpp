/**
Copyright (c) 2016 Ryan Porter - arrayNodes
You may use, distribute, or modify this code under the terms of the MIT license.
*/

/*-----------------------------------------------------------------------------
    axisAngleToQuat node
    Constructs a quaternion whose rotation is expressed by a rotation about an axis.

    axis  (axis)
        The axis about which the rotation occurs.

    angle (an)
        The angle of rotation about the axis.

    outputQuat  (oq)
        Quaternion rotation around the axis.

-----------------------------------------------------------------------------*/

#include "axisAngleToQuat.h"
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

MObject AxisAngleToQuatNode::inputAngle_attr;
MObject AxisAngleToQuatNode::inputAxis_attr;
    MObject AxisAngleToQuatNode::inputAxisX_attr;
    MObject AxisAngleToQuatNode::inputAxisY_attr;
    MObject AxisAngleToQuatNode::inputAxisZ_attr;

MObject AxisAngleToQuatNode::outputQuat_attr;
    MObject AxisAngleToQuatNode::outputQuatX_attr;
    MObject AxisAngleToQuatNode::outputQuatY_attr;
    MObject AxisAngleToQuatNode::outputQuatZ_attr;
    MObject AxisAngleToQuatNode::outputQuatW_attr;

void* AxisAngleToQuatNode::creator()
{
    return new AxisAngleToQuatNode();
}

MStatus AxisAngleToQuatNode::initialize()
{
    MStatus status;

    MFnCompoundAttribute c;
    MFnNumericAttribute n;
    MFnUnitAttribute u;

    inputAxisX_attr = n.create("axisX", "asx", MFnNumericData::kDouble, 1.0, &status);
    MAKE_INPUT(n);

    inputAxisY_attr = n.create("axisY", "asy", MFnNumericData::kDouble, 1.0, &status);
    MAKE_INPUT(n);

    inputAxisZ_attr = n.create("axisZ", "asz", MFnNumericData::kDouble, 1.0, &status);
    MAKE_INPUT(n);

    inputAxis_attr = c.create("axis", "as", &status);
    c.addChild(inputAxisX_attr);
    c.addChild(inputAxisY_attr);
    c.addChild(inputAxisZ_attr);

    inputAngle_attr = u.create("angle", "an", MFnUnitAttribute::kAngle, 0.0);
    MAKE_INPUT(u);

    outputQuatX_attr = n.create("outputQuatX", "oqx", MFnNumericData::kDouble, 0.0, &status);
    MAKE_OUTPUT(n);

    outputQuatY_attr = n.create("outputQuatY", "oqy", MFnNumericData::kDouble, 0.0, &status);
    MAKE_OUTPUT(n);

    outputQuatZ_attr = n.create("outputQuatZ", "oqz", MFnNumericData::kDouble, 0.0, &status);
    MAKE_OUTPUT(n);

    outputQuatW_attr = n.create("outputQuatW", "oqw", MFnNumericData::kDouble, 1.0, &status);
    MAKE_OUTPUT(n);

    outputQuat_attr = c.create("outputQuat", "oq", &status);
    c.addChild(outputQuatX_attr);
    c.addChild(outputQuatY_attr);
    c.addChild(outputQuatZ_attr);
    c.addChild(outputQuatW_attr);

    addAttribute(inputAxis_attr);
    addAttribute(inputAngle_attr);
    addAttribute(outputQuat_attr);

    attributeAffects(inputAxis_attr, outputQuat_attr);
    attributeAffects(inputAngle_attr, outputQuat_attr);

    return MStatus::kSuccess;
}

MStatus AxisAngleToQuatNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != outputQuat_attr && plug.parent() != outputQuat_attr)
        return MStatus::kUnknownParameter;

    MDataHandle inputAxisHandle = data.inputValue(inputAxis_attr);
    double x = inputAxisHandle.child(inputAxisX_attr).asDouble();
    double y = inputAxisHandle.child(inputAxisY_attr).asDouble();
    double z = inputAxisHandle.child(inputAxisZ_attr).asDouble();

    MAngle angle = data.inputValue(inputAngle_attr).asAngle();    
    
    MQuaternion outputQuat(angle.asRadians(), MVector(x, y, z));

    outputQuaternionValue(
        data,
        outputQuat,
        outputQuat_attr,
        outputQuatX_attr,
        outputQuatY_attr,
        outputQuatZ_attr,
        outputQuatW_attr
    );

    return MStatus::kSuccess;   
}