// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftDeployContainerMenu.h"

#include <Widgets/SBoxPanel.h>

#include "SCommonMenuSections.h"
#include "SWidgets/SContainerDeploymentFields.h"
#include "SWidgets/SDeploymentStatus.h"
#include "SWidgets/SNamedRow.h"
#include "SWidgets/SOnlineHyperlink.h"
#include "SWidgets/SSectionsWithHeaders.h"
#include "SWidgets/SSetupMessage.h"
#include "SWidgets/SSelectionComboBox.h"
#include "SWidgets/STextSeparator.h"

#include "Settings/UGameLiftInternalSettings.h"

#include <Async/Async.h>

#include "Settings/UGameLiftDeploymentStatus.h"

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
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(STextBlock)
			.Text(Menu::DeployManagedEC2::kSelectScenarioDescription)
			.AutoWrapText(true)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
		]
		// Links
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SOnlineHyperlink)
				.Text(Menu::DeployManagedEC2::kGameLiftHowToDeployYourFirstGameLinkText)
				.Link(Url::kGameLiftHowToDeployYourFirstGameUrl)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Center)
			[
				SNew(STextSeparator).Separator(TEXT("|"))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SOnlineHyperlink)
				.Text(Menu::DeployManagedEC2::kGameLiftEndpointsLinkText)
				.Link(Url::kGameLiftEndpointsUrl)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Center)
			[
				SNew(STextSeparator).Separator(TEXT("|"))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SOnlineHyperlink)
				.Text(Menu::DeployManagedEC2::kGameLiftPricingPlanLinkText)
				.Link(Url::kGameLiftPricingPlanUrl)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Center)
			[
				SNew(STextSeparator).Separator(TEXT("|"))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SOnlineHyperlink)
				.Text(Menu::DeployContainers::kGameLiftContainersHelpLinkText)
				.Link(Url::kGameLiftContainersHelpUrl)
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		[
			SNew(SNamedRow)
			.NameText(Menu::DeployManagedEC2::kSelectScenarioTitle)
			.RowWidget(
				SNew(SSelectionComboBox)
				.OnListBuilding_Raw(this, &SGameLiftDeployContainerMenu::OnBuildingDeploymentScenarioValues)
				.OnItemSelected_Raw(this, &SGameLiftDeployContainerMenu::OnDeploymentScenarioSelected)
			)
		];
}

TSharedRef<SWidget> SGameLiftDeployContainerMenu::CreateGameParametersSection()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(SPadding::Top_Bottom + SPadding::Right2x)
		.AutoHeight()
		[
			SAssignNew(DeploymentFields, SContainerDeploymentFields)
		];
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
	UGameLiftDeploymentStatus* DeploySettings = GetMutableDefault<UGameLiftDeploymentStatus>();

	auto DeploymentInfo = AsSContainerDeploymentFieldsRef(DeploymentFields);
	DeploymentInfo->SetContainerGroupDefinitionName(DeploySettings->ContainerGroupDefinitionName);
	DeploymentInfo->SetContainerImageURI(DeploySettings->ContainerImageURI);
	DeploymentInfo->SetExtraServerResourcesPath(DeploySettings->ContainerExtraServerResourcesPath);
	DeploymentInfo->SetOutConfigFilePath(DeploySettings->ContainerOutConfigFilePath);

	int previousScenarioSelected = ScenarioNames.FindLastByPredicate([&](const FText& name)
	{
		return name.EqualTo(DeploySettings->Scenario);
	});
	if (previousScenarioSelected != INDEX_NONE)
	{
		CurrentScenarioSelected = previousScenarioSelected;
	}
}

#undef LOCTEXT_NAMESPACE
