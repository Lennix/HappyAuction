HappyAuction v0.9.9

DESCRIPTION
------------------------------------------------------------------------------
HappyAuction is a C++ open source LUA scriptable Diablo 3 auction house bot.
It offers full control over the AH. Some popular bot scripts are included.
Happy botting! :D


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
- LogStash:     Logs all items in your stash. Includes item sell example.
- BestMojo:     Finds the highest damage mojo.
- GemMiner:	    More complex bot that searches across multiple filters finding
                and buying cheap items with expensive gems.


NOTES
------------------------------------------------------------------------------
- HappyAuction can run with D3 in the background (not minimized) while you do
  other stuff. The only exception is if you use haStashSelect or haStashNext.
- There will be a brief 2-3 second delay before running a script the first
  time. This is necessary to run a memory scan of Diablo 3 to detect
  everything HappyAuction needs to operate.
- Performance depends on your FPS.
- Do not use Video/Letterbox option.
- HappyAuction has not been tested with RMAH but should work.


SECURITY
------------------------------------------------------------------------------
- HappyAuction uses the following "human like" methods to reduce detection:
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
- The following is recommended to reduce chance of ban:
    - Include additional delays with haSleep() and haSetGlobalDelay()
    - If you do not use delays don't run scripts too long
- Note that no matter which AH bot you use you WILL get banned IF you spam
  the AH 24/7. No bot, including HappyAuction, is 100% safe even if they're
  completely invisible to Diablo 3 client side. Use at your own risk.


SCRIPTING NOTES
------------------------------------------------------------------------------
- If you are new to LUA visit: http://www.lua.org/manual/5.2/ . There really
  isnt much to learn to operate this bot besides loops if statements and
  some basic operators.
- The main entry script is Lua/Main.lua.
- Always check function return status! Yes they can fail sometimes like when
  normal operation is interupted by some battle.net error. In which case use
  haReLogin to relogin.
- Use haSetGlobalDelay() to slow everything down (fastest by default!)
- If functions are ever deprecated they will remain available for several
  updates before being removed permanently.


SCRIPTING REFERENCE
------------------------------------------------------------------------------
AUCTION/SEARCH:
- haBid() -> status
- haBid(bid) -> status
    Bids on current item and sets an optional bid price.
    - bid:      your max bid price.
    - status:   true if successful

- haBuyout() -> status
    Buys out the current item. Use with caution!
    - status:   true if successful

- haFilterBuyout(amount) -> status
- haFilterBuyout(amount, randomize) -> status
- haFilterBuyout() -> amount
    Sets or gets the buyout amount filter. Randomize will pad your buyout with
    an additional 5% unique random value over your buyout to avoid cached
    searches. It's necessary to use this option when calling haSearch more
    than once per minute (unless Blizzard changes this) or you'll get old
    search results.
    - amount:       buyout amount. -1 to clear.
    - randomize:    if true adds small unique random value to amount.
    - status:       true if successful

- haFilterChar(id) -> status
    Sets character filter.
    - id:       substring identifier of secondary item type.
                example: 'doc' will match 'Witch Doctor'
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

- haFilterStatClear() -> status
    The equivalent of calling haFilterStat(index, 'None', 0) for each preferred
    stat.
    - status:   true if successful

- haFilterType(id) -> status
    Sets item filter. This will also take care of character and primary item
    types automatically. example:
    - id:       substring identifier of secondary item type.
                example: 'voodoo' will match 'Voodoo Mask'
    - status:   true if successful

- haFilterUnique(name) -> status
- haFilterUnique() -> name
    Sets or gets legendary or set item filter.
    - name:     string idenfiying a legendary or set item.
    - status:   true if successful

- haListNext() -> status
    Iterates through the entire search results list selecting every item
    until it reaches the last item of the last page.
    example:
        -- will buyout every item found
        while haListNext() do
            haBuyout()
        end
    - status:   true if successful

- haListSelect(index) -> status
    Selects the current item given a row index from search results.
    - index:    index of item to select. range: 1-11
    - status:   true if successful

- haSearch() -> status
    Hits the search button.
    - status:   true if successful

- haSortBuyout() -> status
    Toggles buyout column sorting order
    - status:   true if successful

