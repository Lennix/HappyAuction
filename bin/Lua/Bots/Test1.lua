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

-- set filters
haFilterType('Helm')
haFilterRarity('Rare')
haFilterStat(1, 'Has Sockets', 1)
haFilterStat(2, 'Magic Find',  20)

-- set buyout to avoid bid onlys
haFilterBuyout(2000000)

for level = 25, 60 do

	-- set level filter
	haFilterLevel(level)

	-- search
	if haActionSearch() then

		-- sort
		haActionSortBuyout()

		-- for every item
		while haListNext() do
			local total_value = 0
			local dps, bid, buyout, nstats, nsockets = haListItem()

			-- calculate total gem value
			for j = 1, nsockets do
				local stat, gtype, rank, value = haListItemSocket(j)
				if rank > 0 then
					total_value = total_value + prices[rank]
				end
			end

			-- buy if total value is over buyout times X
			if buyout > 0 and total_value > (buyout * 1.3) then
				haActionBuyout()
			end
		end
	end
end
