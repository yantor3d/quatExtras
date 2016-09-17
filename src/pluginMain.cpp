/**
    Copyright (c) 2016 Ryan Porter
*/

/*
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/**
    Quat Extra Nodes

    author: Ryan Porter
    version: 1.0.0

    https://github.com/yantor3d

    Description
        Quaternion utility nodes that are missing from Autodesk Maya's quatNodes plugin.

    Nodes
        - axisAngleToQuat
        - quatSlerp node
        - quatToAxisAngle

    Commands
        - n/a
*/

#include "axisAngleToQuat.h"
#include "quatToAxisAngle.h"
#include "quatSlerp.h"

#include <maya/MFnPlugin.h>
#include <maya/MTypeId.h>
#include <maya/MString.h>

const char* kAUTHOR = "Ryan Porter";
const char* kVERSION = "1.0.0";
const char* kREQUIRED_API_VERSION = "Any";

MTypeId AxisAngleToQuatNode::NODE_ID(0x00126b3d);
MTypeId QuatToAxisAngleNode::NODE_ID(0x00126b3e);
MTypeId QuatSlerpNode::NODE_ID(0x00126b3f);

MString AxisAngleToQuatNode::NODE_NAME("axisAngleToQuat");
MString QuatToAxisAngleNode::NODE_NAME("quatToAxisAngle");
MString QuatSlerpNode::NODE_NAME("quatSlerp");


#define REGISTER_NODE(NODE)                    \
    status = fnPlugin.registerNode(            \
        NODE::NODE_NAME,                    \
        NODE::NODE_ID,                        \
        NODE::creator,                        \
        NODE::initialize                    \
    );                                        \
    CHECK_MSTATUS_AND_RETURN_IT(status);    \

#define DEREGISTER_NODE(NODE)                \
    status = fnPlugin.deregisterNode(        \
        NODE::NODE_ID                        \
    );                                        \
    CHECK_MSTATUS_AND_RETURN_IT(status);    \

MStatus initializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin fnPlugin(obj, kAUTHOR, kVERSION, kREQUIRED_API_VERSION);

    REGISTER_NODE(AxisAngleToQuatNode);
    REGISTER_NODE(QuatToAxisAngleNode);
    REGISTER_NODE(QuatSlerpNode);

    return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin fnPlugin(obj, kAUTHOR, kVERSION, kREQUIRED_API_VERSION);

    DEREGISTER_NODE(AxisAngleToQuatNode);
    DEREGISTER_NODE(QuatToAxisAngleNode);
    DEREGISTER_NODE(QuatSlerpNode);

    return MS::kSuccess;
}