#pragma once

#include <windows.h>
#include <string_view>
#include <unordered_map>

#include <variant>
#include <fstream>

#include "../../../engine/structures/structures.hpp"

enum features : int32_t
{
	aimbot_enable,
	aimbot_smoothness,
	aimbot_bone,
	aimbot_max_distance,
	aimbot_show_fov,
	aimbot_snap_lines,
	aimbot_fov,
	aimbot_fov_segments,
	aimbot_hotkey,

	silent_aimbot_enable,
	silent_aimbot_bone,
	silent_hitscan,
	silent_aimbot_max_distance,
	silent_aimbot_show_fov,
	silent_aimbot_snap_lines,
	silent_aimbot_fov,
	silent_aimbot_fov_segments,

	adjust_day_time,
	day_time_value_lat,
	day_time_value_long,
	day_brightness,

	adjust_fov,
	fov_value,
	aspect_ratio_value,

	no_grass,
	
	speed_hack,
	speed_hack_hotkey,

	loot_through_walls,
	loot_through_walls_hotkey,

	teleport_loot,
	teleport_loot_hotkey,

	display_max_distance,
	display_item_max_distance,

	display_items,
	display_items_type,

	display_ignore_infected,
	display_ignore_animals,

	display_combat_mode,

	display_bounding_box,
	display_filled_box,
	display_item_in_hands,
	display_players_name,
	display_players_type,
	display_corner_box,
	display_head_hitbox,
	display_skeleton,
	display_distance,

	disable_data_menu,

	basic_item_color,
	weapon_item_color,
	clothing_item_color,
	magazine_item_color,

	silent_aimbot_fov_color,
	aimbot_fov_color,

	bounding_box_color,
	filled_box_color,
	corner_box_color,
	player_names_color,
	item_in_hands_color,
	player_types_color,
	hitbox_color,
	skeleton_color,
	distance_color,
	health_color
};

namespace menu::config
{
	extern std::variant< bool, int, float, engine::structures::vector4_t > config_map[];
}