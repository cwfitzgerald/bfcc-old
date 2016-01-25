string = """
> ++++           add 6 to cell #1
[                    use loop to set cell #2 to 48
    > ++++           add 4 to cell #2
    < -              sub 1 from cell #1
]               
>                move to cell #2
[                use loop to set 48/48/0
    -                sub 1 from cell #2
    < +++            add 3 to cell #1
    < +++            add 3 to cell #0
    >>               move to cell #2
]               
>>> +++++        add 10 to cell #5
[                use loop to set 57/57/9/9/9
    -               sub 1 from cell #5
    < ++            add 1 to cell #4
    < ++            add 1 to cell #3
    < ++            add 1 to cell #2
    < ++            add 1 to cell #1
    < ++            add 1 to cell #0
    >>>>>           move to cell #5
]             
<<<<< -         sub 1 from cell #0
> -             sub 1 from cell #1
> -             sub 1 from cell #2
[               uses loop to PRINT THE NUMBERS WHOA
    >               move to cell #3
    [               uses loop to do the printing
        <<< .           print 10char
        > .             print 1char
        >>> .           print "\n"
        <<< -           sub 1 from 1char
        >> -            sub 1 from 1cntr
    ]               
    +++++ +++++     add 10 to 1cntr
    < -             sub 1 from 10cntr
    < +++++ +++++   add 10 to 1char 
    < -             sub 1 from 10char
    >>              move to 10cntr
]
>               move to cell #3
[               uses loop to do the printing
    << .            print 1char
    >>> .           print "\n"
    <<< -           sub 1 from 1char
    >> -            sub 1 from 1cntr
]
"""
	
print "".join([x if x in ['<','>','[',']','+','-',',','.'] else "" for x in string])