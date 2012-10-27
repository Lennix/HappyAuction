HappyAuction v0.9.28

DESCRIPTION
------------------------------------------------------------------------------
HappyAuction is a C++ open source LUA scripted Diablo 3 auction house bot.
Major features supported:

- LUA functions exposing key AH operations
- Works with D3 window in background (see NOTES)
- Several sample bots included
- Multiple client support
- Multiple language support (english, russian, chinese)

Happy botting! :D


INSTRUCTIONS
------------------------------------------------------------------------------
1. Run bin/HappyAuction.exe
2. In Diablo 3 visit the auction house
3. Hit CTRL-F12 to start/stop the main script (SnipeBuyout bot by default).
   The taskbar icon will change color while script is active.
4. Edit bin/Lua/Main.lua to enable other sample scripts.


INCLUDED BOTS
------------------------------------------------------------------------------
- SnipeBuyout:  Traditional buyout bot that will buyout loop first item.
- SnipeDps:     Will buyout loop first item if when desired DPS.
- LogResults:   Sets filters and scans all results logging all items to a file
- LogStash:     Logs all items in your stash. Includes item sell example.
- BestMojo:     Finds the highest damage mojo.
- GemMiner:     More complex and useful bot that scans multiple searches for
                cheap listings with expensive gems.


NOTES
------------------------------------------------------------------------------
- The PAUSE key will pause/unpause a script. See HOTKEYS section to change.
- HappyAuction can run with D3 in the background (not minimized) IF you start
  a script with D3 already in the background. The only exception is if you
  use haStash* functions which always require D3 in foreground.
- Interacting with D3 while a script is running is not supported and can 
  cause unintended script operation.
- There will be a brief 2-3 second delay before running a script the first
  time. This is necessary to run a memory scan of Diablo 3 to detect
  everything HappyAuction needs to operate.
- Beyond network latency performance depends on your FPS. Disabling vertical
  sync should also help.
- Do not use Video/Letterbox option.


HOTKEYS
------------------------------------------------------------------------------
- Hotkeys and PauseKeys are configured using bin/Settings.cfg.
    - This file is generated the first time you run HA
- The hotkey format is MOD.KEY or KEY. Examples:
    HotKey1=C.F12       first instance hotkey set to CONTROL-F12
    HotKey2=F11         second instance hotkey set to F11
    HotKey3=CS.NUM0     third instance hotkey set to CONTROL-SHIFT-NUMPAD0
- Supported Modifiers:  A:ALT, C:CONTROL, S:SHIFT, W:WINDOWSKEY
- Supported Keys:       0-9, A-Z, F1-F12, NUM0-NUM9, PAUSE
- HappyAuction must be restarted (right click taskbar icon) to update hotkeys


MULTIPLE CLIENTS (tutorial)
------------------------------------------------------------------------------
1. Edit settings.cfg and add a new hotkey for the 2nd D3 client (see HOTKEYS)
2. Have 2 D3 clients running with both at the auction house
3. Hit the configured hotkeys like you originally would a single one. They
   will each run bin/Main.lua independently for each D3 instance.
4. The taskbar icon should contain a "2" indicating two sessions are running.
5. Use haGetInstance() or haGetAccount() to distinguish clients. The
   following example will run Bot1 in user1@gmail.com's client and Bot2 in
   user2@gmail.com's client:

   if haGetAccount() == 'user1@gmail.com' then
       require('Bots.Bot1')
   elseif haGetAccount() == 'user2@gmail.com' then
       require('Bots.Bot2')
   end


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
  haSetLogin to enable automatic relogin.
- Always test new scripts without haBuyout or haBid to avoid losing gold. I
  use haAlert in their place to show a popup when a buy/bid would occur.
- Use haSetGlobalDelay() to slow everything down (fastest by default!)
- If functions are ever deprecated they will remain available for several
  updates before being removed permanently.
- If using unicode text save your script file in UTF8 format (most text
  editors should support this)


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
    - max:      maximum level. -1 to clear.
    - status:   true if successful

- haFilterPrimary(id) -> status
    Sets item primary filter. For automatic method see haFilterType.
    - id:       substring identifier of primary type. example: 'Off-Hand'
    - status:   true if successful

- haFilterRarity(id) -> status
    Sets item rarity filter.
    - id:       substring identifier of rarity. example: 'rare'
    - status:   true if successful

