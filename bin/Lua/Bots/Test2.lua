while true do
   if haFilterType('Amulet') and
   haFilterRarity('All') and
   haFilterStat(1, 'Gold Find',  40) and
   haFilterBuyout(500000, true) and
   haActionSearch() then
      haListSelect(1)
      --haActionBuyout()
   end

   if haFilterType('Ring') and
   haFilterRarity('All') and
   haFilterStat(1, 'Gold Find',  20) and
   haFilterBuyout(250000, true) and
   haActionSearch() then
      haListSelect(1)
      --haActionBuyout()
   end
end
