# Description

simple persistant key-value store implemented in C

list of supported commands:
- *put*: The format is `p,key,value`, where `key` is an integer, and
`value` an arbitrary string (without commas in it).
- *get*: The format is `g,key`, where `key` is an integer. If the key
is present, the system should print out the key, followed by a comma,
followed by the value.
- *delete*: The format is `d,key`, which deletes the relevant
key-value pair
- *clear*: The format is `c`. This command simply removes all
key-value pairs from the database.
- *all*: The format is `a`. This command prints out all key-value
pairs in the database.

