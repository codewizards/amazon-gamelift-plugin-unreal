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
		virtual int SaveFeatureInstanceTemplate(IAWSAccountInstance* AwsAccountInstance,
		                                        const TMap<FString, FString>& InParams) override
		{
			ContainerInstanceTemplateParams TemplateParams;
			TemplateParams.FromMap(InParams);
			
			const char* ParamValues[] =
			{
				TemplateParams.AccountId.c_str(),
				TemplateParams.ApiGatewayStageNameParameter.c_str(),
				TemplateParams.ContainerGroupDefinitionNameParameter.c_str(),
				TemplateParams.ContainerImageNameParameter.c_str(),
				TemplateParams.ContainerImageUriParameter.c_str(),
				TemplateParams.GameNameParameter.c_str(),
				TemplateParams.LambdaZipS3BucketParameter.c_str(),
				TemplateParams.LambdaZipS3KeyParameter.c_str(),
				TemplateParams.LaunchPathParameter.c_str()
			};

			auto* ParamNames = GetParamNames();
			size_t Size = sizeof(ParamValues) / sizeof(*ParamValues);

			return GameLiftAccountSaveFeatureInstanceTemplates(AwsAccountInstance->GetInstance(), ParamNames, ParamValues, Size);
		}
		
		virtual int UploadGameServer(IAWSAccountInstance* AwsAccountInstance, const std::string& ServerFolderPath, const std::string& ExtraServerResourcesPath)
		{
			return 0;
		};
		virtual int CreateLaunchPathParameter(const FString& BuildOperatingSystem, const FString& BuildFolderPath, const FString& BuildFilePath, std::string& StdLaunchPathParameter)
		{
			return 0;
		};
	};
} // namespace AwsScenarios
