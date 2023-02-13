#include <mutex>

#include "types.hpp"

#include "../engine.hpp"

std::pair< engine::types::table_t, std::uint32_t > engine::types::get_unit_table( )
{
	return std::pair< engine::types::table_t, std::uint32_t >( driver.read< types::table_t >( engine::values::process_base + offsets::core::unit_list ), driver.read< std::uint32_t >( engine::values::process_base + ( offsets::core::unit_list + sizeof( void* ) ) ) );
}

std::vector< engine::types::unit_t > engine::types::game_t::get_units( ) const
{
	std::vector< engine::types::unit_t > units;

	auto unit_table = engine::types::get_unit_table( ).first;

	for ( auto i = 0u; i < engine::types::get_unit_table( ).second; ++i )
	{
		const auto unit = driver.read< engine::types::unit_t >( unit_table.instance + offsets::unit::index + ( ( sizeof( void* ) * 2 ) * i ) );

		if ( unit.instance )
			units.push_back( unit );
	}

	return units;
}

engine::types::unit_t engine::types::game_t::get_local_player( ) const
{
	return driver.read< engine::types::unit_t >( instance + offsets::core::local_player );
}

engine::types::controller_t engine::types::unit_t::get_controller( ) const
{
	return driver.read< engine::types::controller_t >( instance + offsets::unit::controller );
}

engine::structures::vector3_t engine::types::controller_t::get_root_position( ) const
{
	return driver.read< engine::structures::vector3_t >( instance + offsets::unit::position );
}

bool engine::types::game_t::world_to_screen( const engine::structures::vector3_t& in, engine::structures::vector2_t& out ) const
{
	const engine::structures::matrix4x4_t matrix = driver.read< engine::structures::matrix4x4_t >( instance + offsets::game::matrix );

	float width = matrix[0][3] * in.x + matrix[1][3] * in.y + matrix[2][3] * in.z + matrix[3][3];

	if ( std::isnan( width ) || !width )
		return false;

	width = 1.0 / width;

	float x = in.x * matrix[0][0] + in.y * matrix[1][0] + in.z * matrix[2][0] + matrix[3][0];
	float y = in.x * matrix[0][1] + in.y * matrix[1][1] + in.z * matrix[2][1] + matrix[3][1];

	float xw = x * width;
	float yw = y * width;

	const auto [ w, h ] = engine::tools::get_screen_size();

	out.x = ( w / 2 * xw ) + ( xw + w / 2 );
	out.y = -( h / 2 * yw ) + ( yw + h / 2 );

	return true;
}