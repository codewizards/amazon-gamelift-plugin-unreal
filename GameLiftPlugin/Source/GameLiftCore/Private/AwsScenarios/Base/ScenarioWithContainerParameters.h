// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Base/ScenarioWithGameServer.h"
#include "GameLiftCoreConstants.h"
#include "ScenarioWithParameters.h"
#include "GameLiftCore/Private/AwsScenarios/IAwsScenario.h"
#include "GameLiftCore/Public/IAWSAccountInstance.h"

namespace AwsScenarios
{
	class ScenarioWithContainerParameters : public ScenarioWithParameters
	{
	public:
		virtual const char* const* GetParamNames() const override
		{
			static const char* paramNames[] =
			{
				"AccountId",
				"ApiGatewayStageNameParameter",
				"ContainerGroupDefinitionNameParameter",
				"ContainerImageNameParameter",
				"ContainerImageUriParameter",
				"GameNameParameter",
				"LambdaZipS3BucketParameter",
				"LambdaZipS3KeyParameter",
				"LaunchPathParameter"
			};
			return paramNames;
		}

		// TODO Stefan - This should override the virtual function in IAWSScenario;
		//				 need to change the interface to not be tightly coupled to InstanceTemplateParams.
		//				 Probably should change InstanceTemplateParams to something generic and then can pass that
		//				 to AWSScenariosDeployer::DeployScenario instead of having the function be tightly coupled
		//				 to some specific set of parameters.
		int SaveFeatureInstanceTemplateContainers(
			IAWSAccountInstance* AwsAccountInstance,
			const ContainerInstanceTemplateParams& InParams)
		{
			const char* ParamValues[] =
			{
				InParams.AccountId.c_str(),
				InParams.ApiGatewayStageNameParameter.c_str(),
				InParams.ContainerGroupDefinitionNameParameter.c_str(),
				InParams.ContainerImageNameParameter.c_str(),
				InParams.ContainerImageUriParameter.c_str(),
				InParams.GameNameParameter.c_str(),
				InParams.LambdaZipS3BucketParameter.c_str(),
				InParams.LambdaZipS3KeyParameter.c_str(),
				InParams.LaunchPathParameter.c_str()
			};

			auto* ParamNames = GetParamNames();
			size_t Size = sizeof(ParamValues) / sizeof(*ParamValues);

			return GameLiftAccountSaveFeatureInstanceTemplates(AwsAccountInstance->GetInstance(), ParamNames, ParamValues, Size);
		}

		virtual int SaveFeatureInstanceTemplate(IAWSAccountInstance* AwsAccountInstance, const InstanceTemplateParams& InParams)
		{
			return -1;
		};
		virtual int UploadGameServer(IAWSAccountInstance* AwsAccountInstance, const std::string& ServerFolderPath, const std::string& ExtraServerResourcesPath)
		{
			return -1;
		};
		virtual int CreateLaunchPathParameter(const FString& BuildOperatingSystem, const FString& BuildFolderPath, const FString& BuildFilePath, std::string& StdLaunchPathParameter)
		{
			return -1;
		};
	};
} // namespace AwsScenarios
