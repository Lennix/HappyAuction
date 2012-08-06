HappyAuction v0.9.4

DESCRIPTION
------------------------------------------------------------------------------
HappyAuction is a C++ open source LUA scriptable Diablo 3 auction house bot.
It offers full control over the AH search/equipment section and possibly the
entire AH interface in the future. Some popular bot scripts are included.
Happy botting! :D


INSTRUCTIONS
------------------------------------------------------------------------------
1. Run bin/HappyAuction.exe
2. In Diablo 3 visit AuctionHouse/Search/Equipment.
3. Hit CTRL-F12 to start/stop the main script. The taskbar icon will change
   color while script is active.
4. The default sample script will run the basic buyout loop you see in other
   AH bots.
5. See bin/Lua/Main.lua for further details.


INCLUDED BOTS
------------------------------------------------------------------------------
- SnipeBuyout:  Traditional buyout bot that will buyout loop first item.
- SnipeDps:     Will buyout loop first item if when desired DPS.
- LogResults:	Sets filters and scans all results logging all items to a file
- GemMiner:	    More complex bot that searches across multiple filters finding
                and buying cheap items with expensive gems.


NOTES
------------------------------------------------------------------------------
- There will be a brief 2-3 second delay before running a script the first
  time. This is necessary to run a memory scan of Diablo 3 to detect
  everything HappyAuction needs to operate.
- Do not use Video/Letterbox option
- Performance depends on your FPS
- HappyAuction has not been tested with RMAH.
- Can operate while you do other things so long as the left filter side of
  the screen remains uncovered (if you are using a bot that uses filters).
  CTRL-F12 is a global hotkey that can be called any time.


SECURITY
------------------------------------------------------------------------------
- The following measures have been added to reduce detection:
    - Random delays between actions (simulated mouse clicks/keyboard keys)
    - Random buyout adjustments
    - Positioning of mouse clicks is randomized by a few pixels
    - Sent input is minimized. It's mostly mouse movement for a search scan.
- HappyAuction uses the following measures to interact with Diablo 3:
    - Win32 Messages: To send keyboard/mouse events
    - Read Process Memory: To determine item values such as DPS and armor
    - Write Process Memory: Yes it's safe because only text/data memory is
      altered, not instruction memory. It's used only to set the filter
      combobox values and clear item tooltip state.
- The following is recommended as additional security:
    - Include additional delays with haSleep()
- I am aware of other security measures and will be adding them in the future.
- There is no guarantee HappyAuction is 100% safe from detection. Use at your
  own risk.


KNOWN BUGS
------------------------------------------------------------------------------
- Focusing away from the D3 window may cause an active script to fail. Avoid
  by staying either focused on D3 or unfocsed (doing other stuff in windows).


SCRIPTING
------------------------------------------------------------------------------
- If you are new to LUA visit: http://www.lua.org/manual/5.2/ . There really
  isnt much to learn to operate this bot besides loops if statements and
  some basic operators.
- The main entry script is Lua/Main.lua.
- Always check function return status! Yes they can fail sometimes like when
  normal operation is interupted by some battle.net error.
- Use haSetGlobalDelay() to slow everything down (fastest by default!)

FUNCTIONS
The following are the available functions in addition to standard LUA stuff
arranged by category:

AUCTION FILTERS:
- haFilterType(id) -> status
    Sets item filter. This will also take care of character and primary item
    types automatically.
    - id:       substring identifier of secondary item type.
                example: 'voodoo' will match 'Voodoo Mask'
    - status:   true if successful

- haFilterLevel(min,  max) -> status
    Sets item level filter.
    - min:      minimum level. -1 to clear.
    - min:      maximum level. -1 to clear.
    - status:   true if successful

- haFilterRarity(id) -> status
    Sets item rarity filter.
    - id:       substring identifier of rarity. example: 'rare'
    - status:   true if successful

- haFilterStat(index, id, value) -> status
    Sets item preferred stat and minimum value filter.
    - index: specify which of the 3 stat filters to use. range: 1-3
    - id:       substring identifier of type.
                example: 'level req' will match 'Reduced Level Requirement'
    - value:    minimum value for this filter. range: 0-999
    - status:   true if successful

- haFilterBuyout(amount) -> status
- haFilterBuyout(amount, randomize) -> status
- haFilterBuyout() -> amount
    Sets or gets the buyout amount filter.
    - amount:       buyout amount. -1 to clear.
    - randomize:    if true adds a small random value to
                    amount to avoid cached search results and detection.
    - status:       true if successful

