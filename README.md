# malloc(memory);

You are trying to manage computer memory
The computer is managing power for the city, if the computer fails the job
by being too slow then the computer will shut off due to lack of power and game over

The memory is a container that holds data in any pattern the player desires
Data can come in any size but will always be in this shape -------------
When a piece of data is spawned, it is held in a temporary buffer
The player can break up the data however they want but the more distance there is between data it will be slower to retrieve
The player can also move data around at anytime
Robots come and collect data to use
Robots can collide with each other and data when grabbing memory but they will be significantly slower when colliding
After a while, the data is no longer used and becomes garbage
It is up to the player to free that garbage to make space for more data

You have a limited amount of memory and are trying to fit the most important data
There is a level of importantness from 0 to 100
To fulfil the data, the robot must be able to collect the data within an amount of time proportional to the importantness
If the data has been freed or is still in the temporary buffer, the robot cannot fulfil the data request and fulfilment will fail
If the data is not fulfilled, the glitch counter will increase depending on the importantness

Glitching occurs when the glitch counter is not 0
Depending on the glitch counter, some data might be randomly moved
How much it moves and how often it moves and how much data is moved depends on the glitch counter
However data cannot be deleted