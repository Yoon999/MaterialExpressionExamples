#include "MaterialExpressionExamples/Public/MaterialExpressionTest.h"

#if WITH_EDITOR
#include "MaterialCompiler.h"
#endif

UMaterialExpressionTest::UMaterialExpressionTest()
{
	Outputs.Empty();
	Outputs.Add(FExpressionOutput("Tex1"));
	Outputs.Add(FExpressionOutput("Tex2"));
}

#if WITH_EDITOR
int32 UMaterialExpressionTest::Compile(FMaterialCompiler* Compiler, int32 OutputIndex)
{
	FExpressionInput InputTexture;
	UTexture* Texture;
	const UMaterialExpression* InputExpression;
	if (OutputIndex == 0)
	{
		InputTexture = TextureObjectInput1;
		Texture = Texture1;
		InputExpression = TextureObjectInput1.GetTracedInput().Expression;
	}
	else // OutputIndex == 1
	{
		InputTexture = TextureObjectInput2;
		Texture = Texture2;
		InputExpression = TextureObjectInput2.GetTracedInput().Expression;
	}
	
	if (Texture == nullptr && InputExpression == nullptr)
	{
		return CompilerError(Compiler, TEXT("Missing input texture1"));
	}

	int32 TextureReferenceIndex = INDEX_NONE;
	int32 TextureCodeIndex = INDEX_NONE;

	if (InputExpression)
	{
		TextureCodeIndex = InputTexture.Compile(Compiler);
	}
	else
	{
		TextureCodeIndex = Compiler->ExternalTexture(Texture, TextureReferenceIndex);
	}

	if (TextureCodeIndex == INDEX_NONE)
	{
		return INDEX_NONE;
	}

	return Compiler->TextureSample(TextureCodeIndex, Compiler->TextureCoordinate(0, false, false),SAMPLERTYPE_LinearColor);
}

uint32 UMaterialExpressionTest::GetInputType(int32 InputIndex)
{
	return MCT_Texture;
}
#endif
UObject* UMaterialExpressionTest::GetReferencedTexture() const
{
	return Texture1;
}
