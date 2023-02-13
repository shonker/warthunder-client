#include "config.hpp"

#include "../menu.hpp"

std::variant< bool, int, float, engine::structures::vector4_t > menu::config::config_map[]
{
	false,
	5,
	1,
	100,
	false,
	false,
	50,
	0,
	VK_RBUTTON,

	false,
	1,
	false,
	100,
	false,
	false,
	20,
	0,

	false,

	1.f,
	1.f,
	1.f,

	false,
	10.f,
	10.f,

	false,

	false,
	VK_RBUTTON,

	false,
	VK_HOME,

	false,
	VK_LBUTTON,

	750,
	750,

	false,
	5,

	false,
	false,
	false,

	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,

	false,

	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },

	engine::structures::vector4_t { 1.f, 0.f, 0.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },

	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 1.f, 1.f, 1.f, 1.f },
	engine::structures::vector4_t { 0.f, 1.f, 0.f, 1.f },
};