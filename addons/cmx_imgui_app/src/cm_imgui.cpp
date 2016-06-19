//
//  cm_imgui.cpp
//  basic
//
//  Created by Daniel Berio on 09/04/16.
//  Copyright (c) 2016 Daniel Berio. All rights reserved.
//

#include "cm_imgui.h"


namespace cm
{
    extern ImFont * iconFont;
}

namespace ImGui
{
    void BeginToolbar( const std::string & label, float x, float y )
    {
        static bool show = true;
        ImGui::Begin(label.c_str(),&show, ImVec2(x,y), 0.7f, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings);
    }
    
    void BeginHighlightButton()
    {
        float h = 0.0;
        ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(h, 0.8f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(h, 0.7f, 0.9f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(h, 0.8f, 0.9f));
    }
    
    void EndHighlightButton()
    {
        ImGui::PopStyleColor(3);
    }
    
    void Title( const std::string & title )
    {
        static bool alwaystrue = true;
        ImGui::PushStyleColor(ImGuiCol_Header, ImColor::HSV(0.0,0.0,0.3));
        ImGui::Selectable(title.c_str(), &alwaystrue);
        ImGui::PopStyleColor(1);
        alwaystrue = true;
    }
    
    void SetupStyleFromHue()
    {
#if 1
        // FIXME: those should become parameters to the function
        static int hue = 140;
        static float col_main_sat = 180.f/255.f;
        static float col_main_val = 161.f/255.f;
        static float col_area_sat = 124.f/255.f;
        static float col_area_val = 100.f/255.f;
        static float col_back_sat = 59.f/255.f;
        static float col_back_val = 40.f/255.f;
        
        ImGui::Begin("Hue Style");
        ImGui::SliderInt("master hue", &hue, 0, 255);
        
        float dummy;
        ImVec4 rgb;
        ImGui::ColorEditMode(ImGuiColorEditMode_HSV);
        
        ImGui::ColorConvertHSVtoRGB(hue/255.f, col_main_sat, col_main_val, rgb.x, rgb.y, rgb.z);
        ImGui::ColorEdit3("main", &rgb.x);
        ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_main_sat, col_main_val);
        
        ImGui::ColorConvertHSVtoRGB(hue/255.f, col_area_sat, col_area_val, rgb.x, rgb.y, rgb.z);
        ImGui::ColorEdit3("area", &rgb.x);
        ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_area_sat, col_area_val);
        
        ImGui::ColorConvertHSVtoRGB(hue/255.f, col_back_sat, col_back_val, rgb.x, rgb.y, rgb.z);
        ImGui::ColorEdit3("back", &rgb.x);
        ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_back_sat, col_back_val);
        
        ImGui::End();
#endif
        
        ImGuiStyle& style = ImGui::GetStyle();
        
        ImVec4 col_text = ImColor::HSV(hue/255.f,  20.f/255.f, 235.f/255.f);
        ImVec4 col_main = ImColor::HSV(hue/255.f, col_main_sat, col_main_val);
        ImVec4 col_back = ImColor::HSV(hue/255.f, col_back_sat, col_back_val);
        ImVec4 col_area = ImColor::HSV(hue/255.f, col_area_sat, col_area_val);
        
        style.Colors[ImGuiCol_Text]                  = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
        style.Colors[ImGuiCol_TextDisabled]          = ImVec4(col_text.x, col_text.y, col_text.z, 0.58f);
        style.Colors[ImGuiCol_WindowBg]              = ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
        style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(col_area.x, col_area.y, col_area.z, 0.00f);
        style.Colors[ImGuiCol_Border]                = ImVec4(col_text.x, col_text.y, col_text.z, 0.30f);
        style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg]               = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(col_main.x, col_main.y, col_main.z, 0.68f);
        style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
        style.Colors[ImGuiCol_TitleBg]               = ImVec4(col_main.x, col_main.y, col_main.z, 0.45f);
        style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
        style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
        style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(col_area.x, col_area.y, col_area.z, 0.57f);
        style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
        style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
        style.Colors[ImGuiCol_ComboBg]               = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
        style.Colors[ImGuiCol_CheckMark]             = ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);
        style.Colors[ImGuiCol_SliderGrab]            = ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
        style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
        style.Colors[ImGuiCol_Button]                = ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
        style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
        style.Colors[ImGuiCol_ButtonActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
        style.Colors[ImGuiCol_Header]                = ImVec4(col_main.x, col_main.y, col_main.z, 0.76f);
        style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
        style.Colors[ImGuiCol_HeaderActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
        style.Colors[ImGuiCol_Column]                = ImVec4(col_text.x, col_text.y, col_text.z, 0.32f);
        style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(col_text.x, col_text.y, col_text.z, 0.78f);
        style.Colors[ImGuiCol_ColumnActive]          = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
        style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
        style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
        style.Colors[ImGuiCol_CloseButton]           = ImVec4(col_text.x, col_text.y, col_text.z, 0.16f);
        style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(col_text.x, col_text.y, col_text.z, 0.39f);
        style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
        style.Colors[ImGuiCol_PlotLines]             = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
        style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
        style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
//        style.Colors[ImGuiCol_TooltipBg]             = ImVec4(col_main.x, col_main.y, col_main.z, 0.92f);
        style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    }
    
    bool IconButton(const std::string &str)
    {
        ImGui::PushFont(cm::iconFont);
        bool res = ImGui::Button(str.c_str());
        ImGui::PopFont();
        return res;
    }
    
    bool IconSelectable(const std::string &str, bool active)
    {
        ImGui::PushFont(cm::iconFont);
        active = ImGui::Selectable(str.c_str(), active, 0, ImVec2(20.,0));
        ImGui::PopFont();
        return active;
    }
    
}


