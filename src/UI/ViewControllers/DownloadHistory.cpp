#include "UI/ViewControllers/DownloadHistory.hpp"
#include "UI/ViewControllers/SongList.hpp"
#include "main.hpp"
using namespace BetterSongSearch::UI;

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Settings/IncrementSetting.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
using namespace QuestUI;

#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "HMUI/Touchable.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "System/Collections/Generic/List_1.hpp"

DEFINE_TYPE(BetterSongSearch::UI::ViewControllers, DownloadHistoryViewController);
DEFINE_TYPE(CustomComponents, DownloadCustomCellListTableData);
DEFINE_TYPE(CustomComponents, DownloadSongListCellTableCell);

UnityEngine::UI::VerticalLayoutGroup* downloadHistoryLayout;

void CustomComponents::DownloadSongListCellTableCell::ctor()
{
    selectedGroup = List<UnityEngine::GameObject*>::New_ctor();
    hoveredGroup = List<UnityEngine::GameObject*>::New_ctor();
    neitherGroup = List<UnityEngine::GameObject*>::New_ctor();
}

void CustomComponents::DownloadSongListCellTableCell::SelectionDidChange(HMUI::SelectableCell::TransitionType transitionType)
{
    RefreshVisuals();
}

void CustomComponents::DownloadSongListCellTableCell::HighlightDidChange(HMUI::SelectableCell::TransitionType transitionType)
{
    RefreshVisuals();
}

#define UpdateGODownloadList(list, condition) \
    int list## length = list->get_Count(); \
    for (int i = 0; i < list## length; i++) { \
        list->items->values[i]->SetActive(condition); \
    } \

void CustomComponents::DownloadSongListCellTableCell::RefreshVisuals()
{
    bool isSelected = get_selected();
    bool isHighlighted = get_highlighted();

    //bg->background->set_color(UnityEngine::Color(0, 0, 0, isSelected ? 0.9f : isHighlighted ? 0.6f : 0.45f));

    UpdateGODownloadList(selectedGroup, isSelected);
    UpdateGODownloadList(hoveredGroup, isHighlighted);
    UpdateGODownloadList(neitherGroup, !(isSelected || isHighlighted));
}

void CustomComponents::DownloadSongListCellTableCell::RefreshData(const SDC_wrapper::BeatStarSong* data)
{
    auto name = std::string(data->GetName());
    auto author = std::string(data->GetAuthor());

    songName->set_text(il2cpp_utils::newcsstr(name));
    levelAuthorName->set_text(il2cpp_utils::newcsstr(author));
}

HMUI::TableCell* CustomComponents::DownloadCustomCellListTableData::CellForIdx(HMUI::TableView* tableView, int idx)
{
    static auto DownloadSongListCustomCellListCell_cs = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("DownloadSongListCellTableCell");
    static auto DownloadSongListCustomTableCell_cs = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("DownloadSongListCustomTableCell");

    CustomComponents::DownloadSongListCellTableCell* tableCell = reinterpret_cast<CustomComponents::DownloadSongListCellTableCell*>(tableView->DequeueReusableCellForIdentifier(DownloadSongListCustomCellListCell_cs));
    if(!tableCell)
    {
        tableCell = UnityEngine::GameObject::New_ctor()->AddComponent<CustomComponents::DownloadSongListCellTableCell*>();
        tableCell->set_reuseIdentifier(DownloadSongListCustomCellListCell_cs);
        tableCell->set_name(DownloadSongListCustomTableCell_cs);
        auto fitter = tableCell->get_gameObject()->AddComponent<UnityEngine::UI::ContentSizeFitter*>();
        fitter->set_verticalFit(UnityEngine::UI::ContentSizeFitter::FitMode::PreferredSize);
        fitter->set_horizontalFit(UnityEngine::UI::ContentSizeFitter::FitMode::Unconstrained);

        tableCell->get_gameObject()->AddComponent<HMUI::Touchable*>();
        tableCell->set_interactable(true);

        auto verticalLayoutGroup = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(tableCell->get_transform());
        tableCell->bg = verticalLayoutGroup->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
        tableCell->bg->ApplyBackgroundWithAlpha(il2cpp_utils::newcsstr("round-rect-panel"), 0.6f);
        auto fitter2 = verticalLayoutGroup->get_gameObject()->AddComponent<UnityEngine::UI::ContentSizeFitter*>();
        fitter2->set_horizontalFit(UnityEngine::UI::ContentSizeFitter::FitMode::Unconstrained);
        fitter2->set_verticalFit(UnityEngine::UI::ContentSizeFitter::FitMode::PreferredSize);
        auto layoutbg = tableCell->get_gameObject()->AddComponent<UnityEngine::UI::LayoutElement*>();
        layoutbg->set_preferredHeight(9);

        tableCell->get_transform()->SetParent(tableView->get_transform()->GetChild(0)->GetChild(0), false);

        tableCell->bgProgress = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(verticalLayoutGroup->get_transform());
        tableCell->bgProgress->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(tableCell->bgProgress->get_rectTransform()->get_anchoredPosition().x, -3.875f));
        auto bgProgressBG = tableCell->bgProgress->get_gameObject()->AddComponent<Backgroundable*>();
        bgProgressBG->ApplyBackground(il2cpp_utils::newcsstr("panel-fade-gradient"));
        auto bgProgressElement = tableCell->bgProgress->GetComponent<UnityEngine::UI::LayoutElement*>();
        bgProgressElement->set_preferredHeight(1);
        auto bgProgressFitter = tableCell->bgProgress->get_gameObject()->AddComponent<UnityEngine::UI::ContentSizeFitter*>();
        bgProgressFitter->set_verticalFit(UnityEngine::UI::ContentSizeFitter::FitMode::PreferredSize);
        bgProgressFitter->set_horizontalFit(UnityEngine::UI::ContentSizeFitter::FitMode::Unconstrained);

        auto songDataLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(verticalLayoutGroup->get_transform());

        auto topHoriz = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(songDataLayout->get_transform());
        topHoriz->set_spacing(2);
        auto bottomHoriz = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(songDataLayout->get_transform());
        bottomHoriz->set_padding(UnityEngine::RectOffset::New_ctor(0,0,3,0));

        tableCell->songName = QuestUI::BeatSaberUI::CreateText(topHoriz->get_transform(), "Deez Nuts loolollolool");
        tableCell->songName->set_fontSize(2.7f);
        tableCell->songName->set_alignment(TMPro::TextAlignmentOptions::MidlineLeft);
        tableCell->songName->set_overflowMode(TMPro::TextOverflowModes::Ellipsis);
        tableCell->songName->set_enableWordWrapping(false);

        tableCell->levelAuthorName = QuestUI::BeatSaberUI::CreateText(topHoriz->get_transform(), "Deez Nuts loolollolool");
        tableCell->levelAuthorName->set_fontSize(2.3f);
        tableCell->levelAuthorName->set_color(UnityEngine::Color(0.8f, 0.8f, 0.8f, 1));
        tableCell->levelAuthorName->set_alignment(TMPro::TextAlignmentOptions::MidlineRight);
        tableCell->levelAuthorName->set_overflowMode(TMPro::TextOverflowModes::Ellipsis);
        tableCell->levelAuthorName->set_enableWordWrapping(false);

        tableCell->statusLabel = QuestUI::BeatSaberUI::CreateText(bottomHoriz->get_transform(), "Status Here Lol");
        tableCell->statusLabel->set_fontSize(3);
        tableCell->statusLabel->set_color(UnityEngine::Color::get_cyan());
        tableCell->statusLabel->set_alignment(TMPro::TextAlignmentOptions::MidlineLeft);
        tableCell->statusLabel->set_overflowMode(TMPro::TextOverflowModes::Ellipsis);
        tableCell->statusLabel->set_enableWordWrapping(false);
    }
    tableCell->RefreshData(data[idx]);
    return tableCell;
}

