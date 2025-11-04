# memfrob
Frobnicates input passed through standard in.

## Installation
`make install`

## Usage
`echo 'Hello, world!' | memfrob` will output:
```
bOFFE
]EXFN
```

Frobnicating your input twice will give you the original input back.

So `echo 'Hello, world!' | memfrob | memfrob` will output `Hello, world!`

