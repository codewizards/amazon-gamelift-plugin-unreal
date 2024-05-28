// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <sstream>
#include <string>

#include "IAWSAccountInstance.h"
#include "Utils/StringConvertors.h"

namespace AwsScenarios
{
	inline std::string GetLambdaS3Key(const std::string& GameName, const std::string& FunctionsReplacementId)
	{
		std::stringstream StringStream;

		StringStream << GameName;
		StringStream << "/functions/" << GameLift::GetFeatureTypeString(GameLift::FeatureType::Main);
		StringStream << "/" << "requests" << "." << FunctionsReplacementId << ".zip";

		return StringStream.str();
	}

	struct BaseInstanceTemplateParams
	{
		virtual ~BaseInstanceTemplateParams() = default;
		virtual void FromMap(const TMap<FString, FString>& InMap) = 0;
		virtual TMap<FString, FString> ToMap() const = 0;
	};

	struct ManagedEC2InstanceTemplateParams : BaseInstanceTemplateParams
	{
		std::string GameNameParameter;
		std::string BuildOperatingSystemParameter;
		std::string BuildS3BucketParameter;
		std::string LambdaZipS3BucketParameter;
		std::string LambdaZipS3KeyParameter;
		std::string ApiGatewayStageNameParameter;
		std::string AccountId;
		std::string LaunchPathParameter;
		
		ManagedEC2InstanceTemplateParams() = default;
		
		virtual void FromMap(const TMap<FString, FString>& InMap) override
		{
			const FString* InGameNameParameter = InMap.Find("GameNameParameter");
			const FString* InBuildOperatingSystemParameter = InMap.Find("BuildOperatingSystemParameter");
			const FString* InBuildS3BucketParameter = InMap.Find("BuildS3BucketParameter");
			const FString* InLambdaZipS3BucketParameter = InMap.Find("LambdaZipS3BucketParameter");
			const FString* InLambdaZipS3KeyParameter = InMap.Find("LambdaZipS3KeyParameter");
			const FString* InApiGatewayStageNameParameter = InMap.Find("ApiGatewayStageNameParameter");
			const FString* InAccountId = InMap.Find("AccountId");
			const FString* InLaunchPathParameter = InMap.Find("LaunchPathParameter");

			if (InGameNameParameter && InBuildOperatingSystemParameter && InBuildS3BucketParameter
				&& InLambdaZipS3BucketParameter && InLambdaZipS3KeyParameter && InApiGatewayStageNameParameter
				&& InApiGatewayStageNameParameter && InAccountId && InLaunchPathParameter)
			{
				GameNameParameter = Convertors::FSToStdS(*InGameNameParameter);
				BuildOperatingSystemParameter = Convertors::FSToStdS(*InBuildOperatingSystemParameter);
				BuildS3BucketParameter = Convertors::FSToStdS(*InBuildS3BucketParameter);
				LambdaZipS3BucketParameter = Convertors::FSToStdS(*InLambdaZipS3BucketParameter);
				LambdaZipS3KeyParameter = Convertors::FSToStdS(*InLambdaZipS3KeyParameter);
				ApiGatewayStageNameParameter = Convertors::FSToStdS(*InApiGatewayStageNameParameter);
				AccountId = Convertors::FSToStdS(*InAccountId);
				LaunchPathParameter = Convertors::FSToStdS(*InLaunchPathParameter);
			}
		}

		virtual TMap<FString, FString> ToMap() const override
		{
			TMap<FString, FString> ParamsMap = {};
			
			ParamsMap.Emplace("GameNameParameter", GameNameParameter.c_str());
			ParamsMap.Emplace("BuildOperatingSystemParameter", BuildOperatingSystemParameter.c_str());
			ParamsMap.Emplace("BuildS3BucketParameter", BuildS3BucketParameter.c_str());
			ParamsMap.Emplace("LambdaZipS3BucketParameter", LambdaZipS3BucketParameter.c_str());
			ParamsMap.Emplace("LambdaZipS3KeyParameter", LambdaZipS3KeyParameter.c_str());
			ParamsMap.Emplace("ApiGatewayStageNameParameter", ApiGatewayStageNameParameter.c_str());
			ParamsMap.Emplace("AccountId", AccountId.c_str());
			ParamsMap.Emplace("LaunchPathParameter", LaunchPathParameter.c_str());

			return ParamsMap;
		}
	};

