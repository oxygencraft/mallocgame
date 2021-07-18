# malloc(memory);

itch.io page: https://oxygencraft.itch.io/mallocmemory

You are a memory allocator trying to manage the memory of a computer that is managing the power grid.
If the computer fails the job by being too slow then the computer will shut off due to lack of power and game over.

The memory is a container that holds data in any pattern the player desires.
Data can come in any size but will always be in this shape -------------.
When a piece of data is spawned (allocated), it is held in a temporary buffer.
The player can break up the data however they want, but the more distance there is between data it will be slower to retrieve.
The player can also move data around at anytime.

Robots come and collect data for the computer to use.
Robots can collide with data (but not each other) when grabbing memory however they will be significantly slower when colliding with data.
This makes managing your memory layout and space important.
After a while, the data is no longer used and becomes garbage.
It is up to the player to free that garbage to make space for more data.

You must fulfil all data allocations, however you have a limited amount of memory and must fulfil the most important data.
There is a level of importance from 0 to 100 which is randomly generated. Depending on the importance, the tiles will be a different color.
To fulfil the data, the robot must be able to collect the data within an amount of time proportional to the importance.
If the data has been freed or is still in the temporary buffer, the robot cannot fulfil the data allocation and fulfilment will fail.
If the data is not fulfilled, the instability counter will increase depending on the importance of the data.
The allocation request will be deleted and will slightly increase the chances of more data of critical importance spawning.

Instability occurs when the instability counter is above 0.
Depending on the instability counter, some data might be randomly moved. There can also be some visual artifacts depending on the glitch counter.
How much it moves and how often it moves and how much data is moved depends on the instability counter.
However data cannot be deleted. You can reduce instability by successfully fulfilling data allocations.