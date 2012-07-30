function SnipeDps()

	-- get user buyout
	local buyout = haFilterBuyout()

	-- get user DPS from "Legendary or Set Item" input
	local dps = tonumber(haFilterUnique()) or 0

	-- check input
	if buyout == 0 then
		haAlert('Set buyout!')
	elseif dps == 0 then
		haAlert('Set minimum DPS!\nuse "Legendary or Set Item" input')
	else

		-- clear unique input so search can work
		haFilterUnique('')

		while true do

			-- update buyout with randomize
			haFilterBuyout(buyout, true)

			-- search
			if haActionSearch() then

				-- select first item in list
				haListSelect(1)

				-- get item dps
				local idps = haListItem()

				-- if item dps higher than requested dps buy!
				if idps > dps then
					haActionBuyout()
				end
			end

			-- sleep between 1 and 3 seconds (random)
			haSleep(1000, 3000)
		end
	end
end