	struct ContainerInstanceTemplateParams : BaseInstanceTemplateParams
	{
		std::string AccountId;
		std::string ApiGatewayStageNameParameter;
		std::string ContainerGroupDefinitionNameParameter;
		std::string ContainerImageNameParameter;
		std::string ContainerImageUriParameter;
		std::string GameNameParameter;
		std::string LambdaZipS3BucketParameter;
		std::string LambdaZipS3KeyParameter;
		std::string LaunchPathParameter;

		ContainerInstanceTemplateParams() = default;

		virtual void FromMap(const TMap<FString, FString>& InMap) override
		{
			const FString* InAccountId = InMap.Find("AccountId");
			const FString* InApiGatewayStageNameParameter = InMap.Find("ApiGatewayStageNameParameter");
			const FString* InContainerGroupDefinitionNameParameter = InMap.Find("ContainerGroupDefinitionNameParameter");
			const FString* InContainerImageNameParameter = InMap.Find("ContainerImageNameParameter");
			const FString* InContainerImageUriParameter = InMap.Find("ContainerImageUriParameter");
			const FString* InGameNameParameter = InMap.Find("GameNameParameter");
			const FString* InLambdaZipS3BucketParameter = InMap.Find("LambdaZipS3BucketParameter");
			const FString* InLambdaZipS3KeyParameter = InMap.Find("LambdaZipS3KeyParameter");
			const FString* InLaunchPathParameter = InMap.Find("LaunchPathParameter");

			if (InAccountId && InApiGatewayStageNameParameter && InContainerGroupDefinitionNameParameter
				&& InContainerImageNameParameter && InContainerImageUriParameter && InGameNameParameter
				&& InLambdaZipS3BucketParameter && InLambdaZipS3KeyParameter && InLaunchPathParameter)
			{
				AccountId = Convertors::FSToStdS(*InAccountId);
				ApiGatewayStageNameParameter = Convertors::FSToStdS(*InApiGatewayStageNameParameter);
				ContainerGroupDefinitionNameParameter = Convertors::FSToStdS(*InContainerGroupDefinitionNameParameter);
				ContainerImageNameParameter = Convertors::FSToStdS(*InContainerImageNameParameter);
				ContainerImageUriParameter = Convertors::FSToStdS(*InContainerImageUriParameter);
				GameNameParameter = Convertors::FSToStdS(*InGameNameParameter);
				LambdaZipS3BucketParameter = Convertors::FSToStdS(*InLambdaZipS3BucketParameter);
				LambdaZipS3KeyParameter = Convertors::FSToStdS(*InLambdaZipS3KeyParameter);
				LaunchPathParameter = Convertors::FSToStdS(*InLaunchPathParameter);
			}
		}

		virtual TMap<FString, FString> ToMap() const override
		{
			TMap<FString, FString> ParamsMap = {};
			
			ParamsMap.Emplace("AccountId", AccountId.c_str());
			ParamsMap.Emplace("ApiGatewayStageNameParameter", ApiGatewayStageNameParameter.c_str());
			ParamsMap.Emplace("ContainerGroupDefinitionNameParameter", ContainerGroupDefinitionNameParameter.c_str());
			ParamsMap.Emplace("ContainerImageNameParameter", ContainerImageNameParameter.c_str());
			ParamsMap.Emplace("ContainerImageUriParameter", ContainerImageUriParameter.c_str());
			ParamsMap.Emplace("GameNameParameter", GameNameParameter.c_str());
			ParamsMap.Emplace("LambdaZipS3BucketParameter", LambdaZipS3BucketParameter.c_str());
			ParamsMap.Emplace("LambdaZipS3KeyParameter", LambdaZipS3KeyParameter.c_str());
			ParamsMap.Emplace("LaunchPathParameter", LaunchPathParameter.c_str());

			return ParamsMap;
		}
	};

	class IAWSScenario
	{
	public:
		virtual ~IAWSScenario() = default;

		virtual const char* const* GetParamNames() const = 0;
		virtual FText GetTooltip() const = 0;
		virtual FString GetFolderName() const = 0;
		virtual FText GetUserName() const = 0;
		virtual FString GetScenarioPath() const = 0;
		virtual FString GetScenarioInstancePath() const = 0;

		virtual int SaveFeatureInstanceTemplate(IAWSAccountInstance* AwsAccountInstance, const TMap<FString, FString>& InParams) = 0;
		virtual int UploadGameServer(IAWSAccountInstance* AwsAccountInstance, const std::string& ServerFolderPath, const std::string& ExtraServerResourcesPath) = 0;
		virtual int CreateLaunchPathParameter(const FString& BuildOperatingSystem, const FString& BuildFolderPath, const FString& BuildFilePath, std::string& StdLaunchPathParameter) = 0;
	};
} // namespace AwsScenarios
