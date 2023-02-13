#pragma once

#include <mutex>

#include "types/types.hpp"
#include "offsets/offsets.hpp"

namespace engine::values
{
	extern std::mutex global_locker;
	extern std::mutex visuals_unit_vector_locker;

	extern std::mutex loot_visuals_unit_vector_locker;

	extern std::mutex aim_vector_locker;
	extern std::mutex silent_aim_vector_locker;

	extern types::game_t game;

	extern std::vector< engine::types::unit_t > aim_units;
	extern std::vector< engine::types::unit_t > visual_units;

	extern std::uintptr_t process_base;
}

namespace engine::tools
{
	std::pair< std::int32_t, std::int32_t > get_screen_size( );
}

namespace engine::functions
{
	void initiate( );

	void update_aim_units_vector( );

	void update_visual_units_vector( );
}