function LogResults()

	haFilterType('Pants')
	haFilterLevel(60)
	haFilterRarity('Rare')
	haFilterStat(1, 'Has Sockets', 2)
	haFilterStat(2, 'Dexterity', 200)
	haFilterStat(3, 'Vitality', 100)

	local found = 0

	-- if search successful
	if haActionSearch() then

		-- for each search item in search list
		while haListNext() do

			-- get item information
			local dps, bid, buyout, nstats, nsockets,id,currBid,flags,timeleft,name = haListItem()
			haLog('ID: ' .. id .. ' DPS: ' .. dps .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' timeleft: ' .. timeleft .. ' name: ' .. name)


			-- for each stat log stat information
			for i = 1, nstats do
				local stat, value1 = haListItemStat(i)
				haLog('STAT:' .. stat .. ' VALUE:' .. value1)
			end

			-- for each socket log socket information
			for i = 1, nsockets do
				local stat, gtype, rank, value1 = haListItemSocket(i)
				haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)
			end

			found = found + 1
			haLog(' ')
		end
	end

	haLog('TOTAL FOUND: ' .. found)
end