float CustomComponents::DownloadCustomCellListTableData::CellSize()
{
    return 11.7f;
}
int CustomComponents::DownloadCustomCellListTableData::NumberOfCells()
{
    return data.size();
}

void ViewControllers::DownloadHistoryViewController::RefreshTable(float progress, int cellID) {
    if(downloadTableData == nullptr)
        return;
    if(downloadTableData->tableView == nullptr)
        return;
    CustomComponents::DownloadSongListCellTableCell* customTableCell = reinterpret_cast<CustomComponents::DownloadSongListCellTableCell*>(downloadTableData->tableView->visibleCells->get_Item(cellID));
    if(customTableCell == nullptr)
        return;
    auto image = customTableCell->bgProgress->GetComponent<HMUI::ImageView*>();
    if(image == nullptr)
        return;
    image->set_color(UnityEngine::Color::get_green());
    UnityEngine::RectTransform* x = reinterpret_cast<UnityEngine::RectTransform*>(customTableCell->bgProgress->get_transform());
    if(x == nullptr)
        return;
    x->set_anchorMax(UnityEngine::Vector2(progress, 1));
}

void ViewControllers::DownloadHistoryViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling) {
    if (!firstActivation) return;

    downloadHistoryLayout = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
    downloadHistoryLayout->set_childControlHeight(false);

    auto titleLayout = BeatSaberUI::CreateHorizontalLayoutGroup(downloadHistoryLayout->get_transform());
    auto titleLayoutBackground = titleLayout->get_gameObject()->AddComponent<Backgroundable*>();
    titleLayoutBackground->ApplyBackground(il2cpp_utils::newcsstr("panel-top-gradient"));
    auto viewTitle = BeatSaberUI::CreateText(titleLayout->get_rectTransform(), "DOWNLOAD HISTORY");
    viewTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    viewTitle->set_fontStyle(TMPro::FontStyles::Italic);

    auto songDownloadListLayout = BeatSaberUI::CreateHorizontalLayoutGroup(downloadHistoryLayout->get_transform());
    auto songDownloadListLayoutElement = songDownloadListLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
    songDownloadListLayoutElement->set_preferredHeight(72);
    songDownloadListLayoutElement->set_preferredWidth(80);
    songDownloadListLayout->set_padding(UnityEngine::RectOffset::New_ctor(0,0,5,2));

    auto downloadedLayout = BeatSaberUI::CreateVerticalLayoutGroup(songDownloadListLayout->get_transform());
    auto downloadedLayoutElement = downloadedLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
    downloadedLayoutElement->set_preferredHeight(70);

    auto list = QuestUI::BeatSaberUI::CreateScrollableCustomSourceList<CustomComponents::DownloadCustomCellListTableData*>(downloadedLayout->get_transform());
    downloadTableData = list;
    list->tableView->ReloadData();

    auto click = std::function([=](HMUI::TableView* tableView, int row)
    {

    });
}