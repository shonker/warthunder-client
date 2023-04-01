#include <windows.h>

#include <cstdint>
#include <dbghelp.h>
#include <shlobj_core.h>

#include "driver/driver.hpp"

#include "integrity/integrity.hpp"

#include "renderer/renderer.hpp"

#include "settings/settings.hpp"
#include "io/io.hpp"

#include "engine/engine.hpp"
#include "engine/structures/structures.hpp"

#include "dependencies/xorstring/xorstring.hpp"

#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "Dbghelp.lib" )

int core( )
{
	/*bool integrity_status = integrity::check( );

	if constexpr ( !settings::values::using_auth )
		integrity_status = true;

	if ( integrity_status )
	{*/
		/*while ( !GetAsyncKeyState( VK_F2 ) )
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );*/

		if constexpr ( settings::values::debug )
			io::open_console( xs( "NZXT CAM" ) );

		driver.initiate( xs( "DagorWClass" ) );

		std::thread{ engine::functions::initiate }.detach( );

		std::thread{ engine::functions::update_aim_units_vector }.detach();

		std::thread{ engine::functions::update_visual_units_vector }.detach( );

		std::thread( []( )
			{ renderer::start( xs( "DagorWClass" ) ); } ).detach( );
	/*}
	else
	{
		_Exit( 0 );
	}*/

	return 0;
}

bool DllMain( void*, const std::uint32_t injection_reason, void* )
{
	if ( injection_reason == DLL_PROCESS_ATTACH )
		std::thread{ core }.detach( );

	return true;
}