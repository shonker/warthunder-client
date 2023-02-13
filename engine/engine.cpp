#include "engine.hpp"

#include "types/types.hpp"

#include "../settings/settings.hpp"
#include "../renderer/menu/config/config.hpp"

std::mutex engine::values::global_locker;
std::mutex engine::values::visuals_unit_vector_locker;

std::mutex engine::values::loot_visuals_unit_vector_locker;

std::mutex engine::values::aim_vector_locker;
std::mutex engine::values::silent_aim_vector_locker;

std::uintptr_t engine::values::process_base = 0;

engine::types::game_t engine::values::game { 0 };

std::vector< engine::types::unit_t > engine::values::aim_units { };
std::vector< engine::types::unit_t > engine::values::visual_units { };

std::once_flag setup_bases;

static HWND game;

std::pair< std::int32_t, std::int32_t > engine::tools::get_screen_size( )
{
	if ( !game )
		game = lf( FindWindowA )( xs( "DagorWClass" ), nullptr );

	RECT screen_dimensions{ };

	if ( lf( GetClientRect )( game, &screen_dimensions ) )
	{
		return { screen_dimensions.right - screen_dimensions.left, screen_dimensions.bottom - screen_dimensions.top };
	}

	return { 0, 0 };
}

void engine::functions::initiate( )
{
	while ( true )
	{
		std::call_once( setup_bases, [=]()
			{
				engine::values::process_base = driver.base( );
			});

		const auto temporary_game_value = driver.read< types::game_t >( engine::values::process_base + engine::offsets::core::game );

		std::unique_lock<std::mutex> initiate_thread_locker( engine::values::global_locker );

		engine::values::game = temporary_game_value;

		std::printf( "game: %p\n", temporary_game_value.instance );

		initiate_thread_locker.unlock( );

		if ( !engine::values::game.instance )
			continue;

		std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
	}
}

void engine::functions::update_aim_units_vector( )
{
	
}

void engine::functions::update_visual_units_vector( )
{
	while( true )
	{
		std::unique_lock<std::mutex> update_visual_units_global_locker( engine::values::global_locker );

		if ( !engine::values::game.instance )
		{
			update_visual_units_global_locker.unlock( );

			std::unique_lock<std::mutex> update_visual_units_locker( engine::values::visuals_unit_vector_locker );

			engine::values::visual_units.clear( );

			update_visual_units_locker.unlock( );

			continue;
		}

		types::game_t local_game_clone { engine::values::game.instance };

		update_visual_units_global_locker.unlock( );

		const auto temporary_visual_units = local_game_clone.get_units( );

		std::unique_lock<std::mutex> update_visual_units_locker( engine::values::visuals_unit_vector_locker );

		engine::values::visual_units = temporary_visual_units;

		update_visual_units_locker.unlock( );

		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	}
}