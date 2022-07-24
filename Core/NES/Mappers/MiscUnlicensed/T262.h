#pragma once
#include "stdafx.h"
#include "NES/BaseMapper.h"

class T262 : public BaseMapper
{
private:
	bool _locked = false;
	uint8_t _base = 0;
	uint8_t _bank = 0;
	bool _mode = false;

protected:
	uint16_t GetPRGPageSize() override { return 0x4000; }
	uint16_t GetCHRPageSize() override { return 0x2000; }

	void InitMapper() override
	{
		SelectPRGPage(0, 0);
		SelectPRGPage(1, 7);
		SelectCHRPage(0, 0);
	}

	void Serialize(Serializer& s) override
	{
		BaseMapper::Serialize(s);
		SV(_locked);
		SV(_base);
		SV(_bank);
		SV(_mode);
	}

	void WriteRegister(uint16_t addr, uint8_t value) override
	{
		if(!_locked) {
			_base = ((addr & 0x60) >> 2) | ((addr & 0x100) >> 3);
			_mode = (addr & 0x80) == 0x80;
			_locked = (addr & 0x2000) == 0x2000;
			
			SetMirroringType(addr & 0x02 ? MirroringType::Horizontal : MirroringType::Vertical);
		}

		_bank = value & 0x07;

		SelectPRGPage(0, _base | _bank);
		SelectPRGPage(1, _base | (_mode ? _bank : 7));
	}
};