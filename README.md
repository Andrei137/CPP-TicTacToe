My first personal project. It involves a game of Tic-Tac-Toe written in C++ for my Informatics certificate. 

There are two gamemodes : PvE si PvP. 

PvE has two difficulties, a normal one and an impossible one, and a random generator for turns. In the normal one, the AI places his symbol randomly, but it can identify win or lose situations and place accordingly. In the impossible difficulty, the AI is written so that it punish every mistake and, even in a perfectly played game, the player can never win.

PvP obviously involves a gamemode where a player plays against another one. 

The program is done so that one can't type anything besides the right inputs, it remembers the score as long as the same player tries to challenge the same enemy, be it AI or another player (win - 1 point, tie - 0.5 points). At the end of every match, one can select to replay the match (the PvP has an additional option of switching the turns, as PvE does it randomly), select another player, difficutly and, lastly, gameplay.
