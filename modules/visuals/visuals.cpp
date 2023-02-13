#include "visuals.hpp"

#include <mutex>
#include <cmath>

#include <array>
#include <vector>
#include <format>

#include "../../engine/engine.hpp"

#include "../../settings/settings.hpp"

#include "../../renderer/renderer.hpp"
#include "../../renderer/menu/config/config.hpp"

#include "../../engine/structures/structures.hpp"

void modules::visuals::callback( )
{
	std::unique_lock<std::mutex> initiate_thread_locker( engine::values::global_locker );

	const auto game_copy = engine::values::game;

	initiate_thread_locker.unlock( );

	if ( !game_copy.instance )
		return;

	std::unique_lock<std::mutex> update_visual_units_locker( engine::values::visuals_unit_vector_locker );

	const auto visual_units_copy = engine::values::visual_units;

	const auto local_unit_copy = game_copy.get_local_player( );

	update_visual_units_locker.unlock( );

	for ( const auto unit : visual_units_copy )
	{
		const auto draw_list = ImGui::GetBackgroundDrawList( );
		
		if ( unit.get_controller( ).instance )
		{ 
			engine::structures::vector2_t root_screen_position { };

			const auto root_position = unit.get_controller( ).get_root_position( );

			const auto distance = unit.get_controller( ).get_root_position( ).distance( local_unit_copy.get_controller( ).get_root_position( ) );
			
			std::printf( "[game] %p\n", game_copy.instance );

			std::printf( "[unit] %p\n", unit.get_controller( ).instance );
			std::printf( "[l+p] %p\n", local_unit_copy.instance );
			std::printf( "[root] %f, %f, %f\n", root_position.x, root_position.y, root_position.z );

			if ( game_copy.world_to_screen( root_position, root_screen_position ) )
			{ 
				draw_list->AddOutlinedText( renderer::imgui::elements::fonts::pro_font_windows, 9.7f, { root_screen_position.x, root_screen_position.y }, ImColor{ 0, 255, 100 }, "Enemy" );
			}
		}
	}

	update_visual_units_locker.lock( );
}