// Combo box helper allowing to pass an array of strings.
static bool stringCombo(const char* label, int* current_item, const std::string * item_names, int items_count )
{
    std::string str = "";
    for( int i = 0; i < items_count; i++ )
    {
        str += item_names[i];
        str += (char)0;
    }
    return ImGui::Combo(label, current_item, str.c_str());
}

namespace cm
{

ImVec2 Mouse::_oldp;
ImVec2 Mouse::_delta;
    
void imgui( ParamList& plist, float cursorPos  )
{
    std::string id = plist.getPath() + "_ID";
    ImGui::PushID(id.c_str());
    
    float cposyPrev = ImGui::GetCursorPosY();
    
    bool vis = ImGui::CollapsingHeader(plist.getName().c_str(), ImGuiTreeNodeFlags_AllowOverlapMode | ImGuiTreeNodeFlags_DefaultOpen); //, NULL, true, true);
    
    float cposyNext = ImGui::GetCursorPosY();
    //ImGUi::SetCursorPosY(cposyPrev);
    //SameLine();
    
    //ImGui::PushItemWidth(-10);
    // in cm_imgui_app
    extern ImFont * iconFont;
    ImGui::PushFont(iconFont);
    ImGui::SameLine(ImGui::GetWindowWidth()-100);
    if(ImGui::Button("l")) //, ImVec2(100,2)))
    {
        std::string path;
        if(openFileDialog(path,"xml"))
            plist.loadXml(path.c_str());
    }
    //ImGui::NextColumn();
    ImGui::SameLine();
    if(ImGui::Button("s"))//, ImVec2(100,20)))
    {
        std::string path;
        if(saveFileDialog(path,"xml"))
            plist.saveXml(path.c_str());
    }
    ImGui::PopFont();
    //ImGui::PopItemWidth();
    
    if(!vis)
    {
        ImGui::PopID();
        return;
    }
    
    
    //if(!)
    //ImGui::OpenNextNode(true);
    //if(!ImGui::TreeNode(plist.getName().c_str()))
    
    for( int i = 0; i < plist.getNumParams(); i++ )
    {
        Param * p = plist.getParam(i);
        if(p->hasOption("h"))
            continue;
        if(p->hasOption("sameline"))
            ImGui::SameLine();
        
        switch(p->getType())
        {
            case PARAM_FLOAT:
                if(p->hasOption("v"))
                {
                    p->dirty = ImGui::InputFloat(p->getName(),(float*)p->getAddress());
                }
                else
                {
                    p->dirty = ImGui::SliderFloat(p->getName(), (float*)p->getAddress(), p->getMin(), p->getMax());
                }
                break;
                
            case PARAM_INT:
                p->dirty = ImGui::InputInt(p->getName(), (int*)p->getAddress());
                break;
                
            case PARAM_EVENT:
                if(ImGui::Button(p->getName()))
                {
                    p->dirty = true;
                    p->setBool(!p->getBool());
                }
                break;
                
            /*case PARAM_COLOR:
                ImGui::ColorEdit3(p->getName(), (float*)p->getAddress());
                break;
            */
                
            case PARAM_BOOL:
                p->dirty = ImGui::Checkbox(p->getName(), (bool*)p->getAddress());
                break;
                
            case PARAM_UNKNOWN:
                ImGui::Separator();
                break;
                
            case PARAM_SELECTION:
                p->dirty = stringCombo(p->getName(),(int*)p->getAddress(), p->getSelectionNames(), p->getNumElements() );
                break;
                
            case PARAM_CSTRING:
                p->dirty = ImGui::InputText(p->getName(),(char*)p->getAddress(), 50); // HACK!
                break;
                
        }
    }
    
    for( int i = 0; i < plist.getNumChildren(); i++ )
    {
        ImGui::Indent();
        imgui(*plist.getChild(i), cursorPos+20.0 );
        ImGui::Unindent();
    }
    
    //ImGui::TreePop();
    ImGui::PopID();
}

}
