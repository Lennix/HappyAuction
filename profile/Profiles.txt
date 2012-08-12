--[[
	DISCLAIMER:
	This file was automatically created by HAA Profile Creator. It may not be compatible with HA.
	Please do not change this file unless you know what you're doing.
]]--
while 1 do
	-- Profile Barb
	haSettingsQueriesPerHour('800')
	haFilterChar('Barbarian')
	haFilterType('Shoulders')
	haFilterRarity('Rare')
	haFilterLevel(1,60)
	haFilterBuyout(2000000, false)
	haFilterUnique('')
	haFilterStat(1, 'Strength', 100)
	haFilterStat(2, 'Vitality', 100)
	haFilterStat(3, 'All Resistance', 40)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, max_bid, buyout, nstats, nsockets, current_bid, id, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' max bid: ' .. max_bid .. ' buyout: ' .. buyout .. ' current bid: ' .. current_bid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Strength" and value1 >= 100 then found = found + 1 end
				if stat == "Vitality" and value1 >= 100 then found = found + 1 end
				if stat == "All Resistance" and value1 >= 40 then found = found + 1 end
			end
			if found == 3 and flags == 102 then haLog('Found match!') end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
	
	-- Profile Dem
	haSettingsQueriesPerHour('800')
	haFilterChar('Demon Hunter')
	haFilterType('Hand Crossbow')
	haFilterRarity('All')
	haFilterLevel(1,60)
	haFilterBuyout(10000000, false)
	haFilterUnique('')
	haFilterStat(1, 'Dexterity', 100)
	haFilterStat(2, 'Critical Hit Damage', 100)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, max_bid, buyout, nstats, nsockets, current_bid, id, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' max bid: ' .. max_bid .. ' buyout: ' .. buyout .. ' current bid: ' .. current_bid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Dexterity" and value1 >= 100 then found = found + 1 end
				if stat == "Critical Hit Damage" and value1 >= 100 then found = found + 1 end
			end
			if dpsarmor > 1000 then found = found + 1 end
			if found == 3 and flags == 102 then haLog('Found match!') end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
	
	-- Profile Wiz
	haSettingsQueriesPerHour('800')
	haFilterChar('Wizard')
	haFilterType('Wizard Hat')
	haFilterRarity('Legendary')
	haFilterLevel(1,60)
	haFilterBuyout(4000000, false)
	haFilterUnique('')
	haFilterStat(1, 'Intelligence', 75)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, max_bid, buyout, nstats, nsockets, current_bid, id, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' max bid: ' .. max_bid .. ' buyout: ' .. buyout .. ' current bid: ' .. current_bid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Intelligence" and value1 >= 75 then found = found + 1 end
			end
			if found == 1 and flags == 102 then haLog('Found match!') end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
	
	-- Profile WD
	haSettingsQueriesPerHour('800')
	haFilterChar('Witch Doctor')
	haFilterType('Amulet')
	haFilterRarity('All')
	haFilterLevel(1,60)
	haFilterBuyout(-1)
	haFilterUnique('')
	haFilterStat(1, 'Intelligence', 200)
	haFilterStat(2, 'Critical Hit Chance', 4)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, max_bid, buyout, nstats, nsockets, current_bid, id, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' max bid: ' .. max_bid .. ' buyout: ' .. buyout .. ' current bid: ' .. current_bid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Intelligence" and value1 >= 200 then found = found + 1 end
				if stat == "Critical Hit Chance" and value1 >= 4 then found = found + 1 end
			end
			if haParseTime(timeleft) >= haParseTime('1d 10h') then found = found + 1 end
			if found == 3 and flags == 102 then haLog('Found match!') end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
	
	-- Profile Monk
	haSettingsQueriesPerHour('800')
	haFilterChar('Monk')
	haFilterType('Spirit Stone')
	haFilterRarity('All')
	haFilterLevel(1,60)
	haFilterBuyout(4000000, false)
	haFilterUnique('')
	haFilterStat(1, 'Has Socket', 1)
	haFilterStat(2, 'Dexterity', 150)
	haFilterStat(3, 'Vitality', 150)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, max_bid, buyout, nstats, nsockets, current_bid, id, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' max bid: ' .. max_bid .. ' buyout: ' .. buyout .. ' current bid: ' .. current_bid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Dexterity" and value1 >= 150 then found = found + 1 end
				if stat == "Vitality" and value1 >= 150 then found = found + 1 end
			end
			if found == 2 and flags == 102 then haLog('Found match!') end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
end
