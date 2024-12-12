bool ToggleButton(const char* label, bool* v, const ImVec2& size = ImVec2(40, 20), float animationSpeed = 10.0f)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO();
    ImGuiID id = ImGui::GetID(label);
    static std::unordered_map<ImGuiID, float> toggleAnimMap;
    float& toggleAnim = toggleAnimMap[id];
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 buttonSize = size;
    float radius = buttonSize.y * 0.5f;
    if (*v)
        toggleAnim = ImLerp(toggleAnim, 1.0f, animationSpeed * io.DeltaTime);
    else
        toggleAnim = ImLerp(toggleAnim, 0.0f, animationSpeed * io.DeltaTime);
    float togglePosX = pos.x + radius + (buttonSize.x - 2 * radius) * toggleAnim;
    ImVec4 bgColor = ImLerp(ImVec4(0.40f, 0.40f, 0.40f, 1.00f), ImVec4(0.28f, 0.56f, 0.80f, 1.00f), toggleAnim);
    ImGui::InvisibleButton(label, buttonSize);
    bool isToggled = ImGui::IsItemClicked();
    if (isToggled)
    {
        *v = !*v;
    }
    draw_list->AddRectFilled(pos, ImVec2(pos.x + buttonSize.x, pos.y + buttonSize.y), ImGui::GetColorU32(bgColor), radius);
    draw_list->AddCircleFilled(ImVec2(togglePosX, pos.y + radius), radius - 2.0f, ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)));
    ImVec2 labelSize = ImGui::CalcTextSize(label);
    ImVec2 titlePos = ImVec2(pos.x + buttonSize.x + style.ItemInnerSpacing.x, pos.y + radius - labelSize.y * 0.5f);
    ImGui::RenderText(titlePos, label);
    float totalWidth = buttonSize.x + style.ItemInnerSpacing.x + labelSize.x;
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
   
    return isToggled;
}
