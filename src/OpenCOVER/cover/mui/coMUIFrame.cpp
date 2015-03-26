// class, which creates a new menu as VRUI
// creates a Frame as TUI


#include <cover/coVRTui.h>
#include <cover/coTabletUI.h>
#include <cover/coVRPluginSupport.h>
#include <OpenVRUI/coRowMenu.h>
#include <OpenVRUI/coMenuItem.h>
#include "coMUIFrame.h"
#include "support/coMUIConfigManager.h"

using namespace opencover;
using namespace vrui;

// constructor:
coMUIFrame::coMUIFrame(const std::string UniqueIdentifier, coMUIContainer* parent)
{
    ConfigManager = NULL;
    Label = UniqueIdentifier;
    constructor(UniqueIdentifier, parent, Label);
}

coMUIFrame::coMUIFrame(const std::string UniqueIdentifier, coMUIContainer* parent, std::string label)
{
    ConfigManager = NULL;
    Label = label;
    constructor(UniqueIdentifier, parent, Label);
}

// destructor:
coMUIFrame::~coMUIFrame()
{
    ConfigManager->removeElement(Identifier);
    ConfigManager->deletePosFromPosList(Identifier);
}

// underlying constructor:
void coMUIFrame::constructor(const std::string UniqueIdentifier, coMUIContainer* parent, std::string label)
{
    ConfigManager= coMUIConfigManager::getInstance();

    Parent=parent;
    Identifier=UniqueIdentifier;

    ConfigManager->addElement(UniqueIdentifier, this);

    // create defaultvalue or take from constructor:
    // TUI-Tablet-Element:
    Devices.push_back(device());
    Devices[0].Device = ConfigManager->keywordTablet();
    Devices[0].UI = ConfigManager->keywordTUI();
    Devices[0].Identifier = UniqueIdentifier;
    Devices[0].Visible = true;

    Devices[0].Label = ConfigManager->getCorrectLabel(Label, Devices[0].UI, Devices[0].Device, Devices[0].Identifier);
    Parent= ConfigManager->getCorrectParent(Parent, Devices[0].UI, Devices[0].Device, Devices[0].Identifier);
    // create TUI-Element:
    TUIElement.reset(new coTUIFrame(Devices[0].Label, Parent->getTUIID()));

    // VRUI-CAVE-Element:
    Devices.push_back(device());
    Devices[1].Device= ConfigManager->keywordCAVE();
    Devices[1].UI= ConfigManager->keywordVRUI();
    Devices[1].Identifier = UniqueIdentifier;
    Devices[1].Visible = true;

    Devices[1].Label = ConfigManager->getCorrectLabel(Label, Devices[1].UI, Devices[1].Device, Devices[1].Identifier);
    Parent= ConfigManager->getCorrectParent(Parent, Devices[1].UI, Devices[1].Device, Devices[1].Identifier);
    // create VRUI-Element:
    Submenu.reset(new vrui::coRowMenu(Devices[1].Label.c_str()));
    SubmenuItem.reset(new vrui::coSubMenuItem(Devices[1].Label));
    SubmenuItem->setMenu(Submenu.get());

    // find and set correct parameter (get them from configuration file, if possible):
    for (size_t i=0; i<Devices.size(); ++i)
    {
        Devices[i].Visible = ConfigManager->getCorrectVisible(Devices[i].Visible, Devices[i].UI, Devices[i].Device, Devices[i].Identifier);
        Devices[i].Label = ConfigManager->getCorrectLabel(Label, Devices[i].UI, Devices[i].Device, Devices[i].Identifier);

        // create UI-Elements:
        if  (Devices[i].UI==ConfigManager->keywordTUI())                       // create TUI-Element
        {
            std::pair<int,int> pos=ConfigManager->getCorrectPos(Devices[i].UI, Devices[i].Device, Devices[i].Identifier, Parent->getUniqueIdentifier());
            ConfigManager->preparePos(pos, Parent->getUniqueIdentifier());
            TUIElement->setPos(pos.first, pos.second);
            ConfigManager->addPosToPosList(Devices[i].Identifier, pos, Parent->getUniqueIdentifier(), true);
            TUIElement->setHidden(!Devices[i].Visible);
        }
        else if (Devices[i].UI==ConfigManager->keywordVRUI())                  // create VRUI-Elements
        {
            SubmenuItem->setMenu(Submenu.get());

            if (Devices[i].Visible)                                            // visible
            {
                ConfigManager->getCorrectParent(parent, Devices[i].UI, Devices[i].Device, Devices[i].Identifier)->getVRUI()->add(SubmenuItem.get());
            }
            else
            {                                                               // invisible
                ConfigManager->getCorrectParent(parent, Devices[i].UI, Devices[i].Device, Devices[i].Identifier)->getVRUI()->remove(SubmenuItem.get());
            }
        }
        else
        {
            std::cerr << "coMUITab::ParentConstructor: " << Devices[i].UI << " not found in Constructor." << std::endl;
        }
    }
}


