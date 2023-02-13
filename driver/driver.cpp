#include "driver.hpp"
#include "../integrity/integrity.hpp"

#include <tlhelp32.h>
#include <iostream>

driver_t driver;

bool driver_t::initiate( const char* const window_name )
{
	return lf( GetWindowThreadProcessId )( lf( FindWindowA )( window_name, nullptr ), ( DWORD* )&to_process_id );
}

std::string driver_t::read_arma_string( std::uintptr_t address )
{
	char temporary[ 1048 ]; 
	
	auto length = driver.read< int >( address + 0x8 );

	driver.read_arr( address + 0x10, temporary, length );
	
	return temporary;
}