- haFilterSecondary(id) -> status
    Sets item secondary filter. For automatic method see haFilterType.
    - id:       substring identifier of secondary type. example: 'Quiver'
    - status:   true if successful

- haFilterStat(index, id, value) -> status
  haFilterStat(index) -> status
    Sets item preferred stat and minimum value filter. Not specifying and id
    and value will reset this filter to None.
    - index: specify which of the 3 stat filters to use. range: 1-3
    - id:       substring identifier of type. nil to clear.
                example: 'level req' will match 'Reduced Level Requirement'
    - value:    minimum value for this filter. range: 0-999. -1 to clear.
    - status:   true if successful

- haFilterStatClear() -> status
    The equivalent of calling haFilterStat(index, 'None', 0) for each preferred
    stat.
    - status:   true if successful

- haFilterType(id) -> status
    Sets secondary item filter. Unlike haFilterSecondary this will
    automatically change any dependencies. Example:
        haFilterType('Wand')
    will also set character to 'Wizard' and primary to '1-Hand'.
    NOTE: Will only work with English locale
    - id:       substring identifier of secondary item type.
                example: 'voodoo' will match 'Voodoo Mask'
    - status:   true if successful

- haFilterUnique(name, row) -> status
- haFilterUnique(name) -> status
- haFilterUnique() -> name
    Sets or gets legendary or set item filter.
    - name:     string idenfiying a legendary or set item. '' to clear.
    - row:      optional row number of popup to click. range: 1-5
    - status:   true if successful

- haListIterate() -> status
    Iterates through the entire search results list selecting every item
    until it reaches the last item of the last page.
    example:
        -- will buyout every item found
        while haListIterate() do
            haBuyout()
        end
    - status:   true if successful

- haListAt() -> [row, page]
    Returns current list position
    - row:      current list row.
    - page:     current list page.

- haListSelect(index) -> status
    Selects the current item given a row index from search results.
    - index:    index of item to select. range: 1-11
    - status:   true if successful

- haSearch() -> status
    Hits the search button.
    - status:   true if successful

- haSortBuyout() -> status
    Toggles "Buyout" column sorting order
    - status:   true if successful

- haSortDpsArmor() -> status
    Toggles "DPS" or "Armor" column sorting order
    - status:   true if successful

- haSortTimeLeft() -> status
    Toggles "Time Left" column sorting order
    - status:   true if successful


AUCTION/SELL:
- haSell(starting, buyout) -> status
    Sells currently selected stash item for the given starting and optional
    buyout price. Typical reason for failure due to auction limit reached.
    - starting: starting price
    - buyout:   optional buyout price
    - status:   true if successful.

- haSellCancel() -> status
    Cancels the last auction selected by haSellIterate().
    - status:   true if successful.

- haSellIterate()
    Iterates through each of your selling auctions (auctions tab).
    example:
        -- will cancel all auctions expiring in less than 12 hours.
        while haSellIterate() do
            if haItem().rtime < (12 * 60 * 60 * 1000) then
                haSellCancel()
            end
        end
    - status:   true if more remaining.

- haStashAt() -> [column, row, bag]
    Returns current stash position
    - column:   current stash column.
    - row:      current stash row.
    - bag:      current stash bag.

- haStashIterate() -> status
    Iterates through each slot of each bag in sell/stash. Assumes user owns
    all bags but will work regardless.
    example:
        -- will sell every stash item with over 20 intelligence for 1000/2000g
        while haStashIterate() do
            if haItemStat('Intelligence').value1 > 20 then
                haSell(1000, 2000)
            end
        end
    NOTE: D3 window must be in the foreground to use this function.
    - status:   true if successful

- haStashSelect(column, row, bag) -> status
    Selects the current stash item given a column, row, and bag index. This is
    a manual alternative to haStashIterate() which also affects current stash
    position. For example haStashSelect(1,1,2) will cause haStashIterate() to
    begin at bag 2.
    NOTE: D3 window must be in the foreground to use this function.
    - column:   column index of stash item to select. range: 1-7
    - row:      row index of stash item to select. range: 1-10
    - bag:      bag index of stash item to select. range: 1-3
    - status:   true if successful


AUCTION/COMPLETED:
- haSendToStash() -> status
    Sends completed items to stash. Fails if nothing to send. example:
        while haSendToStash() do end
    will send every completed item to stash.
    NOTE: this function will NOT fail if your stash is full.
    - status:   true if successful.


