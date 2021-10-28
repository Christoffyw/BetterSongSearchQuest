#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "SongList.hpp"

#define GET_FIND_METHOD(mPtr) il2cpp_utils::il2cpp_type_check::MetadataGetter<mPtr>::get()


___DECLARE_TYPE_WRAPPER_INHERITANCE(CustomComponents, DownloadCustomCellListTableData, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, UnityEngine::MonoBehaviour, "QuestUI", GetInterfaces(), 0, nullptr,DECLARE_INSTANCE_FIELD(Il2CppString*, cellTemplate);
    DECLARE_INSTANCE_FIELD(float, cellSize);
    DECLARE_INSTANCE_FIELD(HMUI::TableView*, tableView);
    DECLARE_INSTANCE_FIELD(bool, clickableCells);

    //DECLARE_CTOR(ctor);
    //DECLARE_DTOR(dtor);

    DECLARE_OVERRIDE_METHOD(HMUI::TableCell*, CellForIdx, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellForIdx>::get(), HMUI::TableView* tableView, int idx);
    DECLARE_OVERRIDE_METHOD(float, CellSize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellSize>::get());
    DECLARE_OVERRIDE_METHOD(int, NumberOfCells, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::NumberOfCells>::get());

    public:
        QuestUI::CustomCellListWrapper* listWrapper = nullptr;
        std::vector<const SDC_wrapper::BeatStarSong*> data;
)

DECLARE_CLASS_CODEGEN(CustomComponents, DownloadSongListCellTableCell, HMUI::TableCell,
    DECLARE_INSTANCE_FIELD(List<UnityEngine::GameObject*>*, selectedGroup);
    DECLARE_INSTANCE_FIELD(List<UnityEngine::GameObject*>*, hoveredGroup);
    DECLARE_INSTANCE_FIELD(List<UnityEngine::GameObject*>*, neitherGroup);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, songName);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, levelAuthorName);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, statusLabel);
    DECLARE_INSTANCE_FIELD(QuestUI::Backgroundable*, bg);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::VerticalLayoutGroup*, bgProgress);

    DECLARE_CTOR(ctor);

    DECLARE_OVERRIDE_METHOD(void, SelectionDidChange, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::SelectableCell::SelectionDidChange>::get(), HMUI::SelectableCell::TransitionType transitionType);
    DECLARE_OVERRIDE_METHOD(void, HighlightDidChange, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::SelectableCell::HighlightDidChange>::get(), HMUI::SelectableCell::TransitionType transitionType);

    DECLARE_INSTANCE_METHOD(void, RefreshVisuals);
    public:
        void RefreshData(const SDC_wrapper::BeatStarSong* data);
)

DECLARE_CLASS_CODEGEN(BetterSongSearch::UI::ViewControllers, DownloadHistoryViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, GET_FIND_METHOD(&HMUI::ViewController::DidActivate), bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling);
    DECLARE_STATIC_METHOD(void, RefreshTable, float progress, int cellID);
)
inline CustomComponents::DownloadCustomCellListTableData* downloadTableData;