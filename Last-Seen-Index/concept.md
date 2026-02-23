# Main Idea
> Search for some <mark>traits/events</mark> in a given data structure and do something about it.
# General (Micro) Template
- Use `prev = -1` as a _sentinel_, which marks no event/trait has be spotted.
```code
prev = -1   # the index of previous event
for i:
    if event:
        update answer using i - prev
        prev = i
```

