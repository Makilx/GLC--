#include <GLEngine/debug/imGui.hpp>
#include <algorithm>

gle::ImGuiDebugWindow::~ImGuiDebugWindow() {
    Disable();
}

void gle::ImGuiDebugWindow::Enable() {
    ImGuiRenderer::RegisterWindow(this);
}

void gle::ImGuiDebugWindow::Disable() {
    ImGuiRenderer::UnregisterWindow(this);
}

// Renderer //
std::vector<gle::ImGuiDebugWindow *> gle::ImGuiRenderer::windows;

void gle::ImGuiRenderer::Init() {
    // TODO:
}

void gle::ImGuiRenderer::Terminate() {
    windows.clear();
    // TODO:
}

void gle::ImGuiRenderer::Update() {
    // TODO:
    for (auto *w : windows) {
        w->OnRenderFrame();
    }
    // TODO
}

void gle::ImGuiRenderer::RegisterWindow(ImGuiDebugWindow *window) {
    if (IsWindowRegistered(window))
        return;

    windows.push_back(window);
}

void gle::ImGuiRenderer::UnregisterWindow(ImGuiDebugWindow *window) {
    if (!IsWindowRegistered(window))
        return;
    auto it = std::remove(windows.begin(), windows.end(), window);
    windows.erase(it, windows.end());
}

bool gle::ImGuiRenderer::IsWindowRegistered(ImGuiDebugWindow *window) {
    return std::find(windows.begin(), windows.end(), window) != windows.end();
}