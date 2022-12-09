#include "DebugGui.h"

DebugGui::DebugGui(GLFWwindow* window, Camera* camera)
{
    this->window = window;
    this->camera = camera;

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

    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void DebugGui::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    // drawing
    if (showDemoWindow)
    {
        ImGui::ShowDemoWindow(&showDemoWindow);
    }

    {
        ImGui::Begin("Debug");
        FrameTimesGraph();
        ImGui::Spacing();
        if (ImGui::CollapsingHeader("Rendering settings"))
        {
            if (ImGui::TreeNode("Camera"))
            {
                ImGui::Text("Position: x: %.1f, y: %.1f, z: %.1f", camera->position.x, camera->position.y, camera->position.z);
                ImGui::Text("Yaw: %.1f, Pitch: %.1f", camera->yaw, camera->pitch);
                ImGui::Text("Fov: %.1f", camera->fov);
                ImGui::TreePop();
            }
            ImGui::Spacing();
            ImGui::Checkbox("Vsync", &vsync);
            ImGui::Spacing();
            if (ImGui::TreeNode("Polygon mode"))
            {
                ImGui::RadioButton("Solid", &polygonMode, 0);
                ImGui::RadioButton("Wireframe", &polygonMode, 1);
                ImGui::RadioButton("Point", &polygonMode, 2);
                ImGui::TreePop();
            }
            ImGui::Spacing();
            ImGui::SetNextItemWidth(200);
            ImGui::ColorPicker3("Clear color",(float *) &clearColor);
        }
        if (ImGui::CollapsingHeader("Terrain settings"))
        {

        }
        ImGui::Spacing();
        ImGui::Checkbox("Demo window", &showDemoWindow);
        ImGui::End();
    }
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
    // Voxerra Dark Theme style
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0;
    style.DisabledAlpha = 0.6000000238418579;
    style.WindowPadding = ImVec2(8.0, 8.0);
    style.WindowRounding = 4.0;
    style.WindowBorderSize = 0.0;
    style.WindowMinSize = ImVec2(32.0, 32.0);
    style.WindowTitleAlign = ImVec2(0.5, 0.5);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ChildRounding = 4.0;
    style.ChildBorderSize = 0.0;
    style.PopupRounding = 4.0;
    style.PopupBorderSize = 0.0;
    style.FramePadding = ImVec2(4.0, 3.0);
    style.FrameRounding = 4.0;
    style.FrameBorderSize = 0.0;
    style.ItemSpacing = ImVec2(8.0, 4.0);
    style.ItemInnerSpacing = ImVec2(4.0, 4.0);
    style.CellPadding = ImVec2(4.0, 2.0);
    style.IndentSpacing = 21.0;
    style.ColumnsMinSpacing = 6.0;
    style.ScrollbarSize = 14.0;
    style.ScrollbarRounding = 4.0;
    style.GrabMinSize = 10.0;
    style.GrabRounding = 4.0;
    style.TabRounding = 4.0;
    style.TabBorderSize = 0.0;
    style.TabMinWidthForCloseButton = 0.0;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5, 0.5);
    style.SelectableTextAlign = ImVec2(0.0, 0.0);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0, 1.0, 1.0, 1.0);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464, 0.4980392158031464, 0.4980392158031464, 1.0);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.2117647081613541, 0.2235294133424759, 0.2470588237047195, 1.0);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1843137294054031, 0.1921568661928177, 0.2117647081613541, 1.0);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261, 0.0784313753247261, 0.0784313753247261, 0.9399999976158142);
    style.Colors[ImGuiCol_Border] = ImVec4(0.4274509847164154, 0.4274509847164154, 0.4980392158031464, 0.5);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0, 0.0, 0.0, 0.0);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.3098039329051971, 0.3294117748737335, 0.3607843220233917, 1.0);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3098039329051971, 0.3294117748737335, 0.3607843220233917, 1.0);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.3450980484485626, 0.3960784375667572, 0.9490196108818054, 1.0);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.125490203499794, 0.1333333402872086, 0.1450980454683304, 1.0);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.125490203499794, 0.1333333402872086, 0.1450980454683304, 1.0);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.125490203499794, 0.1333333402872086, 0.1450980454683304, 1.0);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.125490203499794, 0.1333333402872086, 0.1450980454683304, 1.0);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153, 0.01960784383118153, 0.01960784383118153, 0.5299999713897705);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971, 0.3098039329051971, 0.3098039329051971, 1.0);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879, 0.407843142747879, 0.407843142747879, 1.0);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906, 0.5098039507865906, 0.5098039507865906, 1.0);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3450980484485626, 0.3960784375667572, 0.9490196108818054, 1.0);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3450980484485626, 0.3960784375667572, 0.9490196108818054, 1.0);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.3450980484485626, 0.3960784375667572, 0.9490196108818054, 1.0);
    style.Colors[ImGuiCol_Button] = ImVec4(0.3098039329051971, 0.3294117748737335, 0.3607843220233917, 1.0);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.407843142747879, 0.4274509847164154, 0.4509803950786591, 1.0);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.125490203499794, 0.1333333402872086, 0.1450980454683304, 1.0);
    style.Colors[ImGuiCol_Header] = ImVec4(0.407843142747879, 0.4274509847164154, 0.4509803950786591, 1.0);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.407843142747879, 0.4274509847164154, 0.4509803950786591, 1.0);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.407843142747879, 0.4274509847164154, 0.4509803950786591, 1.0);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154, 0.4274509847164154, 0.4980392158031464, 0.5);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.09803921729326248, 0.4000000059604645, 0.7490196228027344, 0.7799999713897705);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.09803921729326248, 0.4000000059604645, 0.7490196228027344, 1.0);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2588235437870026, 0.5882353186607361, 0.9764705896377563, 0.2000000029802322);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2588235437870026, 0.5882353186607361, 0.9764705896377563, 0.6700000166893005);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2588235437870026, 0.5882353186607361, 0.9764705896377563, 0.949999988079071);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.1843137294054031, 0.1921568661928177, 0.2117647081613541, 1.0);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2352941185235977, 0.2470588237047195, 0.2705882489681244, 1.0);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.1333333402872086, 0.2588235437870026, 0.4235294163227081, 1.0);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428, 0.1019607856869698, 0.1450980454683304, 0.9724000096321106);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086, 0.2588235437870026, 0.4235294163227081, 1.0);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.3450980484485626, 0.3960784375667572, 0.9490196108818054, 1.0);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.3607843220233917, 0.4000000059604645, 0.4274509847164154, 1.0);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.3450980484485626, 0.3960784375667572, 0.9490196108818054, 1.0);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.3607843220233917, 0.4000000059604645, 0.4274509847164154, 1.0);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104, 0.1882352977991104, 0.2000000029802322, 1.0);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971, 0.3098039329051971, 0.3490196168422699, 1.0);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832, 0.2274509817361832, 0.2470588237047195, 1.0);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0, 0.0, 0.0, 0.0);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0, 1.0, 1.0, 0.05999999865889549);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.05098039284348488, 0.4196078479290009, 0.8588235378265381, 1.0);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.3450980484485626, 0.3960784375667572, 0.9490196108818054, 1.0);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026, 0.5882353186607361, 0.9764705896377563, 1.0);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0, 1.0, 1.0, 0.699999988079071);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929, 0.800000011920929, 0.800000011920929, 0.2000000029802322);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929, 0.800000011920929, 0.800000011920929, 0.3499999940395355);
    style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.3450980484485626, 0.3960784375667572, 0.9490196108818054, 0.5);
}

