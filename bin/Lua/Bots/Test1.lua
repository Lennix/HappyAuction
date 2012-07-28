haActionSearch()
haActionSortBuyout()


local prices =
{
	0,0,0,0,0,0,0,
	120,		-- rank 8: flawless square
	37000,		-- rank 9: perfect square
	180000,		-- rank 10: radiant square
	600000,   	-- rank 11: star
	2000000,	-- rank 12: flawless star
	6000000,	-- rank 13: perfect star
	18000000,	-- rank 14: radiant star
}


haFilterType('Helm')
haFilterRarity('Magic')
haFilterStat(1, 'Has Sockets', 1)
haFilterBuyout(2000000)


for level = 20, 60 do

	haFilterLevel(level)
	haFilterStat(1, 'Magic Find', 20)

	if haActionSearch() then

		haActionSortBuyout()

		while haListNext() do
			local total_value = 0
			local dps, bid, buyout, nstats, nsockets = haListItem()

			for j = 1, nsockets do
				local stat, gtype, rank, value = haListItemSocket(j)
				if rank > 0 then
					total_value = total_value + prices[rank]
				end
			end

			if buyout > 0 and total_value > (buyout * 1.2) then
				haActionBuyout()
			end
		end
	end
end
