// license:BSD-3-Clause
// copyright-holders:Carlos A. Lozano
#ifndef MAME_SEIBU_BLOODBRO_H
#define MAME_SEIBU_BLOODBRO_H

#pragma once

#include "sei021x_sei0220_spr.h"

#include "seibusound.h"

#include "sound/ymopl.h"

#include "emupal.h"
#include "screen.h"
#include "tilemap.h"

class bloodbro_state : public driver_device, public seibu_sound_common
{
public:
	bloodbro_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_spritegen(*this, "spritegen"),
		m_seibu_sound(*this, "seibu_sound"),
		m_ymsnd(*this, "ymsnd"),
		m_spriteram(*this, "spriteram"),
		m_bgvideoram(*this, "bgvideoram"),
		m_fgvideoram(*this, "fgvideoram"),
		m_txvideoram(*this, "txvideoram")
	{ }

	void bloodbro(machine_config &config);
	void skysmash(machine_config &config);

protected:
	virtual void video_start() override;

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	optional_device<sei0210_device> m_spritegen;
	required_device<seibu_sound_device> m_seibu_sound;
	required_device<ym3812_device> m_ymsnd;

	required_shared_ptr<uint16_t> m_spriteram;
	required_shared_ptr<uint16_t> m_bgvideoram;
	required_shared_ptr<uint16_t> m_fgvideoram;
	required_shared_ptr<uint16_t> m_txvideoram;

	uint16_t m_scrollram[6]{};
	uint16_t m_layer_en = 0U;

	tilemap_t *m_bg_tilemap = nullptr;
	tilemap_t *m_fg_tilemap = nullptr;
	tilemap_t *m_tx_tilemap = nullptr;

	void bgvideoram_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void fgvideoram_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void txvideoram_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void layer_en_w(uint16_t data);
	void layer_scroll_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);

	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_tx_tile_info);

	uint32_t screen_update_bloodbro(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void bloodbro_draw_sprites(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t pri_cb(uint8_t pri, uint8_t ext);

	void bloodbro_map(address_map &map);
	void common_map(address_map &map);
	void skysmash_map(address_map &map);
};

class weststry_state : public bloodbro_state
{
public:
	weststry_state(const machine_config &mconfig, device_type type, const char *tag) :
		bloodbro_state(mconfig, type, tag)
	{ }

	void init_weststry();

	void weststry(machine_config &config);

private:
	bool m_weststry_opl_irq = false;
	bool m_weststry_soundnmi_mask = false;

	void weststry_layer_scroll_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void weststry_soundlatch_w(offs_t offset, u8 data);
	void weststry_opl_irq_w(int state);
	void weststry_opl_w(offs_t offset, uint8_t data);
	void weststry_soundnmi_ack_w(uint8_t data);
	void weststry_soundnmi_update();

	uint32_t screen_update_weststry(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void weststry_draw_sprites(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

	void weststry_map(address_map &map);
	void weststry_sound_map(address_map &map);
};

#endif // MAME_SEIBU_BLOODBRO_H
