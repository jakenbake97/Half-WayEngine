﻿#include "BEpch.h"
#include "Buffer.h"

#include "Renderer.h"

#if BE_PLATFORM_WINDOWS
#include "Platform/DirectX11/Dx11Buffer.h"
#endif

namespace Basalt
{
	VertexBuffer* VertexBuffer::Create(const std::vector<Vertex>& vertices)
	{
		switch (Renderer::GetRenderAPI())
		{
			case RendererAPI::None:
				BE_ERROR("RendererAPI::None (headless) is not currently supported File:{0}, Line:{1}", __FILE__, __LINE__);
				return nullptr;
#if BE_PLATFORM_WINDOWS
			case RendererAPI::DirectX11: return new Dx11VertexBuffer(vertices);
#endif

		}
		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform", Renderer::GetRenderAPI());
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(std::vector<uint32> indices)
	{
		switch (Renderer::GetRenderAPI())
		{
			case RendererAPI::None:
				BE_ERROR("RendererAPI::None (headless) is not currently supported File:{0}, Line:{1}", __FILE__, __LINE__);
				return nullptr;
#if BE_PLATFORM_WINDOWS
			case RendererAPI::DirectX11: return new Dx11IndexBuffer(indices);
#endif
		}

		BE_ERROR("RenderAPI ({0}) is currently set to an unknown or unsupported API on the current platform", Renderer::GetRenderAPI());
		return nullptr;
	}
}
