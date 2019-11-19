# top-trumps
## Or, "Have you read K&R properly?"
Just testing that I can actually write some C...
And use git...

## Useful lessons
Plan, plan, plan. Round two when I'd gone into some detail about what functions I might need was so much easier than making them up as I went along. 
Organise functions hierarchically, so that you have some low-level ones for e.g making structures, and higher-level ones that just call those.
Make your functions as agnostic as possible. A previous memory allocation function set a block of memory, and later functions divied up that memory with that foreknowlege. It was hard to get the maths right, and required a lot of thought. Dealing with things item-by-item is much better.