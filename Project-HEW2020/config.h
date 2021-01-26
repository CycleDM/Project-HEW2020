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
#define GAME_GRAVITY	(9.8f)

// ゲームオブジェクトの最大数
#define SINGLE_SCENE_OBJECT_MAX		(128)
#define SINGLE_SCENE_OVERLAY_MAX	(64)
#define UI_OVERLAY_MAX				(64)

// テクスチャーのファイル名
#define TEXTURE_LOADING					"assets/texture/loading.png"
#define TEXTURE_FADE					"assets/texture/fade.png"
#define TEXTURE_BG						"assets/texture/background_only.png"
#define TEXTURE_BG_OVERLAY				"assets/texture/background_overlay.png"
#define TEXTURE_OVERLAY_RANGE			"assets/texture/overlay_range.png"
// Player
#define TEXTURE_PLAYER					"assets/texture/player/player.png"
#define TEXTURE_PLAYER_CLIMBING			"assets/texture/player/climbing.png"
#define TEXTURE_PLAYER_CLIMBING_PAUSED	"assets/texture/player/climbing_paused.png"
#define TEXTURE_PLAYER_IDEA				"assets/texture/player/idea.png"
#define TEXTURE_PLAYER_IDEA_HAND		"assets/texture/player/idea_hand.png"
#define TEXTURE_PLAYER_LOST_HAND1		"assets/texture/player/lost_hand_1.png"
#define TEXTURE_PLAYER_LOST_HAND2		"assets/texture/player/lost_hand_2.png"
#define TEXTURE_PLAYER_LOST_LEG			"assets/texture/player/lost_leg.png"
// Enemy
#define TEXTURE_ROBOT					"assets/texture/wurenji01.png"
// Object
#define TEXTURE_OBJ_BED					"assets/texture/start_bed.png"
#define TEXTURE_OBJ_FLOOR				"assets/texture/2f_ground.png"
#define TEXTURE_OBJ_FLOOR_OVERLAY		"assets/texture/2f_handrail.png"
#define TEXTURE_OBJ_LADDER				"assets/texture/ladder.png"
#define TEXTURE_OBJ_DOOR1				"assets/texture/door1.png"

#define TEXTURE_OBJ_CODED_LOCK_ITEM		"assets/texture/lock/lock_item.png"
#define TEXTURE_CLUI_BASE				"assets/texture/lock/lock_base.png"
#define TEXTURE_CLUI_KEY				"assets/texture/lock/lock_key.png"
#define TEXTURE_CLUI_SHADOW				"assets/texture/lock/lock_shadow.png"
#define TEXTURE_CLUI_LIGHT				"assets/texture/lock/lock_light.png"

// GameScene01
#define TEXTURE_SCENE01_BG				"assets/texture/scene01/background.png"
#define TEXTURE_SCENE01_BG_OVERLAY		"assets/texture/scene01/background_overlay.png"
#define TEXTURE_OBJ_TRASH1				"assets/texture/scene01/trash_stack.png"
#define TEXTURE_OBJ_TRASH2				"assets/texture/scene01/trash_core.png"
#define TEXTURE_OBJ_CRASH_ROBOT			"assets/texture/scene01/crash_robot.png"
#define TEXTURE_OBJ_DIGITAL_DOOR		"assets/texture/scene01/digital_door.png"
#define TEXTURE_ITEM_CODE_CUT1			"assets/texture/scene01/code_cut01.png"
#define TEXTURE_ITEM_CODE_CUT2			"assets/texture/scene01/code_cut02.png"
#define TEXTURE_OBJ_GENERATOR			"assets/texture/scene01/generator.png"
#define TEXTURE_GENERATOR_UI_BASE		"assets/texture/scene01/generator_ui_base.png"
#define TEXTURE_GENERATOR_UI_LINE1		"assets/texture/scene01/generator_ui_line01.png"
#define TEXTURE_GENERATOR_UI_LINE2		"assets/texture/scene01/generator_ui_line02.png"