require('Support.Constants')

function GemMiner(prices)

	haFilterLevel(60)
	haFilterRarity('All')
	haFilterBuyout(2000000)

	-- for each item type
	for i, itype in ipairs(ITEM_TYPES) do

		haFilterType(itype)

		-- if item type has sockets
		if haFilterStat(1, 'has sockets', 1) then

			-- if search successful
			if haActionSearch() then

				-- toggle buyout column to sort in increasing order
				haActionSortBuyout()

				-- for each search item in search list
				while haListNext() do
					local total_value = 0
					local dps, bid, buyout, nstats, nsockets = haListItem()

					-- calculate total gem value of item
					for j = 1, nsockets do
						local stat, gtype, rank, value = haListItemSocket(j)
						if rank > 0 then
							total_value = total_value + prices[rank]
						end
					end

					-- buy item if total gem value is more than twice buyout
					if buyout > 0 and total_value > (buyout * 2) then
						haActionBuyout()
					end
				end
			end
		end
	end

end
