// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Input/Reply.h"
#include "Styling/SlateColor.h"
#include "Types/FTextIntPair.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SPathInput;
class SSelectionComboBox;

class SContainerDeploymentFields : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SContainerDeploymentFields) {}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	void SetContainerGroupDefinitionName(const FText& Name);
	void SetContainerImageName(const FText& Name);
	void SetContainerImageURI(const FText& Path);
	void SetExtraServerResourcesPath(const FText& Path);
	void SetOutConfigFilePath(const FText& Path);

	const FText& GetContainerGroupDefinitionName() const;
	const FText& GetContainerImageName() const;
	const FText& GetContainerImageURI() const;
	const FText& GetExtraServerResourcesPath() const;
	const FText& GetOutConfigFilePath() const;

private:
	TSharedPtr<SPathInput> ContainerGroupDefinitionNameInput;
	TSharedPtr<SPathInput> ContainerImageNameInput;
	TSharedPtr<SPathInput> ContainerImageURIInput;
	TSharedPtr<SPathInput> ExtraServerResourcesPathInput;
	TSharedPtr<SPathInput> OutConfigFilePathInput;
};

inline TSharedRef<SContainerDeploymentFields> AsSContainerDeploymentFieldsRef(TSharedPtr<SWidget> WidgetToCast)
{
	return StaticCastSharedRef<SContainerDeploymentFields>(WidgetToCast.ToSharedRef());
}

inline TSharedRef<SContainerDeploymentFields> AsSContainerDeploymentFieldsRef(TSharedRef<SWidget> WidgetToCast)
{
	return StaticCastSharedRef<SContainerDeploymentFields>(WidgetToCast);
}
