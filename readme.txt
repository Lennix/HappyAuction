HappyAuction v0.9.5

DESCRIPTION
------------------------------------------------------------------------------
HappyAuction is a C++ open source LUA scriptable Diablo 3 auction house bot.
It offers full control over the AH search/equipment and sell sections. Some
popular bot scripts are included. Happy botting! :D


INSTRUCTIONS
------------------------------------------------------------------------------
1. Run bin/HappyAuction.exe
2. In Diablo 3 visit the auction house
3. Hit CTRL-F12 to start/stop the main script. The taskbar icon will change
   color while script is active.
4. The default sample script will run the basic buyout loop you see in other
   AH bots.
5. See bin/Lua/Main.lua for further details.


INCLUDED BOTS
------------------------------------------------------------------------------
- SnipeBuyout:  Traditional buyout bot that will buyout loop first item.
- SnipeDps:     Will buyout loop first item if when desired DPS.
- LogResults:   Sets filters and scans all results logging all items to a file
- GemMiner:	    More complex bot that searches across multiple filters finding
                and buying cheap items with expensive gems.


NOTES
------------------------------------------------------------------------------
- There will be a brief 2-3 second delay before running a script the first
  time. This is necessary to run a memory scan of Diablo 3 to detect
  everything HappyAuction needs to operate.
- Do not use Video/Letterbox option
- Performance depends on your FPS
- HappyAuction has not been tested with RMAH but should work.


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
    - Include additional delays with haSleep() and haSetGlobalDelay()
- I am aware of other security measures and will be adding them in the future.
- There is no guarantee HappyAuction is 100% safe from detection. Use at your
  own risk.


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


SEARCH RESULTS LIST:
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


STASH
- haStashNext() -> status
    Iterates through each slot of each bag in sell/stash. Assumes user owns
    all bags but will work regardless.
    example:
        -- will sell every stash item with over 20 intelligence for 1000/2000g
        while haStashNext() do
            if haItemStat('Intelligence').value1 > 20 then
                haStashSell(1000, 2000)
            end
        end
    - status:   true if successful

- haStashSell(starting, buyout) -> status
    Sells currently selected stash item for the given starting and optional
    buyout price. Typical reason for failure due to auction limit reached.
    - starting: starting price
    - buyout:   optional buyout price
    - status:   true if successful.

ITEM INFORMATION
- haItem() -> item
    Returns information about the last selected item. Values will be 0 if no
    item is selected or if failure occurred.
    - item.dps:     the DPS or armor value found in tooltip.
    - item.mbid:    the max bid price as shown in bid button/input box.
    - item.cbid:    the current bid price as shown in item list. this will be
                    less than mbid if there are bidders, otherwise equal.
    - item.buyout:  the buyout price or 0 if there is no buyout
    - item.stats:   a list of stat objects containing:
        - name:     the name of the stat. example: 'Intelligence'
        - value1-4: stat values. for most stats only value1 will be used.
    - item.sockets: a list of socket objects containing:
        - name:     gem stat name. example: 'Dexterity'
        - gem:      gem name. example: 'Topaz'
        - rank:     gem rank. example: 14 for Radiant Star
        - value1-4: stat values. for most stats only value1 will be used.

- haItemStat(stat) -> stat
    Convenience function for looking up an item stat quickly. Always returns
    a stat object. Will contain 0 values if not found. This allows example:
        if haListItemStat('dexterity').value1 > 200 then
            -- i has item over 200 dex
        end
    to always succeed even if the item has no dexterity stat.
    - stat.name:     stat name. example: 'Attack Speed %'
    - stat.value1-4: stat values. for most stats only value1 will be used.


ACTIONS:
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
    If any disconnect errors exist returns to main login and attempts to log
    back in and back to the auction house to continue scripting as usual. If
    login fails will retry with 3 second delay.
    
    Call this each iteration in your main loop. If other operations are
    suddenly failing its a sign you've been disconnected at which point
    haActionReLogin will take over. See working example in GemMiner.

    - name:     account name
    - password: account password
    - status:   true if successful login or not disconnected


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
