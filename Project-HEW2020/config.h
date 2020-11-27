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

// 重力システム
#define GAME_GRAVITY	(9.8f)

// ゲームオブジェクトの最大数
#define SINGLE_SCENE_OBJECT_MAX		(128)
#define SINGLE_SCENE_OVERLAY_MAX	(8)
#define UI_OVERLAY_MAX				(16)

// テクスチャーのファイル名
#define TEXTURE_FADE					"assets/texture/fade.png"
#define TEXTURE_DEBUG					"assets/texture/debug_font_32x64.png"
#define TEXTURE_BG						"assets/texture/background_only.png"
#define TEXTURE_BG_OVERLAY				"assets/texture/background_overlay.png"
#define TEXTURE_OVERLAY_RANGE			"assets/texture/overlay_range.png"
// Player
#define TEXTURE_PLAYER					"assets/texture/player.png"
#define TEXTURE_PLAYER_CLIMBING			"assets/texture/player_climbing.png"
#define TEXTURE_PLAYER_CLIMBING_PAUSED	"assets/texture/player_climbing_paused.png"
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
