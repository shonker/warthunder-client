#pragma once

namespace engine::offsets::core
{
	constexpr auto game = 0x3E283F0;

	constexpr auto unit_list = 0x3E8F160;

	constexpr auto local_player = 0x3E8F180;
}

namespace engine::offsets::game
{
	constexpr auto matrix = 0x710;
}

namespace engine::offsets::unit
{
	constexpr auto controller = 0x700;

	constexpr auto index = 0x8;

	constexpr auto name = 0xB0;
	constexpr auto team = 0x1048;

	constexpr auto state = 0xFF0;
	constexpr auto flags = 0xFC0;
	constexpr auto info = 0x1078;

	constexpr auto position = 0x8F8;
	constexpr auto rotation = 0x8C4;
	constexpr auto bb_min = 0x208;
	constexpr auto bb_max = 0x214;
}