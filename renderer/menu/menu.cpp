#include "menu.hpp"

#include <array>
#include <functional>

#include "../renderer.hpp"

#include "../../engine/engine.hpp"

#include "../../dependencies/rawdata/person.hpp"
#include "../../dependencies/rawdata/skeleton.hpp"
#include "../../dependencies/libs/imgui_tricks.hpp"

#include "../../dependencies/xorstring/xorstring.hpp"

#include "config/config.hpp"

#include "../../settings/settings.hpp"

#include "../../modules/visuals/visuals.hpp"

static auto current_tab = 0;

void Draw_Main( float, float )
{
    ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, { 0,0 } );

    ImGui::SetCursorPos( { 24, 235 } );
    ImGui::BeginChild( xs( "Main" ), { 337, 530 }, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove );
    {
        switch ( current_tab )
        {
        case 0:
            renderer::imgui::elements::functions::checkbox( xs( "Aimbot" ), xs( "enables aimbot" ), std::get< bool >( menu::config::config_map[features::aimbot_enable] ) );

            renderer::imgui::elements::functions::hotkey( "##1", &std::get< int >( menu::config::config_map[features::aimbot_hotkey] ) );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::information( xs( "Smoothness" ), xs( "sets the smoothness of the aimbot" ), std::get< int >( menu::config::config_map[features::aimbot_smoothness] ), "%i" );

            renderer::imgui::elements::functions::slider_int( "##2", &std::get< int >( menu::config::config_map[features::aimbot_smoothness] ), 0, 10, "" );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::information( xs( "Bone" ), xs( "assigns the aiming bone" ), std::get< int >( menu::config::config_map[features::aimbot_bone] ), "%i" );

            renderer::imgui::elements::functions::combo( "##3", &std::get< int >( menu::config::config_map[features::aimbot_bone] ), "head\0\rneck\0\rchest\0\rpelvis\0\0", 1 );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::information( xs( "Max Distance" ), xs( "sets the distance interval to aim at" ), std::get< int >( menu::config::config_map[features::aimbot_max_distance] ), "%i" );

            renderer::imgui::elements::functions::slider_int( "##4", &std::get< int >( menu::config::config_map[features::aimbot_max_distance] ), 0, 500, "" );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::checkbox( xs( "Show Snap Lines" ), xs( "shows snap lines" ), std::get< bool >( menu::config::config_map[features::aimbot_snap_lines] ) );

            renderer::imgui::elements::functions::checkbox( xs( "Show FOV" ), xs( "shows circular fov" ), std::get< bool >( menu::config::config_map[features::aimbot_show_fov] ) );

            renderer::imgui::elements::functions::information( xs( "FOV" ), xs( "sets the aimbot fov" ), std::get< int >( menu::config::config_map[features::aimbot_fov] ), "%i" );

            renderer::imgui::elements::functions::slider_int( "##5", &std::get< int >( menu::config::config_map[features::aimbot_fov] ), 0, 100, "" );

            renderer::imgui::elements::functions::color_picker( "##6", std::get< engine::structures::vector4_t >( menu::config::config_map[features::aimbot_fov_color] ).color );

            renderer::imgui::elements::functions::information( xs( "FOV Segments" ), xs( "adjusts the aimbot fov shape" ), std::get< int >( menu::config::config_map[features::aimbot_fov_segments] ), "%i" );

            renderer::imgui::elements::functions::slider_int( "##7", &std::get< int >( menu::config::config_map[features::aimbot_fov_segments] ), 0, 10, "" );
        break;
        case 1:
            renderer::imgui::elements::functions::checkbox( xs( "Silent Aimbot" ), xs( "enables silent aimbot" ), std::get< bool >( menu::config::config_map[features::silent_aimbot_enable] ) );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::information( xs( "Bone" ), xs( "assigns the silent aiming bone" ), std::get< int >( menu::config::config_map[features::silent_aimbot_bone] ), "%i" );

            renderer::imgui::elements::functions::combo( "##1", &std::get< int >( menu::config::config_map[features::silent_aimbot_bone] ), "head\0\rneck\0\rchest\0\rpelvis\0\rrandom\0\0", 1 );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::checkbox( xs( "Hitscan" ), xs( "evades server logs, at the cost of accuracy" ), std::get< bool >( menu::config::config_map[features::silent_hitscan] ) );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::information( xs( "Max Distance" ), xs( "sets the distance interval to aim at" ), std::get< int >( menu::config::config_map[features::silent_aimbot_max_distance] ), "%i" );

            renderer::imgui::elements::functions::slider_int( "##2", &std::get< int >( menu::config::config_map[features::silent_aimbot_max_distance] ), 0, 500, "" );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::checkbox( xs( "Show FOV" ), xs( "shows circular fov" ), std::get< bool >( menu::config::config_map[features::silent_aimbot_show_fov] ) );

            renderer::imgui::elements::functions::information( xs( "FOV" ), xs( "sets the silent aimbot fov" ), std::get< int >( menu::config::config_map[features::silent_aimbot_fov] ), "%i" );

            renderer::imgui::elements::functions::slider_int( "##3", &std::get< int >( menu::config::config_map[features::silent_aimbot_fov] ), 0, 100, "" );

            renderer::imgui::elements::functions::color_picker( "##4", std::get< engine::structures::vector4_t >( menu::config::config_map[features::silent_aimbot_fov_color] ).color );

            renderer::imgui::elements::functions::information( xs( "FOV Segments" ), xs( "adjusts the silent aimbot fov shape" ), std::get< int >( menu::config::config_map[features::silent_aimbot_fov_segments] ), "%i" );

            renderer::imgui::elements::functions::slider_int( "##5", &std::get< int >( menu::config::config_map[features::silent_aimbot_fov_segments] ), 0, 10, "" );
        break;
        case 2:
            renderer::imgui::elements::functions::checkbox( xs( "Adjust Day Time" ), xs( "sets the time you want" ), std::get< bool >( menu::config::config_map[features::adjust_day_time] ) );

            if ( std::get< bool >( menu::config::config_map[features::adjust_day_time] ) )
            {
                renderer::imgui::elements::functions::information( xs( "Sun Latitude" ), xs( "sets the latitude" ), std::get< float >( menu::config::config_map[features::day_time_value_lat] ), "%.3f" );

                renderer::imgui::elements::functions::slider_float( "##22", &std::get< float >( menu::config::config_map[features::day_time_value_lat] ), 0, 1000.f, "%.3f", 1.f );

                renderer::imgui::elements::functions::information( xs( "Sun Longitude" ), xs( "sets the longitude" ), std::get< float >( menu::config::config_map[features::day_time_value_long] ), "%.3f" );

                renderer::imgui::elements::functions::slider_float( "##52", &std::get< float >( menu::config::config_map[features::day_time_value_long] ), 0, 1000.f, "%.3f", 1.f );

                renderer::imgui::elements::functions::information( xs( "Sun Brightness" ), xs( "sets the brightness" ), std::get< float >( menu::config::config_map[features::day_brightness] ), "%.3f" );

                renderer::imgui::elements::functions::slider_float( "##62", &std::get< float >( menu::config::config_map[features::day_brightness] ), 0, 10.f, "%.3f", 1.f );
            }

            renderer::imgui::elements::functions::checkbox( xs( "Adjust FOV/Aspect Ratio" ), xs( "sets the game fov and aspect ratio" ), std::get< bool >( menu::config::config_map[features::adjust_fov] ) );

            if ( std::get< bool >( menu::config::config_map[features::adjust_fov] ) )
            {
                renderer::imgui::elements::functions::information( xs( "Current FOV" ), xs( "current fov" ), std::get< float >( menu::config::config_map[features::fov_value] ), "%.3f" );

                renderer::imgui::elements::functions::slider_float( "##23", &std::get< float >( menu::config::config_map[features::fov_value] ), 0, 100.f, "%.3f", 1.f );

                renderer::imgui::elements::functions::information( xs( "Current Aspect Ratio" ), xs( "current aspect ratio" ), std::get< float >( menu::config::config_map[features::aspect_ratio_value] ), "%.3f" );

                renderer::imgui::elements::functions::slider_float( "##25", &std::get< float >( menu::config::config_map[features::aspect_ratio_value] ), 0, 100.f, "%.3f", 1.f );
            }

            renderer::imgui::elements::functions::checkbox( xs( "No Grass" ), xs( "removes the grass" ), std::get< bool >( menu::config::config_map[features::no_grass] ) );

            renderer::imgui::elements::functions::checkbox( xs( "Speed" ), xs( "speed up the time of actions using a hotkey" ), std::get< bool >( menu::config::config_map[features::speed_hack] ) );
                
            renderer::imgui::elements::functions::hotkey( "##1", &std::get< int >( menu::config::config_map[features::speed_hack_hotkey] ) );

            renderer::imgui::elements::functions::checkbox( xs( "Loot Through Walls" ), xs( "phase through walls, using arrow key up and down" ), std::get< bool >( menu::config::config_map[features::loot_through_walls] ) );
                
            renderer::imgui::elements::functions::hotkey( "##2", &std::get< int >( menu::config::config_map[features::loot_through_walls_hotkey] ) );

            renderer::imgui::elements::functions::checkbox( xs( "Teleport Loot" ), xs( "teleport loot to yourself" ), std::get< bool >( menu::config::config_map[features::teleport_loot] ) );
                
            renderer::imgui::elements::functions::hotkey( "##3", &std::get< int >( menu::config::config_map[features::teleport_loot_hotkey] ) );
        break;
        case 3:
            renderer::imgui::elements::functions::information( xs( "Max Distance" ), xs( "sets the max visual distance" ), std::get< int >( menu::config::config_map[features::display_max_distance ] ), "%i" );

            renderer::imgui::elements::functions::slider_int( "##1", &std::get< int >( menu::config::config_map[features::display_max_distance ] ), 0, 1000, "" );

            if ( std::get< bool >( menu::config::config_map[features::display_items] ) )
            {
                renderer::imgui::elements::functions::separator_wide( );

                renderer::imgui::elements::functions::information( xs( "Max Item Distance" ), xs( "sets the max item visual distance" ), std::get< int >( menu::config::config_map[features::display_item_max_distance] ), "%i" );

                renderer::imgui::elements::functions::slider_int( "##2", &std::get< int >( menu::config::config_map[features::display_item_max_distance] ), 0, 1000, "" );

                renderer::imgui::elements::functions::separator_wide( );
            }

            renderer::imgui::elements::functions::checkbox( xs( "Ignore Infected" ), xs( "skips infected as visual/aim units" ), std::get< bool >( menu::config::config_map[features::display_ignore_infected] ) );

            renderer::imgui::elements::functions::checkbox( xs( "Ignore Animals" ), xs( "skips animals as visual/aim units" ), std::get< bool >( menu::config::config_map[features::display_ignore_animals] ) );

            renderer::imgui::elements::functions::checkbox( xs( "Combat Mode" ), xs( "enables features convenient for combat only" ), std::get< bool >( menu::config::config_map[features::display_combat_mode] ) );

            if ( std::get< bool >( menu::config::config_map[features::display_combat_mode] ) )
            {
                std::get< bool >( menu::config::config_map[features::display_ignore_infected] ) = true;
                std::get< bool >( menu::config::config_map[features::display_ignore_animals] ) = true;

                std::get< bool >( menu::config::config_map[features::display_items] ) = true;

                std::get< bool >( menu::config::config_map[features::display_corner_box] ) = true;
                std::get< bool >( menu::config::config_map[features::display_players_name] ) = true;

                std::get< bool >( menu::config::config_map[features::display_distance] ) = true;
                std::get< bool >( menu::config::config_map[features::display_skeleton] ) = true;

                std::get< bool >( menu::config::config_map[features::display_players_type] ) = true;
                std::get< bool >( menu::config::config_map[features::display_item_in_hands] ) = true;

                std::get< int >( menu::config::config_map[features::display_items_type] ) = 4;
            }

            renderer::imgui::elements::functions::separator_wide( );

            renderer::imgui::elements::functions::checkbox( xs( "Items" ), xs( "draws items" ), std::get< bool >( menu::config::config_map[features::display_items ] ) );

            if ( std::get< bool >( menu::config::config_map[features::display_items] ) )
            {
                if ( !std::get< bool >( menu::config::config_map[features::display_combat_mode] ) )
                {
                    renderer::imgui::elements::functions::information( xs( "Item Type" ), xs( "assigns the item type to display" ), std::get< int >( menu::config::config_map[features::display_items_type] ), "%i" );

                    renderer::imgui::elements::functions::combo( "##23", &std::get< int >( menu::config::config_map[features::display_items_type] ), "basic\0\rweapon\0\rclothing\0\rmagazines\0\rcombat\0\rall\0\0", 1 );

                    renderer::imgui::elements::functions::separator( );

                    renderer::imgui::elements::functions::information( xs( "Basic Item Color" ), xs( "sets the color of the basic items" ) );

                    renderer::imgui::elements::functions::color_picker( "##29", std::get< engine::structures::vector4_t >( menu::config::config_map[features::basic_item_color] ).color );
                }

                renderer::imgui::elements::functions::information( xs( "Weapons Color" ), xs( "sets the color of the weapon items" ) );

                renderer::imgui::elements::functions::color_picker( "##39", std::get< engine::structures::vector4_t >( menu::config::config_map[features::weapon_item_color] ).color );

                if ( !std::get< bool >( menu::config::config_map[features::display_combat_mode] ) )
                {
                    renderer::imgui::elements::functions::information( xs( "Clothing Color" ), xs( "sets the color of the clothing items" ) );

                    renderer::imgui::elements::functions::color_picker( "##49", std::get< engine::structures::vector4_t >( menu::config::config_map[features::clothing_item_color] ).color );
                }

                renderer::imgui::elements::functions::information( xs( "Magazines Color" ), xs( "sets the color of the magazine/ammo items" ) );

                renderer::imgui::elements::functions::color_picker( "##59", std::get< engine::structures::vector4_t >( menu::config::config_map[features::magazine_item_color] ).color );
            }

            renderer::imgui::elements::functions::separator_wide( );

            renderer::imgui::elements::functions::checkbox( xs( "Bounding Box" ), xs( "draws a rectangular box on visual units" ), std::get< bool >( menu::config::config_map[features::display_bounding_box] ) );

            renderer::imgui::elements::functions::color_picker( "##11", std::get< engine::structures::vector4_t >( menu::config::config_map[features::bounding_box_color] ).color );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::checkbox( xs( "Filled Box" ), xs( "draws a filled rectangular box on visual units" ), std::get< bool >( menu::config::config_map[features::display_filled_box ] ) );

            renderer::imgui::elements::functions::color_picker( "##12", std::get< engine::structures::vector4_t >( menu::config::config_map[features::filled_box_color ] ).color );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::checkbox( xs( "Corner Box" ), xs( "draws a cornered box on visual units" ), std::get< bool >( menu::config::config_map[features::display_corner_box ] ) );

            renderer::imgui::elements::functions::color_picker( "##13", std::get< engine::structures::vector4_t >( menu::config::config_map[features::corner_box_color ] ).color );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::checkbox( xs( "Head Hitbox" ), xs( "draws a head square on visual units" ), std::get< bool >( menu::config::config_map[features::display_head_hitbox ] ) );

            renderer::imgui::elements::functions::color_picker( "##14", std::get< engine::structures::vector4_t >( menu::config::config_map[features::hitbox_color ] ).color );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::checkbox( xs( "Skeleton" ), xs( "draws skeletons on visual units" ), std::get< bool >( menu::config::config_map[features::display_skeleton ] ) );

            renderer::imgui::elements::functions::color_picker( "##15", std::get< engine::structures::vector4_t >( menu::config::config_map[features::skeleton_color ] ).color );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::checkbox( xs( "unit Name" ), xs( "draws unit's name" ), std::get< bool >( menu::config::config_map[features::display_players_name] ) );

            renderer::imgui::elements::functions::color_picker( "##16", std::get< engine::structures::vector4_t >( menu::config::config_map[features::player_names_color ] ).color );

            renderer::imgui::elements::functions::separator( ); 

            renderer::imgui::elements::functions::checkbox( xs( "Item In Hands" ), xs( "draws unit's item equipped" ), std::get< bool >( menu::config::config_map[features::display_item_in_hands] ) );

            renderer::imgui::elements::functions::color_picker( "##19", std::get< engine::structures::vector4_t >( menu::config::config_map[features::item_in_hands_color ] ).color );

            renderer::imgui::elements::functions::separator( ); 

            renderer::imgui::elements::functions::checkbox( xs( "unit Type" ), xs( "draws unit type name" ), std::get< bool >( menu::config::config_map[features::display_players_type] ) );

            renderer::imgui::elements::functions::color_picker( "##17", std::get< engine::structures::vector4_t >( menu::config::config_map[features::player_types_color ] ).color );

            renderer::imgui::elements::functions::separator( );    

            renderer::imgui::elements::functions::checkbox( xs( "Distance" ), xs( "draws distance of unit" ), std::get< bool >( menu::config::config_map[features::display_distance ] ) );

            renderer::imgui::elements::functions::color_picker( "##18", std::get< engine::structures::vector4_t >( menu::config::config_map[features::distance_color ] ).color );
            break;
        case 4:
            renderer::imgui::elements::functions::checkbox( xs( "Disable Data Menu" ), xs( "disables the data menu" ), std::get< bool >( menu::config::config_map[features::disable_data_menu ] ) );

            renderer::imgui::elements::functions::separator( );

            renderer::imgui::elements::functions::button( xs( "Save Config" ), { 328, 35 }, renderer::imgui::elements::button_flags::BUTTON_PURPLE );

            ImGui::NewLine( );

            renderer::imgui::elements::functions::button( xs( "Load Config" ), { 328, 35 }, renderer::imgui::elements::button_flags::BUTTON_GRAY );
            break;
        default:
            break;
        }
    }
    ImGui::EndChild( );

    ImGui::PopStyleVar( );
}

