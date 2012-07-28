require('Bots.SnipeBuyout')
require('Bots.SnipeDps')
require('Bots.LogResults')
require('Bots.GemMiner')
--require('Bots.Test1')

--[[
	Simple traditional buyout bot that will buyout loop first item.
	Example is set to buyout at 200 gold + small random margin.
]]--
SnipeBuyout(200)


--[[
	Another simple bot that will buyout loop first item reaching desired DPS.
	Example is set to 50 DPS at 200 buyout. This does not set filters so set
	those manually first.
]]--
-- SnipeDps(50, 200)


--[[
	A slightly more complex bot that uses filters then simply logs all found
	items to User.log. The example searches all level 60 Rare Armor with at
	least 1	socket. To change these filters edit Bots/LogResults.lua.
]]--
-- LogResults()


--[[
	A more complex bot that searches and buys items if their total game value
	is twice their buyout price.

	The example bot searches socketed lvl60 items of each type individually.
	The buyout column is sorted in increasing order with a buyout of 2000000
	set to avoid bid only results.

	This bot can easily be improved to include all levels, additional stat
	filters, and specific rarities. Stats specified can also help narrow
	specific gem types to avoid empty or low rank gems. For example
	searching over 20% magic find on lvl60 helms will force only topaz
	results. An even more advanced bot would consider the value of the item.

	The input is a table specifying gem values per rank starting from
	rank 1 (chipped) to rank 14 (radiant star). The example is according to
	the AH prices at the time of me writing this. I consider ranks 1-7
	worthless so I set those to 0.
]]--

--[[
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

GemMiner(prices)
--]]--
