// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftDeployContainerMenu.h"

#include <Widgets/SBoxPanel.h>
#include <Widgets/Text/SRichTextBlock.h>
#include "Widgets/Layout/SWidgetSwitcher.h"
#include <Framework/MetaData/DriverMetaData.h>

#include "SCommonMenuSections.h"
#include "SWidgets/SBootstrapStatus.h"
#include "SWidgets/SDeploymentFields.h"
#include "SWidgets/SDeploymentStatus.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SPathInput.h"
#include "SWidgets/SSectionsWithHeaders.h"
#include "SWidgets/SSetupMessage.h"
#include "SWidgets/STextStatus.h"
#include "SWidgets/SSelectionComboBox.h"
#include "SWidgets/STextSeparator.h"

#include "Settings/UGameLiftDeploymentStatus.h"
#include "Settings/UGameLiftInternalSettings.h"
#include "Settings/UGameLiftSettings.h"

#include "Utils/Misc.h"
#include "Utils/Notifier.h"
#include "Utils/StringPaths.h"
#include <Async/Async.h>

#include "Types/EDeploymentMessageState.h"

#include "IGameLiftCoreModule.h"
#include "GameLiftPlugin.h"
#include <Developer/Settings/Public/ISettingsModule.h>

#define LOCTEXT_NAMESPACE "SGameLiftDeployContainerContent"

void SGameLiftDeployContainerMenu::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;

	DeploymentStatus = SNew(SDeploymentStatus);

	BuildScenarioValues();

	const auto kRunDeploymentGameInfo = FText::Format(
		FText::FromString("<RichTextBlock.TextHighlight>{1}</>: {0}"),
		Menu::DeployManagedEC2::kRunDeploymentGameInfoText,
		Settings::kRichTextBlockNoteText);

	// Create the widgets
	TSharedPtr<SSectionsWithHeaders> SectionsWithHeaders = SNew(SSectionsWithHeaders);
	SectionsWithHeaders->AddSection((SNew(SSetProfileSection))->GetSectionInfo());
	SectionsWithHeaders->AddSection(
		(SNew(SIntegrateGameSection).HideBuildPathInput(true).HowToIntegrateYourGameLinkUrl(
			Url::kHowToIntegrateYourGameForEC2Url))->GetSectionInfo()
	);
	SectionsWithHeaders->AddSection(
		LOCTEXT("ContainersSelectDeploymentScenarioTitle", "3. Select deployment scenario"),
		CreateSelectDeploymentScenarioSection(),
		false
	);
	SectionsWithHeaders->AddSection(
		LOCTEXT("ContainersGameParametersTitle", "4. Set game parameters"),
		CreateGameParametersSection(),
		false
	);
	SectionsWithHeaders->AddSection(
		LOCTEXT("ContainersDeployTitle", "5. Deploy scenario"),
		CreateDeploySection(),
		false
	);
	SectionsWithHeaders->AddSection(
		LOCTEXT("ContainersLaunchClientTitle", "6. Launch client"),
		CreateLaunchClientSection(),
		false
	);

	ChildSlot
		.Padding(SPadding::Top_Bottom + SPadding::Extra_For_Page_End)
		// This adds more space at the bottom so users can scroll down further.
		[
			SectionsWithHeaders.ToSharedRef()
		];

	UGameLiftInternalSettings* Settings = GetMutableDefault<UGameLiftInternalSettings>();

	SetDefaultValues();
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateSelectDeploymentScenarioSection()
{
	return SGameLiftDeployManagedEC2Menu::CreateSelectDeploymentScenarioSection();
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateGameParametersSection()
{
	return SGameLiftDeployManagedEC2Menu::CreateGameParametersSection();
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateDeploySection()
{
	return SGameLiftDeployManagedEC2Menu::CreateDeploySection();
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateLaunchClientSection()
{
	return SGameLiftDeployManagedEC2Menu::CreateLaunchClientSection();
}

void SGameLiftDeployContainerMenu::BuildScenarioValues()
{
	SGameLiftDeployManagedEC2Menu::BuildScenarioValues();
}

void SGameLiftDeployContainerMenu::SetDefaultValues()
{
	SGameLiftDeployManagedEC2Menu::SetDefaultValues();
}

#undef LOCTEXT_NAMESPACE
