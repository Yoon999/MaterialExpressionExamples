#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionTest2.generated.h"

UCLASS()
class MATERIALEXPRESSIONEXAMPLES_API UMaterialExpressionTest2 : public UMaterialExpression
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'Texture1' if not specified"))
	FExpressionInput TextureObjectInput1;

	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'Texture2' if not specified"))
	FExpressionInput TextureObjectInput2;

	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'Const Scalar' if not specified"))
	FExpressionInput Scalar;

	UPROPERTY(EditAnywhere, Category=MaterialExpressionTest2, meta = (OverridingInputProperty = "TextureObject1"))
	UTexture* Texture1;

	UPROPERTY(EditAnywhere, Category=MaterialExpressionTest2, meta = (OverridingInputProperty = "TextureObject2"))
	UTexture* Texture2;
	
	UPROPERTY(EditAnywhere, Category=MaterialExpressionTest2, meta = (OverridingInputProperty = "Scalar", ClampMin = 0, ClampMax = 1))
	float ConstScalar;

	//~ Begin UMaterialExpression Interface
#if WITH_EDITOR
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual uint32 GetInputType(int32 InputIndex) override;
#endif // WITH_EDITOR
	//~ End UMaterialExpression Interface

	virtual UObject* GetReferencedTexture() const override;
	virtual bool CanReferenceTexture() const override { return true; }
};
