// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SContainerDeploymentFields.h"

#include <Widgets/SBoxPanel.h>
#include <Widgets/Layout/SBorder.h>

#include "SWidgets/SPathInput.h"
#include "SWidgets/SNamedRow.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

namespace Internal
{
	TSharedPtr<SPathInput> MakeContainerGroupDefinitionName()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployContainers::kContainerGroupDefinitionNameText)
			.PathHint(Menu::DeployContainers::kContainerGroupDefinitionNameHint)
			.ButtonVisibility(EVisibility::Collapsed);
	}

	TSharedPtr<SPathInput> MakeContainerImageURI()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployContainers::kContainerImageURIText)
			.PathHint(Menu::DeployContainers::kContainerImageURIHint)
			.ButtonVisibility(EVisibility::Collapsed);
	}

	TSharedPtr<SPathInput> MakeContainerExtraServerResourcesPath()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployManagedEC2::kExtraServerResourcesPathTitle)
			.IsFileSelection(false)
			.ToolTipText(Menu::DeployManagedEC2::kExtraServerResourcesPathTooltip);
	}

	TSharedPtr<SPathInput> MakeContainerOutConfigFilePath()
	{
		return SNew(SPathInput)
			.Title(Menu::DeployManagedEC2::kOutConfigFilePathTitle)
			.PathHint(Menu::DeployManagedEC2::kOutConfigFilePathHint)
			.ButtonVisibility(EVisibility::Collapsed);
	}
} // namespace Internal

#define LOCTEXT_NAMESPACE "SContainerDeploymentFields"

void SContainerDeploymentFields::Construct(const FArguments& InArgs)
{
	ContainerGroupDefinitionNameInput = Internal::MakeContainerGroupDefinitionName();
	ContainerImageURIInput = Internal::MakeContainerImageURI();
	ExtraServerResourcesPathInput = Internal::MakeContainerExtraServerResourcesPath();
	OutConfigFilePathInput = Internal::MakeContainerOutConfigFilePath();

	TSharedPtr<SWidget> ContainerGroupDefinitionNameInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployContainers::kContainerGroupDefinitionNameTitle).RowWidget(ContainerGroupDefinitionNameInput);

	TSharedPtr<SWidget> ContainerGroupDefinitionNameInstructionsRow = SNew(SNamedRow)
		.SecondaryColumnLeftPadding(true)
		.RowWidget(
			SNew(STextBlock)
			.Text(Menu::DeployContainers::kContainerGroupDefinitionNameInstructionText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote)
			.AutoWrapText(true)
		);
	
	TSharedPtr<SWidget> ContainerImageURIInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployContainers::kContainerImageURITitle).RowWidget(ContainerImageURIInput);

	TSharedPtr<SWidget> ExtraServerResourcesPathInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployManagedEC2::kExtraServerResourcesPathTitle).RowWidget(ExtraServerResourcesPathInput);

	// Currently, this field does not work, so we hide it from users.
	ExtraServerResourcesPathInputRow->SetVisibility(EVisibility::Collapsed);

	TSharedPtr<SWidget> OutConfigFilePathInputRow = SNew(SNamedRow)
		.NameText(Menu::DeployManagedEC2::kOutConfigFilePathTitle)
		.NameTooltipText(Menu::DeployManagedEC2::kOutConfigFilePathTooltip)
		.RowWidget(OutConfigFilePathInput);

	TSharedPtr<SWidget> FullWidget =
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()
		[
			ContainerGroupDefinitionNameInputRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			ContainerGroupDefinitionNameInstructionsRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			ContainerImageURIInputRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			ExtraServerResourcesPathInputRow.ToSharedRef()
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(SPadding::Top)
		[
			OutConfigFilePathInputRow.ToSharedRef()
		];

	ChildSlot
	[
		SNew(SBox)
		[
			FullWidget.ToSharedRef()
		]
	];
}

void SContainerDeploymentFields::SetContainerGroupDefinitionName(const FText& Name)
{
	ContainerGroupDefinitionNameInput->SetSelectedPath(Name);
}

void SContainerDeploymentFields::SetContainerImageURI(const FText& Path)
{
	ContainerImageURIInput->SetSelectedPath(Path);
}

void SContainerDeploymentFields::SetExtraServerResourcesPath(const FText& Path)
{
	ExtraServerResourcesPathInput->SetSelectedPath(Path);
}

void SContainerDeploymentFields::SetOutConfigFilePath(const FText& Path)
{
	OutConfigFilePathInput->SetSelectedPath(Path);
}

const FText& SContainerDeploymentFields::GetContainerGroupDefinitionName() const
{
	return ContainerGroupDefinitionNameInput->GetSelectedPathRef();
}

const FText& SContainerDeploymentFields::GetContainerImageURI() const
{
	return ContainerImageURIInput->GetSelectedPathRef();
}

const FText& SContainerDeploymentFields::GetExtraServerResourcesPath() const
{
	return ExtraServerResourcesPathInput->GetSelectedPathRef();
}

const FText& SContainerDeploymentFields::GetOutConfigFilePath() const
{
	return OutConfigFilePathInput->GetSelectedPathRef();
}

#undef LOCTEXT_NAMESPACE
