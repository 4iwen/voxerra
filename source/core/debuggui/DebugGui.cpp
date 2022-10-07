#include "DebugGui.h"

DebugGui::DebugGui(GLFWwindow* window)
{

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    SetStyle();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void DebugGui::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    // drawing
    if (_showDemoWindow)
    {
        ImGui::ShowDemoWindow(&_showDemoWindow);
    }

    {
        ImGui::Begin("Debug");
        ImGui::Checkbox("Demo window", &_showDemoWindow);
        if (ImGui::CollapsingHeader("Clear color"))
        {
            ImGui::SetNextItemWidth(200);
            ImGui::ColorPicker4("Clear color",
                                (float *) &_clearColor,
                                ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaBar |ImGuiColorEditFlags_DisplayRGB);
        }
    }
    ImGui::End();
    // drawing end

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

DebugGui::~DebugGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DebugGui::SetStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0;
    style.DisabledAlpha = 0.4000000059604645;
    style.WindowPadding = ImVec2(8.0, 8.0);
    style.WindowRounding = 7.0;
    style.WindowBorderSize = 1.0;
    style.WindowMinSize = ImVec2(32.0, 32.0);
    style.WindowTitleAlign = ImVec2(0.5, 0.5);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 4.0;
    style.ChildBorderSize = 1.0;
    style.PopupRounding = 4.0;
    style.PopupBorderSize = 1.0;
    style.FramePadding = ImVec2(5.0, 2.0);
    style.FrameRounding = 3.0;
    style.FrameBorderSize = 1.0;
    style.ItemSpacing = ImVec2(6.0, 6.0);
    style.ItemInnerSpacing = ImVec2(6.0, 6.0);
    style.CellPadding = ImVec2(6.0, 6.0);
    style.IndentSpacing = 25.0;
    style.ColumnsMinSpacing = 6.0;
    style.ScrollbarSize = 10.0;
    style.ScrollbarRounding = 4.0;
    style.GrabMinSize = 5.0;
    style.GrabRounding = 4.0;
    style.TabRounding = 4.0;
    style.TabBorderSize = 1.0;
    style.TabMinWidthForCloseButton = 0.0;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5, 0.5);
    style.SelectableTextAlign = ImVec2(0.0, 0.0);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0, 1.0, 1.0, 1.0);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464, 0.4980392158031464, 0.4980392158031464, 1.0);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248, 0.09803921729326248, 0.09803921729326248, 1.0);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0, 0.0, 0.0, 0.0);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1882352977991104, 0.1882352977991104, 0.1882352977991104, 0.9200000166893005);
    style.Colors[ImGuiCol_Border] = ImVec4(0.1882352977991104, 0.1882352977991104, 0.1882352977991104, 0.2899999916553497);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0, 0.0, 0.0, 0.239999994635582);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0470588244497776, 0.0470588244497776, 0.0470588244497776, 0.5400000214576721);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1882352977991104, 0.1882352977991104, 0.1882352977991104, 0.5400000214576721);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2000000029802322, 0.2196078449487686, 0.2274509817361832, 1.0);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0, 0.0, 0.0, 1.0);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0, 0.0, 0.0, 1.0);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0, 0.0, 0.0, 1.0);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158, 0.1372549086809158, 0.1372549086809158, 1.0);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776, 0.0470588244497776, 0.0470588244497776, 0.5400000214576721);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.0, 0.9999999403953552, 0.0, 0.7843137383460999);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4000000059604645, 0.4000000059604645, 0.4000000059604645, 0.5400000214576721);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5568627715110779, 0.5568627715110779, 0.5568627715110779, 0.5400000214576721);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0, 1.0, 0.0, 0.7843137383460999);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.0, 0.9999999403953552, 0.0, 0.7843137383460999);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5568627715110779, 0.5568627715110779, 0.5568627715110779, 0.5400000214576721);
    style.Colors[ImGuiCol_Button] = ImVec4(0.0470588244497776, 0.0470588244497776, 0.0470588244497776, 0.5400000214576721);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1882352977991104, 0.1882352977991104, 0.1882352977991104, 0.5400000214576721);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2000000029802322, 0.2196078449487686, 0.2274509817361832, 1.0);
    style.Colors[ImGuiCol_Header] = ImVec4(0.0, 0.0, 0.0, 0.5199999809265137);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0, 0.0, 0.0, 0.3600000143051147);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2000000029802322, 0.2196078449487686, 0.2274509817361832, 0.3300000131130219);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.2784313857555389, 0.2784313857555389, 0.2784313857555389, 0.2899999916553497);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.4392156898975372, 0.4392156898975372, 0.4392156898975372, 0.2899999916553497);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.4000000059604645, 0.4392156898975372, 0.4666666686534882, 1.0);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2784313857555389, 0.2784313857555389, 0.2784313857555389, 0.2899999916553497);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4392156898975372, 0.4392156898975372, 0.4392156898975372, 0.2899999916553497);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4000000059604645, 0.4392156898975372, 0.4666666686534882, 1.0);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.0, 0.0, 0.0, 0.5199999809265137);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1372549086809158, 0.1372549086809158, 0.1372549086809158, 1.0);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.2000000029802322, 0.2000000029802322, 0.2000000029802322, 0.3600000143051147);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0, 0.0, 0.0, 0.5199999809265137);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1372549086809158, 0.1372549086809158, 0.1372549086809158, 1.0);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0, 1.0, 0.0, 1.0);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0, 1.0, 0.0, 0.7081544995307922);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.1372549086809158, 0.1372549086809158, 0.1372549086809158, 1.0);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0, 1.0, 0.0, 0.7098039388656616);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0, 0.0, 0.0, 0.5199999809265137);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0, 0.0, 0.0, 0.5199999809265137);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2784313857555389, 0.2784313857555389, 0.2784313857555389, 0.2899999916553497);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0, 0.0, 0.0, 0.0);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0, 1.0, 1.0, 0.05999999865889549);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2000000029802322, 0.2196078449487686, 0.2274509817361832, 1.0);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0, 1.0, 0.0, 1.0);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.9803921580314636, 1.0, 0.0, 1.0);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.9921568632125854, 1.0, 0.0, 0.1587982773780823);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.0, 1.0, 0.0, 0.1587982773780823);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.9843137264251709, 1.0, 0.0, 0.1587982773780823);
    style.Colors[ImGuiCol_DockingPreview] = ImVec4(1.00f, 1.00f, 0.00f, 0.70f);
}

ImVec4 DebugGui::GetClearColor()
{
    return _clearColor;
}