- haFilterUnique(name) -> status
- haFilterUnique() -> name
    Sets or gets legendary or set item filter.
    - name:     string idenfiying a legendary or set item.
    - status:   true if successful


AUCTION SEARCH LIST:
- haListSelect(index) -> status
    Selects the current item given a row index from search results.
    - index:    index of item to select. range: 1-11
    - status:   true if successful

- haListNext() -> status
    Iterates through the entire search results list selecting every item
    until it reaches the last item of the last page.
    example:
        -- will buyout every item found
        while haListNext() do
            haActionBuyout()
        end
    - status:   true if successful

- haListItem() -> dpsarmor, mbid, buyout, nstats, nsockets, cbid
    Returns information about the selected item. Values will be 0 if no
    item is selected or if failure occurred.
    - dpsarmor: the DPS or armor value found in tooltip.
    - mbid:     the max bid price as shown in bid button/input box.
    - buyout:   the buyout price or 0 if there is no buyout
    - nstats:   the number of stats
    - nsockets: the number of sockets
    - cbid:     the current bid price as shown in item list. this will be
                less than mbid if there are bidders otherwise equal.

- haListItemStat(index) -> stat, value1, value2, value3, value4
- haListItemStat(stat) -> value1, value2, value3, value4
    Gets individual stat information of the selected item. Loop with
    up to nstats to get all item stats or use the second form to quickly
    lookup stat values by name. returns 0 for every value if unsuccessful.
    - index:    the index of the stat to get. range: 1-nstats
    - stat:     the name of the stat. example: 'Attack Speed %'
    - value1-4: stat values. for most stats only value1 will be used.

- haListItemSocket(index) -> stat, type, rank, value1, value2, value3, value4
    Gets individual stat information of the selected socket. Loop with
    up to nsockets to get all socket stats.
    - index:    the index of the socket to get. range: 1-nsockets
    - stat:     the name of the stat. example: 'Intelligence'
    - type:     gem type: 'Amethyst','Emerald','Ruby', or 'Topaz'
    - rank:     gem rank up to radiant star. range: 1-14 or 0 if empty
    - value1-4: stat values. for most stats only value1 will be used.


AUCTION ACTIONS:
- haActionBid() -> status
- haActionBid(bid) -> status
    Bids on current item and sets an optional bid price.
    - bid:      your max bid price.
    - status:   true if successful

- haActionBuyout() -> status
    Buys out the current item. Use with caution!
    - status:   true if successful

- haActionSearch() -> status
    Hits the search button.
    - status:   true if successful

- haActionSortDpsArmor() -> status
    Toggles DPS or Armor column sorting order
    - status:   true if successful

- haActionSortBuyout() -> status
    Toggles buyout column sorting order
    - status:   true if successful

- haActionReLogin(name, password) -> status
    Clears any disconnect errors, logs back in, and into the AH. Intended for
    use with input limit errors to recover script operation. You will know
    to use this when other script operations begin to fail such as
    haActionSearch.
    - name:     account name
    - password: account password
    - status:   true if successful


UTILITIES:
- haLog(message)
    Writes a message to the User.log file
    - message:  message string

- haBeep()
    Beep!

- haSleep(delay)
- haSleep(low, high)
    Delays execution for the specified time.
    - delay:    delay in milliseconds
    - low:      random delay minimum.
    - high:     random delay maximum.

- haAlert(message)
    Opens popup message with specified message.
    - message:  message string


SETTINGS:
- haSetGlobalDelay(delay)
    Adds a global delay to every future action taken. This includes delays
    not available to haSleep such as the individual actions taken by
    haActionBuyout. The actual delay will be a random amount between delay
    and 2*delay. Useful for slowing your script down to avoid input limit
    errors and being detected. Default value is 0.
    - delay:    delay in milliseconds. range: 0-60000


SOURCE LICENSE
------------------------------------------------------------------------------
HappyAuction is under the strict "do whatever the fuck you want just dont
blame me" license. Break these rules and I'll sue your neckbeard off!


SOURCE DIRECTORIES
------------------------------------------------------------------------------
bin/        Build output and everything you'd find in the binary release.
build/      Project files. Open HappyAuction.sln with Visual Studio 2008 or
            higher then build/run.
docs/       Nothing useful here yet :)
source/     The source code! HappyAuction is a combination of 1 executable
            and 3 library packages. Ignore HappyMemory: It's temporary code to
            help me with stuff where Cheat Engine falls short.
