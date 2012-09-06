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
			local item = haItem()
			haLog('ID: ' .. item.id .. ' DPS/Armor: ' .. item.dps .. ' max bid: ' .. item.max_bid .. ' buyout: ' .. item.buyout .. ' current bid: ' .. item.current_bid .. ' flags: ' .. item.flags .. ' ilvl: ' .. item.ilvl .. ' timeleft: ' .. item.timeleft .. ' name: ' .. item.name .. ' type: ' .. item.type)
			local found = 0
			local value = 0
			value = haItemStat('Strength')
			if value.value1 >= 100 then found = found + 1 end
			value = haItemStat('Vitality')
			if value.value1 >= 100 then found = found + 1 end
			value = haItemStat('All Resistance')
			if value.value1 >= 40 then found = found + 1 end
			for i, stat in pairs(item.stats) do
				haLog('STAT:   ' .. stat.name .. '=' .. stat.value1)
			end
			for i, socket in pairs(item.sockets) do
				haLog('SOCKET: ' .. socket.gem .. '=' .. socket.rank)
			end
			if string.find(item.type, 'Shoulders') > 0 then found = found + 1 end
			if found == 4 and item.flags == 102 then haLog('Found match!') end
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
			local item = haItem()
			haLog('ID: ' .. item.id .. ' DPS/Armor: ' .. item.dps .. ' max bid: ' .. item.max_bid .. ' buyout: ' .. item.buyout .. ' current bid: ' .. item.current_bid .. ' flags: ' .. item.flags .. ' ilvl: ' .. item.ilvl .. ' timeleft: ' .. item.timeleft .. ' name: ' .. item.name .. ' type: ' .. item.type)
			local found = 0
			local value = 0
			value = haItemStat('Dexterity')
			if value.value1 >= 100 then found = found + 1 end
			value = haItemStat('Critical Hit Damage')
			if value.value1 >= 100 then found = found + 1 end
			for i, stat in pairs(item.stats) do
				haLog('STAT:   ' .. stat.name .. '=' .. stat.value1)
			end
			for i, socket in pairs(item.sockets) do
				haLog('SOCKET: ' .. socket.gem .. '=' .. socket.rank)
			end
			if item.dps > 1000 then found = found + 1 end
			if string.find(item.type, 'Hand Crossbow') > 0 then found = found + 1 end
			if found == 4 and item.flags == 102 then haLog('Found match!') end
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
			local item = haItem()
			haLog('ID: ' .. item.id .. ' DPS/Armor: ' .. item.dps .. ' max bid: ' .. item.max_bid .. ' buyout: ' .. item.buyout .. ' current bid: ' .. item.current_bid .. ' flags: ' .. item.flags .. ' ilvl: ' .. item.ilvl .. ' timeleft: ' .. item.timeleft .. ' name: ' .. item.name .. ' type: ' .. item.type)
			local found = 0
			local value = 0
			value = haItemStat('Intelligence')
			if value.value1 >= 75 then found = found + 1 end
			for i, stat in pairs(item.stats) do
				haLog('STAT:   ' .. stat.name .. '=' .. stat.value1)
			end
			for i, socket in pairs(item.sockets) do
				haLog('SOCKET: ' .. socket.gem .. '=' .. socket.rank)
			end
			if string.find(item.type, 'Wizard Hat') > 0 then found = found + 1 end
			if found == 2 and item.flags == 102 then haLog('Found match!') end
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
			local item = haItem()
			haLog('ID: ' .. item.id .. ' DPS/Armor: ' .. item.dps .. ' max bid: ' .. item.max_bid .. ' buyout: ' .. item.buyout .. ' current bid: ' .. item.current_bid .. ' flags: ' .. item.flags .. ' ilvl: ' .. item.ilvl .. ' timeleft: ' .. item.timeleft .. ' name: ' .. item.name .. ' type: ' .. item.type)
			local found = 0
			local value = 0
			value = haItemStat('Intelligence')
			if value.value1 >= 200 then found = found + 1 end
			value = haItemStat('Critical Hit Chance')
			if value.value1 >= 4 then found = found + 1 end
			for i, stat in pairs(item.stats) do
				haLog('STAT:   ' .. stat.name .. '=' .. stat.value1)
			end
			for i, socket in pairs(item.sockets) do
				haLog('SOCKET: ' .. socket.gem .. '=' .. socket.rank)
			end
			if haParseTime(item.timeleft) >= haParseTime('1d 10h') then found = found + 1 end
			if string.find(item.type, 'Amulet') > 0 then found = found + 1 end
			if found == 4 and item.flags == 102 then haLog('Found match!') end
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
			local item = haItem()
			haLog('ID: ' .. item.id .. ' DPS/Armor: ' .. item.dps .. ' max bid: ' .. item.max_bid .. ' buyout: ' .. item.buyout .. ' current bid: ' .. item.current_bid .. ' flags: ' .. item.flags .. ' ilvl: ' .. item.ilvl .. ' timeleft: ' .. item.timeleft .. ' name: ' .. item.name .. ' type: ' .. item.type)
			local found = 0
			local value = 0
			value = haItemStat('Dexterity')
			if value.value1 >= 150 then found = found + 1 end
			value = haItemStat('Vitality')
			if value.value1 >= 150 then found = found + 1 end
			for i, stat in pairs(item.stats) do
				haLog('STAT:   ' .. stat.name .. '=' .. stat.value1)
			end
			for i, socket in pairs(item.sockets) do
				haLog('SOCKET: ' .. socket.gem .. '=' .. socket.rank)
			end
			if string.find(item.type, 'Spirit Stone') > 0 then found = found + 1 end
			if found == 3 and item.flags == 102 then haLog('Found match!') end
		end
	end
end
