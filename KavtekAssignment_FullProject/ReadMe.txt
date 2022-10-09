Pong! - Ian Wang
UE Ver. 4.24.3
------------------------------------------------------------------------------------
Total work time: 16 hrs 
· 10hrs - implemented multiplayers & realtime database functions with C++  
· 4hrs - built UI with Blueprint 
· 2hrs - built Pong! gameplay with C++ & BP)
------------------------------------------------------------------------------------
Primary Features:
· No Plug-ins or Unreal Assets were used
· Multiplayer - listen server (not on LAN)
· Transfer/Read sessions & leaderboard data from Firebase realtime database
------------------------------------------------------------------------------------
Details:
· C++ Aspect
    -Have a function to collect a users ip address
    -Have a host game function. This will add the user's IP address and Lobby Name to a section in
    the firebase database.
    -Have a find game function. This will pull all hosted games.
    -Have a function that pushes the score, and names of users in a match to the firebase real-time
    database.
· Blueprint Aspect
    -UI That Collects the user's name.
    -UI that collects users hosted game name.
    -UI that displays all hosted games
    -UI that shows all past games
    -Refresh button to update hosted games
    -Refresh button to update leaderboard games
    -Test UI To Simulate a loser or winner of the game
· Gameplay Loop Hosted Session
    1. 1st User Hosts Session
    2. 1st User goes into waiting for game to start.
    3. 2nd User Joins
    4. Test UI To Push Winner and Loser Entries
    5. Send User to Main Menu
· Gameplay Loop Joined Session
    1. User Looks for Sessions
    2. User hits connect.
    3. Player To Enters a waiting screen.
    4. When Test UI has been submitted send back to main menu.
------------------------------------------------------------------------------------
Realtime database video demo → KavtekAssignment/KavTekAssignmentDemo  or   https://www.youtube.com/watch?v=B54pHLkNOaY
C++ Source Code → KavtekAssignment/Source
Most functions were implemented in → KavtekAssignment/Source/CPPGameInstance
------------------------------------------------------------------------------------
Important!
If you run the full project in Unreal Engine, it may not be able to access/transfer data from Firebase correctly because the folder doesn't include google-services.json file (which holds my Firebase account information)
