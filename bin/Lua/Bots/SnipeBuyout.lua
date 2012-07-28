function SnipeBuyout(buyout)
	while true do
		haFilterBuyout(buyout, true)
		if haActionSearch() then
			haListSelect(1)
			haActionBuyout()
		else
			haSleep(1000)
		end
	end
end