ITEM:
- haItem() -> item
    Returns information about the last selected item. Values will be 0 if no
    item is selected. Some values may be 0 if not in the right context such
    as buyout on an item in your stash (if using haStash functions).
    - item.name:    item name
    - item.id:      a unique id for this auction
    - item.ilevel:  item level
    - item.rarity:  item rarity. legendaries will be 'set' or 'legendary'
    - item.type:    item type. example: 'Helm'
    - item.dps:     DPS (damage per second derp)
    - item.armor:   armor
    - item.cblock:  shield block chance
    - item.mblock:  shield block min
    - item.xblock:  shield block max
    - item.aps:     attacks per second
    - item.mdamage: min weapon damage
    - item.xdamage: max weapon damage
    - item.cbid:    the current bid price as shown in item list. this will be
                    less than mbid if there are bidders, otherwise equal.
    - item.mbid:    the max bid price as shown in bid button/input box.
    - item.buyout:  the buyout price or 0 if there is no buyout
    - item.rtime:   auction remaining time in milliseconds.
    - item.xtime:   auction expire time in UTC seconds.
    - item.stats:   a list of stat objects containing:
        - text:     stripped stat text from tooltip. example:
                        if tooltip is:      '+295 Minimum Damage'
                        stat.text will be:  'Minimum Damage'
        - value1-4: stat values. for most stats only value1 will be used.
    - item.sockets: a list of socket objects containing:
        - text:     gem stat text. example: 'Dexterity'
        - gem:      gem type. example: 'Topaz'
        - rank:     gem rank. example: 14 for Radiant Star
        - value1-4: stat values. for most stats only value1 will be used.

- haItemStat(pattern) -> stat
- haItemStat(pattern, substring) -> stat
    Convenience function for looking up an item stat quickly. Item stat text
    searched is from item tooltip. This will always return a stat object and
    will contain 0 values if the matched stat is not found.
        if haItemStat('dexterity').value1 > 200 then
            -- item has stat with over 200 dex
        end
    - pattern:       pattern to search stat text. matched from beginning.
    - substring:     do substring search instead of matching from beginning.
                     range: true/false.
    - stat.text:     stripped stat text from tooltip
    - stat.value1-4: stat values. for most stats only value1 will be used.


ETC:
- haGetAccount() -> account
    Returns the account name of the logged in account. Like haGetInstance()
    this is useful to identify the D3 client in a multiple client setup.
    - account:      active account name

- haGetGold() -> gold
    Returns your total gold balance.
    - gold:         gold balance.
    
- haGetInstance() -> instance
    Returns a client instance number to distinguish one client from another
    when running multiple D3 clients. The instance number will match the
    hotkey number found in bin/Settings.cfg.
    - instance:     Unique from 1 to 32.

- haLogout()
    Forces a logout. This will trigger haSetLogin() if it's enabled. Combining
    this with haSetLoginDelay() is a good way to have your bot "cool down"
    once in a while to reduce risk of detection... assuming input limit errors
    aren't forcing you to logout already.

- haSetGlobalDelay(delay)
    Adds a global delay to every future action taken. This includes delays
    not available to haSleep such as the individual actions taken by
    haBuyout. The actual delay will be a random amount between delay
    and 2*delay. Useful for slowing your script down to avoid input limit
    errors and being detected. Default value is 0.
    - delay:    delay in milliseconds. range: 0-60000

- haSetLogin(name, password)
    Enables automatic relogin. If a disconnect error occurs will attempt to
    relogin, restore state, and continue script. see example in Main.lua.
    Setting a delay is suggested to reduce detecion.
    - name:     account name
    - password: account password
    - delay:    optional login delay in milliseconds. default: 0

- haSetLoginDelay(delay)
    Adds a delay to the relogin sequence. Delay occurs at login screen before
    user/password is entered. Setting a delay is suggested to reduce detecion.
    - delay:    login delay in milliseconds. default: 0


UTILITIES:
- haAlert(message)
    Opens popup message with specified message. This halts the script and
    persists until user hits OK button.
    - message:  message string

- haBeep()
    Beep!

- haLog(message)
    Writes a message to the User#.log file where # is the instance number.
    If you are not using multiple clients this will be 1.
    - message:  message string

- haPrompt(message) -> status
    Like haAlert but with a YES/NO buttons.
    - message:  message string
    - status:   true if user hit YES button

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
