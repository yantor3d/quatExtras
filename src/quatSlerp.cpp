/**
Copyright (c) 2016 Ryan Porter - arrayNodes
You may use, distribute, or modify this code under the terms of the MIT license.
*/

/*-----------------------------------------------------------------------------
    quatSlerp node
    Computes the spherical linear interpolation of two quaternions.

    input1Quat  (i1q)
        Quaternion to rotate from.

    input2Quat  (i2q)
        Quaternion to rotate to. 
        
    tween       (t)
        Percent of the interpolation between the two inputs. 

    spin        (s)
        Number of complete revolutions around the axis. If spin is negative, 
        the interpolation will take the "long" path on the quaternion sphere.

    outputQuat  (oq)
        Interpolated quaternion rotation.

-----------------------------------------------------------------------------*/


#include "quatSlerp.h"
#include "nodeUtils.h"

#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MPlug.h>
#include <maya/MQuaternion.h>

MObject QuatSlerpNode::input1Quat_attr;
    MObject QuatSlerpNode::input1QuatX_attr;
    MObject QuatSlerpNode::input1QuatY_attr;
    MObject QuatSlerpNode::input1QuatZ_attr;
    MObject QuatSlerpNode::input1QuatW_attr;

MObject QuatSlerpNode::input2Quat_attr;
    MObject QuatSlerpNode::input2QuatX_attr;
    MObject QuatSlerpNode::input2QuatY_attr;
    MObject QuatSlerpNode::input2QuatZ_attr;
    MObject QuatSlerpNode::input2QuatW_attr;

MObject QuatSlerpNode::interpolationValue_attr;
MObject QuatSlerpNode::spin_attr;

MObject QuatSlerpNode::outputQuat_attr;
    MObject QuatSlerpNode::outputQuatX_attr;
    MObject QuatSlerpNode::outputQuatY_attr;
    MObject QuatSlerpNode::outputQuatZ_attr;
    MObject QuatSlerpNode::outputQuatW_attr;

void* QuatSlerpNode::creator()
{
    return new QuatSlerpNode();
}


MStatus QuatSlerpNode::initialize()
{
    MStatus status;

    MFnCompoundAttribute c;
    MFnNumericAttribute n;

    input1QuatX_attr = n.create("input1QuatX", "i1x", MFnNumericData::kDouble, 0.0, &status);
    MAKE_INPUT(n)

    input1QuatY_attr = n.create("input1QuatY", "i1y", MFnNumericData::kDouble, 0.0, &status);
    MAKE_INPUT(n);

    input1QuatZ_attr = n.create("input1QuatZ", "i1z", MFnNumericData::kDouble, 0.0, &status); 
    MAKE_INPUT(n);

    input1QuatW_attr = n.create("input1QuatW", "i1w", MFnNumericData::kDouble, 1.0, &status);
    MAKE_INPUT(n);

    input1Quat_attr = c.create("input1Quat", "i1q", &status);
    c.addChild(input1QuatX_attr);
    c.addChild(input1QuatY_attr);
    c.addChild(input1QuatZ_attr);
    c.addChild(input1QuatW_attr);

    input2QuatX_attr = n.create("input2QuatX", "i2x", MFnNumericData::kDouble, 0.0, &status);
    MAKE_INPUT(n);

    input2QuatY_attr = n.create("input2QuatY", "i2y", MFnNumericData::kDouble, 0.0, &status);
    MAKE_INPUT(n);

    input2QuatZ_attr = n.create("input2QuatZ", "i2z", MFnNumericData::kDouble, 0.0, &status);
    MAKE_INPUT(n);

    input2QuatW_attr = n.create("input2QuatW", "i2w", MFnNumericData::kDouble, 1.0, &status);
    MAKE_INPUT(n);

    input2Quat_attr = c.create("input2Quat", "i2q", &status);
    c.addChild(input2QuatX_attr);
    c.addChild(input2QuatY_attr);
    c.addChild(input2QuatZ_attr);
    c.addChild(input2QuatW_attr);

    interpolationValue_attr = n.create("tween", "t", MFnNumericData::kDouble, 0.0, &status);
    MAKE_INPUT(n);
    n.setMin(0.0);
    n.setMax(1.0);

    spin_attr = n.create("spin", "s", MFnNumericData::kShort, 0.0, &status);
    MAKE_INPUT(n);

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

    addAttribute(input1Quat_attr);
    addAttribute(input2Quat_attr);
    addAttribute(interpolationValue_attr);
    addAttribute(spin_attr);

    addAttribute(outputQuat_attr);

    attributeAffects(input1Quat_attr, outputQuat_attr);
    attributeAffects(input2Quat_attr, outputQuat_attr);
    attributeAffects(interpolationValue_attr, outputQuat_attr);
    attributeAffects(spin_attr, outputQuat_attr);

    return MStatus::kSuccess;
}


MStatus QuatSlerpNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != outputQuat_attr && plug.parent() != outputQuat_attr)
    {
        return MStatus::kUnknownParameter;
    }

    MQuaternion p = inputQuaternionValue(
        data,
        input1Quat_attr,
        input1QuatX_attr,
        input1QuatY_attr,
        input1QuatZ_attr,
        input1QuatW_attr 
    );

    MQuaternion q = inputQuaternionValue(
        data,
        input2Quat_attr,
        input2QuatX_attr,
        input2QuatY_attr,
        input2QuatZ_attr,
        input2QuatW_attr 
    );

    double t = data.inputValue(interpolationValue_attr).asDouble();
    short s = data.inputValue(spin_attr).asShort();

    MQuaternion output = slerp(p, q, t, s);

    outputQuaternionValue(
        data,
        output,
        outputQuat_attr,
        outputQuatX_attr,
        outputQuatY_attr,
        outputQuatZ_attr,
        outputQuatW_attr
    );

    return MStatus::kSuccess;   
}