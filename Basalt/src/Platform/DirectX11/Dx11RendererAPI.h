﻿#pragma once
#include "Basalt/Renderer/RendererAPI.h"

namespace Basalt
{
	class Dx11RendererAPI : public RendererAPI
	{
	public:
		void Clear(Color color) override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

		void SwapBuffers(bool isVsync) override;
	};
}
