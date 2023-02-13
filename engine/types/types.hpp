#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "../offsets/offsets.hpp"
#include "../structures/structures.hpp"

#include "../../driver/driver.hpp"

namespace engine::types
{
	struct table_t
	{
		[[nodiscard]] std::uint32_t size( )
		{
			return driver.read< std::uint32_t >( instance + sizeof( void* ) );
		}

		std::uintptr_t instance;
	};

	struct object_t
	{
		template< class type_t = std::uintptr_t >
		[[nodiscard]] type_t as( ) const
		{
			return type_t{ instance };
		}

		std::uintptr_t instance;
	};

	struct controller_t : public object_t
	{
		[[nodiscard]] engine::structures::vector3_t get_root_position( ) const;
	};

	struct unit_t : public object_t
	{
		[[nodiscard]] controller_t get_controller( ) const;
	};

	struct game_t : public object_t
	{
		[[nodiscard]] std::vector< engine::types::unit_t > get_units( ) const;

		[[nodiscard]] unit_t get_local_player( ) const;

		[[nodiscard]] bool world_to_screen( const engine::structures::vector3_t& in, engine::structures::vector2_t& out ) const;
	};

	std::pair< engine::types::table_t, std::uint32_t > get_unit_table( );
}