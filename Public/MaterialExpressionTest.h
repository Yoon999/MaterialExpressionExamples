#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionTest.generated.h"

UCLASS()
class MATERIALEXPRESSIONEXAMPLES_API UMaterialExpressionTest : public UMaterialExpression
{
	GENERATED_BODY()

public:
	UMaterialExpressionTest();
	
private:
	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'Texture1' if not specified"))
	FExpressionInput TextureObjectInput1;

	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'Texture2' if not specified"))
	FExpressionInput TextureObjectInput2;

	UPROPERTY(EditAnywhere, Category=MaterialExpressionTest, meta = (OverridingInputProperty = "TextureObject1"))
	UTexture* Texture1;

	UPROPERTY(EditAnywhere, Category=MaterialExpressionTest, meta = (OverridingInputProperty = "TextureObject2"))
	UTexture* Texture2;

	//~ Begin UMaterialExpression Interface
#if WITH_EDITOR
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual uint32 GetInputType(int32 InputIndex) override;
#endif // WITH_EDITOR
	//~ End UMaterialExpression Interface

	virtual UObject* GetReferencedTexture() const override;
	virtual bool CanReferenceTexture() const override { return true; }
};
