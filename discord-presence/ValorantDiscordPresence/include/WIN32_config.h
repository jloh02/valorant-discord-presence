#pragma once
#if defined(_WIN32)
#pragma pack(push, 1)
struct BitmapImageHeader
{
	uint32_t const structSize{ sizeof(BitmapImageHeader) };
	int32_t width{ 0 };
	int32_t height{ 0 };
	uint16_t const planes{ 1 };
	uint16_t const bpp{ 32 };
	uint32_t const pad0{ 0 };
	uint32_t const pad1{ 0 };
	uint32_t const hres{ 2835 };
	uint32_t const vres{ 2835 };
	uint32_t const pad4{ 0 };
	uint32_t const pad5{ 0 };

	BitmapImageHeader& operator=(BitmapImageHeader const&) = delete;
};

struct BitmapFileHeader
{
	uint8_t const magic0{ 'B' };
	uint8_t const magic1{ 'M' };
	uint32_t size{ 0 };
	uint32_t const pad{ 0 };
	uint32_t const offset{ sizeof(BitmapFileHeader) + sizeof(BitmapImageHeader) };

	BitmapFileHeader& operator=(BitmapFileHeader const&) = delete;
};
#pragma pack(pop)
#endif