ImVec4 DebugGui::GetClearColor()
{
    return clearColor;
}

int DebugGui::GetPolygonMode() const {
    switch (polygonMode) {
        case 1:
            return GL_LINE;
        case 2:
            return GL_POINT;
        default:
            return GL_FILL;
    }
}

int DebugGui::GetVsync() const {
    return vsync;
}

void DebugGui::FrameTimesGraph() {
    for (size_t i = 1; i < IM_ARRAYSIZE(frameTimes); i++)
    {
        frameTimes[i - 1] = frameTimes[i];
    }

    frameTimes[IM_ARRAYSIZE(frameTimes) - 1] = 1000.0f / ImGui::GetIO().Framerate;

    float maxFrameTime = 0.0f;
    float avgFrameTime = 0.0f;
    for (size_t i = 0; i < IM_ARRAYSIZE(frameTimes); i++)
    {
        maxFrameTime = std::max(maxFrameTime, frameTimes[i]);
        avgFrameTime += frameTimes[i];
    }
    avgFrameTime /= IM_ARRAYSIZE(frameTimes);

    std::string overlayText = "Average frame time: " + std::to_string(frameTimes[IM_ARRAYSIZE(frameTimes) - 1]) + "ms";

    ImGui::PlotLines("Frame times", frameTimes, IM_ARRAYSIZE(frameTimes), 0, overlayText.c_str(), 0.0f, maxFrameTime * 2, ImVec2(300, 100));
}