// returns the parent-element
coMUIContainer* coMUIFrame::getParent()
{
    return Parent;
}

// returns ID of TUI-Element
int coMUIFrame::getTUIID()
{
    return (TUIElement->getID());
}

// returns VRUI-Element
vrui::coMenu* coMUIFrame::getVRUI()
{
    return Submenu.get();
}

// set label for named UI-Elements
void coMUIFrame::setLabel(std::string label, std::string UI)
{
    for (size_t i=0; i<Devices.size(); ++i)
    {
        if (UI.find(Devices[i].UI) != std::string::npos)                       // element to be changed
        {
            Devices[i].Label=ConfigManager->getCorrectLabel(label, Devices[i].UI, Devices[i].Device, Devices[i].Identifier);
            if (Devices[i].UI == ConfigManager->keywordTUI())                  // TUI-Element
            {
                TUIElement->setLabel(Devices[i].Label);
            } else if (Devices[i].UI == ConfigManager->keywordVRUI())          // VRUI-Element
            {
                SubmenuItem->setLabel(Devices[i].Label);
                Submenu->updateTitle(Devices[i].Label.c_str());
            } else
            {
                std::cerr << "coMUIFrame::setLabel(): Elementtype " << Devices[i].UI << " not found in setLabel(std::string, std::string)." << std::endl;
            }
        }
    }
}

// set label for all UI-Elements
void coMUIFrame::setLabel(std::string label)
{
    std::string UI;
    for (size_t i=0; i<Devices.size(); ++i)
    {
        UI.append(Devices[i].UI + " ");
    }
    setLabel(label, UI);
}

// return pointer to TUIElement
coTUIElement* coMUIFrame::getTUI()
{
    return TUIElement.get();
}

// set visible-value for named UI-Elements
void coMUIFrame::setVisible(bool visible, std::string UI)
{
    for (size_t i=0; i<Devices.size(); ++i)
    {
        if (UI.find(Devices[i].UI)!=std::string::npos)                             // element shall be changed
        {
            if (Devices[i].Visible != visible)                                     // visible-value changed
            {
                Devices[i].Visible = ConfigManager->getCorrectVisible(visible, Devices[i].UI, Devices[i].Device, Devices[i].Identifier);
                if (Devices[i].UI == ConfigManager->keywordTUI())                  // TUI-Element
                {
                    TUIElement->setHidden(!Devices[i].Visible);
                } else if (Devices[i].UI == ConfigManager->keywordVRUI())          // VRUI-Element
                {
                    if (Devices[i].Visible)
                    {
                        Parent->getVRUI()->add(SubmenuItem.get());
                    } else{
                        Parent->getVRUI()->remove(SubmenuItem.get());
                    }
                } else{
                    std::cerr << "coMUIFrame::setVisible(): Elementtyp " << Devices[i].UI << " not found in setVisible(string, bool, bool)." << std::endl;
                }
            }
        }
    }
}

// set visible-value for all UI-Elements
void coMUIFrame::setVisible(bool visible)
{
    std::string UI;
    for (size_t i=0; i<Devices.size(); ++i)
    {
        UI.append(Devices[i].UI + " ");
    }
    setVisible(visible, UI);
}

// set position for TUI-Element
void coMUIFrame::setPos(int posx, int posy)
{
    std::pair<int,int> pos(posx,posy);
    for (size_t i=0; i<Devices.size(); ++i)
    {
        if (Devices[i].UI == ConfigManager->keywordTUI())                      // TUI-Element
        {
            if (ConfigManager->getIdentifierByPos(pos, Parent->getUniqueIdentifier()) != Devices[i].Identifier)     // if is equal: Element is already at correct position
            {
                pos=ConfigManager->getCorrectPos(pos, Devices[i].UI, Devices[i].Device, Devices[i].Identifier);
                ConfigManager->preparePos(pos, Parent->getUniqueIdentifier());
                ConfigManager->deletePosFromPosList(Devices[i].Identifier);
                TUIElement->setPos(pos.first,pos.second);
                ConfigManager->addPosToPosList(Devices[i].Identifier, pos, Parent->getUniqueIdentifier(), false);
            }
        }
    }
}

std::string coMUIFrame::getUniqueIdentifier()
{
    return Devices[0].Identifier;
}