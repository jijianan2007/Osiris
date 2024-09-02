#pragma once

#include <GameClasses/PanoramaUiEngine.h>

template <typename HookContext>
struct PanoramaGuiUnloadHandler {
    explicit PanoramaGuiUnloadHandler(HookContext& hookContext) noexcept
        : hookContext{hookContext}
    {
    }

    void handleUnload() const noexcept
    {
        hookContext.panels().deletePanelByHandle(state().guiButtonHandle);
        hookContext.panels().deletePanelByHandle(state().guiPanelHandle);

        if (auto&& settingsPanel = hookContext.panels().getPanelFromHandle(state().settingsPanelHandle))
            PanoramaUiEngine::runScript(settingsPanel, "delete $.Osiris", "", 0);
    }

private:
    [[nodiscard]] auto& state() const noexcept
    {
        return hookContext.panoramaGuiState();
    }

    HookContext& hookContext;
};