- haSortDpsArmor() -> status
    Toggles DPS or Armor column sorting order
    - status:   true if successful


AUCTION/SELL:
- haSell(starting, buyout) -> status
    Sells currently selected stash item for the given starting and optional
    buyout price. Typical reason for failure due to auction limit reached.
    - starting: starting price
    - buyout:   optional buyout price
    - status:   true if successful.

- haStashNext() -> status
    Iterates through each slot of each bag in sell/stash. Assumes user owns
    all bags but will work regardless.
    example:
        -- will sell every stash item with over 20 intelligence for 1000/2000g
        while haStashNext() do
            if haItemStat('Intelligence').value1 > 20 then
                haSell(1000, 2000)
            end
        end
    NOTE: D3 window must be in the foreground to use this function.
    - status:   true if successful

- haStashSelect(column, row, bag) -> status
    Selects the current stash item given a column, row, and bag index. This is
    a manual alternative to haStashNext() which also affects current stash
    position. For example haStashSelect(1,1,2) will cause haStashNext() to
    begin at bag 2.
    NOTE: D3 window must be in the foreground to use this function.
    - column:   column index of item to select. range: 1-7
    - row:      row index of item to select. range: 1-10
    - bag:      bag index of item to select. range: 1-3
    - status:   true if successful


ITEM:
- haItem() -> item
    Returns information about the last selected item. Values will be 0 if no
    item is selected. Some values may be 0 if not in the right context such
    as buyout on an item in your stash (using haStash functions).
    - item.name:    item name
    - item.id:      a unique id for this auction
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
    - item.rtime:   auction remaining time in milliseconds.
    - item.xtime:   auction expire time in UTC seconds.

- haItemStat(stat) -> stat
    Convenience function for looking up an item stat quickly. Always returns
    a stat object. Will contain 0 values if not found. This allows example:
        if haItemStat('dexterity').value1 > 200 then
            -- i has item over 200 dex
        end
    to always succeed even if the item has no dexterity stat.
    - stat.name:     stat name. example: 'Attack Speed %'
    - stat.value1-4: stat values. for most stats only value1 will be used.


ETC:
- haReLogin(name, password) -> status
    If any disconnect errors exist returns to main login and attempts to log
    back in and back to the auction house to continue scripting as usual. If
    login fails will retry with 3 second delay.
    Call this each iteration in your main loop. If other operations are
    suddenly failing its a sign you've been disconnected at which point
    haReLogin will kick in. See working example in Bots/GemMiner.lua. Example:
    - name:     account name
    - password: account password
    - status:   true if successful relogin

- haSendToStash() -> status
    Sends completed items to stash. Fails if nothing to send. example:
        while haSendToStash() do end
    will send every completed item to stash.
    NOTE: this function will NOT fail if your stash is full.
    - status:   true if successful.


SETTINGS:
- haSetGlobalDelay(delay)
    Adds a global delay to every future action taken. This includes delays
    not available to haSleep such as the individual actions taken by
    haBuyout. The actual delay will be a random amount between delay
    and 2*delay. Useful for slowing your script down to avoid input limit
    errors and being detected. Default value is 0.
    - delay:    delay in milliseconds. range: 0-60000


UTILITIES:
- haAlert(message)
    Opens popup message with specified message.
    - message:  message string

- haBeep()
    Beep!

- haLog(message)
    Writes a message to the User.log file
    - message:  message string

- haSleep(delay)
- haSleep(low, high)
    Delays execution for the specified time.
    - delay:    delay in milliseconds
    - low:      random delay minimum.
    - high:     random delay maximum.

- haUpTime() -> time
    Get current system uptime.
    - time:     time in milliseconds


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

SOURCE NOTES
------------------------------------------------------------------------------
- The primary code is split among the following files/classes:
    - HappyAuction/Core/Script:
        LUA to C++ adapter layer
    - Diablo3/Core/Game:
        Common game methods independent of specific area of D3
    - Diablo3/Core/AuctionInterface: 
        Auction house specific methods
    - Diablo3/Core/Trainer:
        All D3 process interaction and memory discovery. This is the file to
        update after a patch.
