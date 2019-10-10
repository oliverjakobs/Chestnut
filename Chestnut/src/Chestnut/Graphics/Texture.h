#pragma once

#include <glad/glad.h>

namespace chst
{
	struct TextureConfig
	{
		int INTERAL_FORMAT;
		uint32_t FORMAT;

		uint32_t TYPE;

		int MIN_FILTER;
		int MAG_FILTER;

		int WRAP_S;
		int WRAP_T;
	};

	constexpr TextureConfig DEFAULT_CONFIG{ GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_NEAREST, GL_REPEAT, GL_REPEAT };

	struct Texture
	{
	private:
		uint32_t m_activeSlot;
	public:
		uint32_t ID;

		int Width;
		int Height;
		int BPP;

		// functions
		Texture(const std::string& path, bool flipOnLoad = true, TextureConfig config = DEFAULT_CONFIG);
		Texture(int width, int height, TextureConfig config = DEFAULT_CONFIG);
		Texture(unsigned char* bitmap, int width, int height, TextureConfig config = DEFAULT_CONFIG);
		~Texture();

		static unsigned int CreateTexture(unsigned char* pixels, int width, int height, TextureConfig config);

		void Bind(uint32_t slot = 0);
		void Unbind();
	};
}