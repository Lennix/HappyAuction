--[[
	DISCLAIMER:
	This file was automatically created by HAA Profile Creator. It may not be compatible with HA.
	Please do not change this file unless you know what you're doing.
]]--
while 1 do
	haFilterStat(1, 'None', 0)
	haFilterStat(2, 'None', 0)
	haFilterStat(3, 'None', 0)
	-- Profile DH 158Dex 50Vit
	haFilterClass('Demon Hunter')
	haFilterType('Pants')
	haFilterRarity('All')
	haFilterBuyout(1200000, false)
	haFilterStat(1, 'Has Sockets', 2)
	haFilterStat(2, 'Dexterity', 158)
	haFilterStat(3, 'Vitality', 50)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, bid, buyout, nstats, nsockets, id, currBid, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Dexterity" and value1 >= 158 then found = found + 1 end
				if stat == "Vitality" and value1 >= 50 then found = found + 1 end
			end
			if dpsarmor > 1 then found = found + 1 end
			if ilvl > 1 then found = found + 1 end
			if found == 4 and flags == 102 then
				if buyout <= 1200000 then
					haLog('Buying item')
					haActionBuyout()
				end
			end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
	haFilterStat(1, 'None', 0)
	haFilterStat(2, 'None', 0)
	haFilterStat(3, 'None', 0)
	
	-- Profile DH 158Dex 100Vit
	if haGetGold() > 30000000 then
		haFilterClass('Demon Hunter')
		haFilterType('Pants')
		haFilterRarity('All')
		haFilterBuyout(2000000, false)
		haFilterStat(1, 'Has Sockets', 2)
		haFilterStat(2, 'Dexterity', 158)
		haFilterStat(3, 'Vitality', 100)
		if haActionSearch() then
			while haListNext() do
				local dpsarmor, bid, buyout, nstats, nsockets, id, currBid, flags, ilvl, timeleft, name = haListItem()
				haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
				local found = 0
				for i = 1, nstats do
					local stat, value1 = haListItemStat(i)
					haLog('STAT:' .. stat .. ' VALUE:' .. value1)
					if stat == "Dexterity" and value1 >= 158 then found = found + 1 end
					if stat == "Vitality" and value1 >= 100 then found = found + 1 end
				end
				if dpsarmor > 1 then found = found + 1 end
				if ilvl > 1 then found = found + 1 end
				if found == 4 and flags == 102 then
					if buyout <= 2000000 then
						haLog('Buying item')
						haActionBuyout()
					end
				end
				for i = 1, nsockets do
					local stat, gtype, rank, value1 = haListItemSocket(i)
					haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
				end
			end
		end
	end
	haFilterStat(1, 'None', 0)
	haFilterStat(2, 'None', 0)
	haFilterStat(3, 'None', 0)
	
	-- Profile WIZ 158INT 100VIT
	haFilterClass('Wizard')
	haFilterType('Pants')
	haFilterRarity('All')
	haFilterBuyout(1800000, false)
	haFilterStat(1, 'Has Sockets', 2)
	haFilterStat(2, 'Intelligence', 158)
	haFilterStat(3, 'Vitality', 100)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, bid, buyout, nstats, nsockets, id, currBid, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Intelligence" and value1 >= 158 then found = found + 1 end
				if stat == "Vitality" and value1 >= 100 then found = found + 1 end
			end
			if dpsarmor > 1 then found = found + 1 end
			if ilvl > 1 then found = found + 1 end
			if found == 4 and flags == 102 then
				if buyout <= 1800000 then
					haLog('Buying item')
					haActionBuyout()
				end
			end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
	haFilterStat(1, 'None', 0)
	haFilterStat(2, 'None', 0)
	haFilterStat(3, 'None', 0)
	
	-- Profile WIZ 158INT 50VIT
	haFilterClass('Wizard')
	haFilterType('Pants')
	haFilterRarity('All')
	haFilterBuyout(800000, false)
	haFilterStat(1, 'Has Sockets', 2)
	haFilterStat(2, 'Intelligence', 158)
	haFilterStat(3, 'Vitality', 50)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, bid, buyout, nstats, nsockets, id, currBid, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Intelligence" and value1 >= 158 then found = found + 1 end
				if stat == "Vitality" and value1 >= 50 then found = found + 1 end
			end
			if dpsarmor > 1 then found = found + 1 end
			if ilvl > 1 then found = found + 1 end
			if found == 4 and flags == 102 then
				if buyout <= 800000 then
					haLog('Buying item')
					haActionBuyout()
				end
			end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
	haFilterStat(1, 'None', 0)
	haFilterStat(2, 'None', 0)
	haFilterStat(3, 'None', 0)
	
	-- Profile BARB 128ST 50AR 50VIT
	haFilterClass('Barbarian')
	haFilterType('Pants')
	haFilterRarity('All')
	haFilterBuyout(2000000, false)
	haFilterStat(1, 'Has Sockets', 2)
	haFilterStat(2, 'Strength', 128)
	haFilterStat(3, 'All Resistance', 50)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, bid, buyout, nstats, nsockets, id, currBid, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Strength" and value1 >= 128 then found = found + 1 end
				if stat == "All Resistance" and value1 >= 50 then found = found + 1 end
				if stat == "Vitality" and value1 >= 50 then found = found + 1 end
			end
			if dpsarmor > 1 then found = found + 1 end
			if ilvl > 1 then found = found + 1 end
			if found == 5 and flags == 102 then
				if buyout <= 2000000 then
					haLog('Buying item')
					haActionBuyout()
				end
			end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
end
