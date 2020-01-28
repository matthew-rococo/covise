/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

/****************************************************************************\ 
 **                                                            (C)2001 HLRS  **
 **                                                                          **
 ** Description: Template Plugin (does nothing)                              **
 **                                                                          **
 **                                                                          **
 ** Author: U.Woessner		                                                **
 **                                                                          **
 ** History:  								                                **
 ** Nov-01  v1	    				       		                            **
 **                                                                          **
 **                                                                          **
\****************************************************************************/

#include "TUIWebviewPlugin.h"
#include <cover/coVRPluginSupport.h>
#include <cover/RenderObject.h>
#include <cover/coVRTui.h>

using namespace opencover;

WebviewPlugin::WebviewPlugin()
{
    //new TUIWebview(int id, int type, QWidget * w, int parent, QString name)
    fprintf(stderr, "WebviewPlugin::WebviewPlugin\n");
}

// this is called if the plugin is removed at runtime
WebviewPlugin::~WebviewPlugin()
{
    fprintf(stderr, "WebviewPlugin::~WebviewPlugin\n");
}

// here we get the size and the current center of the cube
void
WebviewPlugin::newInteractor(RenderObject *container, coInteractor *i)
{
    (void)container;
    (void)i;
    fprintf(stderr, "WebviewPlugin::newInteractor\n");
}

void WebviewPlugin::addObject(RenderObject *container,
                               RenderObject *obj, RenderObject *normObj,
                               RenderObject *colorObj, RenderObject *texObj,
                               osg::Group *root,
                               int numCol, int colorBinding, int colorPacking,
                               float *r, float *g, float *b, int *packedCol,
                               int numNormals, int normalBinding,
                               float *xn, float *yn, float *zn, float transparency)
{
    (void)container;
    (void)obj;
    (void)normObj;
    (void)colorObj;
    (void)texObj;
    (void)root;
    (void)numCol;
    (void)colorBinding;
    (void)colorPacking;
    (void)r;
    (void)g;
    (void)b;
    (void)packedCol;
    (void)numNormals;
    (void)normalBinding;
    (void)xn;
    (void)yn;
    (void)zn;
    (void)transparency;
    fprintf(stderr, "WebviewPlugin::addObject\n");
}

void
WebviewPlugin::removeObject(const char *objName, bool replace)
{
    (void)objName;
    (void)replace;
    fprintf(stderr, "WebviewPlugin::removeObject\n");
}

void
WebviewPlugin::preFrame()
{
}

bool WebviewPlugin::init()
{
    fprintf(stderr, "WebviewPlugin::WebviewPlugin\n");

    WebviewTab = new coTUITab("Webview", coVRTui::instance()->mainFolder->getID());
    WebviewTab->setPos(0, 0);

    const std::string& n = "WebviewTest";
    int pID = 0;
    Webview = new coTUIWebview(n, pID);
    return true;
}

COVERPLUGIN(WebviewPlugin)
