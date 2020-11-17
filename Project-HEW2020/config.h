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

// テクスチャーのファイル名
#define TEXTURE_DEBUG				"assets/texture/debug_font_32x64.png"
#define TEXTURE_BG					"assets/texture/background_only.png"
#define TEXTURE_BG_OVERLAY			"assets/texture/background_overlay.png"
#define TEXTURE_OVERLAY_RANGE		"assets/texture/overlay_range.png"

#define TEXTURE_PLAYER				"assets/texture/player.png"
#define TEXTURE_PLAYER_CLIMBING		"assets/texture/player_climbing.png"

#define TEXTURE_ROBOT				"assets/texture/wurenji01.png"

#define TEXTURE_OBJ_BED				"assets/texture/start_bed.png"
#define TEXTURE_OBJ_FLOOR			"assets/texture/2f_ground.png"
#define TEXTURE_OBJ_FLOOR_OVERLAY	"assets/texture/2f_handrail.png"
#define TEXTURE_OBJECT_LADDER		"assets/texture/ladder.png"