void renderer::menu::draw( )
{
    modules::visuals::callback( );

    if ( renderer::values::renderer->is_menu_open )
    {
        ImGui::SetNextWindowSize( { 375, 770 }, ImGuiCond_Once );

        ImGui::Begin( xs( "DayZ" ), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove );
        {
            auto DrawList = ImGui::GetWindowDrawList( );
            auto Position = ImGui::GetWindowPos( );

            DrawList->AddText( renderer::imgui::elements::fonts::druk_wide_bold, 30, { Position.x + 24, Position.y + 36 }, ImColor{ 255, 255, 255 }, xs( "DayZ" ) );

            DrawList->AddRectFilled( { Position.x + 24, Position.y + 73 }, { Position.x + 24 + 187, Position.y + 73 + 2 }, ImColor{ 255, 255, 255, 10 } );
            DrawList->AddRectFilled( { Position.x + 24, Position.y + 73 }, { Position.x + 24 + 88, Position.y + 73 + 2 }, ImColor{ 127, 128, 246 } );

            ImGui::SetCursorPos( { 24, 107 } );

            ImGui::BeginGroup( );
            {
                renderer::imgui::elements::functions::tab( xs( "LEGIT" ), (const char*)ICON_FA_SHIELD_CHECK, current_tab, 0 );

                ImGui::SameLine( );

                renderer::imgui::elements::functions::tab( xs( "RAGE" ), (const char*)ICON_FA_SHIELD, current_tab, 1 );

                ImGui::SameLine( );

                renderer::imgui::elements::functions::tab( xs( "MISC" ), (const char*)ICON_FA_FOLDER, current_tab, 2 );

                ImGui::SameLine( );

                renderer::imgui::elements::functions::tab( xs( "VISUALS" ), (const char*)ICON_FA_BOLT, current_tab, 3 );

                ImGui::SameLine( );

                renderer::imgui::elements::functions::tab( xs( "CFG" ), (const char*)ICON_FA_ARCHIVE, current_tab, 4 );

            }
            ImGui::EndGroup( );

            Draw_Main( 0.f, 0.f );
        }
        ImGui::End( );
    }
    else
    {
        ImGui::Begin( xs( "DayZ_Watermark" ), nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove );
        { 
            auto DrawList = ImGui::GetWindowDrawList( );

            ImGui::SetWindowSize( { 220, 40 } );

            ImGui::SetWindowPos( { 0, 0 } );

            DrawList->AddText(renderer::imgui::elements::fonts::druk_wide_bold, 25, { 15, 5 }, ImColor{ 255, 255, 255, 70 }, xs("loaded"));
        }
        ImGui::End( );
    }
}