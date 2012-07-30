function SnipeBuyout()

	-- get user buyout
	local buyout = haFilterBuyout()

	-- check input
	if buyout == 0 then
		haAlert('Set buyout!')
	else
		while true do

			-- update buyout with randomize
			haFilterBuyout(buyout, true)

			-- search
			if haActionSearch() then

				-- select first item in list
				haListSelect(1)

				-- buyout
				haActionBuyout()
			else
				-- if no results sleep 1 second
				haSleep(1000)
			end
		end
	end
end
