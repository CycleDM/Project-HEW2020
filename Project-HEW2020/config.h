//----------------------------------------------------------------------------
// 
// Project-HEW2020 [config.h]
// 各種パラメータ、マクロ、定数
// 
// Date:   2020/10/22
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

// スクリーンサイズ
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)

// FONT
#define FONT_FILE_NAME					"assets/font/LanaPixel.ttf"
#define FONT_NAME						"LanaPixel"

// 重力システム
#define GAME_GRAVITY	(20.0f)

// ゲームオブジェクトの最大数
#define SINGLE_SCENE_OBJECT_MAX		(128)
#define SINGLE_SCENE_OVERLAY_MAX	(64)
#define UI_OVERLAY_MAX				(64)

// テクスチャーのファイル名
#define TEXTURE_LOADING					"assets/texture/loading.png"
#define TEXTURE_FADE					"assets/texture/fade.png"
// Player
#define TEXTURE_PLAYER					"assets/texture/player/player.png"
#define TEXTURE_PLAYER_CLIMBING			"assets/texture/player/climbing.png"
#define TEXTURE_PLAYER_CLIMBING_PAUSED	"assets/texture/player/climbing_paused.png"
#define TEXTURE_PLAYER_IDEA				"assets/texture/player/idea.png"
#define TEXTURE_PLAYER_IDEA_HAND		"assets/texture/player/idea_hand.png"
#define TEXTURE_PLAYER_LOST_HAND1		"assets/texture/player/lost_hand_1.png"
#define TEXTURE_PLAYER_LOST_HAND2		"assets/texture/player/lost_hand_2.png"
#define TEXTURE_PLAYER_LOST_LEG			"assets/texture/player/lost_leg.png"

// SCENE
#define TEXTURE_OVERLAY_RANGE			"assets/texture/overlay_range.png"
#define TEXTURE_BG						"assets/texture/room/hew_background_room.png"
#define TEXTURE_BG_OVERLAY				"assets/texture/room/hew_background_overlay.png"
#define TEXTURE_OBJ_CODED_LOCK_ITEM		"assets/texture/lock/lock_item.png"
#define TEXTURE_CLUI_BASE				"assets/texture/lock/lock_base.png"
#define TEXTURE_CLUI_KEY				"assets/texture/lock/lock_key.png"
#define TEXTURE_CLUI_SHADOW				"assets/texture/lock/lock_shadow.png"
#define TEXTURE_CLUI_LIGHT				"assets/texture/lock/lock_light.png"
#define TEXTURE_OBJ_BED					"assets/texture/start_bed.png"
#define TEXTURE_OBJ_FLOOR				"assets/texture/room/2f_ground.png"
#define TEXTURE_OBJ_FLOOR_OVERLAY		"assets/texture/room/hand.png"
#define TEXTURE_OBJ_LADDER				"assets/texture/room/ladder.png"
#define TEXTURE_OBJ_DOOR1				"assets/texture/door_animation.png"

// TitleScene
#define TEXTURE_TITLE_BG				"assets/texture/title/title_bg.png"
#define TEXTURE_TITLE_LOGO				"assets/texture/title/logo.png"
#define TEXTURE_TITLE_BUTTON01			"assets/texture/title/button_start.png"
#define TEXTURE_TITLE_BUTTON02			"assets/texture/title/button_quit.png"

// GameScene01
#define TEXTURE_SCENE01_BG				"assets/texture/scene01/background.png"
#define TEXTURE_SCENE01_BG_OVERLAY		"assets/texture/scene01/background_overlay.png"
#define TEXTURE_OBJ_TRASH1				"assets/texture/scene01/trash_stack.png"
#define TEXTURE_OBJ_TRASH2				"assets/texture/scene01/trash_core.png"
#define TEXTURE_OBJ_CRASH_ROBOT			"assets/texture/scene01/crash_robot.png"
#define TEXTURE_OBJ_CRASH_ROBOT2		"assets/texture/scene01/crash_robot2.png"
#define TEXTURE_OBJ_DIGITAL_DOOR		"assets/texture/scene01/digital_door.png"
#define TEXTURE_ITEM_CODE_CUT1			"assets/texture/scene01/code_cut01.png"
#define TEXTURE_ITEM_CODE_CUT2			"assets/texture/scene01/code_cut02.png"
#define TEXTURE_OBJ_GENERATOR			"assets/texture/scene01/generator.png"
#define TEXTURE_GENERATOR_UI_BASE		"assets/texture/scene01/generator_ui_base.png"
#define TEXTURE_GENERATOR_UI_LINE1		"assets/texture/scene01/generator_ui_line01.png"
#define TEXTURE_GENERATOR_UI_LINE2		"assets/texture/scene01/generator_ui_line02.png"
#define TEXTURE_TALKING_TEXT			"assets/texture/scene01/talking_text.png"
#define TEXTURE_OBJ_SCREEN				"assets/texture/scene01/screen.png"
#define TEXTURE_OBJ_LANGUAGE			"assets/texture/scene01/language_chip.png"
#define TEXTURE_SCREEN_UI				"assets/texture/scene01/screen_ui.png"
#define TEXTURE_OBJ_LIFT_BOX			"assets/texture/scene01/lift_box.png"
#define TEXTURE_LIFT_FRAME				"assets/texture/scene01/lift_frame.png"
#define TEXTURE_LIFT_DOOR				"assets/texture/scene01/lift_door_animation.png"
#define TEXTURE_OBJ_LIFT_PANEL			"assets/texture/scene01/lift_panel.png"
#define TEXTURE_PANEL_BUTTON_BLUE		"assets/texture/scene01/lift_panel_button1.png"
#define TEXTURE_PANEL_BUTTON_GREEN		"assets/texture/scene01/lift_panel_button2.png"
#define TEXTURE_OBJ_COMPUTER			"assets/texture/scene01/2f/computer.png"
#define TEXTURE_COMPUTER_UI_BASE		"assets/texture/scene01/2f/computer_ui.png"
#define TEXTURE_COMPUTER_UI_KEYS		"assets/texture/scene01/2f/computer_keys.png"
#define TEXTURE_COMPUTER_UI_KEYS_OVER	"assets/texture/scene01/2f/computer_keys_overlay.png"
#define TEXTURE_OBJ_MAKER				"assets/texture/scene01/2f/maker.png"
#define TEXTURE_OBJ_NEW_ROBOT			"assets/texture/scene01/2f/new_robot.png"
#define TEXTURE_OBJ_VISUAL				"assets/texture/scene01/2f/visual_chip.png"
#define TEXTURE_ITEM_HAND				"assets/texture/scene01/2f/item_hand.png"