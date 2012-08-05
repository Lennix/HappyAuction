--[[
	DISCLAIMER:
	This file was automatically created by HAA Profile Creator. It may not be compatible with HA.
	Please do not change this file unless you know what you're doing.
]]--
while 1 do
	haFilterStat(1, 'None', 0)
	haFilterStat(2, 'None', 0)
	haFilterStat(3, 'None', 0)
		-- Profile TestProfil1
	haSettingsQueriesPerHour('800')
	haFilterClass('Barbarian')
	haFilterType('Pants')
	haFilterRarity('All')
	haFilterLevel(1,60)
	haFilterBuyout(2000000, false)
	haFilterUnique('')
	haFilterStat(1, 'Strength', 150)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, bid, buyout, nstats, nsockets, id, currBid, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Strength" and value1 >= 150 then found = found + 1 end
			end
			if haParseTime(timeleft) >= haParseTime('1d 10h') then found = found + 1 end
			if found == 2 and flags == 102 then haLog('Found match!') end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
	
  haFilterStat(1, 'None', 0)
	haFilterStat(2, 'None', 0)
	haFilterStat(3, 'None', 0)
	-- Profile Testprofil
	haSettingsQueriesPerHour('800')
	haFilterClass('Barbarian')
	haFilterType('Pants')
	haFilterRarity('All')
	haFilterLevel(1,60)
	haFilterBuyout(2000000, false)
	haFilterUnique('')
	haFilterStat(1, 'Strength', 150)
	if haActionSearch() then
		while haListNext() do
			local dpsarmor, bid, buyout, nstats, nsockets, id, currBid, flags, ilvl, timeleft, name = haListItem()
			haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)
			local found = 0
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
				if stat == "Strength" and value1 >= 150 then found = found + 1 end
			end
			if found == 1 and flags == 102 then haLog('Found match!') end
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end
		end
	end
end
