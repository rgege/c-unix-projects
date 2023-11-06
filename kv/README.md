# Description

simple persistant key-value store implemented in C

list of supported commands:
- *put*: The format is `p,key,value`, where `key` is an integer, and
`value` an arbitrary string (without commas in it).
- *get*: The format is `g,key`, where `key` is an integer. If the key
is present, the system should print out the key, followed by a comma,
followed by the value, followed by a newline (`\n`). If not present,
print an error message on a line by itself, of the form `K not found`
where `K` is the actual value of the key, i.e., some integer. 
- *delete*: The format is `d,key`, which either deletes the relevant
key-value pair (and prints nothing), or fails to do so (and prints
`K not found` where `K` is the actual value of the key, i.e., some
integer).
- *clear*: The format is `c`. This command simply removes all
key-value pairs from the database.
- *all*: The format is `a`. This command prints out all key-value
pairs in the database, in any order, with one key-value pair per line,
each key and value separated by a comma.
