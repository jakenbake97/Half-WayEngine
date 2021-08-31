﻿#pragma once
#include "BEpch.h"
#include "RenderContext.h"

namespace Basalt
{
	//class RenderContext;

	enum class RendererAPI
	{
		None = 0,
		DirectX11 = 1
	};

	class Renderer
	{
	public:
		static void Initialize(void* windowHandle);
		static RendererAPI GetRenderAPI() { return currentAPI; }
		static RenderContext& GetRenderContext();
	private:
		static RendererAPI currentAPI;
		static std::unique_ptr<RenderContext> context;
	};

	struct Vertex
	{
		Vector2 pos;
		ByteColor color;
	};
}
