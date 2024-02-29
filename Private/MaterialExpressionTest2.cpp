#include "MaterialExpressionExamples/Public/MaterialExpressionTest2.h"

#if WITH_EDITOR
#include "MaterialCompiler.h"
#endif

#if WITH_EDITOR
int32 UMaterialExpressionTest2::Compile(FMaterialCompiler* Compiler, int32 OutputIndex)
{
	const UMaterialExpression* InputExpression1 = TextureObjectInput1.GetTracedInput().Expression;
	if (Texture1 == nullptr && InputExpression1 == nullptr)
	{
		return CompilerError(Compiler, TEXT("Missing input texture1"));
	}
	
	const UMaterialExpression* InputExpression2 = TextureObjectInput2.GetTracedInput().Expression;
	if (Texture2 == nullptr && InputExpression2 == nullptr)
	{
		return CompilerError(Compiler, TEXT("Missing input texture2"));
	}

	int32 TextureReferenceIndex1 = INDEX_NONE;
	int32 TextureCodeIndex1 = INDEX_NONE;

	if (InputExpression1)
	{
		TextureCodeIndex1 = TextureObjectInput1.Compile(Compiler);
	}
	else
	{
		TextureCodeIndex1 = Compiler->ExternalTexture(Texture1, TextureReferenceIndex1);
	}

	if (TextureCodeIndex1 == INDEX_NONE)
	{
		return INDEX_NONE;
	}

	int32 TextureReferenceIndex2 = INDEX_NONE;
	int32 TextureCodeIndex2 = INDEX_NONE;

	if (InputExpression2)
	{
		TextureCodeIndex2 = TextureObjectInput2.Compile(Compiler);
	}
	else
	{
		TextureCodeIndex2 = Compiler->ExternalTexture(Texture2, TextureReferenceIndex2);
	}

	if (TextureCodeIndex2 == INDEX_NONE)
	{
		return INDEX_NONE;
	}
	
	const UMaterialExpression* ScalarExpression = Scalar.GetTracedInput().Expression;
	int32 ScalarCodeIndex = INDEX_NONE;
	if (ScalarExpression)
	{
		ScalarCodeIndex = Scalar.Compile(Compiler);
	}
	else
	{
		ScalarCodeIndex = Compiler->Constant(ConstScalar);
	}
	
	int32 TexCoord0 = Compiler->TextureCoordinate(0, false, false);
	int32 Color1 = Compiler->TextureSample(TextureCodeIndex1, TexCoord0,SAMPLERTYPE_LinearColor);
	int32 Color2 = Compiler->TextureSample(TextureCodeIndex2, TexCoord0,SAMPLERTYPE_LinearColor);

	return Compiler->Lerp(Color1, Color2, Compiler->Step(ScalarCodeIndex, Compiler->ComponentMask(TexCoord0, true, false, false, false)));
}

uint32 UMaterialExpressionTest2::GetInputType(int32 InputIndex)
{
	if (InputIndex <= 1)
	{
		return MCT_Texture;
	}
	else
	{
		return MCT_Float;
	}
}
#endif

UObject* UMaterialExpressionTest2::GetReferencedTexture() const
{
	return Texture1;
}