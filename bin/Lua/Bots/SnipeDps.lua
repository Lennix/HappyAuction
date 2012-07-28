function SnipeDps(dps, buyout)
	while true do
		haFilterBuyout(buyout, true)
		if haActionSearch() then
			haListSelect(1)
			local idps = haListItem()
			if idps > dps then
				haActionBuyout()
			end
		end
	end
end
