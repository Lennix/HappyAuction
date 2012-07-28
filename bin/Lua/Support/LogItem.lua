function LogItem()

	haFilterType('All Armor')
	haFilterLevel(60)
	haFilterRarity('All')

	haActionSearch()

	while haListNext() do
		local dps, bid, buyout, nstats, nsockets = haListItem()
		haLog('DPS:' .. dps .. ' BID:' .. bid .. ' BUYOUT:' .. buyout)

		for i = 1, nstats do
			local stat, value1 = haListItemStat(i)
			haLog('STAT:' .. stat .. ' VALUE:' .. value1)
		end

		for i = 1, nsockets do
			local stat, rank, value1 = haListItemSocket(i)
			haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. rank)
		end

		haLog(' ')
	end

end
